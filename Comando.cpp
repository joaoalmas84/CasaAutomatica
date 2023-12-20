#include "Comando.h"
#include "Habitacao.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>

using namespace std;

/***************************************** Public *****************************************/

int Comando::getIndex() {return index;}

vector <string> Comando::getVectorInput() {
    return stringToVector(input);
}

// 0 -> valido; 1 -> invalido; 2 -> argumentos a menos; 3 -> argumentos a mais;
int Comando::validaCmd() {
    string cmdNome = getNomeCmd();

    int cmdIndex = procuraEmVector(comandos, cmdNome);
    if (cmdIndex == -1) {return 1;}

    int cmdNumArg = countArgsCmd();

    if (n_Args[cmdIndex] != -1) {
        if (cmdNumArg < n_Args[cmdIndex]) {return 2;}
        else if (cmdNumArg > n_Args[cmdIndex]) {return 3;}
    } else if (cmdNumArg < 5){return 2;}

    nome = cmdNome;
    index = cmdIndex;
    if (n_Args[cmdIndex] == -1) {numArg = -1;}
    else {numArg = cmdNumArg;}
    return 0;
}

bool Comando::validaStx() {
    vector<string> vectorInput = stringToVector(input);
    int res;

    switch (index) {
        case 1:
        case 5:
        case 7:
        case 8:
            if (!isIntegerString(vectorInput[1])) {return false;}
            else {return true;}
            break;
        case 2:
        case 4:
        case 13:
        case 14:
        case 18:
        case 19:
            if (!isIntegerString({vectorInput[1],vectorInput[2]})) {return false;}
            else {return true;}
            break;
        case 9:
            if (!isIntegerString({vectorInput[1],vectorInput[3]})) {return false;}
            else {return true;}
            break;
        case 10:
            if (!isIntegerString(vectorInput[1])) {return false;}
            if (procuraEmVector(spa, vectorInput[2]) == -1) {return false;}
            return true;
            break;
        case 11:
            if (!isIntegerString({vectorInput[1], vectorInput[2]})) {return false;}
            if (procuraEmVector(spa, vectorInput[2]) == -1) {return false;}
            else {return true;}
            break;
        case 12:
            if (!isIntegerString({vectorInput[1], vectorInput[2], vectorInput[4]})) {return false;}
            else {return true;}
            break;
        case 15:
        case 16:
        case 17:
            if (!isIntegerString({vectorInput[1], vectorInput[2], vectorInput[3]})) {return false;}
            else {return true;}
            break;
        default:
            return true;
    }
    return false;
}

bool Comando::SAIR() const {
    if (nome == "sair") {return true;}
    else {return false;}
}

// Devolve -1 se nao encontrar str. Se encontrar devolve a posicao em que se encontra
int Comando::procuraEmVector(vector<string> v, string str) const {
    auto it = find(v.begin(), v.end(), str);
    if (it == v.end()) {return -1;}
    else {return distance(v.begin(), it);}
}

[[nodiscard]]
bool Comando::hnova() {
    vector <string> inputAux = getVectorInput();

    if (!isBetween(stoi(inputAux[1]), 2, 4)) {return false;}
    if (!isBetween(stoi(inputAux[2]), 2, 4)) {return false;}

    return true;
}

[[nodiscard]]
bool Comando::znova(Habitacao* h) {
    vector <string> inputAux = getVectorInput();

    if (!isBetween(stoi(inputAux[1]), 0, h->getLin()-1)) {return false;}
    if (!isBetween(stoi(inputAux[2]), 0, h->getCol()-1)) {return false;}

    return true;
}


[[nodiscard]]
bool Comando::zrem() {
    vector <string> inputAux = getVectorInput();
    stoi(inputAux[1]);
    return true;
}

/***************************************** Private *****************************************/

string Comando::getNomeCmd() const {
    istringstream iss(input);
    string str;
    iss >> str;
    return str;
}

int Comando::countArgsCmd() const {
    istringstream iss(input);
    string str;
    int i = 0;

    while (iss >> str) {
        i++;
    }

    return i - 1; // <- -1 Porque o nome do comando não conta para o n.º de argumentos
}

bool Comando::isIntegerString(string s) const {
    istringstream iss(s);
    int n;

    iss >> n;
    if (iss.fail()) {return false;}

    return true;
}

bool Comando::isIntegerString(initializer_list<string> list) const {
    int n;

    for (const string & s : list) {
        istringstream iss(s);
        iss >> n;
        if (iss.fail()) {return false;}
    }

    return true;
}

vector<string> Comando::stringToVector(string str) {
    vector<string> v;
    istringstream iss(str);
    string s;

    while (!iss.fail()) {
        iss >> s;
        v.push_back(s);
    }

    return v;
}

[[nodiscard]]
bool Comando::isBetween(int val, int min, int max) {
    if (val >= min && val <= max) {return true;}
    else {return false;}
}