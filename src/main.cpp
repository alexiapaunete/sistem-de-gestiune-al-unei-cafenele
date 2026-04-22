#include <iostream>
#include <iomanip>
#include "Cafenea.h"

int main() {
    std::cout << std::fixed << std::setprecision(2);


    Ingredient espresso("Espresso",  30.0, "ml");
    Ingredient lapte("Lapte",       150.0, "ml");
    Ingredient zahar("Zahar",         5.0, "g");
    Ingredient siropVanilie("Sirop vanilie", 10.0, "ml");
    Ingredient apa("Apa",           200.0, "ml");
    Ingredient cacao("Cacao",         8.0, "g");
    Ingredient frisca("Frisca",      30.0, "ml");

    std::cout << "=== Ingrediente ===\n";
    std::cout << espresso << "\n";
    std::cout << lapte.scalat(2) << " (portie dubla)\n\n";


    Reteta retCapuccino("Cappuccino", 120);
    retCapuccino.adaugaIngredient(espresso);
    retCapuccino.adaugaIngredient(lapte);
    retCapuccino.adaugaIngredient(zahar);

    Reteta retLatte("Caffe Latte", 90);
    retLatte.adaugaIngredient(espresso);
    retLatte.adaugaIngredient(lapte);
    retLatte.adaugaIngredient(siropVanilie);

    Reteta retAmericano("Americano", 60);
    retAmericano.adaugaIngredient(espresso);
    retAmericano.adaugaIngredient(apa);

    Reteta retMocha("Mocha", 150);
    retMocha.adaugaIngredient(espresso);
    retMocha.adaugaIngredient(lapte);
    retMocha.adaugaIngredient(cacao);
    retMocha.adaugaIngredient(frisca);

    std::cout << "=== Retete ===\n";
    std::cout << retCapuccino << "\n";
    std::cout << retLatte     << "\n";
    std::cout << "Contine lapte: " << (retLatte.contineIngredient("Lapte") ? "da" : "nu") << "\n";

    Reteta retCapuccinoDouble = retCapuccino.scalata(2);
    std::cout << "Reteta scalata: " << retCapuccinoDouble << "\n\n";


    Produs capuccino(retCapuccino, "Cafea", 12.0);
    Produs latte    (retLatte,     "Cafea", 14.0);
    Produs americano(retAmericano, "Cafea",  9.0);
    Produs mocha    (retMocha,     "Cafea", 16.0);


    Produs cappuccinoCopie(capuccino);
    std::cout << "=== Produs (copie cu copy-ctor) ===\n" << cappuccinoCopie << "\n";


    Produs produsTemp = latte;
    produsTemp = americano;
    std::cout << "Dupa operator=: " << produsTemp << "\n";

    std::cout << "\n=== Functii Produs ===\n";
    std::cout << "Pret final cappuccino (fara discount): " << capuccino.pretFinal()       << " RON\n";
    std::cout << "Pret final cappuccino (10% discount):  " << capuccino.pretFinal(10.0)   << " RON\n";
    std::cout << "Timp servire cappuccino: "               << capuccino.timpServire()      << "s\n";
    std::cout << "Rezumat meniu: "                         << capuccino.rezumatMeniu()     << "\n\n";


    Cafenea cafenea("Aroma Urbana", "Str. Victoriei 42, Bucuresti");
    cafenea.adaugaProdus(capuccino);
    cafenea.adaugaProdus(latte);
    cafenea.adaugaProdus(americano);
    cafenea.adaugaProdus(mocha);

    cafenea.aprovizioneaza("Espresso", 500.0, 50.0);
    cafenea.aprovizioneaza("Lapte", 1000.0, 200.0);
    cafenea.aprovizioneaza("Zahar", 200.0, 20.0);
    cafenea.aprovizioneaza("Sirop vanilie", 100.0, 10.0);
    cafenea.aprovizioneaza("Apa", 2000.0, 500.0);
    cafenea.aprovizioneaza("Cacao", 200.0, 30.0);
    cafenea.aprovizioneaza("Frisca", 500.0, 50.0);

    std::cout << cafenea << "\n";
    cafenea.afiseazaMeniu();


    auto cafele = cafenea.meniuDupaCategorie("Cafea");
    std::cout << "\nProduse din categoria 'Cafea': " << cafele.size() << "\n";


    cafenea.setDisponibilitate("Mocha", false);
    std::cout << "Dupa dezactivare Mocha:\n";
    cafenea.afiseazaMeniu();


    Comanda c1("Ana Ionescu", 0.0);
    c1.adaugaProdus(capuccino);
    c1.adaugaProdus(latte);

    Comanda c2("Mihai Popescu", 5.0);
    c2.adaugaProdus(americano);
    c2.adaugaProdus(capuccino);
    c2.adaugaProdus(capuccino);

    Comanda c3("Elena Dumitrescu", 0.0);
    c3.adaugaProdus(latte);
    c3.adaugaProdus(mocha);

    std::cout << "\n=== Comenzi ===\n" << c1 << "\n" << c2 << "\n" << c3;


    std::cout << "Total c1: "           << c1.totalComanda()  << " RON\n";
    std::cout << "Timp estimat c1: "    << c1.timpEstimat()   << "s\n";
    std::cout << "Toate disponibile c3: " << (c3.toateDisponibile() ? "da" : "nu") << "\n";


    double discNou = c2.aplicaPromotie(30.0, 5.0);
    std::cout << "Discount c2 dupa promotie: " << discNou << "%\n";
    std::cout << "Total c2 dupa promotie: " << c2.totalComanda() << " RON\n\n";


    c1.avanseazaStatus();
    c1.avanseazaStatus();
    std::cout << "Status c1 dupa 2 avansari: ";
    std::cout << c1 << "\n";


    cafenea.adaugaComanda(c1);
    cafenea.adaugaComanda(c2);
    cafenea.adaugaComanda(c3);
    cafenea.raportZilnic();

    std::cout << "\n\n*** TESTELE AUTOMATE S-AU INCHEIAT ***\n";
    std::cout << "*** PORNIRE MOD INTERACTIV ***\n";


    cafenea.meniuInteractiv();


    return 0;
}
