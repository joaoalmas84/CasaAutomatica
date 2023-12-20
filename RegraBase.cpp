//
// Created by 35193 on 20/12/2023.
//

#include "RegraBase.h"
#include <sstream>
int RegraBase::baseId = 0;

RegraBase::RegraBase(weak_ptr<Sensor> _sensor) : id(baseId++), Psensor(_sensor){}

RegraBase::~RegraBase() = default;


int RegraBase::getvalor() const {
    shared_ptr<Sensor> sensor = Psensor.lock();
    if(sensor){
        return sensor->getvalor();
    }else{
        throw "Erro: A regra não tem nenhum sensor associado.";
    }
}

int RegraBase::getId() const {
    return id;
}

string RegraBase::getAsString() const {
    ostringstream os;
    os << "id : " << id << endl;
    shared_ptr<Sensor> sensor = Psensor.lock();
    if(sensor) {
        os << "Sensor associado : " << sensor->getAsString() << endl;
    }else{
        os << "Sensor associado : " << "Sem sensor associado" << endl;
    }
    return os.str();
}