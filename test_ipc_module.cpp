#include "ipc_module.h" // Add this line to include the ipc_module.h header file
#include <cassert>
#include <cstring>

void testReadFromPipe() {
    int pipefd[2];
    assert(createPipe(pipefd) == 0);

    const char* testData = "This is a test string";
    char readBuffer[1024];
    
    // Write data to the pipe
    assert(writeToPipe(pipefd[1], testData, strlen(testData)) == strlen(testData));

    // Read data from the pipe
    assert(readFromPipe(pipefd[0], readBuffer, sizeof(readBuffer)) != -1);

    // Ensure that the data read from the pipe matches the test data
    assert(strcmp(readBuffer, testData) == 0);
    
    // Close the pipe
    closePipe(pipefd[0]);
    closePipe(pipefd[1]);
}

int main() {
    testReadFromPipe();
    return 0;
}
