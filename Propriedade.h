#ifndef CODIGOFONTE_PROPRIEDADE_H
#define CODIGOFONTE_PROPRIEDADE_H

#include <iostream>
#include <optional>

using namespace std;

class Propriedade {
public:
    //Propriedade(optional<double> max = {}, bool escolha = 'p');
    Propriedade(optional<double> min = {}, optional<double> max = {});
    void definirValor(double v);
    [[nodiscard]]
    double getValor() const;
    [[nodiscard]]
    bool has_max() const;
    [[nodiscard]]
    bool has_min() const;
    [[nodiscard]]
    double getmax() const;
    [[nodiscard]]
    double getmin() const;
    [[nodiscard]]
    int getid() const;

private:
    static int baseId;
    const int id;
    double valor;
    optional<double> minimo;
    optional<double> maximo;
};

#endif //CODIGOFONTE_PROPRIEDADE_H
