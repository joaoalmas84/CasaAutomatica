#include "Interface.h"
#include "utils.h"
#include <sstream>

void UI() {
    string cmd;
    while (1) {
        cmd = "";
        int res = -1;
        Comando c;

        cmd = getCmd();
        res = c.validaCmd(cmd);

        switch (res) {
            case 0:
                cout << c.descricao();
                cout << '\n';
                if (c.validaStx()) {
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

