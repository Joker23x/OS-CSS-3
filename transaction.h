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
#include <fstream>
#include <sstream>
#include <map>
#include <unistd.h>
#include <sys/wait.h>
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