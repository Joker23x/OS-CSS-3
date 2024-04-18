/*
Group Number: 1
Author: William Vang
Email: William.vang10@okstate.edu
Date: 7 APR 2024
*/
//close.cpp

#include "globals.h"
#include "transaction.h"
#include "ipc_module.h"

void closeAcct(transaction trans)
{
    lock_guard<mutex> lock(userMutexes[trans._user]); // ADDED FOR SYNCHRONIZATION

    string fileName = trans._user + ".txt";
    ifstream file(fileName);

    if(file.is_open())
    {
        remove(fileName.c_str());

        // Log the transaction using IPC
        int pipefd[2];
        if (createPipe(pipefd) == -1) {
            cerr << "Error creating pipe" << endl;
            exit(EXIT_FAILURE);
        }

        trans.performTransactionAndLog(pipefd[1]);

        closePipe(pipefd[0]);
        closePipe(pipefd[1]);

        cout << "[* SUCCESS] Account Closed: " << fileName << " was closed : " << __TIME__ << " : " << __DATE__ << endl;
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

        cout << "[* FAILURE] Account NOT Found: " << fileName << " : " << __TIME__ << " : " << __DATE__ << endl;
    }
}
