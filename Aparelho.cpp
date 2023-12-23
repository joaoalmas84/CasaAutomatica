#include "Aparelho.h"

/***************************************** Public *****************************************/
int Aparelho::baseID = 1;

void Aparelho::liga() {ligado = true;}

void Aparelho::desliga() {ligado = false;}

void Aparelho::addProp(string nome, Propriedade* ptr) {
    props.insert(make_pair(nome, ptr));
}

void Aparelho::aumentaProp(string nome, int val) {
    string err = "Propriedade nao encontrada.";
    auto it = props.find(nome);

    if (it == props.end()) {throw err;}

    it->second->aumentaValor(val);
}

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

Aparelho::~Aparelho() = default;

/***************************************** Private *****************************************/
