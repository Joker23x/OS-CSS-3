/*
Group Number: 1
Author: Teague Schnell
Email: tschnel@okstate.edu
Date: 7 APR 2024
*/

#include "globals.h"
#include "transaction.h"
#include "ipc_module.h"

void OpenAcct(transaction trans)
{
    lock_guard<mutex> lock(userMutexes[trans._user]); // ADDED FOR SYNCHRONIZATION

    string fileName = trans._user + ".txt";
    ifstream file(fileName);

    if (!file.is_open())
    {
        ofstream outStream(fileName);
        outStream << trans._amount;

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

        file.close();
        cout << "[* SUCCESS] File Created: " << fileName << " was made : " << __TIME__ << " : " << __DATE__ << endl;
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

        cout << "[* FAILURE] File Exists: " << fileName << " : " << __TIME__ << " : " << __DATE__ << endl;
    }
}

