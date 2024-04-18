/*
Group Number: 1
Author: Teague Schnell
Email: tschnel@okstate.edu
Date: 7 APR 2024
*/

#include "globals.h"

int pipefd[2];

void OpenAcct(transaction trans)
{
    lock_guard<mutex> lock(userMutexes[trans._user]); // ADDED FOR SYNCHRONIZATION

    
    string fileName = trans._user + ".txt";
    ifstream file(fileName);

    string log = "log.txt";
    ifstream logFile(log);
    
    if(!file.is_open())
    {
        ofstream outStream(fileName);
        outStream << trans._amount;

        transactionLog log(trans, "SUCCESSFUL", __DATE__);
        //logs.push_back(log);

        file.close();

        cout << "[* SUCCESS] File Created: " << fileName << " was made : " << __TIME__ << " : " << __DATE__ << endl;
    }
    else
    {
        transactionLog log(trans, "FAILED", __DATE__);
        cout << "[* FAILURE] File Exists: " << fileName << " : " << __TIME__ << " : " << __DATE__ << endl;
    }
}