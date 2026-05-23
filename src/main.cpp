#include <iostream>
#include <iomanip>
#include "Cafenea.h"
#include "Bautura.h"
#include "Desert.h"
#include "Sandwich.h"
#include "Exceptii.h"

int main() {
    std::cout << std::fixed << std::setprecision(2);

    Cafenea cafenea("Aroma Urbana", "Str. Victoriei 42, Bucuresti");

    try {
        cafenea.incarcaInventarDinFisier("assets/inventar.txt");
        cafenea.incarcaProduseDinFisier("assets/produse.txt");
    } catch (const std::exception& e) {
        std::cerr << "[EROARE] " << e.what() << "\n";
        return 1;
    }

    std::cout << cafenea << "\n";
    cafenea.afiseazaMeniu();
    cafenea.raportDupaTip();

    std::cout << "\n=== Polimorfism prin Produs* ===\n";
    {
        Reteta r("Espresso Test", 60);
        r.adaugaIngredient(Ingredient("Espresso", 30, "ml"));
        Bautura  b(r, "Cafea",     10.0, "calda", true);
        Desert   d(r, "Desert",    12.0, 300.0,   false);
        Sandwich s(r, "Sandvisuri",14.0, true,    false);

        Produs* p1 = b.clone();
        Produs* p2 = d.clone();
        Produs* p3 = s.clone();

        std::cout << *p1 << "\n";
        std::cout << *p2 << "\n";
        std::cout << *p3 << "\n";

        std::cout << "Tip p1: " << p1->tip() << " | Pret final (10%): " << p1->pretFinal(10.0) << " RON\n";
        std::cout << "Tip p2: " << p2->tip() << " | Pret final (10%): " << p2->pretFinal(10.0) << " RON\n";
        std::cout << "Tip p3: " << p3->tip() << " | Pret final (10%): " << p3->pretFinal(10.0) << " RON\n";

        delete p1; delete p2; delete p3;
    }

    std::cout << "\n=== dynamic_cast ===\n";
    {
        Reteta r("Test", 60);
        r.adaugaIngredient(Ingredient("Espresso", 30, "ml"));
        Bautura  b(r, "Cafea",     10.0, "rece", false);
        Sandwich s(r, "Sandvisuri",14.0, true,   true);

        const Produs* ptr = &b;
        if (const auto* bptr = dynamic_cast<const Bautura*>(ptr))
            std::cout << "Bautura: temp=" << bptr->getTemperatura()
                      << ", cofeina=" << (bptr->areCofeina() ? "da" : "nu") << "\n";

        ptr = &s;
        if (const auto* sptr = dynamic_cast<const Sandwich*>(ptr))
            std::cout << "Sandwich: vegetarian=" << (sptr->esteVegetarianCheck() ? "da" : "nu")
                      << ", gluten-free=" << (sptr->esteGlutenFreeCheck() ? "da" : "nu") << "\n";
    }

    std::cout << "\n=== Exceptii ===\n";
    try {
        Reteta r("Test", 60);
        Bautura produsRau(r, "Test", -5.0);
    } catch (const PretInvalidException& e) {
        std::cout << "[CATCH PretInvalid] " << e.what() << "\n";
    }

    try {
        Reteta r("Test", 60);
        r.adaugaIngredient(Ingredient("Espresso", 30, "ml"));
        Bautura b(r, "Cafea", 10.0);
        (void)b.pretFinal(150.0);
    } catch (const DiscountInvalidException& e) {
        std::cout << "[CATCH DiscountInvalid] " << e.what() << "\n";
    }

    try {
        Comanda c("Test", -10.0);
    } catch (const DiscountInvalidException& e) {
        std::cout << "[CATCH DiscountInvalid Comanda] " << e.what() << "\n";
    }

    try {
        cafenea.incarcaProduseDinFisier("assets/produse.txt");
        throw CafeneaException("Exceptie generica de test");
    } catch (const std::exception& e) {
        std::cout << "[CATCH std::exception] " << e.what() << "\n";
    }

    std::cout << "\n=== Comenzi ===\n";

    Reteta rC1("Cappuccino", 120);
    rC1.adaugaIngredient(Ingredient("Espresso", 30, "ml"));
    rC1.adaugaIngredient(Ingredient("Lapte", 150, "ml"));
    Bautura cappuccino(rC1, "Cafea", 12.0, "calda", true);

    Reteta rC2("Americano", 60);
    rC2.adaugaIngredient(Ingredient("Espresso", 30, "ml"));
    rC2.adaugaIngredient(Ingredient("Apa", 200, "ml"));
    Bautura americano(rC2, "Cafea", 9.0, "calda", true);

    Reteta rD("Brownie de ciocolata", 180);
    rD.adaugaIngredient(Ingredient("Faina", 100, "g"));
    rD.adaugaIngredient(Ingredient("Cacao", 8, "g"));
    rD.adaugaIngredient(Ingredient("Oua", 2, "buc"));
    rD.adaugaIngredient(Ingredient("Unt", 50, "g"));
    Desert brownie(rD, "Desert", 15.0, 450.0, true);

    Reteta rS("Club Sandwich", 45);
    rS.adaugaIngredient(Ingredient("Paine", 80, "g"));
    rS.adaugaIngredient(Ingredient("Pui", 100, "g"));
    rS.adaugaIngredient(Ingredient("Salata", 30, "g"));
    rS.adaugaIngredient(Ingredient("Rosii", 40, "g"));
    Sandwich clubSandwich(rS, "Sandvisuri", 18.0, false, false);

    Comanda c1("Ana Ionescu", 0.0);
    c1.adaugaProdus(cappuccino);
    c1.adaugaProdus(brownie);

    Comanda c2("Mihai Popescu", 5.0);
    c2.adaugaProdus(americano);
    c2.adaugaProdus(clubSandwich);

    std::cout << c1 << "\n" << c2 << "\n";

    std::cout << "=== Copy-and-swap Comanda ===\n";
    Comanda c1_copie(c1);
    std::cout << "Copie c1: " << c1_copie;
    Comanda c_assign("Temp", 0.0);
    c_assign = c2;
    std::cout << "Dupa operator=: " << c_assign << "\n";

    std::cout << "=== Copy-and-swap Cafenea ===\n";
    Cafenea cafenea2(cafenea);
    std::cout << "Copie cafenea: " << cafenea2 << "\n";

    double disc = c2.aplicaPromotie(20.0, 10.0);
    std::cout << "\nDiscount c2 dupa promotie: " << disc << "%\n";

    c1.avanseazaStatus();
    c1.avanseazaStatus();

    cafenea.adaugaComanda(c1);
    cafenea.adaugaComanda(c2);

    cafenea.setDisponibilitate("Mocha", false);

    cafenea.raportZilnic();
    cafenea.raportDupaTip();

    std::cout << "\n=== Statistici statice ===\n";
    std::cout << "Total produse create:        " << Produs::getTotalProduseCréate()       << "\n";
    std::cout << "Total bauturi vandute:        " << Bautura::getTotalBauturiVandute()      << "\n";
    std::cout << "Total deserturi vandute:      " << Desert::getTotalDeserturiVandute()     << "\n";
    std::cout << "Total sandwichuri vandute:    " << Sandwich::getTotalSandwichuriVandute() << "\n";

    std::cout << "\n*** TOATE TESTELE FINALIZATE ***\n";
    return 0;
}
