#ifndef CODIGOFONTE_LAMPADA_H
#define CODIGOFONTE_LAMPADA_H

#include "Aparelho.h"

class Lampada : public Aparelho {
public:
    Lampada(shared_ptr<Propriedade> iluminacao);
    void liga()override;
    void desliga()override;
    void mudaEstado(const string & nome)override;
};


#endif //CODIGOFONTE_LAMPADA_H
