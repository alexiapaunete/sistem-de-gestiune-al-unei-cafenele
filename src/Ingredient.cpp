#include "Ingredient.h"

Ingredient::Ingredient(std::string n, double c, std::string u)
    : nume(std::move(n)), cantitate(c), unitate(std::move(u)) {}

const std::string& Ingredient::getNume()     const { return nume; }
double             Ingredient::getCantitate() const { return cantitate; }
const std::string& Ingredient::getUnitate()  const { return unitate; }

Ingredient Ingredient::scalat(double factor) const {
    return Ingredient(nume, cantitate * factor, unitate);
}

std::ostream& operator<<(std::ostream& os, const Ingredient& i) {
    os << i.nume << ": " << i.cantitate << " " << i.unitate;
    return os;
}
