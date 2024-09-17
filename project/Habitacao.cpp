#include "Habitacao.h"
#include "Zona.h"

#include <sstream>

/***************************************** Public *****************************************/


                        ///////////////////////////////////////////////////////////////////
                        /////////// Comandos para gerir habitação e zonas//////////////////
                        ///////////////////////////////////////////////////////////////////

Habitacao::Habitacao(const Habitacao &Habitacao): linhas(Habitacao.linhas), colunas(Habitacao.colunas) {
    zonas = new Zona **[linhas];

    for (int i = 0; i < linhas; ++i) {
        zonas[i] = new Zona *[colunas];
    }

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if(Habitacao.zonas[i][j] != nullptr){
                zonas[i][j] = new Zona(*Habitacao.zonas[i][j]);
            }else{
                zonas[i][j] = nullptr;
            }
        }
    }
    for(auto &p : Habitacao.processadorsalva){
        processadorsalva[p.first] = make_shared<Processador>(*p.second);
    }
}
Habitacao::Habitacao(const int &_linhas, const int &_colunas): linhas(_linhas), colunas(_colunas) {
    zonas = new Zona **[linhas];

    for (int i = 0; i < linhas; ++i) {
        zonas[i] = new Zona *[colunas];
    }

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            zonas[i][j] = nullptr;
        }
    }
}

Habitacao::~Habitacao() {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            delete zonas[i][j];
        }
    }
    for (int i = 0; i < linhas; ++i) {
        delete[] zonas[i];
    }
    delete[] zonas;
}

void Habitacao::add_Zona(const int &linha, const int &coluna) {
    if (!validaCoord(coluna, linha)) {
        throw "Zona está fora dos limites da habitação";
    }
    if (zonas[linha][coluna] != nullptr) {
        throw "Ja existe uma Zona nesse lugar";
    }

    zonas[linha][coluna] = new Zona("sala");
}


void Habitacao::removerZona(const int &idZonaARemover) {
    // verificar se existe esta zona
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if(zonas[i][j] != nullptr) {
                if (zonas[i][j]->getId() == idZonaARemover) {
                    delete zonas[i][j];
                    zonas[i][j] = nullptr;
                    return;
                }
            }
        }
    }
}

string Habitacao::getAsStringSimple() const {
    ostringstream os;
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if(zonas[i][j] != nullptr){
                os << "zona: " << zonas[i][j]->getId() << endl;
                os << "\t" << zonas[i][j]->getAsStringSimple() << endl;
            }
        }
    }
    return os.str();
}

int Habitacao::getNumZonas() const {
    int numZonas = 0;
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if(zonas[i][j] != nullptr){
                numZonas++;
            }
        }
    }
    return numZonas;
}

Zona* Habitacao::get_ptrZona(int linha, int coluna) const {
    if (linha < linhas || coluna < colunas) {

    }
    return zonas[linha][coluna];
    return nullptr;
}

string Habitacao::zlista() const {
    ostringstream os;
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if(zonas[i][j] != nullptr){
                os << "zona: " << zonas[i][j]->getId() << endl;
                os << zonas[i][j]->getAsStringSimple() << endl;
            }
        }
    }
    return os.str();
}

string Habitacao::zcomp(const int &IDzona) const {
    for (int i = 0; i < linhas; ++i) {
        for ( int j = 0; j < colunas; ++j) {
            if(zonas[i][j] != nullptr) {
                if (zonas[i][j]->getId() == IDzona){
                    return zonas[i][j]->getAsString();
                }
            }
        }
    }
    return "zona nao existe";
}
string Habitacao::zprops(const int &IDzona) const {
    for (int i = 0; i < linhas; ++i) {
        for ( int j = 0; j < colunas; ++j) {
            if(zonas[i][j] != nullptr) {
                if (zonas[i][j]->getId() == IDzona){
                    return zonas[i][j]->propsAsString();
                }
            }
        }
    }
    return "zona nao existe";
}

bool Habitacao::pmod(const int &IDzona, const string &nomeDaPropriedade, const int &valor) {
    for (int i = 0; i < linhas; ++i) {
        for ( int j = 0; j < colunas; ++j) {
            if(zonas[i][j] != nullptr) {
                if (zonas[i][j]->getId() == IDzona){
                    return zonas[i][j]->setPropriedades(nomeDaPropriedade, valor);
                }
            }
        }
    }
    return false;
}

bool Habitacao::cnovo_sensor(const int &IDzona, const string &tipo) {
    for (int i = 0; i < linhas; ++i) {
        for ( int j = 0; j < colunas; ++j) {
            if(zonas[i][j] != nullptr) {
                if (zonas[i][j]->getId() == IDzona){
                    return zonas[i][j]->addSensor(tipo);
                }
            }
        }
    }
    return false;
}

bool Habitacao::cnovo_aparelho(const int &IDzona, const string &tipo) {
    for (int i = 0; i < linhas; ++i) {
        for ( int j = 0; j < colunas; ++j) {
            if(zonas[i][j] != nullptr) {
                if (zonas[i][j]->getId() == IDzona){
                    return zonas[i][j]->addAparelho(tipo);
                }
            }
        }
    }
    return false;
}
bool Habitacao::cnovo_processador(const int &IDzona, const string &tipo) {
    for (int i = 0; i < linhas; ++i) {
        for ( int j = 0; j < colunas; ++j) {
            if(zonas[i][j] != nullptr) {
                if (zonas[i][j]->getId() == IDzona){
                    return zonas[i][j]->addProcessador(tipo);
                }
            }
        }
    }
    return false;
}

bool Habitacao::crem(const int &IDzona, const string& tipo, const int &id) {
    for (int i = 0; i < linhas; ++i) {
        for ( int j = 0; j < colunas; ++j) {
            if(zonas[i][j] != nullptr) {
                if (zonas[i][j]->getId() == IDzona){
                    if(tipo == "a"){
                        zonas[i][j]->eleminarAparelho(id);
                        return true;
                    }else if(tipo == "p"){
                        zonas[i][j]->eleminarProcessador(id);
                        return true;
                    }else if(tipo == "s"){
                        zonas[i][j]->eleminarSensor(id);
                        return true;
                    }else{
                        return false;
                    }
                }
            }
        }
    }
    return false;
}

bool Habitacao::rnova(const int &IDzona, const int &idproce, const string &funcao, const int& idsensor ,const vector<double> &valores){
    for (int i = 0; i < linhas; ++i) {
        for ( int j = 0; j < colunas; ++j) {
            if(zonas[i][j] != nullptr) {
                if (zonas[i][j]->getId() == IDzona){
                    return zonas[i][j]->addRegrasPorc(idproce, idsensor , funcao, valores);
                }
            }
        }
    }
    return false;
}

bool Habitacao::asoc(const int &IDzona, const int &idproce, const int &idaparelho) {
    for (int i = 0; i < linhas; ++i) {
        for ( int j = 0; j < colunas; ++j) {
            if(zonas[i][j] != nullptr) {
                if (zonas[i][j]->getId() == IDzona){
                    return zonas[i][j]->asoc(idproce, idaparelho);
                }
            }
        }
    }
    return false;
}

bool Habitacao::pmuda(const int &IDzona, const int & idproce, const string &novoComando) {
    for (int i = 0; i < linhas; ++i) {
        for ( int j = 0; j < colunas; ++j) {
            if(zonas[i][j] != nullptr) {
                if (zonas[i][j]->getId() == IDzona){
                    return zonas[i][j]->pmuda(idproce, novoComando);
                }
            }
        }
    }
    return false;
}

string Habitacao::rlista(const int &IDzona, const int &idproce) const {
for (int i = 0; i < linhas; ++i) {
        for ( int j = 0; j < colunas; ++j) {
            if(zonas[i][j] != nullptr){
                if (zonas[i][j]->getId() == IDzona){
                    return zonas[i][j]->rlista(idproce);
                }
            }
        }
    }
    throw "Zona nao existe";
}

bool Habitacao::rrem(const int &IDzona, const int &idproce, const int &idregra) {
for (int i = 0; i < linhas; ++i) {
        for ( int j = 0; j < colunas; ++j) {
            if(zonas[i][j] != nullptr){
                if (zonas[i][j]->getId() == IDzona){
                    return zonas[i][j]->rrem(idproce, idregra);
                }
            }
        }
    }
    return false;
}

bool Habitacao::ades(const int &IDzonam, const int &IDproc, const int &regra) {
    for (int i = 0; i < linhas; ++i) {
        for ( int j = 0; j < colunas; ++j) {
                if(zonas[i][j] != nullptr){
                    if (zonas[i][j]->getId() == IDzonam){
                        return zonas[i][j]->ades(IDproc, regra);
                    }
                }
        }
    }
    return false;
}

bool Habitacao::acom(const int &IDzona, const int &IDaparelho, const string &comdando) {
for (int i = 0; i < linhas; ++i) {
        for ( int j = 0; j < colunas; ++j){
            if(zonas[i][j] != nullptr){
                if (zonas[i][j]->getId() == IDzona){
                    return zonas[i][j]->acom(IDaparelho, comdando);
                }
            }
        }
    }
    return false;
}

void Habitacao::prox() {
    for (int i = 0; i < linhas; ++i) {
        for ( int j = 0; j < colunas; ++j){
            if(zonas[i][j] != nullptr){
                zonas[i][j]->prox();
            }
        }
    }
}

bool Habitacao::psalva(const int &IDzona, const int &idproce, const string &nome) {

    if(processadorsalva.find(nome) != processadorsalva.end()){
        return false;
    }
    for (int i = 0; i < linhas; ++i) {
        for ( int j = 0; j < colunas; ++j){
            if(zonas[i][j] != nullptr){
                if (zonas[i][j]->getId() == IDzona){
                    auto aux = zonas[i][j]->psalva(idproce);
                    if(aux != nullptr){
                        processadorsalva[nome] = aux;
                        return true;
                    }else{
                        return false;
                    }
                }
            }
        }
    }
    return false;
}

string Habitacao::plista() const {
    ostringstream os;
    for(auto &p : processadorsalva){
        os << "\t"<< p.first << endl;
        os << p.second->getAsSting() << endl;
    }
    return os.str();
}

void Habitacao::prem(const string &nome) {
    processadorsalva.erase(nome);
}

void Habitacao::prepoe(const string &nome) {
    auto proc = processadorsalva.find(nome);
    if(proc == processadorsalva.end()){
        throw "Processador nao existe";
    }
    for (int i = 0; i < linhas; ++i) {
        for ( int j = 0; j < colunas; ++j){
            if(zonas[i][j] != nullptr){
                if (zonas[i][j]->getId() == proc->second->getidzona()){
                    zonas[i][j]->prepoe(make_shared<Processador>(*(proc->second)));
                    return;
                }
            }
        }
    }

    throw "Zona do proc nao existe :(";

}



                            //////////////////////////////////////////////////////////////////
                            /////////// Comandos para gerir habitação e zonas/////////////////
                            //////////////////////////////////////////////////////////////////



[[nodiscard]]
int Habitacao::getLin() {return linhas;}

[[nodiscard]]
int Habitacao::getCol() {return colunas;}

bool Habitacao::validaCoord(int col, int lin) const {
    if (col < 0 || lin < 0) {return false;}
    if (col >= colunas || lin >= linhas) {return false;}
    return true;
}