#include "Processador.h"
#include "Sensor.h"
#include "Regra_Igual.h"
#include "Regra_entre.h"
#include "Regra_menor.h"
#include "Regra_maior.h"
#include "Regra_fora.h"
#include <iostream>
#include <sstream>
#include <optional>

using namespace std;

int Processador::baseId = 0;

Processador::Processador(const int &_idzona, const string &_comando) : id(baseId++), idzona(_idzona), comando(_comando){}

Processador::~Processador(){
    regras.clear();
}

bool Processador::addRegra(const string & funcao, weak_ptr<Sensor> sensor, const vector<double> &valores) {
    if(funcao == "igual"){
        regras.push_back(make_unique<Regra_Igual>(sensor, valores[0]));
        return true;
    }else if(funcao == "maior"){
        regras.push_back(make_unique<Regra_maior>(sensor, valores[0]));
        return true;
    }else if(funcao == "menor"){
        regras.push_back(make_unique<Regra_menor>(sensor, valores[0]));
        return true;
    }else if(funcao == "entre"){
        regras.push_back(make_unique<Regra_entre>(sensor, valores[0], valores[1]));
        return true;
    }else if(funcao == "fora"){
        regras.push_back(make_unique<Regra_fora>(sensor, valores[0], valores[1]));
        return true;
    }
    return false;
}

[[nodiscard]]
string Processador::getAsSting() const {
    ostringstream os;
    os << "p" << id << " num regras: " << regras.size() << endl;
    for (auto &r : regras){
        os << "\t" <<r->getAsString();
    }
    return os.str();
}

[[nodiscard]]
bool Processador::testar() const {
    bool test = true;
    for(auto &R : regras){
        if(!R->getEstado())
            test = false;
    }
    return test;
}

[[nodiscard]]
int Processador::getid() const {
    return id;
}

void Processador::eleminarRegra(int idRegra) {
    regras.erase(remove_if(regras.begin(), regras.end(),[&idRegra](unique_ptr<RegraBase> &ptrRegra){return ptrRegra->getId() == idRegra;}), regras.end());
}