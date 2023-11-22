//
// Created by 35193 on 09/11/2023.
//

#ifndef OOP_TRABALHO_REGRA_H
#define OOP_TRABALHO_REGRA_H
#include "Sensor.h"
#include <string>
#include <optional>
#include <memory>
class Regra {
    static int baseId;
    const int id;
    const string funcao;
    optional<double> x;
    optional<double> y;
    weak_ptr<Sensor> Psensor;
public:
    Regra(const string& _funcao, shared_ptr<Sensor> _sensor, optional<double> _x, optional<double> _y = {});
    [[nodiscard]]
    bool getValorDaRegra() const;
    [[nodiscard]]
    string getAsString() const;
private:
    bool igual() const;
    bool menor() const;
    bool maior() const;
    bool entre() const;
    bool naoEstre() const;

};


#endif //OOP_TRABALHO_REGRA_H
