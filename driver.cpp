#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <unistd.h>
#include "transaction.cpp"
#include "transaction.h"
#include "globals.h"


using namespace std;

int main()
{
    readFile("input.txt");
    GetTransactions();
    GetLogs("logs.txt");

    return 0;
}
