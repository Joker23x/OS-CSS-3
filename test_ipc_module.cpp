#include "ipc_module.h"
#include <cassert>
#include <cstring>

void testReadFromPipe() {
    int pipefd[2];
    assert(createPipe(pipefd) == 0);

    const char* testData = "This is a test string";
    char readBuffer[1024];
    
    // Write data to the pipe
    ssize_t bytesWritten = writeToPipe(pipefd[1], testData, strlen(testData));
    assert(bytesWritten == static_cast<ssize_t>(strlen(testData)));

    // Read data from the pipe
    ssize_t bytesRead = readFromPipe(pipefd[0], readBuffer, sizeof(readBuffer));
    assert(bytesRead != -1);

    // Ensure that the data read from the pipe matches the test data
    assert(strncmp(readBuffer, testData, bytesRead) == 0);
    
    // Close the pipe
    closePipe(pipefd[0]);
    closePipe(pipefd[1]);

     std::cout << "Test passed: Data successfully read from and written to the pipe." << std::endl;
}

int main() {
    testReadFromPipe();
   
    return 0;
}
//g++ -o test_ipc_module test_ipc_module.cpp ipc_module.cpp
//./test_ipc_module
