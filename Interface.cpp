#include "Interface.h"
#include <iostream>
#include <sstream>
#include <algorithm>

void UI() {
    string cmd;
    while (cmd != "sair") {
        cmd = "";
        int res = -1;
        Comando c;

        cmd = getCmd();
        res = validaCmd(cmd, c);

        switch (res) {
            case 0:
                cout << c.descricao();
                break;
            case 1:
                wcout << L"Comando nao encontrado";
                break;
            case 2:
                cout << "Faltam argumentos";
                break;
            case 3:
                cout << "Demasiados argumentos";
                break;
        }
        // Comando c é destruido aqui
    }
}

string getCmd() {
    string cmd;
    cin.clear();
    cout << "\n\nComando ->";
    getline(cin, cmd);
    return cmd;
}

int countArgs(string cmd) {
    istringstream iss(cmd);
    string str;
    int i = 0;
    while (iss >> str) {
        i++;
    }
    return i-1; // <- -1 Porque o nome do comando não conta para o n.º de argumentos
}

//0-> valido; 1 -> invalido; 2 -> falta argumentos; 3 -> excesso de argumentos;
int validaCmd(string cmd, Comando& c) {
    int argCount = countArgs(cmd);
    istringstream iss(cmd);
    string str;
    iss >> str;
    auto it = find(comandos.begin(), comandos.end(), str);

    if (it == comandos.end()) {return 1;}
    else if (argCount < nArgs[distance(comandos.begin(), it)]) {return 2;}
    else if (argCount > nArgs[distance(comandos.begin(), it)]) {return 3;}
    else {
        c.setNome(str);
        c.setNumArg(argCount);
        c.setCorpo(cmd);
        c.setSintaxe(stx[distance(comandos.begin(), it)]);
        return 0;
    }
}