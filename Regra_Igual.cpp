//
// Created by 35193 on 20/12/2023.
//

#include "Regra_Igual.h"
#include <sstream>
Regra_Igual::Regra_Igual(weak_ptr<Sensor> _sensor, const double &_X) : RegraBase(_sensor), X(_X) {}

bool Regra_Igual::getEstado() {
    return RegraBase::getvalor() == X;
}
string Regra_Igual::getAsString() const {
    ostringstream os;
    os << RegraBase::getAsString();
    os << "X : " << X << endl;
    return os.str();
}