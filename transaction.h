/*
Group Number: 1
Author: Teague Schnell
Email: tschnel@okstate.edu
Date: 7 APR 2024
*/
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <iostream>
#include <sstream>
#include <map>

using namespace std;

class transaction
{
public:
    string _user;
    string _action;
    int _amount;
    string _altUser;

    transaction(const string& stringLine)
    {
        stringstream stream(stringLine);
        stream >> _user >> _action;

        if (!stream.eof())
        {
            stream >> _amount;
        }
        else
        {
            _amount = 0;
        }

        if (stream >> _altUser)
        {
            // If there's an additional user, read it
        }
    }

    // Function to perform transaction actions and write transaction logs to the pipe
    void performTransactionAndLog(int pipeWriteEnd)
    {
        // Perform transaction actions here

        // Build transaction log message
        string logMessage = "[**] User: " + _user + " | Action: " + _action + ", Amount: " + to_string(_amount);
        if (!_altUser.empty())
        {
            logMessage += ", Alt User: " + _altUser;
        }
        logMessage += "\n";

        // Write transaction log to the pipe
        writeToPipe(pipeWriteEnd, logMessage.c_str(), logMessage.size());
    }
};

class transactionLog
{
public:
    transaction _transaction;
    string _status;
    string _date;

    transactionLog(transaction transact, string status, string date) : _transaction(transact), _status(status), _date(date)
    {
        
    }
};

#endif
