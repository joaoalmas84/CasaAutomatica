#ifndef CODIGOFONTE_PROCESSADOR_H
#define CODIGOFONTE_PROCESSADOR_H

#include "Sensor.h"
#include "Regra.h"
#include "Aparelho.h"

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Processador {
    static int baseId;
    const int id;
    int idzona;// para o psalva ser mais facil;
    vector<unique_ptr<Regra>> regras;
    // ainda nao esta a ser usado para nada
    vector<weak_ptr<Aparelho>> aparelhos;

public:
    Processador(int _idzona);
    ~Processador();
    bool addRegra(const string & funcao, shared_ptr<Sensor> sensor , optional<double> x, optional<double> y = {});
    [[nodiscard]]
    string getAsSting() const;
    [[nodiscard]]
    bool testar() const;
    [[nodiscard]]
    int getid()const;
    void eleminarRegra(int idRegra);
};

#endif //CODIGOFONTE_PROCESSADOR_H
