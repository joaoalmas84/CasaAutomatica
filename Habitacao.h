//
// Created by 35193 on 21/11/2023.
//

#ifndef OOP_TRABALHO_HABITACAO_H
#define OOP_TRABALHO_HABITACAO_H
#include "Zona.h"

class Habitacao {
    Zona ***zonas;
public:
    Habitacao(int linhas, int colunas);
    void add_Zona(int linha, int coluna);
    Zona* get_idZona(int linha, int coluna);





};


#endif //OOP_TRABALHO_HABITACAO_H
