#ifndef PROJECTCASA_COMANDO_H
#define PROJECTCASA_COMANDO_H

#include <iostream>
#include <vector>

using namespace std;

class Comando {
public:
    Comando();
    void setNome(string _nome);
    void setNumArg(int _numArg);
    void setCorpo(string _corpo);
    void setSintaxe(string _sintaxe);
    [[nodiscard]]
    bool avaliaCmd();
    [[nodiscard]]
    string descricao();
    ~Comando();
private:
    [[nodiscard]]
    string vectorToString();

    string nome;
    vector<string> corpo;
    int numArg;
    string sintaxe;
};


#endif //PROJECTCASA_COMANDO_H
