#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Ingredient.h"

class Reteta {
    std::string         numeBautura;
    std::vector<Ingredient> ingrediente;
    int                 timpPreparare;

    static bool cantitatEValida(double c);

public:
    explicit Reteta(std::string nume = "", int timpSec = 0);

    void adaugaIngredient(const Ingredient& ing);

    [[nodiscard]] const std::string& getNume()          const;
    [[nodiscard]] int                getTimpPreparare()  const;
    [[nodiscard]] int                numarIngrediante()  const;

    [[nodiscard]] Reteta scalata(double factor) const;

    [[nodiscard]] bool contineIngredient(const std::string& numeIng) const;

    friend std::ostream& operator<<(std::ostream& os, const Reteta& r);

    const std::vector<Ingredient>& getListaIngrediente() const {
        return ingrediente;
    }
};
