#include "Aquecedor.h"

/***************************************** Public *****************************************/

Aquecedor::Aquecedor(Propriedade* temperatura, Propriedade* ruido): Aparelho(){
    addProp("Temperatura", temperatura);
    addProp("Ruido", ruido);
}

void Aquecedor::liga() {
    Aparelho::liga();

    try {
        aumentaProp("Temperatura", 3);
    } catch(string err) {cout << err;}

    try {
        aumentaProp("Ruido", 5);
    } catch(string err) {cout << err;}
}

void Aquecedor::desliga() {
    Aparelho::desliga();
    try {
        diminuiProp("Ruido", getPropValue("Ruido"));
    } catch(string err) {cout << err;}
}
void Aquecedor::mudaEstado(const std::string &nome) {
    if(nome == "ligar"){
        liga();
    }
}
/***************************************** Private *****************************************/
