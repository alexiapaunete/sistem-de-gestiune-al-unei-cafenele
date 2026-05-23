#pragma once
#include "Produs.h"
class Bautura : public Produs {
    std::string temperatura;   
    bool        contineCofeina;

    static int totalBauturiVandute;

public:
    Bautura(const Reteta& r, std::string cat, double pret,
            std::string temp = "calda", bool cofeina = true);

    [[nodiscard]] Bautura* clone() const override;

    [[nodiscard]] double      pretFinal(double discount = 0.0) const override;
    [[nodiscard]] std::string rezumatMeniu() const override;
    [[nodiscard]] std::string tip() const override;
    [[nodiscard]] int         timpServire() const override;

    [[nodiscard]] bool        areCofeina()     const;
    [[nodiscard]] const std::string& getTemperatura() const;

    static int getTotalBauturiVandute();
    static void inregistreazaVanzare();

    friend std::ostream& operator<<(std::ostream& os, const Bautura& b);

protected:
    void afiseaza(std::ostream& os) const override;
};
