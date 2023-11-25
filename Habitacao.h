#ifndef OOP_TRABALHO_HABITACAO_H
#define OOP_TRABALHO_HABITACAO_H

#include "Zona.h"

class Habitacao {
public:
    //hnova <num linhas> <num colunas>
    Habitacao(const int &_linhas,const int &_colunas);
    //hrem
    ~Habitacao();
    //znova <linha> <coluna>
    void add_Zona(const int &linha,const int &coluna);
    //zrem <ID zona>
    void removerZona(const int &idZonaARemover);
    Zona* get_idZona(int linha, int coluna) const;
    //zlista
    string zlista() const;

                        //////////////////////////////////////////////////////////////////
                        /////////// Comandos para gerir habitação e zonas/////////////////
                        //////////////////////////////////////////////////////////////////

    [[nodiscard]]
    string zcomp (const int &IDzona) const;

private:
    Zona ***zonas;
    int linhas;
    int colunas;
};


#endif //OOP_TRABALHO_HABITACAO_H
