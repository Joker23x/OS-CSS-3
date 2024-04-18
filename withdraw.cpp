/*
Group Number: 1
Author: William Vang
Email: William.vang10@okstate.edu
Date: 7 APR 2024
*/

#include "globals.h"
#include "transaction.h"
#include "ipc_module.h"

void withdraw(transaction trans)
{
    lock_guard<mutex> lock(userMutexes[trans._user]); // ADDED FOR SYNCHRONIZATION
    
    string fileName = trans._user + ".txt";
    ifstream file(fileName);

    string line;
    int tempAmt;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            tempAmt = stoi(line);
        }

        // Check if the withdrawal amount is greater than the current balance
        if (trans._amount > tempAmt)
        {
            transactionLog log(trans, "FAILED", __DATE__);
            logs.push_back(log);
            cout << "[* FAILURE] Withdraw Failed: " << trans._user << " Insufficient Balance" << " : " << __TIME__ << " : " << __DATE__ << endl;
        }
        else
        {
            ofstream outStream(fileName);
            outStream << (tempAmt - trans._amount);

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
            cout << "[* SUCCESS] Withdraw Successful: " << trans._user << " : " << " Amount : " << trans._amount << " : " << __TIME__ << " : " << __DATE__ << endl;
        }
    }
    else
    {
        transactionLog log(trans, "FAILED", __DATE__);
        logs.push_back(log);
        cout << "[* FAILURE] Withdraw Failed: " << trans._user << " Account Does NOT exist" << " : " << __TIME__ << " : " << __DATE__ << endl;
    }
}
