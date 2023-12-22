//
// Created by 35193 on 22/12/2023.
//

#ifndef OOP_TRABALHO_REGRA_MAIOR_H
#define OOP_TRABALHO_REGRA_MAIOR_H
#include "RegraBase.h"

class Regra_maior : public RegraBase {
    double X;
public:
    Regra_maior(weak_ptr<Sensor> _sensor, const double &_X);
    [[nodiscard]]
    bool getEstado() final;
    [[nodiscard]]
    string getAsString()const final;
    ~Regra_maior() = default;
};


#endif //OOP_TRABALHO_REGRA_MAIOR_H
