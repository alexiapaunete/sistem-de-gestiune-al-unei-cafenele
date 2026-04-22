#include "Reteta.h"

Reteta::Reteta(std::string nume, int timpSec)
    : numeBautura(std::move(nume)), timpPreparare(timpSec) {}

bool Reteta::cantitatEValida(double c) {
    return c > 0.0;
}

void Reteta::adaugaIngredient(const Ingredient& ing) {
    if (cantitatEValida(ing.getCantitate()))
        ingrediente.push_back(ing);
}

const std::string& Reteta::getNume()         const { return numeBautura; }
int                Reteta::getTimpPreparare() const { return timpPreparare; }
int                Reteta::numarIngrediante() const { return static_cast<int>(ingrediente.size()); }

Reteta Reteta::scalata(double factor) const {
    Reteta r(numeBautura + " x" + std::to_string(static_cast<int>(factor)), timpPreparare);
    for (const auto& ing : ingrediente)
        r.ingrediente.push_back(ing.scalat(factor));
    return r;
}

bool Reteta::contineIngredient(const std::string& numeIng) const {
    for (const auto& ing : ingrediente)
        if (ing.getNume() == numeIng)
            return true;
    return false;
}

std::ostream& operator<<(std::ostream& os, const Reteta& r) {
    os << "Reteta [" << r.numeBautura << "] (" << r.timpPreparare << "s): ";
    for (const auto& ing : r.ingrediente)
        os << "[" << ing << "] ";
    return os;
}
