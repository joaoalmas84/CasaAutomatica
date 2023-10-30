#ifndef PROJECTCASA_INTERFACE_H
#define PROJECTCASA_INTERFACE_H

#include <string>
#include <vector>
#include "Comando.h"
using namespace std;

const vector <string> comandos = {"prox", "avanca", "hnova", "hrem", "znova", "zrem", "zlista", "zcomp", "zprops", "pmod","cnovo",
                                   "crem", "rnova", "pmuda", "rlista", "rrem", "asoc", "ades", "acom", "psalva", "prepoe", "prem",
                                   "plista", "exec", "sair"};

const vector <int> nArgs = {0, 1, 2, 0, 2, 1, 0, 1, 1, 3, 3, 3, 99, 3, 2, 3, 3, 3, 3, 3, 1, 1, 0, 1, 0};

const vector <string> stx = {"prox", "avanc <n>", "hnova <num linhas> <num colunas>", "hrem", "znova <linha> <coluna>",
                             "zrem <ID zona>", "zlista", "zcomp <ID zona>", "zprops <ID zona>", "pmod <ID zona> <nome> <valor>",
                             "cnovo <ID zona> <s | p | a> <tipo | comando>", "crem <ID zona> <s | p | a> <ID>",
                             "rnova <ID zona> <ID proc. regras> <regra> <ID sensor> [param1] [param2] [...]",
                             "pmuda <ID zona> <ID proc. regras> <novo comando>", "rlista <ID zona> <ID proc. regras>",
                             "rrem <ID zona> <ID proc. regras> <ID regra>", "asoc <ID zona> <ID proc. regras> <ID aparelho>",
                             "ades <ID zona> <ID proc. regras> <ID aparelho>", "acom <ID zona> <ID aparelho> <comando>",
                             "psalva <ID zona> <ID proc. regras> <nome>", "prepoe <nome>", "prem <nome>", "plista",
                             "exec <nome de ficheiro>", "sair"};
void UI();
[[nodiscard]]
string getCmd();
[[nodiscard]]
int countArgs(string cmd);
[[nodiscard]]
// return 0 -> valido; 1 -> invalido; 2 -> falta argumentos; 3 -> excesso de argumentos;
int validaCmd(string cmd, Comando& c);

#endif //PROJECTCASA_INTERFACE_H
