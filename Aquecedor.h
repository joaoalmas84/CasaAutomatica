#ifndef CODIGOFONTE_AQUECEDOR_H
#define CODIGOFONTE_AQUECEDOR_H

#include "Aparelho.h"
#include "Propriedade.h"

#include <iostream>
#include <map>
#include <memory>

using namespace std;

class Aquecedor : public Aparelho {
public:
    Aquecedor(shared_ptr<Propriedade> temperatura, shared_ptr<Propriedade> ruido);
    void liga()override;
    void desliga()override;
    void mudaEstado(const string & nome)override;
};


#endif //CODIGOFONTE_AQUECEDOR_H
