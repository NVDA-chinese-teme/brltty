/*
 * BRLTTY - A background process providing access to the console screen (when in
 *          text mode) for a blind person using a refreshable braille display.
 *
 * Copyright (C) 1995-2013 by The BRLTTY Developers.
 *
 * BRLTTY comes with ABSOLUTELY NO WARRANTY.
 *
 * This is free software, placed under the terms of the
 * GNU General Public License, as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any
 * later version. Please see the file LICENSE-GPL for details.
 *
 * Web Page: http://mielke.cc/brltty/
 *
 * This software is maintained by Dave Mielke <dave@mielke.cc>.
 */

#include "prologue.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#include "io_misc.h"
#include "log.h"
#include "async.h"

typedef struct InputOutputMethodsStruct InputOutputMethods;

typedef struct {
  const InputOutputMethods *methods;

  union {
    FileDescriptor file;
    SocketDescriptor socket;
  } descriptor;
} InputOutputHandle;

typedef struct {
  unsigned ready:1;
} EventMonitor;

typedef int MonitorEventMethod (const InputOutputHandle *ioh, AsyncHandle *handle, EventMonitor *evm);
typedef ssize_t ReadDataMethod (const InputOutputHandle *ioh, void *buffer, size_t size);
typedef ssize_t WriteDataMethod (const InputOutputHandle *ioh, const void *buffer, size_t size);

struct InputOutputMethodsStruct {
  MonitorEventMethod *monitorInput;
  MonitorEventMethod *monitorOutput;
  MonitorEventMethod *monitorAlert;

  ReadDataMethod *readData;
  WriteDataMethod *writeData;
};

static int
setEventMonitor (const AsyncMonitorResult *result) {
  EventMonitor *evm = result->data;

  evm->ready = 1;
  return 0;
}

static int
testEventMonitor (void *data) {
  EventMonitor *evm = data;

  return evm->ready;
}

static int
awaitEvent (const InputOutputHandle *ioh, int timeout, MonitorEventMethod *monitorEvent) {
  EventMonitor evm = {
    .ready = 0
  };

  AsyncHandle monitor;

  if (monitorEvent(ioh, &monitor, &evm)) {
    asyncAwaitCondition(timeout, testEventMonitor, &evm);
    asyncCancelRequest(monitor);
    if (evm.ready) return 1;

#ifdef ETIMEDOUT
    errno = ETIMEDOUT;
#else /* ETIMEDOUT */
    errno = EAGAIN;
#endif /* ETIMEDOUT */
  }

  return 0;
}

static int
awaitInput (const InputOutputHandle *ioh, int timeout) {
  return awaitEvent(ioh, timeout, ioh->methods->monitorInput);
}

static int
awaitOutput (const InputOutputHandle *ioh, int timeout) {
  return awaitEvent(ioh, timeout, ioh->methods->monitorOutput);
}

static int
awaitAlert (const InputOutputHandle *ioh, int timeout) {
  return awaitEvent(ioh, timeout, ioh->methods->monitorAlert);
}

static ssize_t
readData (
  const InputOutputHandle *ioh,
  void *buffer, size_t size,
  int initialTimeout, int subsequentTimeout
) {
  unsigned char *address = buffer;

#ifdef __MSDOS__
  int tried = 0;
  goto noInput;
#endif /* __MSDOS__ */

  while (size > 0) {
    ssize_t count = ioh->methods->readData(ioh, address, size);

#ifdef __MSDOS__
    tried = 1;
#endif /* __MSDOS__ */

    if (count == -1) {
      if (errno == EINTR) continue;
      if (errno == EAGAIN) goto noInput;

#ifdef EWOULDBLOCK
      if (errno == EWOULDBLOCK) goto noInput;
#endif /* EWOULDBLOCK */

      logSystemError("read");
      return count;
    }

    if (!count) {
      unsigned char *start;
      unsigned int offset;
      int timeout;

    noInput:
      start = buffer;
      offset = address - start;
      timeout = offset? subsequentTimeout: initialTimeout;

      if (timeout) {
        if (awaitInput(ioh, timeout)) continue;
        logMessage(LOG_WARNING, "input byte missing at offset %u", offset);
      } else

#ifdef __MSDOS__
      if (!tried) {
        if (awaitInput(ioh, 0)) continue;
      } else
#endif /* __MSDOS__ */

      {
        errno = EAGAIN;
      }

      break;
    }

    address += count;
    size -= count;
  }

  {
    unsigned char *start = buffer;

    return address - start;
  }
}

static ssize_t
writeData (const InputOutputHandle *ioh, const void *buffer, size_t size) {
  const unsigned char *address = buffer;

canWrite:
  while (size > 0) {
    ssize_t count = ioh->methods->writeData(ioh, address, size);

    if (count == -1) {
      if (errno == EINTR) continue;
      if (errno == EAGAIN) goto noOutput;

#ifdef EWOULDBLOCK
      if (errno == EWOULDBLOCK) goto noOutput;
#endif /* EWOULDBLOCK */

      logSystemError("Write");
      return count;
    }

    if (!count) {
      errno = EAGAIN;

    noOutput:
      do {
        if (awaitOutput(ioh, 15000)) goto canWrite;
      } while (errno == EAGAIN);

      return -1;
    }

    address += count;
    size -= count;
  }

  {
    const unsigned char *start = buffer;
    return address - start;
  }
}

static int
monitorFileInput (const InputOutputHandle *ioh, AsyncHandle *handle, EventMonitor *evm) {
  return asyncMonitorFileInput(handle, ioh->descriptor.file, setEventMonitor, evm);
}

static int
monitorFileOutput (const InputOutputHandle *ioh, AsyncHandle *handle, EventMonitor *evm) {
  return asyncMonitorFileOutput(handle, ioh->descriptor.file, setEventMonitor, evm);
}

static int
monitorFileAlert (const InputOutputHandle *ioh, AsyncHandle *handle, EventMonitor *evm) {
  return asyncMonitorFileAlert(handle, ioh->descriptor.file, setEventMonitor, evm);
}


#ifdef __MINGW32__
static ssize_t
readFileData (const InputOutputHandle *ioh, void *buffer, size_t size) {
  {
    DWORD count;

    if (ReadFile(ioh->descriptor.file, buffer, size, &count, NULL)) return count;
  }

  setSystemErrno();
  return -1;
}

static ssize_t
writeFileData (const InputOutputHandle *ioh, const void *buffer, size_t size) {
  {
    DWORD count;

    if (WriteFile(ioh->descriptor.file, buffer, size, &count, NULL)) return count;
  }

  setSystemErrno();
  return -1;
}

#else /* __MINGW32__ */
static ssize_t
readFileData (const InputOutputHandle *ioh, void *buffer, size_t size) {
  return read(ioh->descriptor.file, buffer, size);
}

static ssize_t
writeFileData (const InputOutputHandle *ioh, const void *buffer, size_t size) {
  return write(ioh->descriptor.file, buffer, size);
}
#endif /* __MINGW32__ */

static const InputOutputMethods fileMethods = {
  .monitorInput = monitorFileInput,
  .monitorOutput = monitorFileOutput,
  .monitorAlert = monitorFileAlert,

  .readData = readFileData,
  .writeData = writeFileData
};

static void
makeFileHandle (InputOutputHandle *ioh, FileDescriptor fileDescriptor) {
  ioh->methods = &fileMethods;
  ioh->descriptor.file = fileDescriptor;
}

void
closeFile (FileDescriptor *fileDescriptor) {
  if (*fileDescriptor != INVALID_FILE_DESCRIPTOR) {
    closeFileDescriptor(*fileDescriptor);
    *fileDescriptor = INVALID_FILE_DESCRIPTOR;
  }
}

int
awaitFileInput (FileDescriptor fileDescriptor, int timeout) {
  InputOutputHandle ioh;

  makeFileHandle(&ioh, fileDescriptor);
  return awaitInput(&ioh, timeout);
}

int
awaitFileOutput (FileDescriptor fileDescriptor, int timeout) {
  InputOutputHandle ioh;

  makeFileHandle(&ioh, fileDescriptor);
  return awaitOutput(&ioh, timeout);
}

int
awaitFileAlert (FileDescriptor fileDescriptor, int timeout) {
  InputOutputHandle ioh;

  makeFileHandle(&ioh, fileDescriptor);
  return awaitAlert(&ioh, timeout);
}

ssize_t
readFile (
  FileDescriptor fileDescriptor, void *buffer, size_t size,
  int initialTimeout, int subsequentTimeout
) {
  InputOutputHandle ioh;

  makeFileHandle(&ioh, fileDescriptor);
  return readData(&ioh, buffer, size, initialTimeout, subsequentTimeout);
}

ssize_t
writeFile (FileDescriptor fileDescriptor, const void *buffer, size_t size) {
  InputOutputHandle ioh;

  makeFileHandle(&ioh, fileDescriptor);
  return writeData(&ioh, buffer, size);
}

#ifdef IO_HAVE_SOCKETS
static int
monitorSocketInput (const InputOutputHandle *ioh, AsyncHandle *handle, EventMonitor *evm) {
  return asyncMonitorSocketInput(handle, ioh->descriptor.socket, setEventMonitor, evm);
}

static int
monitorSocketOutput (const InputOutputHandle *ioh, AsyncHandle *handle, EventMonitor *evm) {
  return asyncMonitorSocketOutput(handle, ioh->descriptor.socket, setEventMonitor, evm);
}

static int
monitorSocketAlert (const InputOutputHandle *ioh, AsyncHandle *handle, EventMonitor *evm) {
  return asyncMonitorSocketAlert(handle, ioh->descriptor.socket, setEventMonitor, evm);
}

static ssize_t
readSocketData (const InputOutputHandle *ioh, void *buffer, size_t size) {
  return recv(ioh->descriptor.socket, buffer, size, 0);
}

static ssize_t
writeSocketData (const InputOutputHandle *ioh, const void *buffer, size_t size) {
  return send(ioh->descriptor.socket, buffer, size, 0);
}

static const InputOutputMethods socketMethods = {
  .monitorInput = monitorSocketInput,
  .monitorOutput = monitorSocketOutput,
  .monitorAlert = monitorSocketAlert,

  .readData = readSocketData,
  .writeData = writeSocketData
};

static void
makeSocketHandle (InputOutputHandle *ioh, SocketDescriptor socketDescriptor) {
  ioh->methods = &socketMethods;
  ioh->descriptor.socket = socketDescriptor;
}

void
closeSocket (SocketDescriptor *socketDescriptor) {
  if (*socketDescriptor != INVALID_SOCKET_DESCRIPTOR) {
    closeSocketDescriptor(*socketDescriptor);
    *socketDescriptor = INVALID_SOCKET_DESCRIPTOR;
  }
}

int
awaitSocketInput (SocketDescriptor socketDescriptor, int timeout) {
  InputOutputHandle ioh;

  makeSocketHandle(&ioh, socketDescriptor);
  return awaitInput(&ioh, timeout);
}

int
awaitSocketOutput (SocketDescriptor socketDescriptor, int timeout) {
  InputOutputHandle ioh;

  makeSocketHandle(&ioh, socketDescriptor);
  return awaitOutput(&ioh, timeout);
}

int
awaitSocketAlert (SocketDescriptor socketDescriptor, int timeout) {
  InputOutputHandle ioh;

  makeSocketHandle(&ioh, socketDescriptor);
  return awaitAlert(&ioh, timeout);
}

ssize_t
readSocket (
  SocketDescriptor socketDescriptor, void *buffer, size_t size,
  int initialTimeout, int subsequentTimeout
) {
  InputOutputHandle ioh;

  makeSocketHandle(&ioh, socketDescriptor);
  return readData(&ioh, buffer, size, initialTimeout, subsequentTimeout);
}

ssize_t
writeSocket (SocketDescriptor socketDescriptor, const void *buffer, size_t size) {
  InputOutputHandle ioh;

  makeSocketHandle(&ioh, socketDescriptor);
  return writeData(&ioh, buffer, size);
}

int
connectSocket (
  SocketDescriptor socketDescriptor,
  const struct sockaddr *address,
  size_t addressLength,
  int timeout
) {
  int result = connect(socketDescriptor, address, addressLength);

  if (result == -1) {
#ifdef EINPROGRESS
    if (getSocketError() == EINPROGRESS) {
      if (awaitSocketOutput(socketDescriptor, timeout)) {
        int error;
        socklen_t length = sizeof(error);

        if (getSocketOption(socketDescriptor, SOL_SOCKET, SO_ERROR, &error, &length) != -1) {
          if (!error) return 0;
          errno = error;
        }
      }

      close(socketDescriptor);
    }
#endif /* EINPROGRESS */
  }

  return result;
}
#endif /* IO_HAVE_SOCKETS */

int
changeOpenFlags (int fileDescriptor, int flagsToClear, int flagsToSet) {
#if defined(F_GETFL) && defined(F_SETFL)
  int flags;

  if ((flags = fcntl(fileDescriptor, F_GETFL)) != -1) {
    flags &= ~flagsToClear;
    flags |= flagsToSet;
    if (fcntl(fileDescriptor, F_SETFL, flags) != -1) {
      return 1;
    } else {
      logSystemError("F_SETFL");
    }
  } else {
    logSystemError("F_GETFL");
  }
#else /* defined(F_GETFL) && defined(F_SETFL) */
  errno = ENOSYS;
#endif /* defined(F_GETFL) && defined(F_SETFL) */

  return 0;
}

int
setOpenFlags (int fileDescriptor, int state, int flags) {
  if (state) {
    return changeOpenFlags(fileDescriptor, 0, flags);
  } else {
    return changeOpenFlags(fileDescriptor, flags, 0);
  }
}

int
setBlockingIo (int fileDescriptor, int state) {
#ifdef O_NONBLOCK
  if (setOpenFlags(fileDescriptor, !state, O_NONBLOCK)) return 1;
#else /* O_NONBLOCK */
  errno = ENOSYS;
#endif /* O_NONBLOCK */

  return 0;
}

int
setCloseOnExec (int fileDescriptor, int state) {
#if defined(F_SETFD) && defined(FD_CLOEXEC)
  if (fcntl(fileDescriptor, F_SETFD, (state? FD_CLOEXEC: 0)) != -1) return 1;
#else /* defined(F_SETFD) && defined(FD_CLOEXEC) */
  errno = ENOSYS;
#endif /* defined(F_SETFD) && defined(FD_CLOEXEC) */

  return 0;
}
