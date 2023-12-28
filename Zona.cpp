#include "Zona.h"
#include "Aquecedor.h"
#include "Aspersor.h"
#include "Refrigerador.h"
#include "Lampada.h"

#include <iostream>
#include <optional>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <memory>

using namespace std;

/***************************************** Public *****************************************/


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
    switch (procuraEmVector(nomes, tipotoupper)) {
        case -1:
            return false;
            break;
        case 0:
            return addAquecedor();
            break;
        case 1:
            return addAspersor();
            break;
        case 2:
            return addRefrigerador();
            break;
        case 3:
            return addLampada();
            break;
        default:
            return false;
            break;
    }
    return false;
}

bool Zona::asoc(const int &idproce, const int &idaparelho) {
    auto it = processadores.begin();
    while (it != processadores.end()) {
        if ((*it)->getid() == idproce) {
            break;
        }
        ++it;
    }
    auto it2 = aparelhos.begin();
    while (it2 != aparelhos.end()){
        if ((*it2)->getid() == idaparelho) {
            break;
        }
        ++it2;
    }
    if(it != processadores.end() && it2 != aparelhos.end()) {
        (*it)->addAparelho(weak_ptr<Aparelho>(*it2));
        (*it)->alteraEstada();
        return true;
    } else {
        return false;
    }
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
    if (it != processadores.end() && it2 != sensores.end()) {
        return (*it)->addRegra(funcao, weak_ptr<Sensor>(*it2), valores);
    } else {return false;}
}

string Zona::listaPropriedades() const {
    ostringstream os;
    for (auto props : propriedades) {
        os << "propriedade: " << props.second->getid() << " : " << props.first << endl;
    }
    return os.str();
}

void Zona::eleminarSensor(const int &_id) {
        sensores.erase(std::remove_if(sensores.begin(), sensores.end(), [&_id](const std::shared_ptr<Sensor>& s) {
            cout << s->getid() << " ";return s->getid() == _id;}), sensores.end());
}

void Zona::eleminarProcessador(const int &_id) {
    processadores.erase(remove_if(processadores.begin(), processadores.end(), [&_id](const shared_ptr<Processador> & p){
        return  p->getid() == _id;}), processadores.end());
}

void Zona::eleminarAparelho(const int &_id) {
    aparelhos.erase(remove_if(aparelhos.begin(), aparelhos.end(), [&_id](const shared_ptr<Aparelho> & a){
        return  a->getid() == _id;}), aparelhos.end());
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

bool Zona::pmuda(const int &idproce, const string &novoComando) {
    auto it = std::find_if(processadores.begin(), processadores.end(),[idproce](const auto& processo) {return processo->getid() == idproce;});
    if (it != processadores.end()) {
        (*it)->setComando(novoComando);
        (*it)->alteraEstada();
        return true;
    } else{
        return false;
    }
}

Zona::~Zona() {
    sensores.clear();
    processadores.clear();
    aparelhos.clear();
}

/***************************************** Private *****************************************/

void Zona::iniciarPropriedadesDefault() {
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

// Devolve -1 se nao encontrar str. Se encontrar devolve a posicao em que se encontra
int Zona::procuraEmVector(vector<string> v, string str) const {
    auto it = find(v.begin(), v.end(), str);
    if (it == v.end()) {return -1;}
    else {return distance(v.begin(), it);}
}
bool Zona::addAquecedor() {
    auto tem = propriedades["Temperatura"];
    auto rui = propriedades["Vibracao"];

    if(tem == nullptr || rui == nullptr){return false;}

    aparelhos.push_back(make_shared<Aquecedor>(tem, rui));

    return true;
}

bool Zona::addAspersor() {
    auto hum = propriedades["Humidade"];
    auto vib = propriedades["Vibracao"];
    auto fum = propriedades["Fumo"];

    if(hum == nullptr || vib == nullptr || fum == nullptr){return false;}

    aparelhos.push_back(make_shared<Aspersor>(hum, vib, fum));

    return true;
}

bool Zona::addRefrigerador() {
    auto temp = propriedades["Temperatura"];
    auto rui = propriedades["Vibracao"];

    if(temp == nullptr || rui == nullptr){return false;}

    aparelhos.push_back(make_shared<Refrigerador>(temp, rui));

    return true;
}

bool Zona::addLampada() {
    auto ilum = propriedades["Luz"];

    if(ilum == nullptr){return false;}

    aparelhos.push_back(make_shared<Lampada>(ilum));

    return true;
}