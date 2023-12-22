//
// Created by 35193 on 20/12/2023.
//

#ifndef OOP_TRABALHO_REGRA_IGUAL_H
#define OOP_TRABALHO_REGRA_IGUAL_H
#include "RegraBase.h"

class Regra_Igual : public RegraBase{
    double X;
public:
    Regra_Igual(weak_ptr<Sensor> _sensor,const double &_X);
    [[nodiscard]]
    bool getEstado() final;
    [[nodiscard]]
    string getAsString()const final;
    ~Regra_Igual() = default;
};


#endif //OOP_TRABALHO_REGRA_IGUAL_H
