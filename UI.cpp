#include "UI.h"
#include "Terminal.h"
#include "Comando.h"

#include <sstream>
#include <fstream>

using namespace term;

/***************************************** Public *****************************************/

UI::UI(): t(Terminal::instance()), dimx(t.getNumCols()), dimy(t.getNumRows()), linhas(0), colunas(0), dadosW(nullptr), dimzonasy((dimy - 3) / 4), dimzonasx((dimy - 3) / 4 * 3){
    habitacao = nullptr;
    numdados = 0;
    ini_cor();
    cmdW = ini_cmd_UI();
    *cmdW << set_color(3) <<move_to(0,0) << "Comando -> ";
    dadosW = ini_dadosW_UI();
}

UI::~UI() {
    deleteZonasWindow();
    delete dadosW;
    delete cmdW;
    delete habitacao;
}

/************************************************ Gestão da parte gráfica ************************************************/

Window *UI::ini_cmd_UI() {
    return new Window(0, dimy - 3, dimx, 3);
}

Window *UI::ini_dadosW_UI() {
    delete dadosW;
    numdados = 0;
    return new Window(dimzonasx*colunas, 0, dimx - (dimzonasx*colunas), dimy-3);
}

void UI::ini_cor(){
    for(int i=1; i<20; i++) {
        t.init_color(i, i, 0);
    }
}

void UI::atulizar_cmdW() {
    cmdW->clear();
    *cmdW << set_color(3) << move_to(0,0) << "Comando -> ";
}

void UI::criarZonasWindow() {
    zonasW = new Window **[linhas];

    for (int i = 0; i < linhas; ++i) {
        zonasW[i] = new Window *[colunas];
    }

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            zonasW[i][j] = nullptr;
        }
    }
}

void UI::deleteZonasWindow() {

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            delete zonasW[i][j];
        }
    }

    for (int i = 0; i < linhas; ++i) {
        delete[] zonasW[i];
    }

    delete[] zonasW;
}



void UI::atualizar_zonas_UI(const int &linha, const int &coluna) {
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            if(habitacao->get_ptrZona(i, j) != nullptr){

                if(zonasW[i][j] == nullptr)
                    zonasW[i][j] = new Window(j*dimzonasx, i*dimzonasy, dimzonasx, dimzonasy);

                (zonasW[i][j])->clear();
                *(zonasW[i][j]) << set_color(3) << move_to(0, 0) << habitacao->get_ptrZona(i, j)->getId();
                *(zonasW[i][j]) << set_color(3) << move_to(0, 1) << ""<< habitacao->get_ptrZona(i, j)->getAsStringSimple();

            }else if(zonasW[i][j] != nullptr){
                    delete zonasW[i][j];
                    zonasW[i][j] = nullptr;
                }
        }
    }
}

/********************************************************************************************************************************/

void UI::START() {
    string cmd;
    int res = 0;
    int i = 0;

    *dadosW << set_color(5) << move_to(0 , numdados++) << "\t\t\t\tBem Vindo\nAs dimensoes de uma habitacao tem obrigatoriamente de estar entre 2x2 e 4x4\n\tUma zona nao pode estar fora da habitacao";

    while (res != 1) {
        cleandados();
        cmd = getCmd();
        if (i == 0) {
            dadosW = ini_dadosW_UI();
        }
        i++;
        res = commandLine(cmd);
        cleandados();
    }
}

string UI::getCmd() {
    string cmd;
    (*cmdW) >> cmd;
    atulizar_cmdW();
    return cmd;
}

int UI::commandLine(string cmd) {
    istringstream iss(cmd);
    string s1, s2;
    iss >> s1 >> s2;
    int res;

    if (s1 == "exec") {
        res = exec(s2);
        if (res == 1) {return res;}
    }

    Comando c(cmd);
    *dadosW << set_color(5) << move_to(0, numdados++) << cmd;
    switch (c.validaCmd()) {
        case 0:
            bool flag;
            if (c.validaStx()) {
                if (c.SAIR()) {return 1;}

                vector <string> inputAux = c.getVectorInput();

                switch (c.getIndex()) {
                    case 2:
                        if (habitacao == nullptr) { // <- Habitação ainda não existe
                            if (c.hnova()) {
                                linhas = stoi(inputAux[1]);
                                colunas = stoi(inputAux[2]);
                                habitacao = new Habitacao(linhas, colunas);
                                criarZonasWindow();
                                dadosW =ini_dadosW_UI();
                            } else {
                                *dadosW << set_color(5) << move_to(0, numdados++) << "Dimensoes invalidas";
                            }
                        } else { // <- Habitação já existe
                            *dadosW << set_color(5) << move_to(0, numdados++) << "Ja existe uma habitacao";
                        }
                        break;
                    case 3:
                        if (habitacao != nullptr) {
                            delete habitacao;
                            habitacao = nullptr;
                            linhas = 0;
                            colunas = 0;
                            deleteZonasWindow();
                            dadosW = ini_dadosW_UI();
                            *dadosW << set_color(5) << move_to(0, numdados++) << "\t\t\t\tBem Vindo\nAs dimensoes de uma habitacao tem obrigatoriamente de estar entre 2x2 e 4x4\n\tUma zona nao pode estar fora da habitacao";
                        }
                        break;
                    case 4:
                        if (habitacao != nullptr) { // <- Habitação já existe
                            int linhasTemp, colunasTemp;
                            if (c.znova(habitacao)) {
                                linhasTemp = stoi(inputAux[1]);
                                colunasTemp = stoi(inputAux[2]);
                                try{
                                    habitacao->add_Zona(linhasTemp, colunasTemp);
                                    atualizar_zonas_UI(linhas, colunas);
                                }catch(const char* exce){
                                    *dadosW << set_color(5) << move_to(0, numdados++) << exce;
                                }
                            } else {
                                *dadosW << set_color(5) << move_to(0, numdados++) << "Dimensoes invalidas";
                            }
                        } else { // <- Habitação ainda não existe
                            *dadosW << set_color(3) << move_to(0, numdados++) << "Habitacao ainda nao existe";
                        }
                        break;
                    case 5:
                        if (habitacao != nullptr) { // <- Habitação já existe
                            //teste a mudar
                            int idzona;

                            if (c.zrem()) {
                                idzona = stoi(inputAux[1]);
                                try{
                                    habitacao->removerZona(idzona);
                                    atualizar_zonas_UI(linhas, colunas);
                                }catch(const char* exce){
                                    *dadosW << set_color(5) << move_to(0, numdados++) << exce;
                                }
                            }
                        } else { // <- Habitação ainda não existe
                            *dadosW << set_color(3) << move_to(0, numdados++) << "Habitacao ainda nao existe";
                        }
                        break;
                    case 6:
                        if(habitacao != nullptr) {
                            *dadosW << set_color(5) << move_to(0, numdados) << habitacao->zlista();
                            numdados += habitacao->getNumZonas()*2;
                        }
                        break;
                    case 10:
                        if (inputAux[2] == "s" && c.procuraEmVector(sensores, inputAux[3]) == -1) {
                            *dadosW << set_color(3) << move_to(0, numdados++) << "Sensor desconhecido";
                        }
                        if (inputAux[2] == "a" && c.procuraEmVector(aparelhos, inputAux[3]) == -1) {
                            *dadosW << set_color(3) << move_to(0, numdados++) << "Aparelho desconhecido";
                        }
                        break;
                    case 11:
                        if (inputAux[2] == "s" && c.procuraEmVector(sensores, inputAux[3]) == -1) {
                            *dadosW << set_color(3) << move_to(0, numdados++) << "Sensor desconhecido";
                        }
                        if (inputAux[2] == "a" && c.procuraEmVector(aparelhos, inputAux[3]) == -1) {
                            *dadosW << set_color(3) << move_to(0, numdados++) << "Aparelho desconhecido";
                        }
                    default:
                        break;
                }
            } else {
                *dadosW << set_color(19) << move_to(0, numdados++) << "Sintaxe invalida";
            }
            break;

        case 1:
            *dadosW << set_color(19) << move_to(0, numdados++) << "Comando nao encontrado";
            break;
        case 2:
            *dadosW << set_color(19) << move_to(0, numdados++) << "Argumentos a menos";
            break;
        case 3:
            *dadosW << set_color(19) << move_to(0, numdados++) << "Argumentos a mais";
            break;
        default:
            break;
    }
    // Comando c é destruido aqui
    return 0;
}

[[nodiscard]]
int UI::exec(string fileName)  {
    ifstream ifs(fileName);
    string line;
    int n = 0, res = 0;

    if(!ifs.is_open()) {return -1;}

    while (!ifs.eof()) {
        getline(ifs, line);
        res = commandLine(line);
        n++;
    }

    ifs.close();

    return res;
}

vector<string> UI::stringToVector(string str) {
    vector<string> v;
    istringstream iss(str);
    string s;

    while (!iss.fail()) {
        iss >> s;
        v.push_back(s);
    }

    return v;
}

/***************************************** Private *****************************************/


bool UI::isIntegerString(string s) const {
    istringstream iss(s);
    int n;

    iss >> n;
    if (iss.fail()) {return false;}

    return true;
}
void UI::cleandados() {
    if (numdados + 8 >= dimy - 4){
        numdados = 0;
        dadosW->clear();
    }
}


bool UI::isIntegerString(initializer_list<string> list) const {
    int n;

    for (const string & s : list) {
        istringstream iss(s);
        iss >> n;
        if (iss.fail()) {return false;}
    }

    return true;
}

