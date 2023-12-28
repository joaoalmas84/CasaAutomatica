#ifndef CODIGOFONTE_LAMPADA_H
#define CODIGOFONTE_LAMPADA_H

#include "Aparelho.h"

class Lampada : public Aparelho {
public:
    Lampada(weak_ptr<Propriedade> iluminacao);
    void liga()override;
    void desliga()override;
    void mudaEstado(const string & nome)override;
    void prox();
};


#endif //CODIGOFONTE_LAMPADA_H
