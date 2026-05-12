#include "Inventar.h"
#include <stdexcept>
#include <iomanip>

Inventar::Inventar() = default;

Inventar::Inventar(const Inventar& other)
    : stoc(other.stoc), praguri(other.praguri) {}

Inventar& Inventar::operator=(const Inventar& other) {
    if (this != &other) {
        stoc    = other.stoc;
        praguri = other.praguri;
    }
    return *this;
}

Inventar::~Inventar() = default;

std::string Inventar::stareToString(StareStoc s) {
    switch (s) {
        case StareStoc::SUFICIENT:   return "Suficient";
        case StareStoc::AVERTIZARE:  return "Avertizare";
        case StareStoc::EPUIZAT:     return "Epuizat";
        default:                     return "Necunoscut";
    }
}

void Inventar::adaugaIngredient(const std::string& nume, double cantitate, double prag) {
    if (cantitate < 0 || prag < 0) throw std::invalid_argument("Valori negative!");
    stoc[nume] += cantitate;
    praguri[nume] = prag;
}

bool Inventar::verificaDisponibilitate(const std::string& nume, double cantitate) const {
    auto it = stoc.find(nume);
    return (it != stoc.end() && it->second >= cantitate);
}

bool Inventar::consuma(const std::string& nume, double cantitate) {
    if (!verificaDisponibilitate(nume, cantitate)) return false;
    stoc[nume] -= cantitate;
    return true;
}

StareStoc Inventar::getStareIngredient(const std::string& nume) const {
    if (stoc.at(nume) <= 0) return StareStoc::EPUIZAT;
    if (stoc.at(nume) < praguri.at(nume)) return StareStoc::AVERTIZARE;
    return StareStoc::SUFICIENT;
}

std::ostream& operator<<(std::ostream& os, const Inventar& inv) {
    os << "\n=== STATUS INVENTAR ===\n";
    for (const auto& [nume, cant] : inv.stoc) {
        os << "- " << std::left << std::setw(12) << nume << ": " << cant
           << " | " << Inventar::stareToString(inv.getStareIngredient(nume)) << "\n";
    }
    return os;
}