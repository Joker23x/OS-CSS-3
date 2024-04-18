// ipc_module.h

#ifndef IPC_MODULE_H
#define IPC_MODULE_H

#include <unistd.h>

// Function to create a pipe
int createPipe(int pipefd[2]);

// Function to write data to a pipe
ssize_t writeToPipe(int fd, const void *buf, size_t count);

// Function to read data from a pipe
ssize_t readFromPipe(int fd, void *buf, size_t count);

// Function to close a pipe
void closePipe(int fd);

#endif
