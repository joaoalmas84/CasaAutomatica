#include "Regra.h"
#include "Sensor.h"

#include <iostream>
#include <sstream>
#include <optional>

using namespace std;

int Regra::baseId = 0;

/***************************************** Public *****************************************/

Regra::Regra(const std::string &_funcao, shared_ptr<Sensor> _sensor, optional<double> _x, optional<double> _y)
            : id(baseId++), funcao(_funcao), Psensor(_sensor), x(_x), y(_y) {}

bool Regra::getValorDaRegra() const {
    if (funcao == "igual") {
        return igual();
    } else if(funcao == "menor") {
        return menor();
    } else if(funcao == "maior") {
        return maior();
    } else if(funcao == "entre") {
        return entre();
    } else if(funcao == "naoEstre") {
        return naoEstre();
    } else {
        throw "erro essa regra nao existe";
    }
}

string Regra::getAsString() const {
    ostringstream os;
    os << "id Da Regra: " << id << endl;
    os << "Regra " << id << " x: " << x.value() << endl;

    try{os << "valor obtido : " << getValorDaRegra() << endl;}catch(const char* strcatch){os << strcatch;}
    if(y.has_value())
        os << "Regra " << id << " y: " << y.value() << endl;
    os << "funcao : " << funcao << endl;
    return os.str();
}

int Regra::getId() const {
    return id;
}

/***************************************** Private *****************************************/

bool Regra::igual() const {
    shared_ptr<Sensor> sensor = Psensor.lock();
    if(sensor){
        return sensor->getvalor() == x;
    }else{
        throw "Erro: A regra não tem nenhum sensor associado.";
    }

}
bool Regra::menor() const {
    shared_ptr<Sensor> sensor = Psensor.lock();
    if(sensor){
        return sensor->getvalor() < x;
    }else{
        throw "Erro: A regra não tem nenhum sensor associado.";
    }
}
bool Regra::maior() const {
    shared_ptr<Sensor> sensor = Psensor.lock();
    if(sensor){
        return sensor->getvalor() > x;
    }else{
        throw "Erro: A regra não tem nenhum sensor associado.";
    }
}
bool Regra::entre() const {
    shared_ptr<Sensor> sensor = Psensor.lock();
    if(sensor){
        return sensor->getvalor() > x && sensor->getvalor() < y;
    }else{
        throw "Erro: A regra não tem nenhum sensor associado.";
    }
}
bool Regra::naoEstre() const {
    shared_ptr<Sensor> sensor = Psensor.lock();
    if(sensor){
        return sensor->getvalor() < x || sensor->getvalor() > y;
    }else{
        throw "Erro: A regra não tem nenhum sensor associado.";
    }
}