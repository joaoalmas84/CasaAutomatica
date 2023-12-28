#include "Aquecedor.h"

/***************************************** Public *****************************************/

Aquecedor::Aquecedor(weak_ptr<Propriedade> temperatura, weak_ptr<Propriedade> ruido): instantes(3) {
    addProp("Temperatura", temperatura);
    addProp("Ruido", ruido);
}

void Aquecedor::liga() {
    if(getligado()){
        return;
    }

    Aparelho::liga();
    try {
        aumentaProp("Ruido", 5);
    } catch(const char* err){}
}

void Aquecedor::desliga() {

    if(!getligado()){
        return;
    }

    Aparelho::desliga();
    try {
        diminuiProp("Ruido", 5);
        instantes = 3;
    } catch(const char* err){}
}

void Aquecedor::mudaEstado(const string & nome) {
    if (nome == "ligar") {liga();}
    else if (nome == "desligar") {desliga();}
}

void Aquecedor::prox(){
    if(getligado()){
        instantes--;
        if(instantes <= 0){
            if(getPropValue("Temperatura") < 50){
                aumentaProp("Temperatura", 1);
                instantes = 3;
            }
        }
    }
}
/***************************************** Private *****************************************/
