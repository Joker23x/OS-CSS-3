#ifndef GLOBALS_H
#define GLOBALS_H
#include "transaction.h"
#include <map>
#include <mutex>
#include <vector>

extern map<string, vector<transaction> > userTransactions;
extern int UserCount;
extern vector<transactionLog> logs;
extern map<string, mutex> userMutexes; // ADDED FOR SYNCHRONIZATION

#endif
