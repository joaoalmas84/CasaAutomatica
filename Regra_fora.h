//
// Created by 35193 on 22/12/2023.
//

#ifndef OOP_TRABALHO_REGRA_FORA_H
#define OOP_TRABALHO_REGRA_FORA_H
#include "RegraBase.h"

class Regra_fora : public RegraBase{
    double Y;
    double X;
public:
    Regra_fora(weak_ptr<Sensor> _sensor,const double &X, const double &Y);
    [[nodiscard]]
    bool getEstado() final;
    [[nodiscard]]
    string getAsString()const final;
    ~Regra_fora() = default;
};


#endif //OOP_TRABALHO_REGRA_FORA_H
