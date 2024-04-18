#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <unistd.h>
#include "transaction.h"
#include "transaction.cpp"
#include "globals.h"
#include "ipc_module.h" 
#include "ipc_module.cpp"

using namespace std;

int main()
{
    readFile("input.txt");
    GetTransactions();
    GetLogs("logfile.txt");

    return 0;
}
