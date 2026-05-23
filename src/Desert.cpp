#include "Desert.h"
#include <iomanip>
#include <sstream>

int Desert::totalDeserturiVandute = 0;

Desert::Desert(const Reteta& r, std::string cat, double pret,
               double cal, bool gluten)
    : Produs(r, std::move(cat), pret),
      calorii(cal),
      contineGluten(gluten)
{}

Desert* Desert::clone() const {
    return new Desert(*this);
}

double Desert::pretFinal(double discount) const {
    if (discount < 0.0 || discount > 100.0)
        throw DiscountInvalidException(discount);
    double multiplicator = (calorii > 500.0) ? 1.1 : 1.0;
    return pretBaza * multiplicator * (1.0 - discount / 100.0);
}

std::string Desert::rezumatMeniu() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << getNume()
        << " - " << pretBaza << " RON"
        << " | " << calorii << " kcal"
        << (contineGluten ? "" : " [fara gluten]");
    return oss.str();
}

std::string Desert::tip() const { return "Desert"; }

int Desert::timpServire() const {
    return reteta.getTimpPreparare() + 60;
}

double Desert::getCalorii()  const { return calorii; }
bool   Desert::areGluten()   const { return contineGluten; }

int  Desert::getTotalDeserturiVandute()  { return totalDeserturiVandute; }
void Desert::inregistreazaVanzare()      { ++totalDeserturiVandute; }

void Desert::afiseaza(std::ostream& os) const {
    Produs::afiseaza(os);
    os << " | Calorii: " << calorii
       << " | Gluten: " << (contineGluten ? "da" : "nu");
}

std::ostream& operator<<(std::ostream& os, const Desert& d) {
    d.afiseaza(os);
    return os;
}
