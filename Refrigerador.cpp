#include "Refrigerador.h"

/***************************************** Public *****************************************/
Refrigerador::Refrigerador(shared_ptr<Propriedade> temperatura, shared_ptr<Propriedade> ruido) : Aparelho() {
    addProp("Temperatura", temperatura);
    addProp("Ruido", ruido);
}

void Refrigerador::liga() {
    Aparelho::liga();
    try {
        diminuiProp("Temperatura", 1);
    } catch(string err) {cout << err;}

    try {
        aumentaProp("Ruido", 20);
    } catch(string err) {cout << err;}
}

void Refrigerador::desliga() {
    Aparelho::desliga();
    try {
        diminuiProp("Ruido", 20);
    } catch(string err) {cout << err;}
}

void Refrigerador::mudaEstado(const string & nome) {
    if (nome == "ligar") {liga();}
    else if (nome == "desligar") {desliga();}
}

/***************************************** Private *****************************************/
