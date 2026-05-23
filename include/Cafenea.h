#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Produs.h"
#include "Comanda.h"
#include "Inventar.h"

class Cafenea {
    std::string          nume;
    std::string          adresa;
    std::vector<Produs*> meniu;
    std::vector<Comanda> istoricComenzi;
    Inventar             stocGeneral;

    void copiazaMeniu(const std::vector<Produs*>& sursa);
    void elibereazaMeniu();

public:
    Cafenea(std::string numeLocal, std::string adresaLocal);

    Cafenea(const Cafenea& other);
    Cafenea& operator=(Cafenea other);
    ~Cafenea();

    friend void swap(Cafenea& a, Cafenea& b) noexcept;

    void adaugaProdus(const Produs& p);
    void afiseazaMeniu() const;
    void setDisponibilitate(const std::string& numeProdus, bool disponibilitate);
    void adaugaComanda(Comanda c);
    void raportZilnic() const;
    void aprovizioneaza(const std::string& ingredient, double cantitate, double prag = 10.0);

    void raportDupaTip() const;

    friend std::ostream& operator<<(std::ostream& os, const Cafenea& c);
};
