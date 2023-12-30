//
// Created by 35193 on 20/12/2023.
//

#ifndef OOP_TRABALHO_REGRABASE_H
#define OOP_TRABALHO_REGRABASE_H
#include "Sensor.h"
#include <memory>
class RegraBase {
    static int baseId;
    const int id;
    weak_ptr<Sensor> Psensor;
public:

    RegraBase(weak_ptr<Sensor> _sensor);
    [[nodiscard]]
    virtual string getAsString() const;
    [[nodiscard]]
    virtual bool getEstado() = 0;
    [[nodiscard]]
    int getId()const;
    int getvalor()const;
    virtual unique_ptr<RegraBase> clone() = 0;
    virtual ~RegraBase() = 0;
};


#endif //OOP_TRABALHO_REGRABASE_H
