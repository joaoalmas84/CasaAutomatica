#ifndef CODIGOFONTE_ASPERSOR_H
#define CODIGOFONTE_ASPERSOR_H

#include "Aparelho.h"

class Aspersor : public Aparelho {
    int instantes;
public:
    Aspersor(weak_ptr<Propriedade> humidade, weak_ptr<Propriedade> vibracao, weak_ptr<Propriedade> fumo);
    void liga()override;
    void desliga()override;
    void mudaEstado(const string & nome)override;
    void prox() override;
    shared_ptr<Aparelho> clone() final;
};


#endif //CODIGOFONTE_ASPERSOR_H
