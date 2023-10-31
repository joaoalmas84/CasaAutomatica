#ifndef CODIGOFONTE_UTILS_H
#define CODIGOFONTE_UTILS_H

#include <iostream>
#include <vector>

using namespace std;


const vector <string> comandos = {"prox", "avanc", "hnova", "hrem", "znova", "zrem", "zlista", "zcomp", "zprops", "pmod","cnovo",
                                  "crem", "rnova", "pmuda", "rlista", "rrem", "asoc", "ades", "acom", "psalva", "prepoe", "prem",
                                  "plista", "exec", "sair"};

const vector <int> nArgs = {0, 1, 2, 0, 2, 1, 0, 1, 1, 3, -1,3, -1, -1, 2, 3, 3, 3, -1, 3, 1, 1, 0, 1, 0};

const vector <string> spa = {"s", "p", "a"};

const vector <string> stx = {"prox",
                             "avanc <n>",
                             "hnova <num linhas> <num colunas>",
                             "hrem",
                             "znova <linha> <coluna>",
                             "zrem <ID zona>",
                             "zlista",
                             "zcomp <ID zona>",
                             "zprops <ID zona>",
                             "pmod <ID zona> <nome> <valor>",
                             "cnovo <ID zona> <s | p | a> <tipo | comando>",
                             "crem <ID zona> <s | p | a> <ID>",
                             "rnova <ID zona> <ID proc. regras> <regra> <ID sensor> [param1] [param2] [...]",
                             "pmuda <ID zona> <ID proc. regras> <novo comando>",
                             "rlista <ID zona> <ID proc. regras>",
                             "rrem <ID zona> <ID proc. regras> <ID regra>",
                             "asoc <ID zona> <ID proc. regras> <ID aparelho>",
                             "ades <ID zona> <ID proc. regras> <ID aparelho>",
                             "acom <ID zona> <ID aparelho> <comando>",
                             "psalva <ID zona> <ID proc. regras> <nome>",
                             "prepoe <nome>",
                             "prem <nome>",
                             "plista",
                             "exec <nome de ficheiro>",
                             "sair"};


const vector <string> sensores = {"temperatura", "movimento", "luminosidade", "radiação", "radiação", "humidade", "som", "fumo"};

const vector <string> sensoresLetra = {"t", "v", "m", "d", "h", "o", "f"};

const vector <string> sensoresProp = {"Temperatura", "Vibração", "Luz", "Radiação", "Humidade", "Som", "Fumo"};


const vector <string> aparelhos = {"aquecedor", "aspersor", "refrigerador", "lampada"};

const vector <string> aparelhosLetra = {"a", "s", "r", "l"};


#endif //CODIGOFONTE_UTILS_H
