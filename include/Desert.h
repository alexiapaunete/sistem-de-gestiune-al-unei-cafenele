#pragma once
#include "Produs.h"

class Desert : public Produs {
    double calorii;
    bool   contineGluten;

    static int totalDeserturiVandute;

public:
    Desert(const Reteta& r, std::string cat, double pret,
           double cal, bool gluten = true);

    [[nodiscard]] Desert* clone() const override;

    [[nodiscard]] double      pretFinal(double discount = 0.0) const override;
    [[nodiscard]] std::string rezumatMeniu() const override;
    [[nodiscard]] std::string tip() const override;
    [[nodiscard]] int         timpServire() const override;

    [[nodiscard]] double getCalorii()      const;
    [[nodiscard]] bool   areGluten()       const;

    static int getTotalDeserturiVandute();
    static void inregistreazaVanzare();

    friend std::ostream& operator<<(std::ostream& os, const Desert& d);

protected:
    void afiseaza(std::ostream& os) const override;
};
