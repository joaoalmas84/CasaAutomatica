#ifndef CODIGOFONTE_SENSOR_H
#define CODIGOFONTE_SENSOR_H

#include "Propriedade.h"
#include <iostream>
#include <memory>
using namespace std;

class Sensor {
    static int baseId;
    const int id;
    weak_ptr<Propriedade> propriedade;
    double ultimaMedicao;

public:
    Sensor(weak_ptr<Propriedade> propriedade);
    ~Sensor();
    [[nodiscard]]
    int getid()const;
    [[nodiscard]]
    double getvalor();
    [[nodiscard]]
    string getAsString()const;
    bool medir();
};

#endif //CODIGOFONTE_SENSOR_H
