

#ifndef SKIRT_UI_H
#define SKIRT_UI_H

#include <iostream>
#include <vector>
#include "Terminal.h"
#include "Habitacao.h"
using namespace std;
using namespace term;
class UI{
     Terminal &t;
     Window *cmdW;
     Window *dadosW;
     Window ***zonasW;
     const int dimx;
     const int dimy;
     int linhas;
     int colunas;
     const int dimzonasx;
     const int dimzonasy;
     int numdados;
     Habitacao *habitacao;

public:
    UI();
    Window *ini_cmd_UI();
    Window *ini_dadosW_UI();
    int exec(string fileName);
    void START();
    string getCmd();
    int commandLine(string cmd);
    void ini_cor();
    void atulizar_cmdW();
    void criarZonasWindow();
    void atualizar_zonas_UI(const int &linha, const int &coluna);

};

#endif //SKIRT_UI_H
