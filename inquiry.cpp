/*
Group Number: 1
Author: Mohammed Sheshtar
Email: mohammed.sheshtar@okstate.edu
Date: 7 APR 2024
*/
#include "globals.h"

void inquiry(transaction trans)
{
    lock_guard<mutex> lock(userMutexes[trans._user]); // ADDED FOR SYNCHRONIZATION

    string fileName = trans._user + ".txt";
    ifstream inputFile(fileName);
    
    if(inputFile.is_open())
    {
        string line;
        while (getline(inputFile, line))
        {
            cout << "[* SUCCESS] Inquiry Satisfied: " << trans._user <<" : " << "Amount: " << line << " : " << __TIME__ << " : " << __DATE__ << endl;
        }

        transactionLog log(trans, "SUCCESSFUL", __DATE__);
        inputFile.close();
    }
    else
    {
        transactionLog log(trans, "FAILED", __DATE__);
        cout << "[* FAILURE] Inquiry Failed: " << trans._user << " : " << "Account Does NOT exist" << " : " << __TIME__ << " : " << __DATE__ << endl;
    }
}