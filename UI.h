#ifndef SKIRT_UI_H
#define SKIRT_UI_H

#include <iostream>
#include <vector>

using namespace std;

void START();
string getCmd();
int commandLine(string cmd);
int exec(string fileName);

#endif //SKIRT_UI_H
