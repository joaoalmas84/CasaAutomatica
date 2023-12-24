#ifndef CODIGOFONTE_APARELHO_H
#define CODIGOFONTE_APARELHO_H

#include "Propriedade.h"

#include <iostream>
#include <memory>
#include <map>

using namespace std;

class Aparelho {
    static int baseID;
    int id;
    bool ligado;
    map<string, Propriedade*> props;

public:
    Aparelho() : id(baseID++), ligado(false) {props.clear();}
    virtual void liga();
    virtual void desliga();
    void addProp(string nome, Propriedade* ptr);
    void aumentaProp(string nome, int val);
    void diminuiProp(string nome, int val);
    int getPropValue(string nome)const;
    virtual void mudaEstado(const string& nome) = 0;
    virtual ~Aparelho() = 0;
private:
    bool findProp(string nome);

};


#endif //CODIGOFONTE_APARELHO_H
