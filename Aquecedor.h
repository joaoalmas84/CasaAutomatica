#ifndef CODIGOFONTE_AQUECEDOR_H
#define CODIGOFONTE_AQUECEDOR_H

#include "Aparelho.h"
#include "Propriedade.h"

#include <iostream>
#include <map>
#include <memory>

using namespace std;

class Aquecedor : public Aparelho {
    int instantes;
    int instantesfumo;
public:
    Aquecedor(weak_ptr<Propriedade> temperatura, weak_ptr<Propriedade> ruido);
    void liga()override;
    void desliga()override;
    void mudaEstado(const string & nome)override;
    void prox();
};


#endif //CODIGOFONTE_AQUECEDOR_H
