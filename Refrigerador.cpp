#include "Refrigerador.h"

/***************************************** Public *****************************************/
Refrigerador::Refrigerador(weak_ptr<Propriedade> temperatura, weak_ptr<Propriedade> ruido) : instantes(3){
    addProp("Temperatura", temperatura);
    addProp("Ruido", ruido);
}

void Refrigerador::liga() {
    if(getligado()){ // se ja estiver ligado, nao faz nada
        return;
    }

    Aparelho::liga();
    /*
    try {
        diminuiProp("Temperatura", 1);
    } catch(string err) {cout << err;}
    */
    try {
        aumentaProp("Ruido", 20);
    } catch(const char* err) {}
}

void Refrigerador::desliga() {
    if(!getligado()){ // se ja estiver desligado, nao faz nada
        return;
    }

    Aparelho::desliga();
    try {
        diminuiProp("Ruido", 20);
    } catch(const char* err) {}
}

void Refrigerador::mudaEstado(const string & nome) {
    if (nome == "ligar") {liga();}
    else if (nome == "desligar") {desliga();}
}

void Refrigerador::prox() {
    if(getligado()){
        instantes--;
        if(instantes <= 0){
            try {
                diminuiProp("Temperatura", 1);
            } catch(const char* err) {}
            instantes = 3;
        }
    }
}

/***************************************** Private *****************************************/
