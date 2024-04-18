// ipc_module.cpp

#include "ipc_module.h"

// Function to create a pipe
int createPipe(int pipefd[2]) {
    return pipe(pipefd);
}

// Function to write data to a pipe
ssize_t writeToPipe(int fd, const void *buf, size_t count) {
    return write(fd, buf, count);
}

// Function to read data from a pipe
ssize_t readFromPipe(int fd, void *buf, size_t count) {
    return read(fd, buf, count);
}

// Function to close a pipe
void closePipe(int fd) {
    close(fd);
}
