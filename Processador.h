//
// Created by 35193 on 01/11/2023.
//

#ifndef POO_PROCESSADOR_H
#define POO_PROCESSADOR_H
#include <vector>
#include "Regra.h"
using namespace std;

class Processador {
    static int CONT;
    const int ID;
    vector<Regra> regras;

public:
    Processador();
    bool ativarProcessador();
    bool operator==(const Processador& pro)const;
};


#endif //POO_PROCESSADOR_H
