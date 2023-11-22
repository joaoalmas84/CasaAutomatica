#include "Comando.h"

#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

/***************************************** Public *****************************************/

// 0 -> valido; 1 -> invalido; 2 -> argumentos a menos; 3 -> argumentos a mais;
int Comando::validaCmd() {
    string cmdNome = getNomeCmd();

    int cmdIndex = procuraEmVector(comandos, cmdNome);
    if (cmdIndex == -1) {return 1;}

    int cmdNumArg = countArgsCmd();
    if (cmdNumArg < n_Args[cmdIndex] && n_Args[cmdIndex] != -1) {return 2;}
    else if (cmdNumArg > n_Args[cmdIndex] && n_Args[cmdIndex] != -1) {return 3;}

    nome = cmdNome;
    index = cmdIndex;
    if (n_Args[cmdIndex] == -1) {numArg = -1;}
    else {numArg = cmdNumArg;}
    stx = sintaxe[cmdIndex];
    return 0;
}

bool Comando::validaStx() {
    vector<string> vectorInput = stringToVector(input);
    switch (index) {
        case 1:
        case 5:
        case 7:
        case 8:
            if (isIntegerString(vectorInput[1])) {return true;}
            else {return false;}
            break;
        case 2:
        case 4:
            if (isIntegerString(vectorInput[1]) && isIntegerString(vectorInput[2])) {return true;}
            else {return false;}
            break;
        case 9:
            if (isIntegerString(vectorInput[1]) && isIntegerString(vectorInput[3])) {return true;}
            else {return false;}
            break;
        case 10:    // <- Caso especial, possibilidade de n.º de argumentos variar
            // (Está a funcionar tudo exceto a variante corpo[2]="p" quando o processador recebe comandos com parametros)
            bool flag;

            if (isIntegerString(vectorInput[1])) {flag = true;}
            else {return false;}

            if (vectorInput[2] == "s") {
                if (procuraEmVector(sensores, vectorInput[3]) == -1) {
                    cout << "\nSensor desconhecido";
                    flag = false;
                }
            } else if (vectorInput[2] == "p") {
                auto it = vectorInput.begin() + 3;
                string cmd = "";
                for (; it + 1 != vectorInput.end(); it++) {
                    if (it + 2 == vectorInput.end()) {cmd += *it;}
                    else {cmd += *it + ' ';}
                }
                Comando aux(cmd);
                if (aux.validaCmd() == 0 && aux.validaStx()) {// <- Alerta Recursividade!!!!
                    cout << "\nComando no parametro nr.3:";
                    cout << aux.descricao();
                    flag = true;
                } else {
                    cout << "\nComando no parametro nr.3 invalido";
                    return false;
                }
            } else if (vectorInput[2] == "a") {
                if (procuraEmVector(aparelhos, vectorInput[3]) == -1) {
                    cout << "\nAparelho desconhecido";
                    flag = false;
                }
            } else {return false;}
            return flag;
            break;
        case 11:
            if (isIntegerString(vectorInput[1])
                && procuraEmVector(spa, vectorInput[2]) != -1
                && isIntegerString(vectorInput[3])) {return true;}
            else {return false;}
            break;
        case 12:
            
            break;
            //case 13: por fazer
            //case 14: por fazer
            //case 15: por fazer
            //case 16: por fazer
            //case 17: por fazer
            //case 18: por fazer
            //case 19: por fazer
            //case 20: por fazer
            //case 21: por fazer
            //case 23: por fazer
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
        << "\nSintaxe:\t" << stx;

    return oss.str();
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

bool Comando::isIntegerString(string str) {
    istringstream iss(str);
    int n = 0;
    iss >> n;
    if (iss.fail()) {return false;}
    else {return true;}
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