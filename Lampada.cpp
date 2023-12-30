#include "Lampada.h"

/***************************************** Public *****************************************/
Lampada::Lampada(weak_ptr<Propriedade> iluminacao) : Aparelho() {
    addProp("Iluminacao", iluminacao);
}

void Lampada::liga() {
    if(getligado()){ // se ja estiver ligado, nao faz nada
        return;
    }

    Aparelho::liga();
    try {
        aumentaProp("Iluminacao", 900);
    } catch(const char* err) {}
}

void Lampada::desliga() {
    if(!getligado()){ // se ja estiver desligado, nao faz nada
        return;
    }

    Aparelho::desliga();
    try {
        diminuiProp("Iluminacao", 900);
    } catch(const char* err) {}
}

void Lampada::mudaEstado(const string & nome) {
    if (nome == "ligar") {liga();}
    else if (nome == "desligar") {desliga();}
}

void Lampada::prox() {}

shared_ptr<Aparelho> Lampada::clone() {
    return make_shared<Lampada>(*this);
}
/***************************************** Private *****************************************/
