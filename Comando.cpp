#include "Comando.h"
#include "utils.h"
#include <sstream>
#include <algorithm>

// Public:
Comando::Comando() : id(0), nome(""), corpo(), numArg(0), sintaxe("") {
    //cout << "\n\nComando vazio criado";
}

void Comando::setId(int _id) {id = _id;}

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

void Comando::setSintaxe(string _sintaxe) {sintaxe = _sintaxe;}

// 0 -> valido; 1 -> invalido; 2 -> falta argumentos; 3 -> excesso de argumentos;
int Comando::validaCmd(string cmd) {
    int argCount = countArgs(cmd);
    istringstream iss(cmd);
    string str;
    iss >> str;
    int index = isInVector(comandos, str);
    if (index == -1) {return 1;}
    else if (argCount < nArgs[index]) {return 2;}
    else if (argCount > nArgs[index]) {return 3;}
    else {
        setId(index);
        setNome(str);
        setNumArg(argCount);
        setCorpo(cmd);
        setSintaxe(stx[(index)]);
        return 0;
    }
}

bool Comando::validaStx() {
    switch (id) {
        case 1:
        case 5:
        case 7:
        case 8:
            if (isIntegerString(corpo[1])) {return true;}
            else {return false;}
            break;
        case 2:
        case 4:
            if (isIntegerString(corpo[1]) && isIntegerString(corpo[2])) {return true;}
            else {return false;}
            break;
        case 9:
            if (isIntegerString(corpo[1]) && isIntegerString(corpo[3])) {return true;}
            else {return false;}
            break;
        case 10:    // <- Caso especial, possibilidade de n.º de argumentos variar
                    // (Está a funcionar tudo exceto a variante corpo[2]="p" quando o processador recebe comandos com parametros)
            bool flag;

            if (isIntegerString(corpo[1])) {flag = true;}
            else {return false;}

            if (corpo[2] == "s") {
                if (isInVector(sensores, corpo[3]) == -1) {
                    cout << "\nSensor desconhecido";
                    flag = true;
                }
            } else if (corpo[2] == "p") {
                Comando aux;
                string cmd = "";
                vector<string>::iterator itAux = corpo.begin()+3;
                for (; itAux != corpo.end(); itAux++) {
                    cmd += *itAux + ' ';
                }
                if (aux.validaCmd(cmd) == 0 && aux.validaStx()) {// <- Alerta Recursividade!!!!
                    cout << "\nExecuta comando " << aux.nome;
                    flag = true;
                } else {return false;}
            } else if (corpo[2] == "a") {
                if (isInVector(aparelhos, corpo[3]) == -1) {
                    cout << "\nAparelho desconhecido";
                    flag = true;
                }
            } else {return false;}
            return flag;
            break;
        case 11:
            if (isIntegerString(corpo[1]) && isInVector(spa, corpo[2]) != -1 && isIntegerString(corpo[3])) {return true;}
            else {return false;}
            break;
        //case 12: por fazer
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

void Comando::execCmd() {
    switch (id) {
        case 24:
            cout << "\nA sair...\n";
            exit(1);
            break;
        case 25:
            system("cls");
            break;
        case 26:
            cout << "\nSintaxe dos comandos:";
            for (string s : stx) {
                cout << "\n-> " << s;
            }
            cout << '\n';
            break;
        default:
            break;
    }
}

string Comando::descricao() {
    ostringstream oss;
    oss << "\nId:\t\t" << id
        << "\nNome:\t\t" << nome
        << "\nCorpo:\t\t" << vectorToString()
        << "\nArgumentos:\t" << numArg
        << "\nSintaxe:\t" << sintaxe;
    return oss.str();
}

Comando::~Comando() {
    //cout << "\nComando " << nome << " destruido";
}

// Private:
int Comando::countArgs(string cmd) {
    istringstream iss(cmd);
    string str;
    int i = 0;
    while (iss >> str) {
        i++;
    }
    return i-1; // <- -1 Porque o nome do comando não conta para o n.º de argumentos
}

string Comando::vectorToString() {
    string str = "";
    for (string s : corpo) {
        str += s + ' ';
    }
    return str;
}

bool Comando::isIntegerString(string str) {
    istringstream iss(str);
    int n = 0;
    iss >> n;
    if (iss.fail()) {return false;}
    else {return true;}
}

// -1 <- se nao encontrar str; se encontrar devolve o indice da posicao
int Comando::isInVector(vector<string>v, string str) {
    auto it = find(v.begin(), v.end(), str);
    if (it != v.end()) {
        return distance(v.begin(), it);
    } else {
        return -1;
    }
}
