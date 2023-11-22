#include "Interface.h"
#include "Habitacao.h"
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

void atualizar_zonas_UI(int linhas, int colunas,int tamzona, Habitacao &H, Window ***wzonas){
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if(wzonas[i][j] != nullptr){
                (wzonas[i][j])->clear();
            }
        }
    }

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if(H.get_idZona(i, j) != nullptr){

                if(wzonas[i][j] == nullptr)
                    wzonas[i][j] = new Window(j*tamzona*2, i*tamzona, tamzona*2, tamzona);

                *(wzonas[i][j]) << set_color(3) << H.get_idZona(i, j)->getId();


            }
        }
    }
}

void UI2() {
    int ee;
    int dim[2];

    cout << "teste = 1 " << "simular = 2 ";
    cin >> ee;

    if (ee == 2) {
        Terminal &t = Terminal::instance();
        inicializar(t, dim);
        ini_cor(t);
        Window Wcmd = ini_cmd_UI(dim);
        atualizar_cmd(Wcmd);

        vector<Window *> wzona;


        string numeroDeZOnas = "quantas zonas 2x2 ate 4x4";
        t << move_to(dim[0] / 2 - (numeroDeZOnas.size() / 2), dim[1] / 2 - 4) << numeroDeZOnas;
        Wcmd >> numeroDeZOnas;

        int p = (int) numeroDeZOnas[0] - 48;
        int f = (int) numeroDeZOnas[2] - 48;

        Habitacao He(p, f);
        /*for (int i = 0; i < p; ++i) {
            for (int j = 0; j < f; ++j) {
                He.add_Zona(i,j);
            }
        }*/
        He.add_Zona(0, 0);
        He.add_Zona(p - 1, f - 1);
        He.add_Zona(p - 1, 0);
        Window ***wzona2;
        wzona2 = new Window **[p];

        for (int i = 0; i < p; ++i) {
            wzona2[i] = new Window *[f];
        }

        for (int i = 0; i < p; ++i) {
            for (int j = 0; j < f; ++j) {
                wzona2[i][j] = nullptr;
            }
        }

        int ztam = (dim[1] - 3) / 4;


        atualizar_zonas_UI(p, f, ztam, He, wzona2);
        /*for(int i = 0; i < p; i++)
            for(int j = 0; j < f; j++){
                wzona.push_back(new Window(ztam * 2 * j, i * ztam , ztam * 2, ztam));
            }*/
        atualizar_cmd(Wcmd);
        Window wdados = Window(f * (ztam * 2), 0, dim[0] - f * (ztam * 2), ztam * 4);
        wdados << set_color(3) << f;
        Wcmd >> numeroDeZOnas;
        He.add_Zona(p - 2, 0);

        atualizar_zonas_UI(p, f, ztam, He, wzona2);

        Wcmd >> numeroDeZOnas;
    }else{
        for (int i = 0; i < 3; ++i) {
            cout << i << " " << endl;
        }
        Zona z2, z1("quarto");
        z1.setPropriedades("Temperatura", -1900);
        z1.setPropriedades("Radiacao", 11100);
        z1.setPropriedades("Humidade", 11100);
        z1.setPropriedades("Fumo", 10);
        z1.addSensor("Temperatura");
        z1.addSensor("Fumo");
        z1.addSensor("Radiacao");
        z1.addSensor("Radiacao");
        z1.addSensor("Radiacao");
        /*z1.addProcessador();
        z1.addProcessador();
        z1.addRegrasPorc(0, 0, "maior", -300);
        z1.addRegrasPorc(0, 1, "menor", 2);*/

        cout <<" eeeeeeeeeeee " << z1.getAsString() << endl;

        z1.eleminarSensor(0);
        //cout << z1.listaPropriedades();

        //z1.setPropriedades("Fumo", -20);

        cout <<" eeeeeeeeeeee " << z1.getAsString() << endl;

        cout << "=====================================================" << endl;

        Habitacao He(2, 3);

        std::cout << "Hello, World!" << std::endl;

    }
}
void inicializar(Terminal& t, int *dim){
    dim[0] = t.getNumCols();
    dim[1] = t.getNumRows();
    t.clear();
}
Window ini_cmd_UI(int *dim){
    return Window(0, dim[1] - 3, dim[0], 3);
}
void ini_cor(Terminal& t){
    for(int i=1; i<20; i++) {
        t.init_color(i, i, 0);
    }
}
void atualizar_cmd(Window &Wcmd){
    Wcmd.clear();
    Wcmd << set_color(3) << "comando: ";
}



