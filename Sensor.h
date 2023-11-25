//
// Created by 35193 on 09/11/2023.
//

#ifndef OOP_TRABALHO_SENSOR_H
#define OOP_TRABALHO_SENSOR_H
#include "Propriedade.h"
#include <string>

using namespace std;

class Sensor {
public:
    Sensor(Propriedade* propriedade);

    ~Sensor();

    [[nodiscard]]
    int getid() const;

    [[nodiscard]]
    double getvalor();

    bool medir();

    [[nodiscard]]
    string getAsString() const;

private:
    static int baseId;
    const int id;
    Propriedade* propriedade;
    double ultimaMedicao;
};


#endif //OOP_TRABALHO_SENSOR_H
