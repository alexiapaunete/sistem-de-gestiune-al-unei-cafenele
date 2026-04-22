#pragma once
#include <iostream>
#include <string>
#include "Reteta.h"
#include "Inventar.h"

class Produs {
    Reteta reteta;
    std::string categorie;
    double pretBaza;
    bool disponibil;

public:
    Produs(const Reteta& r, std::string cat, double pret);

    Produs(const Produs& other);
    Produs& operator=(const Produs& other);
    ~Produs() = default;

    [[nodiscard]] double pretFinal(double discount = 0.0) const;
    [[nodiscard]] int timpServire() const;
    [[nodiscard]] std::string rezumatMeniu() const;

    [[nodiscard]] std::string getCategorie() const;
    [[nodiscard]] std::string getNume() const;
    void setDisponibil(bool stare);
    [[nodiscard]] bool esteDisponibil() const;

    bool prepara(Inventar& inv) const;

    friend std::ostream& operator<<(std::ostream& os, const Produs& p);
};