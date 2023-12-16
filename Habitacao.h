#ifndef OOP_TRABALHO_HABITACAO_H
#define OOP_TRABALHO_HABITACAO_H

#include "Zona.h"

class Habitacao {
    Zona ***zonas;
    int linhas;
    int colunas;

public:
    //hnova <num linhas> <num colunas>
    Habitacao(const int &_linhas,const int &_colunas);
    //hrem
    ~Habitacao();
    //znova <linha> <coluna>
    void add_Zona(const int &linha,const int &coluna);
    //zrem <ID zona>
    void removerZona(const int &idZonaARemover);
    Zona* get_ptrZona(int linha, int coluna)const;
    //zlista
    string zlista() const;

                        //////////////////////////////////////////////////////////////////
                        /////////// Comandos para gerir habitação e zonas/////////////////
                        //////////////////////////////////////////////////////////////////

    [[nodiscard]]
    string zcomp (const int &IDzona) const;
    [[nodiscard]]
    int getLin();
    [[nodiscard]]
    int getCol();
private:
    [[nodiscard]]
    bool validaCoord(int col, int lin)const;
};


#endif //OOP_TRABALHO_HABITACAO_H
