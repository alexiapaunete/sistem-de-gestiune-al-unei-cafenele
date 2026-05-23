#include "Comanda.h"
#include <iomanip>
#include <algorithm>

int Comanda::contor = 0;

std::string Comanda::statusToString(StatusComanda s) {
    switch (s) {
        case StatusComanda::IN_ASTEPTARE: return "In asteptare";
        case StatusComanda::IN_PREPARARE: return "In preparare";
        case StatusComanda::FINALIZATA:   return "Finalizata";
        case StatusComanda::ANULATA:      return "Anulata";
        default:                          return "Necunoscut";
    }
}

void Comanda::copiazaProduse(const std::vector<Produs*>& sursa) {
    produse.reserve(sursa.size());
    for (const auto* p : sursa)
        produse.push_back(p->clone());
}

void Comanda::elibereazaProduse() {
    for (auto* p : produse) delete p;
    produse.clear();
}

Comanda::Comanda(std::string client, double discount)
    : id(++contor), numeClient(std::move(client)),
      status(StatusComanda::IN_ASTEPTARE), discountGlobal(discount)
{
    if (discount < 0.0 || discount > 100.0)
        throw DiscountInvalidException(discount);
}

Comanda::Comanda(const Comanda& other)
    : id(other.id), numeClient(other.numeClient),
      status(other.status), discountGlobal(other.discountGlobal)
{
    copiazaProduse(other.produse);
}

Comanda& Comanda::operator=(Comanda other) {
    swap(*this, other);
    return *this;
}

Comanda::~Comanda() {
    elibereazaProduse();
}

void swap(Comanda& a, Comanda& b) noexcept {
    using std::swap;
    swap(a.id,             b.id);
    swap(a.numeClient,     b.numeClient);
    swap(a.produse,        b.produse);
    swap(a.status,         b.status);
    swap(a.discountGlobal, b.discountGlobal);
}

void Comanda::adaugaProdus(const Produs& p) {
    produse.push_back(p.clone());
}

double Comanda::totalComanda() const {
    double total = 0.0;
    for (const auto* p : produse)
        total += p->pretFinal(discountGlobal);
    return total;
}

int Comanda::timpEstimat() const {
    int maxTimp = 0;
    for (const auto* p : produse)
        if (p->timpServire() > maxTimp)
            maxTimp = p->timpServire();
    return maxTimp;
}

double Comanda::aplicaPromotie(double pragValoare, double discountExtra) {
    if (totalComanda() >= pragValoare) {
        discountGlobal += discountExtra;
        if (discountGlobal > 100.0) discountGlobal = 100.0;
    }
    return discountGlobal;
}

bool Comanda::toateDisponibile() const {
    for (const auto* p : produse)
        if (!p->esteDisponibil()) return false;
    return true;
}

void Comanda::avanseazaStatus() {
    switch (status) {
        case StatusComanda::IN_ASTEPTARE: status = StatusComanda::IN_PREPARARE; break;
        case StatusComanda::IN_PREPARARE: status = StatusComanda::FINALIZATA;   break;
        default: break;
    }
}

int                         Comanda::getId()         const { return id; }
const std::string&          Comanda::getNumeClient() const { return numeClient; }
StatusComanda               Comanda::getStatus()     const { return status; }
const std::vector<Produs*>& Comanda::getProduse()    const { return produse; }

std::ostream& operator<<(std::ostream& os, const Comanda& c) {
    os << std::fixed << std::setprecision(2);
    os << "Comanda #" << c.id
       << " [" << c.numeClient << "]"
       << " | Status: " << Comanda::statusToString(c.status)
       << " | Discount: " << c.discountGlobal << "%"
       << " | Total: " << c.totalComanda() << " RON"
       << " | Timp estimat: " << c.timpEstimat() << "s\n"
       << "  Produse (" << c.produse.size() << "):\n";
    for (const auto* p : c.produse)
        os << "    - " << p->rezumatMeniu() << "\n";
    return os;
}
