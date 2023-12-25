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
    [[nodiscard]]
    string getAsStringSimple()const;
    [[nodiscard]]
    int getNumZonas()const;
    [[nodiscard]]
    Zona* get_ptrZona(int linha, int coluna)const;
    //zlista
    [[nodiscard]]
    string zlista() const;
    [[nodiscard]]
    string zprops(const int &IDzona) const;
    [[nodiscard]]
    bool pmod(const int &IDzona, const string &nomeDaPropriedade, const int &valor);
    [[nodiscard]]
    bool cnovo_sensor(const int &IDzona, const string &tipo);
    bool cnovo_aparelho(const int &IDzona, const string &tipo);
    bool cnovo_processador(const int &IDzona, const string &tipo);
    bool crem(const int &IDzona, const string &tipo, const int &id);
    bool rnova(const int &IDzona, const int &idproce, const string &funcao, const int& idsensor ,const vector<double> &valores);
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
