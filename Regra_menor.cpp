//
// Created by 35193 on 22/12/2023.
//

#include "Regra_menor.h"
#include <sstream>

Regra_menor::Regra_menor(weak_ptr<Sensor> _sensor, const double &_X) : RegraBase(_sensor), X(_X) {}
bool Regra_menor::getEstado() {
    return RegraBase::getvalor() < X;
}
string Regra_menor::getAsString() const {
    ostringstream os;
    os << RegraBase::getAsString();
    os << "X : " << X << " | fum: menor"<<endl;
    return os.str();
}