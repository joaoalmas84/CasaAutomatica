//
// Created by 35193 on 09/11/2023.
//

#include "Zona.h"
#include <sstream>
#include <new>
#include <utility>
#include <iostream>

// inicialiar as var static;;
int Zona::baseId = 1;

// criar
Zona::Zona(string  nomeDaZona): tilulo(std::move(nomeDaZona)), id(baseId++){
    iniciarPropriedadesDefault();
}

// info
string Zona::getAsString() const {
    ////////////////////////////// colocar os nome e id da zona;
    ////////////////////////////// inumerar os propriedades;
    ////////////////////////////// inumerar os Sensores
    ostringstream dados;
    dados << "Id da zona " << tilulo << " : " << id << endl;
    int num = 0;
    for(const auto& prop : propriedades){
        dados << "Propriedades : " << num++ << "=> " << prop.first << " / " << prop.second->getValor()<<endl;
    }
    for(const auto& sens : sensores){
        dados << "Sensores : " << sens->getAsString() << endl;
    }
    for(const auto& proc : processadores){
        dados << "processadores : " << proc->getAsSting() << endl;
    }

    return dados.str();
}
int Zona::getId() const {
    return id;
}
int Zona::getNumeroPropriedades() const {
    return (int)propriedades.size();
}

//private
void Zona::iniciarPropriedadesDefault(){
    int min[] = {-273, 0};
    int max[] = {100};

    propriedades["Temperatura"] = new Propriedade(min[0]);
    propriedades["Luz"] = new Propriedade(min[1]);
    propriedades["Radiacao"] = new Propriedade(min[1]);
    propriedades["Vibracao"] = new Propriedade(min[1]);
    propriedades["Humidade"] = new Propriedade(min[1], max[0]);
    propriedades["Fumo"] = new Propriedade(min[1], max[0]);
    propriedades["Som"] = new Propriedade(min[1]);
}

//propriedade
bool Zona::addPropriedade(const string& nomeDaPropriedades, optional<double> min){
    if(propriedades.find(nomeDaPropriedades) != propriedades.end()){
        return false;
    }
    propriedades[nomeDaPropriedades] = new Propriedade(min);
    return true;
}
bool Zona::addPropriedade(const string& nomeDaPropriedades, optional<double> min, optional<double> max){
    if(propriedades.find(nomeDaPropriedades) != propriedades.end()){
        return false;
    }
    propriedades[nomeDaPropriedades] = new Propriedade(min, max);
    return true;
}
bool Zona::addPropriedade(const string& nomeDaPropriedades){
    if(propriedades.find(nomeDaPropriedades) != propriedades.end()){
        return false;
    }
    propriedades[nomeDaPropriedades] = new Propriedade();
    return true;
}
bool Zona::setPropriedades(const string& nomeDaPropriedades, int valor) {
    if(propriedades.find(nomeDaPropriedades) == propriedades.end()){
        return false;
    }
    propriedades[nomeDaPropriedades]->definirValor(valor);
    return true;
}

// Sensor
bool Zona::addSensor(const string &propsNome) {
    if(propriedades.find(propsNome) == propriedades.end()){
        return false;
    }
    sensores.push_back(make_shared<Sensor>(propriedades[propsNome]));
    return true;
}

bool Zona::addProcessador() {
    processadores.push_back(make_shared<Processador>());
    return true;
}

bool Zona::addRegrasPorc(int idProc,int idsensor, const std::string &funcao, optional<double> x, optional<double> y) {
    auto it = processadores.begin();
    while (it != processadores.end()){
        if((*it)->getid() == idProc){
            break;
        }
        ++it;
    }
    auto it2 = sensores.begin();
    while (it2 != sensores.end()){
        if((*it2)->getid() == idsensor){
            break;
        }
        ++it2;
    }
    if(it != processadores.end() && it2 != sensores.end()){
        (*it)->addRegra(funcao, (*it2), x, y);
        return true;
    }else{
        return false;
    }
}

string Zona::listaPropriedades() const {
    ostringstream os;
    for(auto props : propriedades){
        os << "propriedade: " << props.second->getid() << " : " << props.first << endl;
    }
    return os.str();
}

void Zona::eleminarSensor(int id) {
        sensores.erase(std::remove_if(sensores.begin(), sensores.end(), [&id](const std::shared_ptr<Sensor>& s) {
            return s->getid() == id;}), sensores.end());
}

void Zona::eleminarProcessador(int id) {
    processadores.erase(remove_if(processadores.begin(), processadores.end(), [&id](const shared_ptr<Processador> & p){
        return  p->getid() == id;}), processadores.end());
}

Zona::~Zona() {
    propriedades.clear();
    sensores.clear();
    processadores.clear();
}