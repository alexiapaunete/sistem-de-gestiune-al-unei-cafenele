#include <iostream>
#include <iomanip>
#include "Cafenea.h"
#include "Bautura.h"
#include "Desert.h"
#include "Exceptii.h"

int main() {
    std::cout << std::fixed << std::setprecision(2);

    Ingredient espresso("Espresso",    30.0,  "ml");
    Ingredient lapte   ("Lapte",      150.0,  "ml");
    Ingredient zahar   ("Zahar",        5.0,  "g");
    Ingredient sirop   ("Sirop vanilie",10.0, "ml");
    Ingredient apa     ("Apa",        200.0,  "ml");
    Ingredient cacao   ("Cacao",        8.0,  "g");
    Ingredient frisca  ("Frisca",      30.0,  "ml");
    Ingredient faina   ("Faina",      100.0,  "g");
    Ingredient oua     ("Oua",          2.0,  "buc");
    Ingredient unt     ("Unt",         50.0,  "g");

    Reteta retCapuccino("Cappuccino", 120);
    retCapuccino.adaugaIngredient(espresso);
    retCapuccino.adaugaIngredient(lapte);
    retCapuccino.adaugaIngredient(zahar);

    Reteta retLatte("Caffe Latte", 90);
    retLatte.adaugaIngredient(espresso);
    retLatte.adaugaIngredient(lapte);
    retLatte.adaugaIngredient(sirop);

    Reteta retAmericano("Americano", 60);
    retAmericano.adaugaIngredient(espresso);
    retAmericano.adaugaIngredient(apa);

    Reteta retMocha("Mocha", 150);
    retMocha.adaugaIngredient(espresso);
    retMocha.adaugaIngredient(lapte);
    retMocha.adaugaIngredient(cacao);
    retMocha.adaugaIngredient(frisca);

    Reteta retIcedLatte("Iced Latte", 60);
    retIcedLatte.adaugaIngredient(espresso);
    retIcedLatte.adaugaIngredient(lapte);

    Reteta retBrownie("Brownie de ciocolata", 180);
    retBrownie.adaugaIngredient(faina);
    retBrownie.adaugaIngredient(cacao);
    retBrownie.adaugaIngredient(oua);
    retBrownie.adaugaIngredient(unt);

    Reteta retCroissant("Croissant", 60);
    retCroissant.adaugaIngredient(faina);
    retCroissant.adaugaIngredient(unt);

    Bautura capuccino (retCapuccino, "Cafea",     12.0, "calda", true);
    Bautura latte     (retLatte,     "Cafea",     14.0, "calda", true);
    Bautura americano (retAmericano, "Cafea",      9.0, "calda", true);
    Bautura mocha     (retMocha,     "Cafea",     16.0, "calda", true);
    Bautura icedLatte (retIcedLatte, "Cafea rece",13.0, "rece",  true);
    Desert  brownie   (retBrownie,   "Desert",    15.0, 450.0,   true);
    Desert  croissant (retCroissant, "Patiserie",  8.0, 280.0,  false);

    std::cout << "=== Polimorfism prin Produs* ===\n";
    Produs* p1 = capuccino.clone();
    Produs* p2 = brownie.clone();
    std::cout << *p1 << "\n";
    std::cout << *p2 << "\n";
    std::cout << "Tip p1: " << p1->tip() << "\n";
    std::cout << "Tip p2: " << p2->tip() << "\n";
    std::cout << "Pret final p1 (10% disc): " << p1->pretFinal(10.0) << " RON\n";
    std::cout << "Pret final p2 (10% disc): " << p2->pretFinal(10.0) << " RON\n\n";
    delete p1;
    delete p2;

    std::cout << "=== dynamic_cast ===\n";
    const Produs* ptr = &latte;
    if (const auto* b = dynamic_cast<const Bautura*>(ptr)) {
        std::cout << "Este Bautura. Temperatura: " << b->getTemperatura()
                  << ", cofeina: " << (b->areCofeina() ? "da" : "nu") << "\n";
    }
    ptr = &brownie;
    if (const auto* d = dynamic_cast<const Desert*>(ptr)) {
        std::cout << "Este Desert. Calorii: " << d->getCalorii()
                  << ", gluten: " << (d->areGluten() ? "da" : "nu") << "\n\n";
    }

    std::cout << "=== Exceptii ===\n";

    try {
        Bautura produsRau(retAmericano, "Test", -5.0);
    } catch (const PretInvalidException& e) {
        std::cout << "[CATCH PretInvalid] " << e.what() << "\n";
    }

    try {
        (void)capuccino.pretFinal(150.0);
    } catch (const DiscountInvalidException& e) {
        std::cout << "[CATCH DiscountInvalid] " << e.what() << "\n";
    }

    try {
        Comanda c("Test", -10.0);
    } catch (const DiscountInvalidException& e) {
        std::cout << "[CATCH DiscountInvalid Comanda] " << e.what() << "\n";
    }

    try {
        throw CafeneaException("Exceptie generica de test");
    } catch (const std::exception& e) {
        std::cout << "[CATCH std::exception] " << e.what() << "\n\n";
    }

    Cafenea cafenea("Aroma Urbana", "Str. Victoriei 42, Bucuresti");

    cafenea.aprovizioneaza("Espresso",      500.0,  50.0);
    cafenea.aprovizioneaza("Lapte",        1000.0, 200.0);
    cafenea.aprovizioneaza("Zahar",         200.0,  20.0);
    cafenea.aprovizioneaza("Sirop vanilie", 100.0,  10.0);
    cafenea.aprovizioneaza("Apa",          2000.0, 500.0);
    cafenea.aprovizioneaza("Cacao",         200.0,  30.0);
    cafenea.aprovizioneaza("Frisca",        500.0,  50.0);
    cafenea.aprovizioneaza("Faina",         500.0,  50.0);
    cafenea.aprovizioneaza("Oua",            20.0,   5.0);
    cafenea.aprovizioneaza("Unt",           300.0,  30.0);

    cafenea.adaugaProdus(capuccino);
    cafenea.adaugaProdus(latte);
    cafenea.adaugaProdus(americano);
    cafenea.adaugaProdus(mocha);
    cafenea.adaugaProdus(icedLatte);
    cafenea.adaugaProdus(brownie);
    cafenea.adaugaProdus(croissant);

    try {
        cafenea.adaugaProdus(capuccino);
    } catch (const ProdusDuplicatException& e) {
        std::cout << "[CATCH ProdusDuplicat] " << e.what() << "\n\n";
    }

    std::cout << cafenea << "\n";
    cafenea.afiseazaMeniu();
    cafenea.raportDupaTip();

    std::cout << "\n=== Comenzi ===\n";
    Comanda c1("Ana Ionescu", 0.0);
    c1.adaugaProdus(capuccino);
    c1.adaugaProdus(brownie);

    Comanda c2("Mihai Popescu", 5.0);
    c2.adaugaProdus(americano);
    c2.adaugaProdus(latte);
    c2.adaugaProdus(croissant);

    Comanda c3("Elena Dumitrescu", 0.0);
    c3.adaugaProdus(icedLatte);
    c3.adaugaProdus(mocha);

    std::cout << c1 << "\n" << c2 << "\n" << c3;

    std::cout << "=== Copy-and-swap Comanda ===\n";
    Comanda c1_copie(c1);
    std::cout << "Copie c1: " << c1_copie;
    Comanda c_assign("Temp", 0.0);
    c_assign = c2;
    std::cout << "Dupa operator= : " << c_assign << "\n";

    std::cout << "=== Copy-and-swap Cafenea ===\n";
    Cafenea cafenea2(cafenea);
    std::cout << "Copie cafenea: " << cafenea2 << "\n";

    double disc = c2.aplicaPromotie(20.0, 10.0);
    std::cout << "Discount c2 dupa promotie: " << disc << "%\n";

    c1.avanseazaStatus();
    c1.avanseazaStatus();

    cafenea.adaugaComanda(c1);
    cafenea.adaugaComanda(c2);
    cafenea.adaugaComanda(c3);

    cafenea.setDisponibilitate("Mocha", false);
    std::cout << "\nToate disponibile c3 (Mocha indisponibil): "
              << (c3.toateDisponibile() ? "da" : "nu") << "\n";

    cafenea.raportZilnic();
    cafenea.raportDupaTip();

    std::cout << "\n=== Statistici statice ===\n";
    std::cout << "Total produse create:      " << Produs::getTotalProduseCréate()    << "\n";
    std::cout << "Total bauturi vandute:     " << Bautura::getTotalBauturiVandute()  << "\n";
    std::cout << "Total deserturi vandute:   " << Desert::getTotalDeserturiVandute() << "\n";

    std::cout << "\n*** TOATE TESTELE FINALIZATE ***\n";
    return 0;
}
