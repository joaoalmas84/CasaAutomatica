#include "Lampada.h"

/***************************************** Public *****************************************/
Lampada::Lampada(shared_ptr<Propriedade> iluminacao) : Aparelho() {
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

void Lampada::mudaEstado(const string & nome) {
    if (nome == "ligar") {liga();}
    else if (nome == "desligar") {desliga();}
}
/***************************************** Private *****************************************/
