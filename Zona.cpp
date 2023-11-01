//
// Created by 35193 on 30/10/2023.
//

#include "Zona.h"
#include <sstream>
#include <optional>
using namespace std;

int Zona::CONT = 0;

    Zona::Zona(string nome): nome(nome), ID(CONT + 1){
        CONT++;
        iniciarPropriedadesDefault();
    }

    Zona::Zona(bool Default, string nome):ID(CONT + 1){
        CONT++;
        iniciarPropriedadesDefault();
    }

    double Zona::getValor_propriedade(string chave){
        if (propriedades.find(chave) != propriedades.end()) {
            return propriedades[chave].obterValor();
        }else
            throw "Nao existe essa propriedade";
    }

    string Zona::getAsString() const{
      ostringstream os;
        os << nome << endl;
        os <<" ID ZONA : "<< ID << endl;
        for(const auto& par : propriedades){
            os <<" propriedade : "<< par.first << ": " << par.second.obterValor() << endl;
        }
        for(const Sensor* p : sensores){
            os <<" sensores = " << p << endl;
        }
        return os.str();
    }

    void Zona::setValor_Propriedades(string nomeDaPropriedades, int valor){
        propriedades[nomeDaPropriedades].definirValor(valor);
    }

    void Zona::setPropriedade(string nomeDaPropriedades, optional<double> min){
        propriedades[nomeDaPropriedades] = Propriedade(min);
    }

    void Zona::setPropriedade_max(string nomeDaPropriedades, optional<double> max){
        propriedades[nomeDaPropriedades] = Propriedade(max);
    }

    void Zona::setPropriedade(string nomeDaPropriedades, optional<double> min, optional<double> max){
        propriedades[nomeDaPropriedades] = Propriedade(min, max);
    }

    void Zona::setPropriedade(string nomeDaPropriedades){
        propriedades[nomeDaPropriedades] = Propriedade();
    }

    void Zona::iniciarPropriedadesDefault(){
        vector<string> nome = {"Temperatura", "Luz", "Radiacao", "Vibracao", "Humidade", "Fumo", "Som"};
        propriedades["Temperatura"] = Propriedade(-273);
        propriedades["Luz"] = Propriedade(0);
        propriedades["Radiacao"] = Propriedade(0);
        propriedades["Vibracao"] = Propriedade(0);
        propriedades["Humidade"] = Propriedade(0, 100);
        propriedades["Fumo"] = Propriedade(0, 100);
        propriedades["Som"] = Propriedade(0);
    }

    bool Zona::addSensor(Sensor & Asensor){
        bool encontrado = false;

        for (auto elemento : sensores) {
            if (elemento == &Asensor) {
                encontrado = true;
                break; // Se encontrado, saia do loop
            }
        }
        if(encontrado){
            sensores.push_back(&Asensor);
            return true;
        }else{
            return false;
        }
    }

    bool Zona::addProcessador(Processador & Aprocessador ){
        bool encontrado = false;

        for (auto elemento : processador) {
            if (elemento == Aprocessador) {
                encontrado = true;
                break; // Se encontrado, saia do loop
            }
        }
        if(encontrado){
            processador.push_back(Aprocessador);
            return true;
        }else{
            return false;
        }
    }
