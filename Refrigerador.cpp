#include "Refrigerador.h"

/***************************************** Public *****************************************/
Refrigerador::Refrigerador(Propriedade* temperatura, Propriedade* ruido) {
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

/***************************************** Private *****************************************/
