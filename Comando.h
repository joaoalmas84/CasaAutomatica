#ifndef CODIGOFONTE_COMANDO_H
#define CODIGOFONTE_COMANDO_H

#include "Habitacao.h"

#include <iostream>
#include <vector>

using namespace std;

class Comando {
    string nome;
    int index;
    string input;
    int numArg;

public:
    Comando(string _input) : nome(""), index(-1), input(_input), numArg(-1) {}
    [[nodiscard]]
    int getIndex();
    [[nodiscard]]
    vector <string> getVectorInput();
    [[nodiscard]]
    int validaCmd(); // 0 -> valido; 1 -> invalido; 2 -> falta argumentos; 3 -> excesso de argumentos;
    [[nodiscard]]
    bool validaStx();
    [[nodiscard]]
    bool SAIR()const;
    [[nodiscard]]
    int procuraEmVector(vector<string> v, string str)const;// <- Devolve -1 se nao encontrar str. Se encontrar devolve o indice da posicao
    [[nodiscard]]
    bool hnova();
    [[nodiscard]]
    bool znova(Habitacao* h);

private:
    [[nodiscard]]
    string getNomeCmd()const;
    [[nodiscard]]
    int countArgsCmd()const;
    [[nodiscard]]
    bool isIntegerString(string s)const;
    [[nodiscard]]
    bool isIntegerString(initializer_list<string> list)const;
    [[nodiscard]]
    vector<string> stringToVector(string str);
    [[nodiscard]]
    bool isBetween(int val, int min, int max);
};

const vector <string> comandos = {"prox", "avanc", "hnova", "hrem", "znova", "zrem", "zlista", "zcomp",
                                  "zprops", "pmod","cnovo","crem", "rnova", "pmuda", "rlista", "rrem",
                                  "asoc", "ades", "acom", "psalva", "prepoe", "prem", "plista", "exec",
                                  "sair"};

// Comandos com n_Args == -1 podem ter um número variável de argumentos
const vector <int> n_Args = {0, 1, 2, 0, 2, 1, 0, 1, 1,
                             3, 3, 3, -1, 3, 2, 3, 3,
                             3, 3, 3,1, 1, 0, 1, 0};

const vector <string> spa = {"s", "p", "a"};

const vector <string> sensores = {"temperatura", "movimento", "luminosidade", "radiacao", "humidade", "som", "fumo"};

const vector <string> sensoresLetra = {"t", "v", "m", "d", "h", "o", "f"};

const vector <string> sensoresProp = {"temperatura", "vibracao", "luz", "radiacao", "humidade", "som", "fumo"};

const vector <string> aparelhos = {"aquecedor", "aspersor", "refrigerador", "lampada"};

const vector <string> aparelhosLetra = {"a", "s", "r", "l"};


#endif //CODIGOFONTE_COMANDO_H
