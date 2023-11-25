#include "Zona.h"

#include <iostream>
#include <optional>
#include <sstream>
#include <algorithm>

using namespace std;

// inicialiar as var static;;
int Zona::baseId = 1;


                    //////////////////////////////////////////////////////////////////
                    /////////// Comandos para gerir habitação e zonas/////////////////
                    //////////////////////////////////////////////////////////////////

Zona::Zona(string  nomeDaZona): tilulo(std::move(nomeDaZona)), id(baseId++){iniciarPropriedadesDefault();}

// info
string Zona::getAsString() const {

    ostringstream os;
    os << "componente do tipo : sensores" << endl;
    for (auto s: sensores) {
        os << "s" << s->getid() << " // nome sensor // " << "estado: " << s->getvalor() << endl;
    }
    os << "componente do tipo : processadores" << endl;
    for (auto p: processadores) {
        os << "s" << p->getid() << " // nome sensor // " << "estado: " << endl;//<< p->();
    }
    os << "componente do tipo : aparelhos" << endl;
    for (auto a: aparelhos) {
        //os << "s" << s->getid() << " // nome sensor // " << "estado: " << s->getvalor();
    }

    return os.str();
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

bool Zona::addRegrasPorc(const int idProc,int idsensor, const std::string &funcao, optional<double> x, optional<double> y) {
    //
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

void Zona::eleminarSensor(int _id) {
        sensores.erase(std::remove_if(sensores.begin(), sensores.end(), [&_id](const std::shared_ptr<Sensor>& s) {
            cout << s->getid() << " ";return s->getid() == _id;}), sensores.end());
}

void Zona::eleminarProcessador(int _id) {
    processadores.erase(remove_if(processadores.begin(), processadores.end(), [&_id](const shared_ptr<Processador> & p){
        return  p->getid() == _id;}), processadores.end());
}

Zona::~Zona() {
    for (auto pro: propriedades) {
        delete pro.second;
    }
    sensores.clear();
    processadores.clear();
    aparelhos.clear();
}

int Zona::numeroDeSensores() const {
    return sensores.size();
}

int Zona::numeroDeAparelhos() const {
    return aparelhos.size();
}

int Zona::numeroDeProcessadores() const {
    return processadores.size();
}