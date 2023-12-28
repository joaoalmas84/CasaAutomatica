//
// Created by 35193 on 22/12/2023.
//

#include "Regra_entre.h"
#include <sstream>
Regra_entre::Regra_entre(weak_ptr<Sensor> _sensor, double _X, double _Y) : RegraBase(_sensor), X(_X), Y(_Y) {
    if(_X > _Y){
        X = _Y;
        Y = _X;
    }
}
bool Regra_entre::getEstado() {
    return RegraBase::getvalor() >= X && RegraBase::getvalor() <= Y;
}

string Regra_entre::getAsString() const {
    ostringstream os;
    os << RegraBase::getAsString();
    os << "X : " << X << "Y : " << Y << " | fum: entre" << endl;
    return os.str();
}
Regra_entre::~Regra_entre() {}