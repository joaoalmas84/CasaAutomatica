//
// Created by 35193 on 17/11/2023.
//

#ifndef OOP_TRABALHO_APARELHO_H
#define OOP_TRABALHO_APARELHO_H
#include "Propriedade.h"
struct modifa{
    Propriedade* propriedade;
    double valorA_Modeficar;
};

class Aparelho {
    bool ligado;
    struct modifa *modifica;

public:
    ~Aparelho();

};


#endif //OOP_TRABALHO_APARELHO_H
