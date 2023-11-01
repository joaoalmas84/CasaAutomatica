//
// Created by 35193 on 01/11/2023.
//

#ifndef POO_REGRA_H
#define POO_REGRA_H
#include <string>
#include "Sensor.h"
using namespace std;

class Regra {
    Sensor& sensor;
    string type;
    double value;
    double minValue;
    double maxValue;

public:
    Regra(Sensor& Asensor, const string& type, double value);
    Regra(Sensor& sensor, const std::string& type, double minValue, double maxValue);
    bool evaluate() const;
};


#endif //POO_REGRA_H
