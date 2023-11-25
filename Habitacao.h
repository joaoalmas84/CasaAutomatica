//
// Created by 35193 on 21/11/2023.
//

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
    Zona* get_idZona(int linha, int coluna) const;
    //zlista
    string zlista() const;

                        //////////////////////////////////////////////////////////////////
                        /////////// Comandos para gerir habitação e zonas/////////////////
                        //////////////////////////////////////////////////////////////////

    [[nodiscard]]
    string zcomp (const int &IDzona) const;





};


#endif //OOP_TRABALHO_HABITACAO_H
