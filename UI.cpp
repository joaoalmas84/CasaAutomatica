#include "UI.h"
#include "Comando.h"

void START() {
    string cmd;

    while (1) {

        cmd = getCmd();
        Comando c(cmd);

        switch (c.validaCmd()) {
            case 0:
                if (c.validaStx()) {
                    cout << '\n' << c.descricao();
                    cout << "\n\nSintaxe valida";
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
    }
}

string getCmd() {
    string cmd;
    cin.clear();
    cout << "\n\nComando -> ";
    getline(cin, cmd);
    return cmd;
}