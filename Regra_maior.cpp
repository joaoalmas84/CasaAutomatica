//
// Created by 35193 on 22/12/2023.
//

#include "Regra_maior.h"
#include <sstream>

Regra_maior::Regra_maior(weak_ptr<Sensor> _sensor, const double &_X) : RegraBase(_sensor), X(_X) {}
bool Regra_maior::getEstado() {
    return RegraBase::getvalor() > X;
}
string Regra_maior::getAsString() const {
    ostringstream os;
    os << RegraBase::getAsString();
    os << "X : " << X << " | fum: maior" << endl;
    return os.str();
}
unique_ptr<RegraBase> Regra_maior::clone() {
    return make_unique<Regra_maior>(*this);
}