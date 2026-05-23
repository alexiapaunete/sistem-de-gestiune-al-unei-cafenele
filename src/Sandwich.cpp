#include "Sandwich.h"
#include <iomanip>
#include <sstream>

int Sandwich::totalSandwichuriVandute = 0;

Sandwich::Sandwich(const Reteta& r, std::string cat, double pret,
                   bool vegetarian, bool glutenFree)
    : Produs(r, std::move(cat), pret),
      esteVegetarian(vegetarian),
      esteGlutenFree(glutenFree)
{}

Sandwich* Sandwich::clone() const {
    return new Sandwich(*this);
}

double Sandwich::pretFinal(double discount) const {
    if (discount < 0.0 || discount > 100.0)
        throw DiscountInvalidException(discount);
    double multiplicator = esteVegetarian ? 0.95 : 1.0;
    return pretBaza * multiplicator * (1.0 - discount / 100.0);
}

std::string Sandwich::rezumatMeniu() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << getNume()
        << " - " << pretBaza << " RON";
    if (esteVegetarian)  oss << " [vegetarian]";
    if (esteGlutenFree)  oss << " [gluten-free]";
    return oss.str();
}

std::string Sandwich::tip() const { return "Sandwich"; }

int Sandwich::timpServire() const {
    return reteta.getTimpPreparare() + 30;
}

bool Sandwich::esteVegetarianCheck() const { return esteVegetarian; }
bool Sandwich::esteGlutenFreeCheck() const { return esteGlutenFree; }

int  Sandwich::getTotalSandwichuriVandute() { return totalSandwichuriVandute; }
void Sandwich::inregistreazaVanzare()       { ++totalSandwichuriVandute; }

void Sandwich::afiseaza(std::ostream& os) const {
    Produs::afiseaza(os);
    os << " | Vegetarian: " << (esteVegetarian ? "da" : "nu")
       << " | Gluten-free: " << (esteGlutenFree ? "da" : "nu");
}

std::ostream& operator<<(std::ostream& os, const Sandwich& s) {
    s.afiseaza(os);
    return os;
}
