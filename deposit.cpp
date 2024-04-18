/*
Group Number: 1
Author: Mohammed Sheshtar
Email: mohammed.sheshtar@okstate.edu
Date: 7 APR 2024
*/
#include "globals.h"

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

        transactionLog log(trans, "SUCCESSFUL", __DATE__);

        file.close();
        cout << "[* SUCCESS] Deposit Successful: " << trans._user << " : " << trans._action << " was made: " << trans._amount << " : "  << __TIME__ << " : " << __DATE__ << endl;
    }
    else
    {
        transactionLog log(trans, "FAILED", __DATE__);
        cout << "[* FAILURE] Deposit Unsuccessful: " << trans._user << " : " << trans._action << "Account Does NOT exist" << " : " << __TIME__ << " : " << __DATE__ << endl;
    }
}