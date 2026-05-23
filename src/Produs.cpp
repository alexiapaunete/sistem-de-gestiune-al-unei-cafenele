#include "Produs.h"
#include <iomanip>

int Produs::totalProduseCréate = 0;

Produs::Produs(const Reteta& r, std::string cat, double pret)
    : reteta(r), categorie(std::move(cat)), pretBaza(pret), disponibil(true)
{
    if (pret <= 0.0)
        throw PretInvalidException(pret);
    ++totalProduseCréate;
}

int Produs::timpServire() const {
    return reteta.getTimpPreparare();
}

bool Produs::prepara(Inventar& inv) const {
    for (const auto& ing : reteta.getListaIngrediente()) {
        if (!inv.verificaDisponibilitate(ing.getNume(), ing.getCantitate()))
            throw StocInsuficientException(ing.getNume());
    }
    for (const auto& ing : reteta.getListaIngrediente()) {
        inv.consuma(ing.getNume(), ing.getCantitate());
    }
    return true;
}

const std::string& Produs::getCategorie()  const { return categorie; }
std::string        Produs::getNume()        const { return reteta.getNume(); }
void               Produs::setDisponibil(bool stare) { disponibil = stare; }
bool               Produs::esteDisponibil() const { return disponibil; }
double             Produs::getPretBaza()    const { return pretBaza; }
const Reteta&      Produs::getReteta()      const { return reteta; }

int Produs::getTotalProduseCréate() { return totalProduseCréate; }

void Produs::afiseaza(std::ostream& os) const {
    os << std::fixed << std::setprecision(2);
    os << "[" << tip() << "] " << getNume()
       << " | Categorie: " << categorie
       << " | Pret: " << pretBaza << " RON"
       << " | Disponibil: " << (disponibil ? "da" : "nu");
}

std::ostream& operator<<(std::ostream& os, const Produs& p) {
    p.afiseaza(os);
    return os;
}
