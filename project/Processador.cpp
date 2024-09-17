#include "Processador.h"
#include "Sensor.h"
#include "Regra_Igual.h"
#include "Regra_entre.h"
#include "Regra_menor.h"
#include "Regra_maior.h"
#include "Regra_fora.h"

#include <iostream>
#include <sstream>
#include <memory>
#include <algorithm>

using namespace std;

int Processador::baseId = 0;

Processador::Processador(const Processador &p) : id(p.id), idzona(p.idzona), comando(p.comando) {
    for(auto &r : p.regras){
        regras.push_back(r->clone());
    }

    for(auto &aparelho : p.aparelhos){
        aparelhos.push_back(aparelho);
    }
}

Processador::Processador(const int &_idzona, const string &_comando) : id(baseId++), idzona(_idzona), comando(_comando) {}

Processador::~Processador() {
    regras.clear();
}

bool Processador::addRegra(const string & funcao, weak_ptr<Sensor> sensor, const vector<double> &valores) {
    if (funcao == "igual") {
        regras.push_back(make_unique<Regra_Igual>(sensor, valores[0]));
        return true;
    }else if(funcao == "maior"){
        regras.push_back(make_unique<Regra_maior>(sensor, valores[0]));
        return true;
    }else if(funcao == "menor"){
        regras.push_back(make_unique<Regra_menor>(sensor, valores[0]));
        return true;
    }else if(funcao == "entre"){
        if(valores.size() < 2)
            return false;
        regras.push_back(make_unique<Regra_entre>(sensor, valores[0], valores[1]));
        return true;
    }else if(funcao == "fora"){
        if(valores.size() < 2)
            return false;
        regras.push_back(make_unique<Regra_fora>(sensor, valores[0], valores[1]));
        return true;
    }
    return false;
}

string Processador::getAsSting() const {
    ostringstream os;
    os << "p" << id << " | func: " << comando << " | estado: " << testar() << endl;
    os << " | num regras: " << regras.size() << " : "<< endl;
    for (auto &r : regras){
        os <<r->getAsString();
    }
    if(!aparelhos.empty())
        os << "Aparelhos: " << endl;
    else
        os << "Sem Aparelhos" << endl;
    for(auto &aparelho : aparelhos){
        if(aparelho.lock() != nullptr){
            if(aparelho.lock() != nullptr){
                os << aparelho.lock()->getid() << " | ";
            }
        }
    }
    return os.str();
}

bool Processador::testar() const {
    bool test = true;
    int algumaRegra = 0;
    for(auto &R : regras){
        if(R->temSensor()) {
            algumaRegra++;
            if (!R->getEstado())
                test = false;
        }
    }
    return algumaRegra > 0 && test;
}

int Processador::getid() const {
    return id;
}

int Processador::getidzona() const {
    return idzona;
}

void Processador::alteraEstada() {
    bool estado = true;
    int algumaRegra = 0;
    for(auto &R : regras){
        if(R->temSensor()) {
            algumaRegra++;
            if (!R->getEstado())
                estado = false;
        }
    }
    if(algumaRegra > 0 && estado){
        for(auto &aparelho : aparelhos){
            if(aparelho.lock() != nullptr){
                aparelho.lock()->mudaEstado(comando);
            }
        }
    }
}

void Processador::eleminarRegra(int idRegra) {
    regras.erase(remove_if(regras.begin(), regras.end(),[&idRegra](unique_ptr<RegraBase> &ptrRegra){return ptrRegra->getId() == idRegra;}), regras.end());
}

void Processador::addAparelho(weak_ptr<Aparelho> _aparelhos) {
    auto it = find_if(aparelhos.begin(), aparelhos.end(), [&_aparelhos](weak_ptr<Aparelho> &aparelho){
        return aparelho.lock()->getid() == _aparelhos.lock()->getid();});

    if(it != aparelhos.end()){
        return;
    }

    aparelhos.push_back(_aparelhos);
}

void Processador::setComando(const string &_comando) {
    this->comando = _comando;
}

string Processador::getRegraAsString() const {
    ostringstream os;
    for(auto &R : regras){
        os << R->getAsString();
    }
    return os.str();
}

void Processador::removerRegra(const int &idRegra) {
    regras.erase(remove_if(regras.begin(), regras.end(), [&idRegra](const auto& regra){
        return regra->getId() == idRegra;}), regras.end());
}

void Processador::removerAparelho(const int& idAparelho) {
    aparelhos.erase(remove_if(aparelhos.begin(), aparelhos.end(), [&idAparelho](const auto& aparelho){
        return aparelho.lock()->getid() == idAparelho;}), aparelhos.end());
}