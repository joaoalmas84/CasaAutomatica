#include "Processador.h"
#include "Sensor.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <optional>

using namespace std;

int Processador::baseId = 0;

Processador::~Processador(){
    regras.clear();
}

bool Processador::addRegra(const string & funcao, shared_ptr<Sensor> sensor, optional<double> x, optional<double> y) {
    regras.push_back(make_unique<Regra>(funcao, sensor, x, y));
    return true;
}

[[nodiscard]]
string Processador::getAsSting() const {
    ostringstream os;
    os << "Processador id: " << id <<endl;
    os << "numero de regras: " << regras.size() << endl;
    for (auto &r : regras){
        os << "\t" <<r->getAsString();
    }
    return os.str();
}

[[nodiscard]]
bool Processador::testar() const {
    bool test = true;
    for(auto &R : regras){
        if(!R->getValorDaRegra())
            test = false;
    }
    return test;
}

[[nodiscard]]
int Processador::getid() const {
    return id;
}

void Processador::eleminarRegra(int idRegra) {
    regras.erase(remove_if(regras.begin(), regras.end(),[&idRegra](unique_ptr<Regra> &ptrRegra){return ptrRegra->getId() == idRegra;}), regras.end());
}