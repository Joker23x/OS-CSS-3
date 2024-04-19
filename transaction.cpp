/*
Group Number: 1
Author: Teague Schnell
Email: tschnel@okstate.edu
Date: 7 APR 2024
*/

#include "transaction.h"
#include "deposit.cpp"
#include "withdraw.cpp"
#include "inquiry.cpp"
#include "open.cpp"
#include "transfer.cpp"
#include "close.cpp"
#include "transaction.h"
#include <sys/wait.h>


map<string, mutex> userMutexes; // ADDED FOR SYNCHRONIZATION
map<string, vector<transaction> > userTransactions;
vector<transactionLog> logs;
int UserCount = 0;

void readFile(string filePath)
{
    ifstream inputFile(filePath);
    
    int LineCount = 0;
    if (inputFile.is_open())
    {
        string line;
        
        while (getline(inputFile, line))
        {
            if (LineCount == 0)
            {
                UserCount = stoi(line);
                LineCount += 1;
            }
            else
            {
                transaction transact(line);
                userTransactions[transact._user].push_back(transact);
                LineCount += 1;
            } 
        }
        inputFile.close();
    }
    else
    {
        cout << "Unable to open file" << endl;
    }
}

void printUserTransactions(const string& userId, int pipeWriteEnd)
{
    string logMessage;

    for (const auto& t : userTransactions[userId])
    {
        // Process transaction and build log message
        logMessage += " [**] User: " + t._user;
        logMessage += " | Action: " + t._action + ", ";
        logMessage += "Amount: " + to_string(t._amount);
        if (!t._altUser.empty())
        {
            logMessage += ", Alt User: " + t._altUser;
        }
        logMessage += "\n";

        // Perform transaction actions
        if(t._action == "Open")
        {
            OpenAcct(t);
        }
        else if(t._action == "Inquiry")
        {
            inquiry(t);
        }
        else if(t._action == "Deposit")
        {
            deposit(t);
        }
        else if(t._action == "Withdraw")
        {
            withdraw(t);
        }
        else if(t._action == "Close")
        {
            closeAcct(t);
        }
        else if(t._action == "Transfer")
        {
            transfer(t);
        }
        else
        {
            cerr << "Error thrown at the transaction reading level..." << endl;
        }
    }

    // Write transaction logs to the pipe
    writeToPipe(pipeWriteEnd, logMessage.c_str(), logMessage.size());
}

void GetTransactions() {
    cout << "User Count: " << UserCount << endl;

    // Create a pipe for each child process
    vector<int> pipes(UserCount * 2);
    for (int i = 0; i < UserCount; ++i) {
        if (pipe(&pipes[i * 2]) == -1) {
            cerr << "Error creating pipe" << endl;
            exit(EXIT_FAILURE);
        }else{
            cout<<"Pipe Created for user: "<< i<< endl;
        }
        }
    

    // Fork a child process for each user
    int i = 0; // Moved outside the loop
    for (const auto& pair : userTransactions) {
        string userId = pair.first;
        if (fork() == 0) {
            // Child process
            close(pipes[2 * i + 1]); // Close the write end of the pipe
            printUserTransactions(userId, pipes[2 * i]); // Write transaction logs to the pipe
            close(pipes[2 * i]); // Close the read end of the pipe in the child process
            exit(0);
        }
        ++i; // Increment i for the next iteration
    }

    // Parent process
    for (int i = 0; i < UserCount; ++i) {
        close(pipes[2 * i]); // Close the read end of each pipe
        cout<<"Pipe being closed for user: "<< i << endl;
    }

    
 // Read transaction logs from each child process
char buffer[1024];
int bytesRead;
for (int i = 0; i < UserCount; ++i) {
    // Print the descriptor value for debugging
    cout << "Read end Descriptor for user " << i << ": " << pipes[2 * i + 1] << endl;
   
    while ((bytesRead = readFromPipe(pipes[2 * i + 1], buffer, sizeof(buffer))) > 0) {
        cout << "Received transaction log: " << string(buffer, bytesRead) << endl;
    }
    if (bytesRead == -1) {
        cerr << "Error reading from pipe" << endl;
    }
}


    // Wait for all child processes to finish
    int status;
    for (int i = 0; i < UserCount; ++i) {
        wait(&status);
    }
}


void GetLogs(string fileName)
{
    cout << "LOG FILE: " << endl;
}
