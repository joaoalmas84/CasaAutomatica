#ifndef CODIGOFONTE_LAMPADA_H
#define CODIGOFONTE_LAMPADA_H

#include "Aparelho.h"

class Lampada : public Aparelho {
public:
    Lampada(Propriedade* iluminacao);
    void liga()override;
    void desliga()override;
};


#endif //CODIGOFONTE_LAMPADA_H
