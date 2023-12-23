#include "Lampada.h"

/***************************************** Public *****************************************/
Lampada::Lampada(Propriedade* iluminacao) {
    addProp("Iluminacao", iluminacao);
}

void Lampada::liga() {
    Aparelho::liga();

    try {
        aumentaProp("Iluminacao", 900);
    } catch(string err) {cout << err;}
}

void Lampada::desliga() {
    Aparelho::desliga();

    try {
        diminuiProp("Iluminacao", 900);
    } catch(string err) {cout << err;}
}


/***************************************** Private *****************************************/
