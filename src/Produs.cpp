#include "Produs.h"

Produs::Produs(const Reteta& r, std::string cat, double pret)
    : reteta(r), categorie(std::move(cat)), pretBaza(pret), disponibil(true) {}

Produs::Produs(const Produs& other)
    : reteta(other.reteta), categorie(other.categorie), pretBaza(other.pretBaza), disponibil(other.disponibil) {}

Produs& Produs::operator=(const Produs& other) {
    if (this != &other) {
        reteta    = other.reteta;
        categorie = other.categorie;
        pretBaza  = other.pretBaza;
        disponibil = other.disponibil;
    }
    return *this;
}

Produs::~Produs() = default;

double Produs::pretFinal(double discount) const {
    return pretBaza - (pretBaza * discount / 100.0);
}

int Produs::timpServire() const {
    return reteta.getTimpPreparare();
}

std::string Produs::rezumatMeniu() const {
    return reteta.getNume() + " (" + categorie + ") - " + std::to_string(pretBaza) + " RON";
}

std::string Produs::getCategorie() const { return categorie; }
std::string Produs::getNume() const { return reteta.getNume(); }
void Produs::setDisponibil(bool stare) { disponibil = stare; }
bool Produs::esteDisponibil() const { return disponibil; }

bool Produs::prepara(Inventar& inv) const {
    if (!disponibil) return false;

    for (const auto& ing : reteta.getListaIngrediente()) {
        if (!inv.verificaDisponibilitate(ing.getNume(), ing.getCantitate())) {
            return false;
        }
    }

    for (const auto& ing : reteta.getListaIngrediente()) {
        inv.consuma(ing.getNume(), ing.getCantitate());
    }

    return true;
}

std::ostream& operator<<(std::ostream& os, const Produs& p) {
    os << p.reteta.getNume() << " | Pret: " << p.pretBaza << " RON | "
       << (p.disponibil ? "Disponibil" : "Indisponibil");
    return os;
}