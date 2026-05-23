#pragma once
#include "Produs.h"

class Sandwich : public Produs {
    bool  esteVegetarian;
    bool  esteGlutenFree;

    static int totalSandwichuriVandute;

public:
    Sandwich(const Reteta& r, std::string cat, double pret,
             bool vegetarian = false, bool glutenFree = false);

    [[nodiscard]] Sandwich* clone() const override;

    [[nodiscard]] double      pretFinal(double discount = 0.0) const override;
    [[nodiscard]] std::string rezumatMeniu() const override;
    [[nodiscard]] std::string tip() const override;
    [[nodiscard]] int         timpServire() const override;

    [[nodiscard]] bool esteVegetarianCheck() const;
    [[nodiscard]] bool esteGlutenFreeCheck() const;

    static int getTotalSandwichuriVandute();
    static void inregistreazaVanzare();

    friend std::ostream& operator<<(std::ostream& os, const Sandwich& s);

protected:
    void afiseaza(std::ostream& os) const override;
};
