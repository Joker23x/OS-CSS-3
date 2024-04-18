/*
Group Number: 1
Author: William Vang
Email: William.vang10@okstate.edu
Date: 7 APR 2024
*/


#include "globals.h"

void closeAcct(transaction trans)
{
    lock_guard<mutex> lock(userMutexes[trans._user]); // ADDED FOR SYNCHRONIZATION

    string fileName = trans._user + ".txt";
    ifstream file(fileName);

    if(file.is_open())
    {
        remove(fileName.c_str());

        transactionLog log(trans, "SUCCESSFUL", __DATE__);

        cout << "[* SUCCESS] Account Closed: " << fileName << " was closed : " << __TIME__ << " : " << __DATE__ << endl;
    }
    else
    {
        transactionLog log(trans, "FAILED", __DATE__);
        cout << "[* FAILURE] Account NOT Found: " << fileName << " : " << __TIME__ << " : " << __DATE__ << endl;
    }
}