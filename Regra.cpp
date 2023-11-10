//
// Created by 35193 on 09/11/2023.
//

#include "Regra.h"
#include <sstream>
int Regra::baseId = 0;

Regra::Regra(const std::string &_funcao, Sensor* _sensor, optional<double> _x, optional<double> _y)
            :id(baseId++), funcao(_funcao), sensor(_sensor), x(_x), y(_y){}

bool Regra::getValorDaRegra() const {
    if(funcao == "igual"){
        return igual();
    }else if(funcao == "menor"){
        return menor();
    }else if(funcao == "maior"){
        return maior();
    }else if(funcao == "entre"){
        return entre();
    }else if(funcao == "naoEstre"){
        return naoEstre();
    }else{
        return false;
    }
}

bool Regra::igual() const {
    return sensor->getvalor() == x;
}
bool Regra::menor() const {
    return sensor->getvalor() < x;
}
bool Regra::maior() const {
    return sensor->getvalor() > x;
}
bool Regra::entre() const {
    return sensor->getvalor() > x && sensor->getvalor() < y;
}
bool Regra::naoEstre() const {
    return sensor->getvalor() < x || sensor->getvalor() > y;
}

string Regra::getAsString() const {
    ostringstream os;
    os << "id Da Regra: " << id << endl;
    os << "Regra " << id << " x: " << x.value() << endl;
    if(y.has_value())
        os << "Regra " << id << " y: " << y.value() << endl;
    os << "funcao : " << funcao << endl;
    return os.str();
}