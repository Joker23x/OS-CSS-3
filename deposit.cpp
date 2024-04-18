/*
Group Number: 1
Author: Mohammed Sheshtar
Email: mohammed.sheshtar@okstate.edu
Date: 7 APR 2024
*/
#include "globals.h"
#include "transaction.h"
#include "ipc_module.h"

void deposit(transaction trans)
{
    lock_guard<mutex> lock(userMutexes[trans._user]); // ADDED FOR SYNCHRONIZATION

    string fileName = trans._user + ".txt";
    ifstream file(fileName);

    string line;
    int tempAmt;

    if(file.is_open())
    {
        while(getline(file, line))
        {
            tempAmt = stoi(line);
        }

        ofstream outStream(fileName);
        outStream << (tempAmt + trans._amount);

        // Log the transaction using IPC
        int pipefd[2];
        if (createPipe(pipefd) == -1) {
            cerr << "Error creating pipe" << endl;
            exit(EXIT_FAILURE);
        }

        trans.performTransactionAndLog(pipefd[1]);

        closePipe(pipefd[0]);
        closePipe(pipefd[1]);

        file.close();
        cout << "[* SUCCESS] Deposit Successful: " << trans._user << " : " << trans._action << " was made: " << trans._amount << " : "  << __TIME__ << " : " << __DATE__ << endl;
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
        cout << "[* FAILURE] Deposit Unsuccessful: " << trans._user << " : " << trans._action << "Account Does NOT exist" << " : " << __TIME__ << " : " << __DATE__ << endl;
    }
}

}