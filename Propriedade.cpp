#include "Propriedade.h"

#include <optional>
#include <map>

/***************************************** Public *****************************************/
int Propriedade::baseId = 0;

Propriedade::Propriedade(optional<double> min, optional<double> max) : minimo(min), maximo(max), valor(0), id(baseId++) {
    if (minimo.has_value() && maximo.has_value())
        if (minimo > maximo){
            tie(minimo, maximo) = make_tuple(maximo, minimo);
        }
}

//Propriedade::Propriedade(optional<double> max, bool escolha): minimo({}), maximo(max), valor(0){}

void Propriedade::aumentaValor(double val) {
    if (has_max()) {
        if (getValor() == getmax()) {return;}
        else if ((valor += val) >= getmax()) {
            valor = getmax();
            return;
        } else {valor += val;}
    }
}

void Propriedade::diminuiValor(double val) {
    if (has_min()) {
        if (getValor() == getmin()) {return;}
        else if ((valor -= val) <= getmin()) {
            valor = getmin();
            return;
        } else {valor -= val;}
    }
}

double Propriedade::getValor() const {return valor;}

bool Propriedade::has_max() const {return maximo.has_value();}

bool Propriedade::has_min() const {return minimo.has_value();}

double Propriedade::getmax() const {
    if (maximo.has_value())
        return maximo.value();
    else
        throw "erro nao ha maximo";
}

double Propriedade::getmin() const {
    if (minimo.has_value())
        return minimo.value();
    else
        throw "erro nao ha minimo";
}

int Propriedade::getid() const {return id;}


/***************************************** Private *****************************************/
