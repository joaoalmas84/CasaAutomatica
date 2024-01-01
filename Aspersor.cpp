#include "Aspersor.h"

/***************************************** Public *****************************************/
Aspersor::Aspersor(weak_ptr<Propriedade> humidade, weak_ptr<Propriedade> vibracao, weak_ptr<Propriedade> fumo): instantes(-1){
    addProp("Humidade", humidade);
    addProp("Vibracao", vibracao);
    addProp("Fumo", fumo);
}

void Aspersor::liga() {
    if(getligado()){ // se ja estiver ligado, nao faz nada
        return;
    }

    Aparelho::liga();
    instantes = 5;
    try {
        if(getPropValue("Humidade") <= 25){
            aumentaProp("Humidade", 50);
        }else{
            double val = 75 - getPropValue("Humidade");
            aumentaProp("Humidade", val);
        }
    } catch(const char* err) {}

    try {
        aumentaProp("Vibracao", 100);
    } catch(const char* err) {}

}

void Aspersor::desliga() {
    Aparelho::desliga();
    /*
    try {
        diminuiProp("Vibracao", 100);
    } catch(string err) {cout << err;}
     */
}

void Aspersor::mudaEstado(const std::string &nome) {
    if (nome == "ligar") {liga();}
    else if (nome == "desligar") {desliga();}
}

void Aspersor::prox() {

    if(instantes > 0){
        instantes--;
        if(instantes == 3){
            try {
                diminuiProp("Fumo", getPropValue("Fumo"));
            } catch(const char* err) {}
        }
    }
    if(instantes == 0 && !getligado()){
        try {
            diminuiProp("Vibracao", 100);
            instantes = -1;
        } catch(const char* err) {}
    }
}
shared_ptr<Aparelho> Aspersor::clone() {
    return make_shared<Aspersor>(*this);
}

/***************************************** Private *****************************************/
