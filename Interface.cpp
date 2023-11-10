#include "Interface.h"
#include "utils.h"
#include <sstream>

void UI() {
    string cmd;
    int res;
    // * ... aqui.
    while (1) {
        cmd = "";
        res = -1;
        Comando c; // <- Exprimentar por este comando ... *

        cmd = getCmd();
        res = c.validaCmd(cmd);
        switch (res) {
            case 0:
                cout << c.descricao();
                cout << '\n';
                if (c.validaStx()) {
                    c.execCmd();
                    cout << "\nSintaxe valida";
                } else {
                    cout << "\nSintaxe invalida";
                }
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
            default:
                break;
        }
        // Comando c é destruido aqui
    }
}

string getCmd() {
    string cmd;
    cin.clear();
    cout << "\n\nComando -> ";
    getline(cin, cmd);
    return cmd;
}

