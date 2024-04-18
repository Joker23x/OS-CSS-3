/*
Group Number: 1
Author: Mohammed Sheshtar
Email: mohammed.sheshtar@okstate.edu
Date: 7 APR 2024
*/
//inquiry.cpp

#include "globals.h"
#include "transaction.h"
#include "ipc_module.h"

void inquiry(transaction trans)
{
    lock_guard<mutex> lock(userMutexes[trans._user]); // ADDED FOR SYNCHRONIZATION

    string fileName = trans._user + ".txt";
    ifstream inputFile(fileName);

    if (inputFile.is_open())
    {
        string line;
        while (getline(inputFile, line))
        {
            cout << "[* SUCCESS] Inquiry Satisfied: " << trans._user << " : " << "Amount: " << line << " : " << __TIME__ << " : " << __DATE__ << endl;
        }

        // Log the transaction using IPC
        int pipefd[2];
        if (createPipe(pipefd) == -1) {
            cerr << "Error creating pipe" << endl;
            exit(EXIT_FAILURE);
        }

        trans.performTransactionAndLog(pipefd[1]);

        closePipe(pipefd[0]);
        closePipe(pipefd[1]);

        transactionLog log(trans, "SUCCESSFUL", __DATE__);
        logs.push_back(log);
    }
    else
    {
        // Log the transaction using IPC
        int pipefd[2];
        if (createPipe(pipefd) == -1) {
            cerr << "Error creating pipe" << endl;
            exit(EXIT_FAILURE);
        }

        trans.performTransactionAndLog(pipefd[1]);

        closePipe(pipefd[0]);
        closePipe(pipefd[1]);

        transactionLog log(trans, "FAILED", __DATE__);
        logs.push_back(log);
        cout << "[* FAILURE] Inquiry Failed: " << trans._user << " : " << "Account Does NOT exist" << " : " << __TIME__ << " : " << __DATE__ << endl;
    }
}

