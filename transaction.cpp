/*
Group Number: 1
Author: Teague Schnell
Email: tschnel@okstate.edu
Date: 7 APR 2024
*/

#include "transaction.h"
#include "deposit.cpp"
#include "withdraw.cpp"
#include "inquiry.cpp"
#include "open.cpp"
#include "transfer.cpp"
#include "close.cpp"
#include <vector>

map<string, mutex> userMutexes; // ADDED FOR SYNCHRONIZATION
map<string, vector<transaction> > userTransactions;
vector<string> logs;
int UserCount = 0;

void readFile(string filePath)
{
    ifstream inputFile(filePath);
    
    int LineCount = 0;
    if (inputFile.is_open())
    {
        string line;
        
        while (getline(inputFile, line))
        {
            if (LineCount == 0)
            {
                UserCount = stoi(line);
                LineCount += 1;
            }
            else
            {
                transaction transact(line);
                userTransactions[transact._user].push_back(transact);
                LineCount += 1;
            } 
        }
        inputFile.close();
    }
    else
    {
        cout << "Unable to open file" << endl;
    }
}

void printUserTransactions(const string& userId)
{
    // cout << "User: " << userId << endl; // DEDBUG BLOCK

    for (const auto& t : userTransactions[userId])
    {
        //cout << " [**] User: " << t._user;
        //cout << " | Action: " << t._action << ", ";
        //cout << "Amount: " << t._amount;
        if (!t._altUser.empty())
        {
            //cout << ", Alt User: " << t._altUser;
        }

        if(t._action == "Open")
        {
            OpenAcct(t);
        }
        else if(t._action == "Inquiry")
        {
            inquiry(t);
        }
        else if(t._action == "Deposit")
        {
            deposit(t);
        }
        else if(t._action == "Withdraw")
        {
            withdraw(t);
        }
        else if(t._action == "Close")
        {
            closeAcct(t);
        }
        else if(t._action == "Transfer")
        {
            transfer(t);
        }
        else
        {
            cout << "Error thrown at the transaction reading level..." << endl;
        }
        sleep(1);
    }
}

void GetTransactions()
{
    cout << "User Count: " << UserCount << endl;

    for (const auto& pair : userTransactions)
    {
        string userId = pair.first;

        if (fork() == 0)  // Create a fork for each user
        {
            //cout << "[*] Current Process: " << getpid() << endl;
            printUserTransactions(userId);  // ## DEBUG LINE

            exit(0);
        }
    }

    int status;
    for (int i = 0; i < UserCount; ++i)
        wait(&status);
}

void GetLogs(string fileName)
{
    cout << "LOG FILE: " << endl;
}