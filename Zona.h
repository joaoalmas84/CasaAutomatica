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
public:
    ////////////////////////////construtores da class zona
    explicit Zona(string nomeDaZona = "zona sem nome");
    ~Zona();

    [[nodiscard]]
    string getAsString() const;
    [[nodiscard]]
    int getNumeroPropriedades() const;
    [[nodiscard]]
    int getId() const;

    /////////////////////// criar uma propriedade nova e mudar o valor a funcao set nao deve ser usar e sum para testar

    bool addPropriedade(const string& nomeDaPropriedades, optional<double> min);
    bool addPropriedade(const string& nomeDaPropriedades, optional<double> min, optional<double> max);
    bool addPropriedade(const string& nomeDaPropriedades);
    bool setPropriedades(const string& nomeDaPropriedades, int valor);

    ///////////////////// criar sensores
    // a funcao tem um porblema
    bool addSensor(const string& propsNome);

    bool addProcessador();

    bool addRegrasPorc(const int idProc,int idsensor, const std::string &funcao, optional<double> x, optional<double> y = {});
    [[nodiscard]]
    string listaPropriedades() const;

    void eleminarSensor(int id);
    void eleminarProcessador(int id);
    void eleminarRegraPorc(const int idProc);

    // ESTE MÉTODOS SÃO PARA O MÉTODO DE DA CLASSE HABITAÇÃO
    [[nodiscard]]
    int numeroDeSensores() const;
    [[nodiscard]]
    int numeroDeProcessadores() const;
    [[nodiscard]]
    int numeroDeAparelhos() const;

private:
    void iniciarPropriedadesDefault();

    static int baseId;
    const int id;
    string tilulo;
    map<string, Propriedade*> propriedades;
    vector<shared_ptr<Sensor>> sensores;
    vector<shared_ptr<Processador>> processadores;
    vector<shared_ptr<Aparelho>> aparelhos;
};


#endif //CODIGOFONTE_ZONA_H
