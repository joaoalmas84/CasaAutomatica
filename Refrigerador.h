#ifndef CODIGOFONTE_REFRIGERADOR_H
#define CODIGOFONTE_REFRIGERADOR_H

#include "Aparelho.h"
#include "Propriedade.h"

#include <iostream>
#include <map>
#include <memory>

using namespace std;

class Refrigerador : public Aparelho {
public:
    Refrigerador(Propriedade* temperatura, Propriedade* ruido);
    void liga()override;
    void desliga()override;
};


#endif //CODIGOFONTE_REFRIGERADOR_H
