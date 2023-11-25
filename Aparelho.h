#ifndef CODIGOFONTE_APARELHO_H
#define CODIGOFONTE_APARELHO_H

#include "Propriedade.h"

struct modifa {
    Propriedade* propriedade;
    double valorA_Modeficar;
};

class Aparelho {
public:
    ~Aparelho();

private:
    bool ligado;
    struct modifa *modifica;
};


#endif //CODIGOFONTE_APARELHO_H
