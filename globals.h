#ifndef GLOBALS_H
#define GLOBALS_H
#include "transaction.h"
#include <map>
#include <mutex>

extern map<string, vector<transaction> > userTransactions;
extern int UserCount;
extern vector<string> logs;
extern map<string, mutex> userMutexes; // ADDED FOR SYNCHRONIZATION

#endif