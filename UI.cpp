
#include "Comando.h"
#include "UI.h"
#include <sstream>
#include <fstream>

UI::UI(): t(Terminal::instance()), dimx(t.getNumCols()), dimy(t.getNumRows()), linhas(0), colunas(0), dadosW(nullptr), dimzonasy((dimy - 3) / 4), dimzonasx((dimy - 3) / 4 * 3){
    habitacao = nullptr;
    numdados = 0;
    ini_cor();
    cmdW = ini_cmd_UI();
    *cmdW << set_color(3) <<move_to(0,0) << "Comando -> ";
    dadosW = ini_dadosW_UI();
}

void UI::START() {
    string cmd;
    int res = 0;

    while (res != 1) {
        cmd = getCmd();
        res = commandLine(cmd);
    }
}

string UI::getCmd() {
    string cmd;
    (*cmdW) >> cmd;
    atulizar_cmdW();
    return cmd;
}

int UI::commandLine(string cmd) {
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
                *dadosW << set_color(5) << move_to(0, numdados) << c.descricao();
                numdados += 6;
                if (c.SAIR()) {return 1;}
                string aux;
                switch (c.getIndex()) {
                    case 2:

                        if(habitacao == nullptr){
                            ///// REVOMER DEPOIS DA CLASS COMANDOS ESTAR COMPLETA = TRABALHO DA CLASS COMANDOS
                            col:
                        *dadosW << set_color(5) << move_to(0, numdados++) << "Intruduza o numero de colunas";
                        *cmdW >> aux;
                        atulizar_cmdW();
                        try{colunas = stoi(aux);}catch(const std::invalid_argument& ia){goto col;}
                        lin:
                        *dadosW << set_color(5) << move_to(0, numdados++) << "Intruduza o numero de linhas";
                        *cmdW >> aux;
                        atulizar_cmdW();
                        try{linhas = stoi(aux);}catch(const std::invalid_argument& ia){goto lin;}
                        if(!(linhas > 1 && linhas < 5) ||  !(colunas > 1 && colunas < 5))
                            goto col;
                            ///// REVOMER DEPOIS DA CLASS COMANDOS ESTAR COMPLETA = TRABALHO DA CLASS COMANDOS

                        habitacao = new Habitacao(linhas, colunas);
                        criarZonasWindow();
                        dadosW =ini_dadosW_UI();

                        }else{
                            *dadosW << set_color(5) << move_to(0, numdados++) << "ja existe uma habitacao";
                        }
                        break;
                    case 4:
                        if(habitacao != nullptr){
                            int linhasTemp, colunasTemp;

                            ///// REVOMER DEPOIS DA CLASS COMANDOS ESTAR COMPLETA = TRABALHO DA CLASS COMANDOS
                            re:
                            *dadosW << set_color(5) << move_to(0, numdados++) << "Intruduza o numero de colunas";
                            *cmdW >> aux;
                            atulizar_cmdW();
                            try{colunasTemp = stoi(aux);}catch(const std::invalid_argument& ia){goto re;}
                            de:
                            *dadosW << set_color(5) << move_to(0, numdados++) << "Intruduza o numero de linhas";
                            *cmdW >> aux;
                            atulizar_cmdW();
                            try{linhasTemp = stoi(aux);}catch(const std::invalid_argument& ia){goto de;}
                            ///// REVOMER DEPOIS DA CLASS COMANDOS ESTAR COMPLETA = TRABALHO DA CLASS COMANDOS
                            habitacao->add_Zona(linhasTemp, colunasTemp);
                            atualizar_zonas_UI(linhas, colunas);

                        }else{
                            *dadosW << set_color(5) << move_to(0, numdados++) << "nao existe zona";
                        }

                        break;
                    default:
                        *dadosW << set_color(5) << move_to(0, numdados++) << "Erro";
                        break;
                }








            } else {
                *dadosW << set_color(19) << move_to(0, numdados++) << "Sintaxe invalida";
            }
            break;
        case 1:
            *dadosW << set_color(19) << move_to(0, numdados++) << "Comando nao encontrado";
            break;
        case 2:
            *dadosW << set_color(19) << move_to(0, numdados++) << "Argumentos a menos";
            break;
        case 3:
            *dadosW << set_color(19) << move_to(0, numdados++) << "Argumentos a mais";
            break;
        default:
            break;
    }
    // Comando c é destruido aqui
    return 0;
}

int UI::exec(string fileName)  {
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

Window *UI::ini_cmd_UI() {
    return new Window(0, dimy - 3, dimx, 3);

}

Window *UI::ini_dadosW_UI() {
        delete dadosW;
        numdados = 0;
        return new Window(dimzonasx*colunas, 0, dimx - (dimzonasx*colunas), dimy-3);

}
void UI::ini_cor(){
    for(int i=1; i<20; i++) {
        t.init_color(i, i, 0);
    }
}

void UI::atulizar_cmdW() {
    cmdW->clear();
    *cmdW << set_color(3) << move_to(0,0) << "Comando -> ";
}

void UI::criarZonasWindow() {
    zonasW = new Window **[linhas];

    for (int i = 0; i < linhas; ++i) {
        zonasW[i] = new Window *[colunas];
    }

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            zonasW[i][j] = nullptr;
        }
    }
}

void UI::atualizar_zonas_UI(const int &linha, const int &coluna){
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            if(habitacao->get_idZona(i, j) != nullptr){

                if(zonasW[i][j] == nullptr)
                    zonasW[i][j] = new Window(j*dimzonasx, i*dimzonasy, dimzonasx, dimzonasy);

                (zonasW[i][j])->clear();
                *(zonasW[i][j]) << set_color(3) << habitacao->get_idZona(i, j)->getId();
            }
        }
    }
}
