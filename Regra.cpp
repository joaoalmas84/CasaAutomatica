//
// Created by 35193 on 01/11/2023.
//

#include "Regra.h"
    Regra::Regra(Sensor& Asensor, const string& type, double value): sensor(Asensor) {
    }

    Regra::Regra(Sensor& Asensor, const string& type, double minValue, double maxValue):sensor(Asensor)  {
    }
    bool Regra::evaluate() const {
        // Avalie a regra com base nos valores do sensor e nos parâmetros
        if (type == "igual_a") {
            // Implemente a comparação igual_a
        } else if (type == "menor_que") {
            // Implemente a comparação menor_que
        } else if (type == "maior_que") {
            // Implemente a comparação maior_que
        } else if (type == "entre") {
            // Implemente a comparação entre
        } else if (type == "fora") {
            // Implemente a comparação fora
        }
        return true;
    }