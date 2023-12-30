//
// Created by 35193 on 22/12/2023.
//

#ifndef OOP_TRABALHO_REGRA_MENOR_H
#define OOP_TRABALHO_REGRA_MENOR_H
#include "RegraBase.h"

class Regra_menor : public RegraBase {
    double X;
public:
    Regra_menor(weak_ptr<Sensor> _sensor, const double &_X);
    [[nodiscard]]
    bool getEstado() final;
    [[nodiscard]]
    string getAsString()const final;
    ~Regra_menor() = default;
    unique_ptr<RegraBase> clone() final;
};


#endif //OOP_TRABALHO_REGRA_MENOR_H
