#include "Comando.h"

#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

/***************************************** Public *****************************************/

int Comando::getIndex() {return index;}

// 0 -> valido; 1 -> invalido; 2 -> argumentos a menos; 3 -> argumentos a mais;
int Comando::validaCmd() {
    string cmdNome = getNomeCmd();

    int cmdIndex = procuraEmVector(comandos, cmdNome);
    if (cmdIndex == -1) {return 1;}

    int cmdNumArg = countArgsCmd();

    if (n_Args[cmdIndex] != -1) {
        if (cmdNumArg < n_Args[cmdIndex]) {return 2;}
        else if (cmdNumArg > n_Args[cmdIndex]) {return 3;}
    } else {
        switch (cmdIndex) {
            case 10:
            case 13:
            case 18:
                if (cmdNumArg < 3) {return 2;}
                break;
            case 12:
                if (cmdNumArg < 5) {return 2;}
                break;
            default:
                break;
        }
    }

    nome = cmdNome;
    index = cmdIndex;
    if (n_Args[cmdIndex] == -1) {numArg = -1;}
    else {numArg = cmdNumArg;}
    stx = sintaxe[cmdIndex];
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
        case 14:
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

            if (vectorInput[2] == "s") {
                if (procuraEmVector(sensores, vectorInput[3]) == -1) {
                    cout << "\nSensor desconhecido";
                    return false;
                }
            } else if (vectorInput[2] == "p") {
                return avaliaCmdFromParm(vectorInput, 3);
            } else if (vectorInput[2] == "a") {
                if (procuraEmVector(aparelhos, vectorInput[3]) == -1) {
                    cout << "\nAparelho desconhecido";
                    return false;
                }
            } else {return false;}
            return true;
            break;
        case 11:
            if (!isIntegerString({vectorInput[1], vectorInput[2]}) || procuraEmVector(spa, vectorInput[2]) != -1) {return false;}
            else {return true;}
            break;
        case 12:
            if (!isIntegerString({vectorInput[1], vectorInput[2], vectorInput[4]})) {return false;}
            else {return true;}
            break;
        case 13:
        case 18:
            if (!isIntegerString({vectorInput[1], vectorInput[2]})) {return false;}
            else {return avaliaCmdFromParm(vectorInput, 3);}
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

string Comando::descricao() const {
    ostringstream oss;
    string aux;

    if (numArg == -1) {aux = "Nr. indefinido";}
    else {aux = to_string(numArg);}

    oss << "\nInput:\t\t" << input
        << "\nComando:\t" << nome
        << "\nIndex:\t\t" << index
        << "\nArgumentos:\t" << aux
        << "\nSintaxe:\t" << stx
        << '\n';

    return oss.str();
}

bool Comando::SAIR() const {
    if (nome == "sair") {return true;}
    else {return false;}
}

/***************************************** Private *****************************************/

string Comando::getNomeCmd() const {
    istringstream iss(input);
    string str;
    iss >> str;
    return str;
}

// Devolve -1 se nao encontrar str. Se encontrar devolve a posicao em que se encontra
int Comando::procuraEmVector(vector<string> v, string str) const {
    auto it = find(v.begin(), v.end(), str);
    if (it == v.end()) {return -1;}
    else {return distance(v.begin(), it);}
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

bool Comando::avaliaCmdFromParm(vector<string> v, int pos) const {
    auto it = v.begin() + pos;
    string cmd = "";

    for (; it + 1 != v.end(); it++) {
        if (it + 2 == v.end()) {cmd += *it;}
        else {cmd += *it + ' ';}
    }

    Comando aux(cmd);

    if (aux.validaCmd() != 0 || !aux.validaStx()) {// <- Alerta Recursividade!!!!
        cout << "\n\nComando no parametro nr." << pos << " invalido";
        return false;
    } else {
        cout << "\n\nComando no parametro nr." << pos << ':';
        cout << aux.descricao();
        return true;
    }
}