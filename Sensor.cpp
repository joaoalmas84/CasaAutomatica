#include "Sensor.h"
#include "Propriedade.h"

#include <iostream>
#include <sstream>

using namespace std;

int Sensor::baseId = 0;

Sensor::Sensor(weak_ptr<Propriedade> propriedade): propriedade(propriedade), id(baseId++){medir();}

Sensor::~Sensor() {}

[[nodiscard]]
int Sensor::getid() const {
    return id;
}

[[nodiscard]]
double Sensor::getvalor(){
    return ultimaMedicao;
}

[[nodiscard]]
string Sensor::getAsString() const {
    ostringstream os;
    os << "s" << id << " ||  Estado: " << ultimaMedicao << endl;
    return os.str();
}

bool Sensor::medir() {
    shared_ptr<Propriedade> propriedade = this->propriedade.lock();
    if(!propriedade){
        throw "Erro: O sensor não tem nenhuma propriedade associada.";
    }
    ultimaMedicao = propriedade->getValor();
    return true;
}

void Sensor::prox() {
    medir();
}
