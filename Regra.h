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
public:
    Regra(const string& _funcao, shared_ptr<Sensor> _sensor, optional<double> _x, optional<double> _y = {});
    ~Regra();
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


#endif //OOP_TRABALHO_REGRA_H
