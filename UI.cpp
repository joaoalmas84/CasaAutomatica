#include "UI.h"
#include "Comando.h"

#include <sstream>
#include <fstream>

void START() {
    string cmd;
    int res = 0;

    while (res != 1) {
        cmd = getCmd();
        res = commandLine(cmd);
    }
}

string getCmd() {
    string cmd;
    cin.clear();
    cout << "\n\nComando -> ";
    getline(cin, cmd);
    return cmd;
}

int commandLine(string cmd) {
    istringstream iss(cmd);
    string s1, s2;
    iss >> s1 >> s2;
    int res;

    if (s1 == "exec") {
        res = exec(s2);
        if (res == 1) {return res;}
    }

    Comando c(cmd);

    switch (c.validaCmd()) {
        case 0:
            if (c.validaStx()) {
                cout << '\n' << c.descricao();
                if (c.SAIR()) {return 1;}
            } else {
                cout << "\n\nSintaxe invalida";
            }
            break;
        case 1:
            cout << "\n\nComando nao encontrado";
            break;
        case 2:
            cout << "\n\nArgumentos a menos";
            break;
        case 3:
            cout << "\n\nArgumentos a mais";
            break;
        default:
            break;
    }
    // Comando c é destruido aqui
    return 0;
}

int exec(string fileName)  {
    ifstream ifs(fileName);
    string line;
    int n = 0, res = 0;

    if(!ifs.is_open()) {return -1;}

    while (!ifs.eof()) {
        getline(ifs, line);
        res = commandLine(line);
        n++;
    }

    ifs.close();

    return res;
}
