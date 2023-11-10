#ifndef PROJECTCASA_COMANDO_H
#define PROJECTCASA_COMANDO_H

#include <iostream>
#include <vector>

using namespace std;

class Comando {
public:
    Comando();
    void setId(int _id);
    void setNome(string _nome);
    void setNumArg(int _numArg);
    void setCorpo(string _corpo);
    void setSintaxe(string _sintaxe);
    [[nodiscard]]
    int validaCmd(string cmd);// return 0 -> valido; 1 -> invalido; 2 -> falta argumentos; 3 -> excesso de argumentos;
    [[nodiscard]]
    bool validaStx();
    void execCmd();
    [[nodiscard]]
    string descricao();
    ~Comando();
private:
    [[nodiscard]]
    int countArgs(string cmd);
    [[nodiscard]]
    string vectorToString();
    [[nodiscard]]
    bool isIntegerString(string str);
    [[nodiscard]]
    int isInVector(vector<string> v, string str); // Devolve -1 se nao encontrar str. Se encontrar devolve o indice da posicao

    int id;
    string nome;
    vector<string> corpo;
    int numArg;
    string sintaxe;
};


#endif //PROJECTCASA_COMANDO_H
