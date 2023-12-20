//
// Created by 35193 on 20/12/2023.
//

#ifndef OOP_TRABALHO_REGRA_IGUAL_H
#define OOP_TRABALHO_REGRA_IGUAL_H
#include "RegraBase.h"

class Regra_Igual : public RegraBase{
    double X;
public:
    Regra_Igual(weak_ptr<Sensor> _sensor, double _X);
    [[nodiscard]]
    bool getEstado();
    [[nodiscard]]
    string getAsString()const;
    ~Regra_Igual();
};


#endif //OOP_TRABALHO_REGRA_IGUAL_H
