//
// Created by 35193 on 01/11/2023.
//

#include "Processador.h"
int Processador::CONT = 0;

    Processador::Processador(): ID(CONT + 1){
        CONT++;
    }
    bool Processador::ativarProcessador(){
        for(auto regra: regras){
            if (regra.evaluate()){
                return false;
            }
        }
        return true;
    }
    bool Processador::operator==(const Processador& pro)const{
        if(ID == pro.ID)
            return false;
        else
            return true;
    }
