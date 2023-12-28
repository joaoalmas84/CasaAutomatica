#include "Aparelho.h"

#include <sstream>

/***************************************** Public *****************************************/
int Aparelho::baseID = 1;

Aparelho::Aparelho(Aparelho & outro) {
    id = baseID++;
    ligado = outro.ligado;
    props.clear();
    for (const auto & pair : outro.props) {
        props.emplace(pair);
    }
}

void Aparelho::liga() {ligado = true;}

void Aparelho::desliga() {ligado = false;}

string Aparelho::getAsString() const {
    ostringstream oss;
    oss << "\nID: " << id
        << "\nEstado: " << ligado
        << listProps();
    return oss.str();
}

string Aparelho::listProps() const {
    ostringstream oss;
    oss << "\nPropriedades que afeta:";
    for (const auto & pair : props) {
       oss << '\n' << pair.first;
    }
    return oss.str();
}

void Aparelho::addProp(string nome, weak_ptr<Propriedade> &ptr) {
    props.emplace(nome, ptr);
}

void Aparelho::aumentaProp(string nome, double val) {
    auto pro = props.find(nome);
    if(pro != props.end()){
        auto ptr = pro->second;
        if(ptr.lock() != nullptr){
            ptr.lock()->aumentaValor(val);
        }
    }
}

int Aparelho::getid() const {return id;}

void Aparelho::diminuiProp(string nome, double val) {
    auto pro = props.find(nome);
    if(pro != props.end()){
        auto ptr = pro->second;
        if(ptr.lock() != nullptr){
            ptr.lock()->diminuiValor(val);
        }
    }
}

int Aparelho::getPropValue(string nome) const {
    auto it = props.find(nome);
    if (it != props.end()){
        auto ptr = it->second;
        if(ptr.lock() != nullptr){
            return ptr.lock()->getValor();
        }
    }
    throw "erro nao exisre propriedade";
}

bool Aparelho::getligado() const {return ligado;}

Aparelho::~Aparelho() {
    props.clear();
}

/***************************************** Private *****************************************/

