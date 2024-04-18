/*
Group Number: 1
Author: William Vang
Email: William.vang10@okstate.edu
Date: 7 APR 2024
*/


#include "globals.h"

void withdraw(transaction trans)
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
        outStream << (tempAmt - trans._amount);

        transactionLog log(trans, "SUCCESSFUL", __DATE__);

        file.close();
        cout << "[* SUCCESS] Withdraw Successful: " << trans._user << " : " << " Amount : " << trans._amount << " : " << __TIME__ << " : " << __DATE__ << endl;
    }
    else
    {
        transactionLog log(trans, "FAILED", __DATE__);
        cout << "[* FAILURE] Withdraw Failed: " << trans._user << " Account Does NOT exist" << " : " << __TIME__ << " : " << __DATE__ << endl;
    }
}