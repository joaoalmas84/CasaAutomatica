#include "Habitacao.h"
#include "Zona.h"

#include <sstream>

/***************************************** Public *****************************************/


                        ///////////////////////////////////////////////////////////////////
                        /////////// Comandos para gerir habitação e zonas//////////////////
                        ///////////////////////////////////////////////////////////////////

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
                os << "\t" << zonas[i][j]->getAsStringSimple();
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