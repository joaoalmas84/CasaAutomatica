#ifndef CODIGOFONTE_ZONA_H
#define CODIGOFONTE_ZONA_H

#include "Propriedade.h"
#include "Sensor.h"
#include "Processador.h"
#include "Aparelho.h"

#include <iostream>
#include <map>
#include <optional>

using namespace std;

class Zona {
    static int baseId;
    const int id;
    string tilulo;
    map<string, shared_ptr<Propriedade>> propriedades;
    vector<shared_ptr<Sensor>> sensores;
    vector<shared_ptr<Processador>> processadores;
    vector<shared_ptr<Aparelho>> aparelhos;

public:
    ////////////////////////////construtores da class zona
    explicit Zona(string nomeDaZona = "zona sem nome");
    [[nodiscard]]
    string getAsStringSimple()const;
    [[nodiscard]]
    string getAsString() const;
    [[nodiscard]]
    string propsAsString() const;
    [[nodiscard]]
    int getId() const;
    [[nodiscard]]
    int getNumeroPropriedades()const;

    /////////////////////// criar uma propriedade nova e mudar o valor a funcao set nao deve ser usar e sum para testar

    bool addPropriedade(const string& nomeDaPropriedades, optional<double> min);
    bool addPropriedade(const string& nomeDaPropriedades, optional<double> min, optional<double> max);
    bool addPropriedade(const string& nomeDaPropriedades);
    bool setPropriedades(const string& nomeDaPropriedades, int valor);

    ///////////////////// criar sensores
    // a funcao tem um porblema
    [[nodiscard]]
    bool addSensor(const string& propsNome);
    [[nodiscard]]
    bool addProcessador(const string& comando);
    [[nodiscard]]
    bool addAparelho(const string& tipo);
    bool addRegrasPorc(const int idProc,int idsensor, const std::string &funcao, const vector<double>& valores);
    [[nodiscard]]
    string listaPropriedades()const;

    void eleminarSensor(int id);
    void eleminarRegraPorc(const int &idProc);
    void eleminarProcessador(int id);

    // ESTE MÉTODOS SÃO PARA O MÉTODO DE DA CLASSE HABITAÇÃO
    [[nodiscard]]
    int numeroDeSensores()const;
    [[nodiscard]]
    int numeroDeAparelhos()const;
    [[nodiscard]]
    int numeroDeProcessadores()const;

    ~Zona();

private:
    void iniciarPropriedadesDefault();

};


#endif //CODIGOFONTE_ZONA_H
