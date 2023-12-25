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

void Aparelho::addProp(string nome, shared_ptr<Propriedade> ptr) {
    props.emplace(make_pair(nome, ptr));
}

void Aparelho::aumentaProp(string nome, int val) {
    string err = "Propriedade nao encontrada.";
    auto it = props.find(nome);

    if (it == props.end()) {throw err;}

    it->second->aumentaValor(val);
}

int Aparelho::getid() const {return id;}

void Aparelho::diminuiProp(string nome, int val) {
    string err = "Propriedade nao encontrada.";
    auto it = props.find(nome);

    if (it == props.end()) {throw err;}

    it->second->diminuiValor(val);
}

int Aparelho::getPropValue(string nome) const {
    string err = "Propriedade nao encontrada.";
    auto it = props.find(nome);

    if (it == props.end()) {throw err;}

    return it->second->getValor();
}

Aparelho::~Aparelho() {
    props.clear();
}

/***************************************** Private *****************************************/

