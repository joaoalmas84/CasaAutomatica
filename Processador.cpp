//
// Created by 35193 on 10/11/2023.
//

#include "Processador.h"
#include <sstream>
int Processador::baseId = 0;
Processador::Processador(): id(baseId++) {}

bool Processador::addRegra(const string & funcao, shared_ptr<Sensor> sensor, optional<double> x, optional<double> y){
    regras.push_back(new Regra(funcao, sensor, x, y));
    return true;
}

string Processador::getAsSting() const {
    ostringstream os;
    os << "Processador id: " << id <<endl;
    os << "numero de regras: " << regras.size() << endl;
    for (auto r : regras){
        os << "\t" <<r->getAsString();
    }
    return os.str();
}

bool Processador::testar() const {
    bool test = true;
    for(auto R : regras){
        if(!R->getValorDaRegra())
            test = false;
    }
    return test;
}

int Processador::getid() const {
    return id;
}