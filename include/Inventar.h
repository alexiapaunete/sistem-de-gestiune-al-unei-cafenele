#ifndef INVENTAR_H
#define INVENTAR_H

#include <map>
#include <string>
#include <vector>

class Inventar {
private:
    std::map<std::string, double> stoc;
    Inventar() {} 

public:
    static Inventar& getInstance(); 

    void adaugaStoc(std::string nume, double cantitate);
    bool verificaSiConsuma(std::map<std::string, double> reteta);
    void afiseazaRaportAprovizionare() const;
};

#endif