/*
Group Number: 1
Author: Teague Schnell
Email: tschnel@okstate.edu
Date: 7 APR 2024
*/

#include "globals.h"

void transfer(transaction trans)
{
    lock_guard<mutex> lock1(userMutexes[trans._user]); // ADDED FOR SYNCHRONIZATION
    lock_guard<mutex> lock2(userMutexes[trans._altUser]); // ADDED FOR SYNCHRONIZATION

    string userFile = trans._user + ".txt";
    string altuserFile = trans._altUser + ".txt";
    ifstream userFileStream(userFile);
    ifstream altuserFileStream(altuserFile);

    string line;
    int tempAmt;

    if(userFileStream.is_open())
    {
        while(getline(userFileStream, line))
        {
            tempAmt = stoi(line);
        }

        ofstream outStream(userFile);
        outStream << (tempAmt - trans._amount);

        transactionLog log(trans, "SUCCESSFUL", __DATE__);

        userFileStream.close();
        cout << "[* SUCCESS] Transfer Made: " << userFile << " : " << "Amount: " << trans._amount << " : To : " << trans._altUser << " : " << __TIME__ << " : " << __DATE__ << endl;
    }
    else
    {
        transactionLog log(trans, "FAILED", __DATE__);
        cout << "[* FAILURE] Transfer Failed: " << trans._user << "Account Does NOT exist " << __TIME__ << " : " << __DATE__ << endl;
    }

    if(altuserFileStream.is_open())
    {
        while(getline(altuserFileStream, line))
        {
            tempAmt = stoi(line);
        }

        ofstream outStream(altuserFile);
        outStream << (tempAmt + trans._amount);

        transactionLog log(trans, "SUCCESSFUL", __DATE__);

        altuserFileStream.close();
        //cout << "[* SUCCESS] Transfer Made to: " << altuserFile << " : " << "Amount: " << trans._amount << " : From : " << trans._user << " : " << __TIME__ << " : " << __DATE__ << endl;
    }
    else
    {
        transactionLog log(trans, "FAILED", __DATE__);
        //cout << "[* FAILURE] Transfer Failed: " << trans._altUser << " : " << "Account Does NOT exist " << __TIME__ << " : " << __DATE__ << endl;
    }
}