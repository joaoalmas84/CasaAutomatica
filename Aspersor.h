#ifndef CODIGOFONTE_ASPERSOR_H
#define CODIGOFONTE_ASPERSOR_H

#include "Aparelho.h"

class Aspersor : public Aparelho {

public:
    Aspersor(Propriedade* humidade, Propriedade* vibracao, Propriedade* fumo);
    void liga()override;
    void desliga()override;
    void mudaEstado(const string& nome);
};


#endif //CODIGOFONTE_ASPERSOR_H
