//
// Created by 35193 on 22/12/2023.
//

#ifndef OOP_TRABALHO_REGRA_ENTRE_H
#define OOP_TRABALHO_REGRA_ENTRE_H
#include "RegraBase.h"

class Regra_entre : public RegraBase{
    double Y;
    double X;
public:
    Regra_entre(weak_ptr<Sensor> _sensor, double X, double Y);
    [[nodiscard]]
    bool getEstado() final;
    [[nodiscard]]
    string getAsString()const final;
    ~Regra_entre();
};


#endif //OOP_TRABALHO_REGRA_ENTRE_H
