#ifndef CODIGOFONTE_REGRA_H
#define CODIGOFONTE_REGRA_H

#include "Sensor.h"

#include <iostream>
#include <optional>
#include <memory>

using namespace std;

class Regra {
public:
    Regra(const string& _funcao, shared_ptr<Sensor> _sensor, optional<double> _x, optional<double> _y = {});
    [[nodiscard]]
    bool getValorDaRegra() const;
    [[nodiscard]]
    string getAsString() const;
    [[nodiscard]]
    int getId() const;

private:
    [[nodiscard]]
    bool igual() const;
    [[nodiscard]]
    bool menor() const;
    [[nodiscard]]
    bool maior() const;
    [[nodiscard]]
    bool entre() const;
    [[nodiscard]]
    bool naoEstre() const;

    static int baseId;
    const int id;
    const string funcao;
    optional<double> x;
    optional<double> y;
    weak_ptr<Sensor> Psensor;

};


#endif //CODIGOFONTE_REGRA_H
