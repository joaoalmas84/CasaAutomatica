//
// Created by 35193 on 09/11/2023.
//

#ifndef OOP_TRABALHO_ZONA_H
#define OOP_TRABALHO_ZONA_H
#include "Propriedade.h"
#include "Sensor.h"
#include "Processador.h"
#include <string>
#include <map>
#include <vector>

using namespace std;
class Zona {
    static int baseId;
    const int id;
    string tilulo;
    map<string, Propriedade*> propriedades;
    vector<Sensor*> sensores;
    vector<Processador*> processadores;


public:

    ////////////////////////////construtores da class zona
    explicit Zona(string nomeDaZona = "zona sem nome");
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

    bool addRegrasPorc(int idProc,int idsensor, const std::string &funcao, optional<double> x, optional<double> y = {});

    string listaPropriedades() const;



private:
    void iniciarPropriedadesDefault();

};


#endif //OOP_TRABALHO_ZONA_H
