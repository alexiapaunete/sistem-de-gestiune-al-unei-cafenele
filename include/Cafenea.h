#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Produs.h"
#include "Comanda.h"
#include "Inventar.h"

class Cafenea {
private:
    std::string nume;
    std::string adresa;
    std::vector<Produs> meniu;
    std::vector<Comanda> istoricComenzi;
    Inventar stocGeneral;

public:
    Cafenea(std::string numeLocal, std::string adresaLocal);

    void adaugaProdus(const Produs& p);
    void afiseazaMeniu() const;
    std::vector<Produs> meniuDupaCategorie(const std::string& categorie) const;
    void setDisponibilitate(const std::string& numeProdus, bool disponibilitate);
    void adaugaComanda(Comanda c);
    void raportZilnic() const;
    void aprovizioneaza(std::string ingredient, double cantitate, double prag = 10.0);

    void meniuInteractiv();

    friend std::ostream& operator<<(std::ostream& os, const Cafenea& c);
};
