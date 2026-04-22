#include "Cafenea.h"

Cafenea::Cafenea(std::string n, std::string a) : nume(n), adresa(a) {}

void Cafenea::adaugaProdus(const Produs& p) {
    meniu.push_back(p);
}

void Cafenea::aprovizioneaza(std::string ingredient, double cantitate, double prag) {
    stocGeneral.adaugaIngredient(ingredient, cantitate, prag);
}

void Cafenea::adaugaComanda(Comanda c) {
    bool comandaReusita = true;

    for (auto& produs : c.getProduse()) {
        if (!produs.prepara(stocGeneral)) {
            comandaReusita = false;
            break;
        }
    }

    if (comandaReusita) {
        c.avanseazaStatus();
        c.avanseazaStatus();
        istoricComenzi.push_back(c);
    } else {
        std::cout << "[!] Comanda #" << c.getId() << " a fost anulata. Stoc insuficient!\n";
    }
}

void Cafenea::raportZilnic() const {
    std::cout << "\n========== RAPORT ZILNIC: " << nume << " ==========\n";
    double totalIncasari = 0;
    for (const auto& c : istoricComenzi) {
        totalIncasari += c.totalComanda();
    }
    std::cout << "Incasari totale: " << totalIncasari << " RON\n";
    std::cout << "Comenzi onorate: " << istoricComenzi.size() << "\n";

    std::cout << stocGeneral;
    std::cout << "=================================================\n";
}

void Cafenea::afiseazaMeniu() const {
    std::cout << "--- Meniu " << nume << " ---\n";
    for (const auto& p : meniu) {
        std::cout << p << "\n";
    }
}

std::vector<Produs> Cafenea::meniuDupaCategorie(const std::string& categorie) const {
    std::vector<Produs> rezultat;
    for (const auto& p : meniu) {
        if (p.getCategorie() == categorie) {
            rezultat.push_back(p);
        }
    }
    return rezultat;
}

void Cafenea::setDisponibilitate(const std::string& numeProdus, bool stare) {
    for (auto& p : meniu) {
        if (p.getNume() == numeProdus) {
            p.setDisponibil(stare);
            break;
        }
    }
}

void Cafenea::meniuInteractiv() {
    int optiune = -1;

    while (optiune != 0) {
        std::cout << "\n====== CASA DE MARCAT: " << nume << " ======\n";
        std::cout << "1. Vinde Cappuccino\n";
        std::cout << "2. Vinde Caffe Latte\n";
        std::cout << "3. Vinde Americano\n";
        std::cout << "4. Vinde Mocha\n";
        std::cout << "5. Verifica Stocul (Inventar)\n";
        std::cout << "6. Afiseaza Raportul Zilnic\n";
        std::cout << "0. Iesire\n";
        std::cout << "========================================\n";
        std::cout << "Alege o actiune: ";

        std::cin >> optiune;

        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            optiune = -1;
        }

        switch (optiune) {
            case 1:
            case 2:
            case 3:
            case 4: {
                std::string numeClient;
                std::cout << "Introdu numele clientului (fara spatii): ";
                std::cin >> numeClient;

                Comanda c(numeClient, 0.0);

                c.adaugaProdus(meniu[optiune - 1]);

                std::cout << "\n[Procesare] Se prepara comanda...\n";
                adaugaComanda(c);
                break;
            }
            case 5:
                std::cout << stocGeneral;
                break;
            case 6:
                raportZilnic();
                break;
            case 0:
                std::cout << "\n[Sistem] Casa de marcat se inchide. O zi buna!\n";
                break;
            default:
                std::cout << "\n[Eroare] Optiune invalida! Incearca din nou.\n";
                break;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Cafenea& c) {
    os << "Cafeneaua: " << c.nume << " (" << c.adresa << ")";
    return os;
}