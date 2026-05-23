#include "Cafenea.h"
#include "Bautura.h"
#include "Desert.h"
#include "Sandwich.h"
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>

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

void Cafenea::incarcaInventarDinFisier(const std::string& cale) {
    std::ifstream f(cale);
    if (!f.is_open())
        throw std::runtime_error("Nu pot deschide fisierul de inventar: " + cale);

    std::string linie;
    while (std::getline(f, linie)) {
        if (linie.empty() || linie[0] == '#') continue;
        std::istringstream ss(linie);
        std::string nume, cantStr, pragStr;
        if (!std::getline(ss, nume, '|')    ||
            !std::getline(ss, cantStr, '|') ||
            !std::getline(ss, pragStr))
            continue;
        stocGeneral.adaugaIngredient(nume, std::stod(cantStr), std::stod(pragStr));
    }
}

void Cafenea::incarcaProduseDinFisier(const std::string& cale) {
    std::ifstream f(cale);
    if (!f.is_open())
        throw std::runtime_error("Nu pot deschide fisierul de produse: " + cale);

    std::string linie;
    std::string tipCurent, numeCurent, catCurent;
    int timpCurent = 0;
    double pretCurent = 0.0;
    std::string p1, p2;
    Reteta* retetaCurenta = nullptr;

    auto finalizeazaProdus = [&]() {
        if (!retetaCurenta) return;
        try {
            if (tipCurent == "BAUTURA") {
                Bautura b(*retetaCurenta, catCurent, pretCurent,
                          p1, p2 == "1");
                adaugaProdus(b);
            } else if (tipCurent == "DESERT") {
                Desert d(*retetaCurenta, catCurent, pretCurent,
                         std::stod(p1), p2 == "1");
                adaugaProdus(d);
            } else if (tipCurent == "SANDWICH") {
                Sandwich s(*retetaCurenta, catCurent, pretCurent,
                           p1 == "1", p2 == "1");
                adaugaProdus(s);
            }
        } catch (const ProdusDuplicatException&) {
        }
        delete retetaCurenta;
        retetaCurenta = nullptr;
    };

    while (std::getline(f, linie)) {
        if (linie.empty() || linie[0] == '#') continue;
        std::istringstream ss(linie);
        std::string token;
        std::getline(ss, token, '|');

        if (token == "ING") {
            if (!retetaCurenta) continue;
            std::string numeIng, cantStr, unit;
            std::getline(ss, numeIng, '|');
            std::getline(ss, cantStr, '|');
            std::getline(ss, unit);
            retetaCurenta->adaugaIngredient(
                Ingredient(numeIng, std::stod(cantStr), unit));
        } else if (token == "BAUTURA" || token == "DESERT" || token == "SANDWICH") {
            finalizeazaProdus();
            tipCurent = token;
            std::string timpStr, pretStr;
            std::getline(ss, numeCurent, '|');
            std::getline(ss, timpStr,    '|');
            std::getline(ss, catCurent,  '|');
            std::getline(ss, pretStr,    '|');
            std::getline(ss, p1,         '|');
            std::getline(ss, p2);
            timpCurent  = std::stoi(timpStr);
            pretCurent  = std::stod(pretStr);
            retetaCurenta = new Reteta(numeCurent, timpCurent);
        }
    }
    finalizeazaProdus();
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
            else if (dynamic_cast<const Sandwich*>(produs) != nullptr)
                Sandwich::inregistreazaVanzare();
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
    int bauturi = 0, deserturi = 0, sandwichuri = 0, altele = 0;
    for (const auto* p : meniu) {
        if      (dynamic_cast<const Bautura*>(p))   ++bauturi;
        else if (dynamic_cast<const Desert*>(p))    ++deserturi;
        else if (dynamic_cast<const Sandwich*>(p))  ++sandwichuri;
        else                                         ++altele;
    }
    std::cout << "Bauturi in meniu:     " << bauturi     << "\n";
    std::cout << "Deserturi in meniu:   " << deserturi   << "\n";
    std::cout << "Sandwichuri in meniu: " << sandwichuri << "\n";
    std::cout << "Altele:               " << altele      << "\n";
    std::cout << "Bauturi vandute:      " << Bautura::getTotalBauturiVandute()     << "\n";
    std::cout << "Deserturi vandute:    " << Desert::getTotalDeserturiVandute()    << "\n";
    std::cout << "Sandwichuri vandute:  " << Sandwich::getTotalSandwichuriVandute()<< "\n";
    std::cout << "Produse create total: " << Produs::getTotalProduseCréate()       << "\n";
    std::cout << "========================\n";
}

std::ostream& operator<<(std::ostream& os, const Cafenea& c) {
    os << "Cafeneaua: " << c.nume << " (" << c.adresa << ")";
    return os;
}
