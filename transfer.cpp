/*
Group Number: 1
Author: Teague Schnell
Email: tschnel@okstate.edu
Date: 7 APR 2024
*/
#include "globals.h"
#include "transaction.h"
#include "ipc_module.h"

void transfer(transaction trans)
{
    string first = min(trans._user, trans._altUser); // ADDED FOR SYNCHRONIZATION
    string second = max(trans._user, trans._altUser); // ADDED FOR SYNCHRONIZATION

    lock_guard<mutex> lock1(userMutexes[first]); // ADDED FOR SYNCHRONIZATION
    lock_guard<mutex> lock2(userMutexes[second]); // ADDED FOR SYNCHRONIZATION

    string userFile = trans._user + ".txt";
    string altuserFile = trans._altUser + ".txt";
    ifstream userFileStream(userFile);
    ifstream altuserFileStream(altuserFile);

    string line;
    int tempAmt;

    if (userFileStream.is_open() && altuserFileStream.is_open())
    {
        while (getline(userFileStream, line))
        {
            tempAmt = stoi(line);
        }

        ofstream outStream(userFile);
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

        userFileStream.close();
        cout << "[* SUCCESS] Transfer Made: " << userFile << " : " << "Amount: " << trans._amount << " : To : " << trans._altUser << " : " << __TIME__ << " : " << __DATE__ << endl;
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

        cout << "[* FAILURE] Transfer Failed: One or both accounts do not exist" << __TIME__ << " : " << __DATE__ << endl;
    }

    if (altuserFileStream.is_open())
    {
        while (getline(altuserFileStream, line))
        {
            tempAmt = stoi(line);
        }

        ofstream outStream(altuserFile);
        outStream << (tempAmt + trans._amount);

        transactionLog log(trans, "SUCCESSFUL", __DATE__);
        logs.push_back(log);

        altuserFileStream.close();
        // cout << "[* SUCCESS] Transfer Made to: " << altuserFile << " : " << "Amount: " << trans._amount << " : From : " << trans._user << " : " << __TIME__ << " : " << __DATE__ << endl;
    }
    else
    {
        transactionLog log(trans, "FAILED", __DATE__);
        logs.push_back(log);
        // cout << "[* FAILURE] Transfer Failed: " << trans._altUser << " : " << "Account Does NOT exist " << __TIME__ << " : " << __DATE__ << endl;
    }
}
