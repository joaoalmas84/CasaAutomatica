//
// Created by 35193 on 21/11/2023.
//

#include "Habitacao.h"
Habitacao::Habitacao(int linhas, int colunas) {
    zonas = new Zona **[linhas];

    for (int i = 0; i < linhas; ++i) {
        zonas[i] = new Zona *[colunas];
    }

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            zonas[i][j] = nullptr;
        }
    }
}

void Habitacao::add_Zona(int linha, int coluna) {
    zonas[linha][coluna] = new Zona("sala");
}

Zona* Habitacao::get_idZona(int linha, int coluna) {

    return zonas[linha][coluna];
}
