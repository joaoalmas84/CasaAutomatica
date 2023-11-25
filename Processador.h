//
// Created by 35193 on 10/11/2023.
//

#ifndef OOP_TRABALHO_PROCESSADOR_H
#define OOP_TRABALHO_PROCESSADOR_H
#include "Regra.h"
#include "Aparelho.h"

#include <vector>
#include <memory>

class Processador {
    static int baseId;
    const int id;
    vector<shared_ptr<Regra>> regras;
    // ainda nao esta a ser usado para nada
    vector<weak_ptr<Aparelho>> aparelhos;
public:
    Processador();
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

#endif //OOP_TRABALHO_PROCESSADOR_H
