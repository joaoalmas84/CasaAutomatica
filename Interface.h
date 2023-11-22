#ifndef PROJECTCASA_INTERFACE_H
#define PROJECTCASA_INTERFACE_H

#include "Comando.h"
#include "Terminal.h"
#include "Habitacao.h"
using namespace term;
using namespace std;


void UI();
[[nodiscard]]
string getCmd();

// gui
void UI2();
void atualizar_zonas_UI(int linhas, int colunas,int tamzona, Habitacao &H, Window ***wzonas);
void inicializar(Terminal& t, int *dim);
Window ini_cmd_UI(int *dim);
void ini_cor(Terminal& t);
void atualizar_cmd(Window &Wcmd);


#endif //PROJECTCASA_INTERFACE_H
