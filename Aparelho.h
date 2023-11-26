#ifndef CODIGOFONTE_APARELHO_H
#define CODIGOFONTE_APARELHO_H

#include "Propriedade.h"

struct modifa {
    Propriedade* propriedade;
    double valorA_Modeficar;
};

class Aparelho {
    bool ligado;
    struct modifa *modifica;

public:
    ~Aparelho();
};

#endif //CODIGOFONTE_APARELHO_H
