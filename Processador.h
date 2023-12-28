#ifndef CODIGOFONTE_PROCESSADOR_H
#define CODIGOFONTE_PROCESSADOR_H

#include "Sensor.h"
#include "Aparelho.h"

#include <iostream>
#include <memory>
#include <vector>
#include "RegraBase.h"
using namespace std;

class Processador {
    static int baseId;
    const int id;
    int idzona;// para o psalva ser mais facil;
    string comando;
    vector<unique_ptr<RegraBase>> regras;
    // ainda nao esta a ser usado para nada
    vector<weak_ptr<Aparelho>> aparelhos;

public:
    Processador(const int &_idzona,const string& _comando);
    ~Processador();
    bool addRegra(const string & funcao, weak_ptr<Sensor> sensor ,const vector<double> &valores);
    [[nodiscard]]
    string getAsSting() const;
    [[nodiscard]]
    bool testar() const;
    [[nodiscard]]
    int getid()const;
    void eleminarRegra(int idRegra);
    void alteraEstada();
    void addAparelho(weak_ptr<Aparelho> _aparelhos);
    void setComando(const string &comando);
    [[nodiscard]]
    string getRegraAsString() const;
    void removerRegra(const int &idRegra);
    void removerAparelho(const int &idAparelho);

};

#endif //CODIGOFONTE_PROCESSADOR_H
