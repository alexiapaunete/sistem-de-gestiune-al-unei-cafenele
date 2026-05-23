#include "Cafenea.h"
#include "Bautura.h"
#include "Desert.h"
#include <iomanip>
#include <algorithm>

void Cafenea::copiazaMeniu(const std::vector<Produs*>& sursa) {
    meniu.reserve(sursa.size());
    for (const auto* p : sursa)
        meniu.push_back(p->clone());
}

void Cafenea::elibereazaMeniu() {
    for (auto* p : meniu) delete p;
    meniu.clear();
}

Cafenea::Cafenea(std::string n, std::string a)
    : nume(std::move(n)), adresa(std::move(a)) {}

Cafenea::Cafenea(const Cafenea& other)
    : nume(other.nume), adresa(other.adresa),
      istoricComenzi(other.istoricComenzi),
      stocGeneral(other.stocGeneral)
{
    copiazaMeniu(other.meniu);
}

Cafenea& Cafenea::operator=(Cafenea other) {
    swap(*this, other);
    return *this;
}

Cafenea::~Cafenea() {
    elibereazaMeniu();
}

void swap(Cafenea& a, Cafenea& b) noexcept {
    using std::swap;
    swap(a.nume,            b.nume);
    swap(a.adresa,          b.adresa);
    swap(a.meniu,           b.meniu);
    swap(a.istoricComenzi,  b.istoricComenzi);
    swap(a.stocGeneral,     b.stocGeneral);
}

void Cafenea::adaugaProdus(const Produs& p) {
    for (const auto* existing : meniu)
        if (existing->getNume() == p.getNume())
            throw ProdusDuplicatException(p.getNume());
    meniu.push_back(p.clone());
}

void Cafenea::aprovizioneaza(const std::string& ingredient, double cantitate, double prag) {
    stocGeneral.adaugaIngredient(ingredient, cantitate, prag);
}

void Cafenea::adaugaComanda(Comanda c) {
    try {
        for (const auto* produs : c.getProduse())
            produs->prepara(stocGeneral);

        for (const auto* produs : c.getProduse()) {
            if (dynamic_cast<const Bautura*>(produs) != nullptr)
                Bautura::inregistreazaVanzare();
            else if (dynamic_cast<const Desert*>(produs) != nullptr)
                Desert::inregistreazaVanzare();
        }

        c.avanseazaStatus();
        c.avanseazaStatus();
        istoricComenzi.push_back(std::move(c));

    } catch (const StocInsuficientException& e) {
        std::cout << "[!] Comanda #" << c.getId()
                  << " anulata: " << e.what() << "\n";
    }
}

void Cafenea::afiseazaMeniu() const {
    std::cout << "--- Meniu " << nume << " ---\n";
    for (const auto* p : meniu)
        std::cout << *p << "\n";
}

void Cafenea::setDisponibilitate(const std::string& numeProdus, bool stare) {
    for (auto* p : meniu)
        if (p->getNume() == numeProdus) {
            p->setDisponibil(stare);
            return;
        }
}

void Cafenea::raportZilnic() const {
    std::cout << "\n========== RAPORT ZILNIC: " << nume << " ==========\n";
    std::cout << std::fixed << std::setprecision(2);
    double total = 0.0;
    for (const auto& c : istoricComenzi)
        total += c.totalComanda();
    std::cout << "Incasari totale: " << total << " RON\n";
    std::cout << "Comenzi onorate: " << istoricComenzi.size() << "\n";
    std::cout << stocGeneral;
    std::cout << "=================================================\n";
}

void Cafenea::raportDupaTip() const {
    std::cout << "\n=== RAPORT PE TIPURI ===\n";
    int bauturi = 0, deserturi = 0, altele = 0;
    for (const auto* p : meniu) {
        if (dynamic_cast<const Bautura*>(p))       ++bauturi;
        else if (dynamic_cast<const Desert*>(p))   ++deserturi;
        else                                        ++altele;
    }
    std::cout << "Bauturi in meniu:   " << bauturi   << "\n";
    std::cout << "Deserturi in meniu: " << deserturi << "\n";
    std::cout << "Altele:             " << altele    << "\n";
    std::cout << "Bauturi vandute (total sesiune): "
              << Bautura::getTotalBauturiVandute()  << "\n";
    std::cout << "Deserturi vandute (total sesiune): "
              << Desert::getTotalDeserturiVandute() << "\n";
    std::cout << "Produse create total: "
              << Produs::getTotalProduseCréate()    << "\n";
    std::cout << "========================\n";
}

std::ostream& operator<<(std::ostream& os, const Cafenea& c) {
    os << "Cafeneaua: " << c.nume << " (" << c.adresa << ")";
    return os;
}
