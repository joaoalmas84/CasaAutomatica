//
// Created by 35193 on 30/10/2023.
//

#ifndef POO_ZONA_H
#define POO_ZONA_H
#include "Sensor.h"
#include "Propriedade.h"
#include "Processador.h"
#include <string>
#include <map>
#include <iostream>
#include <vector>

using namespace std;

class Zona {
    static int CONT;
    const int ID;
    string nome;
    vector<Sensor*> sensores;
    vector<Processador> processador;
    //vector<Aparelho*> Aparelho;
    map<string, Propriedade> propriedades;


public:

    //sobre a class Zona
    Zona(string nome = "Sem Nome");
    Zona(bool Default, string nome = "sem Nome");
    string getAsString() const;
    int get_NumSensor() const;


    // sobre as class SENSOR
    double getValor_propriedade(string chave);
    void setValor_Propriedades(string nomeDaPropriedades, int valor);
    bool redefineValor_setValor_Propriedades(string nomeDaPropriedades, int valor);
    void setPropriedade(string nomeDaPropriedades, optional<double> min);
    void setPropriedade(string nomeDaPropriedades, optional<double> min, optional<double> max);
    void setPropriedade(string nomeDaPropriedades);
    void setPropriedade_max(string nomeDaPropriedades, optional<double> max);
    bool addSensor(Sensor & Asensor);


    bool addProcessador(Processador & Aprocessador );
    void addAparelho();

    void removeSensor(int id);
    void removeProcessador(int id);
    void removeAparelho(int id);

private:
    void iniciarPropriedadesDefault();






};


#endif //POO_ZONA_H
