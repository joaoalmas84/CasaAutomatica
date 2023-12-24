#include "Zona.h"

#include <iostream>
#include <optional>
#include <sstream>
#include <algorithm>
#include <cctype>
#include "Aquecedor.h"
using namespace std;

// inicialiar as var static;;
int Zona::baseId = 1;


                    //////////////////////////////////////////////////////////////////
                    /////////// Comandos para gerir habitação e zonas/////////////////
                    //////////////////////////////////////////////////////////////////

Zona::Zona(string  nomeDaZona): tilulo(std::move(nomeDaZona)), id(baseId++){iniciarPropriedadesDefault();}

// info
string Zona::getAsStringSimple() const {
    ostringstream os;
    os << "S: " << numeroDeSensores();
    os << " || P : " << numeroDeProcessadores();
    os << " || A : " << numeroDeAparelhos() <<  endl;
    int cont = 0;
    for(auto props : propriedades){
        os << props.first.at(0) << ": "  << props.second->getValor() << " ";
        cont++;
        if(cont % 3 == 0){
            os << endl;
        }
    }
    return os.str();
}

string Zona::getAsString() const {
    ostringstream os;
    os << "Zona: " << id << endl;
    os << "A : " << numeroDeAparelhos() <<  endl;
    for (auto a: aparelhos) {
        //os << "\ta" << a-> << " // nome sensor // " << "estado: " << s->getvalor();
    }
    os << "S : " << numeroDeSensores() <<  endl;
    for (auto s: sensores) {
        os << "\t" << s->getAsString();
    }
    os << "P : " << numeroDeProcessadores() <<  endl;
    for (auto p: processadores) {
        os << "\t" << p->getAsSting();//<< p->();
    }
    return os.str();
}

string Zona::propsAsString() const {
    ostringstream os;
    os << "Zona: " << id << endl;
    for(auto props : propriedades){
        os << "propriedade: " << props.second->getid() << " : " << props.first << " valor: " << props.second->getValor() << endl;
    }
    return os.str();
}

int Zona::getId() const {
    return id;
}

bool Zona::addAparelho(const string &tipo) {
    string tipotoupper = tipo;
    transform(tipotoupper.begin(), tipotoupper.end(), tipotoupper.begin(), [](unsigned char c){ return std::toupper(c); });
    if(tipotoupper == "AQUECEDOR"){

        ///// temporatio // temporatio // temporatio // temporatio // temporatio // temporatio // temporatio
        Propriedade *tem = nullptr, *rui = nullptr;
        for(auto p : propriedades){
            if(p.first == "Temperatura"){
                tem = p.second.get();
            }
            if(p.first == "Ruido"){
                rui = p.second.get();
            }
        }
        ///// temporatio // temporatio // temporatio // temporatio // temporatio // temporatio // temporatio // temporatio
        aparelhos.push_back(make_shared<Aquecedor>(tem, rui));
    }
    return true;
}

int Zona::getNumeroPropriedades() const {
    return (int)propriedades.size();
}

//propriedade
bool Zona::addPropriedade(const string& nomeDaPropriedades, optional<double> min) {
    if (propriedades.find(nomeDaPropriedades) != propriedades.end()) {
        return false;
    }
    propriedades[nomeDaPropriedades] = make_shared<Propriedade>(min);
    return true;
}

bool Zona::addPropriedade(const string& nomeDaPropriedades, optional<double> min, optional<double> max) {
    if (propriedades.find(nomeDaPropriedades) != propriedades.end()) {
        return false;
    }
    propriedades[nomeDaPropriedades] = make_shared<Propriedade>(min, max);
    return true;
}

bool Zona::addPropriedade(const string& nomeDaPropriedades) {
    if (propriedades.find(nomeDaPropriedades) != propriedades.end()) {
        return false;
    }
    propriedades[nomeDaPropriedades] = make_shared<Propriedade>();
    return true;
}

bool Zona::setPropriedades(const string& nomeDaPropriedades, int valor) {
    if (propriedades.find(nomeDaPropriedades) == propriedades.end()) {
        return false;
    }
    if(valor < 0){
        propriedades[nomeDaPropriedades]->diminuiValor((-valor));
    }else{
        propriedades[nomeDaPropriedades]->aumentaValor(valor);
    }
    return true;
}

// Sensor
bool Zona::addSensor(const string &propsNome) {
    if (propriedades.find(propsNome) == propriedades.end()) {
        return false;
    }
    sensores.push_back(make_shared<Sensor>(weak_ptr<Propriedade>(propriedades[propsNome])));
    return true;
}

bool Zona::addProcessador(const string& comando) {
    processadores.push_back(make_shared<Processador>(id, comando));
    return true;
}

bool Zona::addRegrasPorc(const int idProc,int idsensor, const string &funcao, const vector<double>& valores) {
    auto it = processadores.begin();
    while (it != processadores.end()) {
        if ((*it)->getid() == idProc) {
            break;
        }
        ++it;
    }
    auto it2 = sensores.begin();
    while (it2 != sensores.end()){
        if ((*it2)->getid() == idsensor) {
            break;
        }
        ++it2;
    }
    if(it != processadores.end() && it2 != sensores.end()) {
        (*it)->addRegra(funcao, weak_ptr<Sensor>(*it2), valores);
        return true;
    } else {
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

int Zona::numeroDeSensores() const {
    return sensores.size();
}

int Zona::numeroDeAparelhos() const {
    return aparelhos.size();
}

int Zona::numeroDeProcessadores() const {
    return processadores.size();
}

Zona::~Zona() {
    sensores.clear();
    processadores.clear();
    aparelhos.clear();
}

//private
void Zona::iniciarPropriedadesDefault(){
    int min[] = {-273, 0};
    int max[] = {100};

    propriedades["Temperatura"] = make_shared<Propriedade>(min[0]);
    propriedades["Luz"] = make_shared<Propriedade>(min[1]);
    propriedades["Radiacao"] = make_shared<Propriedade>(min[1]);
    propriedades["Vibracao"] = make_shared<Propriedade>(min[1]);
    propriedades["Humidade"] = make_shared<Propriedade>(min[1], max[0]);
    propriedades["Fumo"] = make_shared<Propriedade>(min[1], max[0]);
    propriedades["Som"] = make_shared<Propriedade>(min[1]);
}