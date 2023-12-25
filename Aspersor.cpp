#include "Aspersor.h"

/***************************************** Public *****************************************/
Aspersor::Aspersor(shared_ptr<Propriedade> humidade, shared_ptr<Propriedade> vibracao, shared_ptr<Propriedade> fumo) : Aparelho() {
    addProp("Humidade", humidade);
    addProp("Vibracao", vibracao);
    addProp("Fumo", fumo);
}

void Aspersor::liga() {
    Aparelho::liga();
    try {
        aumentaProp("Humidade", 50);
    } catch(string err) {cout << err;}

    try {
        aumentaProp("Vibracao", 100);
    } catch(string err) {cout << err;}

    try {
        diminuiProp("Fumo", getPropValue("Fumo"));
    } catch(string err) {cout << err;}
}

void Aspersor::desliga() {
    Aparelho::desliga();
    try {
        diminuiProp("Vibracao", 100);
    } catch(string err) {cout << err;}
}

void Aspersor::mudaEstado(const std::string &nome) {
    if (nome == "ligar") {liga();}
    else if (nome == "desligar") {desliga();}
}

/***************************************** Private *****************************************/
