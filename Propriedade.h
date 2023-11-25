//
// Created by 35193 on 09/11/2023.
//

#ifndef OOP_TRABALHO_PROPRIEDADE_H
#define OOP_TRABALHO_PROPRIEDADE_H
#include <optional>
#include <string>

using namespace std;

class Propriedade {
    static int baseId;
    const int id;
    double valor;
    optional<double> minimo;
    optional<double> maximo;
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
};



#endif //OOP_TRABALHO_PROPRIEDADE_H
