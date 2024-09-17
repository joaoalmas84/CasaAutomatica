#include "UI.h"
#include "Terminal.h"
#include "Comando.h"

#include <sstream>
#include <fstream>

using namespace term;

/***************************************** Public *****************************************/

UI::UI(const UI &outro): t(Terminal::instance()), dimx(outro.dimx), dimy(outro.dimy), dimzonasx(outro.dimzonasx), dimzonasy(outro.dimzonasy) {
    linhas = outro.linhas;
    colunas = outro.colunas;
    numdados = outro.numdados;
    habitacao = new Habitacao(*outro.habitacao);
    instantes = outro.instantes;
    cmdW = ini_cmd_UI();
    dadosW = ini_dadosW_UI();

    zonasW = new Window **[linhas];

    for (int i = 0; i < linhas; ++i) {
        zonasW[i] = new Window *[colunas];
    }

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if(outro.zonasW[i][j] != nullptr){
                zonasW[i][j] = new Window(j*dimzonasx, i*dimzonasy, dimzonasx, dimzonasy);
            }else{
                zonasW[i][j] = nullptr;
            }

        }
    }
    atualizar_zonas_UI(linhas, colunas);
}

UI::UI(): t(Terminal::instance()), dimx(t.getNumCols()), dimy(t.getNumRows()), linhas(0), colunas(0), dadosW(nullptr), dimzonasy((dimy - 3) / 4), dimzonasx((dimy - 3) / 4 * 3), instantes(0){
    habitacao = nullptr;
    numdados = 0;
    ini_cor();
    cmdW = ini_cmd_UI();
    *cmdW << set_color(6) <<move_to(0,0) << "Comando -> ";
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
    numdados = 1;
    return new Window(dimzonasx*colunas, 0, dimx - (dimzonasx*colunas), dimy-3);
}

void UI::ini_cor(){
    for(int i=1; i<20; i++) {
        t.init_color(i, i, 0);
    }
}

void UI::atulizar_cmdW() {
    cmdW->clear();
    *cmdW << set_color(6) << move_to(0,0) << "Comando -> ";
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
                *(zonasW[i][j]) << set_color(6) << move_to(0, 0) << "zona Id: "<< habitacao->get_ptrZona(i, j)->getId();
                *(zonasW[i][j]) << set_color(6) << move_to(0, 1) << habitacao->get_ptrZona(i, j)->getAsStringSimple();

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
    *dadosW << set_color(6) << move_to((dimx-9)  / 2 , (dimy - 10) / 2 + numdados++) << "Bem Vindo";
    *dadosW << set_color(6) << move_to((dimx-75)  / 2 , (dimy -10) / 2 +numdados++) << "As dimensoes de uma habitacao tem obrigatoriamente de estar entre 2x2 e 4x4";
    *dadosW << set_color(6) << move_to((dimx-41)  / 2 , (dimy -10) / 2 +numdados++) << "Uma zona nao pode estar fora da habitacao";


    while (res != 1) {
        cmd = getCmd();
        if (i == 0) {
            dadosW = ini_dadosW_UI();
        }
        i++;
        cleandados();
        res = commandLine(cmd);
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
    *dadosW << set_color(12) << move_to(0, numdados++) << cmd;
    *dadosW << set_color(4) << move_to(0, 0) << "Instantes: " << instantes;
    switch (c.validaCmd()) {
        case 0:
            bool flag;
            if (c.validaStx()) {
                if (c.SAIR()) {return 1;}

                vector <string> inputAux = c.getVectorInput();

                switch (c.getIndex()) {
                    case 0:
                        if (habitacao != nullptr) { // <- Habitação ainda não existe
                            habitacao->prox();
                            instantes++;
                            *dadosW << set_color(4) << move_to(0, 0) << "Instantes: " << instantes;
                            atualizar_zonas_UI(linhas, colunas);
                        } else { // <- Habitação já existe
                            *dadosW << set_color(10) << move_to(0, numdados++) << "Ja existe uma habitacao";
                        }
                        break;
                    case 1:
                        if (habitacao != nullptr) { // <- Habitação ainda não existe
                            for (int i = 0; i < stoi(inputAux[1]); ++i) {
                                habitacao->prox();
                                instantes++;
                            }
                            *dadosW << set_color(4) << move_to(0, 0) << "Instantes: " << instantes;
                            atualizar_zonas_UI(linhas, colunas);
                        } else { // <- Habitação já existe
                            *dadosW << set_color(10) << move_to(0, numdados++) << "Ja existe uma habitacao";
                        }
                        break;
                    case 2:
                        if (habitacao == nullptr) { // <- Habitação ainda não existe
                            if (c.verificaDimensoes_habitacao()) {
                                linhas = stoi(inputAux[1]);
                                colunas = stoi(inputAux[2]);
                                habitacao = new Habitacao(linhas, colunas);
                                criarZonasWindow();
                                dadosW =ini_dadosW_UI();
                            } else {
                                *dadosW << set_color(10) << move_to(0, numdados++) << "Dimensoes invalidas";
                            }
                        } else { // <- Habitação já existe
                            *dadosW << set_color(10) << move_to(0, numdados++) << "Ja existe uma habitacao";
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
                            *dadosW << set_color(6) << move_to((dimx-9)  / 2 , (dimy - 10) / 2 + numdados++) << "Bem Vindo";
                            *dadosW << set_color(6) << move_to((dimx-75)  / 2 , (dimy -10) / 2 +numdados++) << "As dimensoes de uma habitacao tem obrigatoriamente de estar entre 2x2 e 4x4";
                            *dadosW << set_color(6) << move_to((dimx-41)  / 2 , (dimy -10) / 2 +numdados++) << "Uma zona nao pode estar fora da habitacao";
                        }
                        break;
                    case 4:
                        if (habitacao != nullptr) { // <- Habitação já existe
                            int linhasTemp, colunasTemp;
                            if (c.verificaDimensoes_zona(habitacao)) {
                                linhasTemp = stoi(inputAux[1]);
                                colunasTemp = stoi(inputAux[2]);
                                try{
                                    habitacao->add_Zona(linhasTemp, colunasTemp);
                                    atualizar_zonas_UI(linhas, colunas);
                                }catch(const char* exce){
                                    *dadosW << set_color(10) << move_to(0, numdados++) << exce;
                                }
                            } else {
                                *dadosW << set_color(10) << move_to(0, numdados++) << "Dimensoes invalidas " << habitacao->getLin() << " " << habitacao->getCol();
                            }
                        } else { // <- Habitação ainda não existe
                            *dadosW << set_color(10) << move_to(0, numdados++) << "Habitacao ainda nao existe";
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
                                    *dadosW << set_color(10) << move_to(0, numdados++) << exce;
                                }
                            }
                        } else { // <- Habitação ainda não existe
                            *dadosW << set_color(10) << move_to(0, numdados++) << "Habitacao ainda nao existe";
                        }
                        break;
                    case 6:
                        if(habitacao != nullptr) {
                            string texto = habitacao->zlista();
                            *dadosW << set_color(7) << move_to(0, numdados) << texto;
                            numdados += contlinhas(texto);
                        }
                        break;
                    case 7:
                        if(habitacao != nullptr) {
                            string texto = habitacao->zcomp(stoi(inputAux[1]));
                            *dadosW << set_color(7) << move_to(0, numdados) << texto;
                            numdados += contlinhas(texto);
                        }
                        break;
                    case 8:
                        if (habitacao != nullptr) { // <- Habitação já existe
                            int idzona;

                            if (c.zrem()) {
                                idzona = stoi(inputAux[1]);
                                    string texto = habitacao->zprops(idzona);
                                    *dadosW << set_color(7) << move_to(0, numdados) << texto;
                                    numdados += contlinhas(texto);
                            }
                        } else { // <- Habitação ainda não existe
                            *dadosW << set_color(10) << move_to(0, numdados++) << "Habitacao ainda nao existe";
                        }
                        break;
                    case 9:
                        if (habitacao != nullptr) { // <- Habitação já existe
                            if(habitacao->pmod(stoi(inputAux[1]), inputAux[2], stoi(inputAux[3]))){
                                *dadosW << set_color(7) << move_to(0, numdados++) << "Propriedade alterada";
                                atualizar_zonas_UI(linhas, colunas);
                            }else{
                                *dadosW << set_color(10) << move_to(0, numdados++) << "Nao foi possivil alterar a propridade";
                            }
                        } else { // <- Habitação ainda não existe
                            *dadosW << set_color(10) << move_to(0, numdados++) << "Habitacao ainda nao existe";
                        }

                        break;
                    case 10:

                        if(habitacao != nullptr){
                            // falta verificacao  de erros !
                            // e so um teste para ver se  funcionar

                            if(inputAux[2] == "s"){
                                if(habitacao->cnovo_sensor(stoi(inputAux[1]), inputAux[3])) {
                                    *dadosW << set_color(7) << move_to(0, numdados++) << "Sensor adicionado";
                                }else{
                                    *dadosW << set_color(10) << move_to(0, numdados++) << "erro a adicionar sensor";
                                }
                            }else if(inputAux[2] == "a"){
                                if(habitacao->cnovo_aparelho(stoi(inputAux[1]), inputAux[3])) {
                                    *dadosW << set_color(7) << move_to(0, numdados++) << "aparelho adicionado";
                                }else{
                                    *dadosW << set_color(10) << move_to(0, numdados++) << "erro a adicionar aparelho";
                                }
                            } else if(inputAux[2] == "p"){
                                if(habitacao->cnovo_processador(stoi(inputAux[1]), inputAux[3])) {
                                    *dadosW << set_color(7) << move_to(0, numdados++) << "processador adicionado";
                                }else{
                                    *dadosW << set_color(10) << move_to(0, numdados++) << "erro a adicionar processador";
                                }
                            }else{
                                *dadosW << set_color(10) << move_to(0, numdados++) << "erro de sintaxe";
                            }
                            atualizar_zonas_UI(linhas, colunas);
                        }

                        break;
                    case 11:
                        if(habitacao != nullptr){
                            // falta verificacao  de erros !
                            // e so um teste para ver se  funcionar
                            habitacao->crem(stoi(inputAux[1]), inputAux[2], stoi(inputAux[3]));
                            atualizar_zonas_UI(linhas, colunas);
                        }

                        break;
                    case 12:
                        if(habitacao != nullptr){
                            // falta verificacao  de erros !
                            // e so um teste para ver se  funcionar
                            vector<double> valores;
                            for (int i = 5; i < inputAux.size() - 1; i++) {
                                valores.emplace_back(stoi(inputAux[i]));
                            }
                            if(habitacao->rnova(stoi(inputAux[1]), stoi(inputAux[2]), inputAux[3], stoi(inputAux[4]), valores)){
                                atualizar_zonas_UI(linhas, colunas);
                            }else{
                                *dadosW << set_color(10) << move_to(0, numdados++) << "erro a adicionar regra";
                            }

                        }

                        break;
                    case 13:
                        if(habitacao != nullptr){
                            if(habitacao->pmuda(stoi(inputAux[1]), stoi(inputAux[2]), inputAux[3])){
                                atualizar_zonas_UI(linhas, colunas);
                            }else{
                                *dadosW << set_color(10) << move_to(0, numdados++) << "erro na mudaca do comdando";
                            }

                        }

                        break;
                    case 14:
                        if(habitacao != nullptr){
                            try{
                                string texto = habitacao->rlista(stoi(inputAux[1]), stoi(inputAux[2]));
                                *dadosW << set_color(7) << move_to(0, numdados) << texto;
                                numdados += contlinhas(texto);
                            }catch(const char* exce){
                                *dadosW << set_color(10) << move_to(0, numdados++) << exce;
                            }
                        }
                        break;
                    case 15:
                        if(habitacao != nullptr){
                            if(habitacao->rrem(stoi(inputAux[1]), stoi(inputAux[2]), stoi(inputAux[3]))){
                                atualizar_zonas_UI(linhas, colunas);
                            }else {
                                *dadosW << set_color(10) << move_to(0, numdados++) << "Erro na remocao das regras";
                            }
                        }
                        break;
                    case 16:
                        if(habitacao != nullptr){
                            // falta verificacao  de erros !
                            // e so um teste para ver se  funcionar
                            if(habitacao->asoc(stoi(inputAux[1]), stoi(inputAux[2]), stoi(inputAux[3]))){
                                atualizar_zonas_UI(linhas, colunas);
                            }else{
                                *dadosW << set_color(10) << move_to(0, numdados++) << "Erro na associacao";
                            }

                        }
                        break;
                    case 17:
                        if(habitacao != nullptr){
                            // falta verificacao  de erros !
                            // e so um teste para ver se  funcionar
                            if(habitacao->ades(stoi(inputAux[1]), stoi(inputAux[2]), stoi(inputAux[3]))){
                                atualizar_zonas_UI(linhas, colunas);
                            }else{
                                *dadosW << set_color(10) << move_to(0, numdados++) << "erro na remocao da associacao";
                            }

                        }
                        break;
                    case 18:
                        if(habitacao != nullptr){
                            // falta verificacao  de erros !
                            // e so um teste para ver se  funcionar
                            if(habitacao->acom(stoi(inputAux[1]), stoi(inputAux[2]), inputAux[3])){
                                atualizar_zonas_UI(linhas, colunas);
                            }else{
                                *dadosW << set_color(10) << move_to(0, numdados++) << "erro a enviar o comando para o aparelho";
                            }

                        }
                        break;
                    case 19:
                        if(habitacao != nullptr){
                            // falta verificacao  de erros !
                            // e so um teste para ver se  funcionar
                            if(habitacao->psalva(stoi(inputAux[1]), stoi(inputAux[2]), inputAux[3])){
                                atualizar_zonas_UI(linhas, colunas);
                            }else{
                                *dadosW << set_color(10) << move_to(0, numdados++) << "erro do psalva";
                            }
                        }
                        break;
                    case 20:
                        if(habitacao != nullptr){
                            // falta verificacao  de erros !
                            // e so um teste para ver se  funcionar
                            try {
                                habitacao->prepoe(inputAux[1]);
                                atualizar_zonas_UI(linhas, colunas);
                            }catch(const char* exce) {
                                *dadosW << set_color(10) << move_to(0, numdados++) << exce;
                            }
                        }
                        break;
                    case 21:
                        if(habitacao != nullptr){
                            habitacao->prem(inputAux[1]);
                        }else{
                            *dadosW << set_color(10) << move_to(0, numdados++) << "erro na remocao do processador salvo";
                        }
                        break;
                    case 22:
                        if(habitacao != nullptr){
                            // falta verificacao  de erros !
                            // e so um teste para ver se  funcionar
                            string testo = habitacao->plista();
                            *dadosW << set_color(7) << move_to(0, numdados) << testo;
                            numdados += contlinhas(testo);
                        }
                        break;
                    default:
                        break;
                }
            } else {
                *dadosW << set_color(10) << move_to(0, numdados++) << "Sintaxe invalida";
            }
            break;

        case 1:
            *dadosW << set_color(10) << move_to(0, numdados++) << "Comando nao encontrado";
            break;
        case 2:
            *dadosW << set_color(10) << move_to(0, numdados++) << "Argumentos a menos";
            break;
        case 3:
            *dadosW << set_color(10) << move_to(0, numdados++) << "Argumentos a mais";
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
        numdados = 1;
        dadosW->clear();
        *dadosW << set_color(12) << move_to(0, 0) << "Instantes: " << instantes;
    }
}

int UI::contlinhas(const string &texto)const{
    int n=0;
    for(int i=0; i<texto.size(); i++){
        if(texto[i] == '\n')
            n++;
    }
    return n;
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

