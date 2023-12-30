//
// Created by 35193 on 22/12/2023.
//

#include "Regra_fora.h"
#include <sstream>
Regra_fora::Regra_fora(weak_ptr<Sensor> _sensor,const double &X, const double &Y) : RegraBase(_sensor), X(X), Y(Y) {
    if(X > Y){
        this->X = Y;
        this->Y = X;
    }
}
bool Regra_fora::getEstado() {
    return RegraBase::getvalor() < X || RegraBase::getvalor() > Y;
}
string Regra_fora::getAsString() const {
    ostringstream os;
    os << RegraBase::getAsString();
    os << "X : " << X << " Y : " << Y << " | fum: fora" << endl;
    return os.str();
}
unique_ptr<RegraBase> Regra_fora::clone() {
    return make_unique<Regra_fora>(*this);
}