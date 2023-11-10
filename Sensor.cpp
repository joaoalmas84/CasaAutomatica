//
// Created by 35193 on 09/11/2023.
//

#include "Sensor.h"
#include <sstream>
int Sensor::baseId = 0;

Sensor::Sensor(Propriedade* propriedade): propriedade(propriedade), id(baseId++){medir();}

int Sensor::getid() const {
    return id;
}

double Sensor::getvalor(){
    medir();
    return ultimaMedicao;
}

bool Sensor::medir() {
    ultimaMedicao = propriedade->getValor();
    return true;
}

string Sensor::getAsString() const {
    ostringstream os;
    os << "Sensor id: " << id << endl;
    os << "Ultima medicao: " << ultimaMedicao << endl;
    return os.str();
}