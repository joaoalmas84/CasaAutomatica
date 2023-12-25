#ifndef CODIGOFONTE_ASPERSOR_H
#define CODIGOFONTE_ASPERSOR_H

#include "Aparelho.h"

class Aspersor : public Aparelho {

public:
    Aspersor(shared_ptr<Propriedade> humidade, shared_ptr<Propriedade> vibracao, shared_ptr<Propriedade> fumo);
    void liga()override;
    void desliga()override;
    void mudaEstado(const string & nome)override;
};


#endif //CODIGOFONTE_ASPERSOR_H
