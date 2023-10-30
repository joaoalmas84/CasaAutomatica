#include "Comando.h"
#include <sstream>

Comando::Comando() : nome(""), corpo(), numArg(0) {
    //cout << "\n\nComando vazio criado";
}

void Comando::setNome(string _nome) {nome = _nome;}

void Comando::setNumArg(int _numArg) {numArg = _numArg;}

void Comando::setCorpo(string _corpo) {
    istringstream iss(_corpo);
    string str;
    int i = 0;
    while (iss >> str) {
      corpo.push_back(str);
    }
}

string Comando::vectorToString() {
    string str = "";
    for (string s : corpo) {
        str += s + ' ';
    }
    return str;
}

void Comando::setSintaxe(string _sintaxe) {sintaxe = _sintaxe;}

bool Comando::avaliaCmd() {

}

string Comando::descricao() {
    ostringstream oss;
    oss << "\nNome:\t\t" << nome
        << "\nCorpo:\t\t" << vectorToString()
        << "\nNr argumentos:\t" << numArg
        << "\nSintaxe:\t" << sintaxe;
    return oss.str();
}

Comando::~Comando() {
    //cout << "\nComando " << nome << " destruido";
}