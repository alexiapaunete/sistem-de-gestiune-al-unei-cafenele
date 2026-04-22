#pragma once
#include <iostream>
#include <string>
#include <map>

enum class StareStoc { SUFICIENT, AVERTIZARE, EPUIZAT, NECUNOSCUT };

class Inventar {
    std::map<std::string, double> stoc;
    std::map<std::string, double> praguri;

    static std::string stareToString(StareStoc s);

public:
    Inventar() = default;

    void adaugaIngredient(const std::string& nume, double cantitate, double prag);
    bool consuma(const std::string& nume, double cantitate);

    [[nodiscard]] bool verificaDisponibilitate(const std::string& nume, double cantitate) const;
    [[nodiscard]] StareStoc getStareIngredient(const std::string& nume) const;

    friend std::ostream& operator<<(std::ostream& os, const Inventar& inv);
};