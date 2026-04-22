#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Produs.h"

enum class StatusComanda { IN_ASTEPTARE, IN_PREPARARE, FINALIZATA, ANULATA };

class Comanda {
    int                  id;
    std::string          numeClient;
    std::vector<Produs>  produse;
    StatusComanda        status;
    double               discountGlobal;

    static int contor;


    static std::string statusToString(StatusComanda s);

public:
    explicit Comanda(std::string numeClient, double discountGlobal = 0.0);

    void adaugaProdus(const Produs& p);


    [[nodiscard]] double totalComanda() const;


    [[nodiscard]] int timpEstimat() const;


    double aplicaPromotie(double pragValoare, double discountExtra);


    [[nodiscard]] bool toateDisponibile() const;

    void avanseazaStatus();

    [[nodiscard]] int                       getId()        const;
    [[nodiscard]] const std::string&        getNumeClient() const;
    [[nodiscard]] StatusComanda             getStatus()     const;
    [[nodiscard]] const std::vector<Produs>& getProduse()   const;

    friend std::ostream& operator<<(std::ostream& os, const Comanda& c);
};
