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
    map<string, shared_ptr<Propriedade>> props;

public:
    Aparelho() : id(baseID++), ligado(false) {props.clear();}
    virtual void liga();
    virtual void desliga();
    virtual string getAsString()const;
    string listProps()const;
    int getid()const;
    void addProp(string nome, shared_ptr<Propriedade> ptr);
    void aumentaProp(string nome, int val);
    void diminuiProp(string nome, int val);
    int getPropValue(string nome)const;
    virtual void mudaEstado(const string & nome) = 0;
    virtual ~Aparelho() = 0;
private:
};


#endif //CODIGOFONTE_APARELHO_H
