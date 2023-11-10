//
// Created by 35193 on 09/11/2023.
//

#include "Propriedade.h"
#include <map>
#include <sstream>
int Propriedade::baseId = 0;

Propriedade::Propriedade(optional<double> min, optional<double> max): minimo(min), maximo(max), valor(0), id(baseId++){
    if (minimo.has_value() && maximo.has_value())
        if (minimo > maximo){
            tie(minimo, maximo) = make_tuple(maximo, minimo);
        }

}

//Propriedade::Propriedade(optional<double> max, bool escolha): minimo({}), maximo(max), valor(0){}

void Propriedade::definirValor(double valorA) {

    if(minimo.has_value() && maximo.has_value()){
        if(valor + valorA < minimo.value())
            valor = minimo.value();
        else if(valor + valorA > maximo.value())
            valor = maximo.value();
        else
            valor += valorA;

    }else if(minimo.has_value()){
        if(valor + valorA < minimo.value())
            valor = minimo.value();
        else
            valor += valorA;

    }else if(maximo.has_value()){
        if(valor + valorA > maximo.value())
            valor = maximo.value();
        else
            valor += valorA;

    }else
        valor += valorA;
}

double Propriedade::getValor() const {
    return valor;
}
bool Propriedade::has_max() const{
    return minimo.has_value();
}
bool Propriedade::has_min() const{
    return maximo.has_value();
}

double Propriedade::getmax() const{
    if (maximo.has_value())
        return maximo.value();
    else
        throw "erro nao ha maximo";
}
double Propriedade::getmin() const{
    if (minimo.has_value())
        return minimo.value();
    else
        throw "erro nao ha minimo";
}
int Propriedade::getid() const {
    return id;
}