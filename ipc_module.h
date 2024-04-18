// ipc_module.h

#ifndef IPC_MODULE_H
#define IPC_MODULE_H

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

// Define constants
#define SHARED_MEMORY_KEY 1234
#define SHARED_MEMORY_SIZE 1024
#define PERMISSIONS 0666

// Function prototypes
int initializeSharedMemory();
void* attachSharedMemory(int shmid);
void detachSharedMemory(void* shmaddr);
void writeData(void* shmaddr, const char* data);
void readData(void* shmaddr, char* buffer);
void cleanupSharedMemory(int shmid);

#endif
