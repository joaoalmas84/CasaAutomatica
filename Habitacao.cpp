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
    if (linha < 0 || linha >= linhas || coluna < 0 || coluna >= colunas){
        throw "Zona está fora dos limites da habitação";
    }
    if(zonas[linha][coluna] != nullptr){
        throw "Ja existe uma Zona nesse lugar";
    }
    zonas[linha][coluna] = new Zona("sala");
}

void Habitacao::removerZona(const int &idZonaARemover) {
    // verificar se existe esta zona
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if(zonas[i][j] != nullptr)
                if(zonas[i][j]->getId() == idZonaARemover){
                    delete zonas[i][j];
                    zonas[i][j] = nullptr;
                    return;
                }
        }
    }
}

Zona* Habitacao::get_idZona(int linha, int coluna) const {
    //if(linha < linhas && coluna < colunas)
    return zonas[linha][coluna];
    return nullptr;
}

string Habitacao::zlista() const {
    ostringstream os;

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if(zonas[i][j] != nullptr) {
                os << "ID Zona: " << zonas[i][j]->getId() << endl;
                os << "numero de sensores: " << zonas[i][j]->numeroDeSensores() << endl;
                os << "numero de processadores: " << zonas[i][j]->numeroDeProcessadores() << endl;
                os << "numero de aparelhos: " << zonas[i][j]->numeroDeAparelhos() << endl;
            }
        }
    }
    return os.str();
}

                            //////////////////////////////////////////////////////////////////
                            /////////// Comandos para gerir habitação e zonas/////////////////
                            //////////////////////////////////////////////////////////////////

string Habitacao::zcomp(const int &IDzona) const {
    int i;
    int j;
    for (i = 0; i < linhas; ++i) {
        for (j = 0; j < colunas; ++j) {
            if(zonas[i][j] != nullptr) {
                if (zonas[i][j]->getId() == IDzona){
                    goto found;
                }
            }
        }
    }
    return "zona nao existe";
    found:
    return  zonas[i][j]->getAsString();
}

[[nodiscard]]
int Habitacao::getLin() {return linhas;}

[[nodiscard]]
int Habitacao::getCol() {return colunas;}
