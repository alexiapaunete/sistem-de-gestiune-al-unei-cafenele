#pragma once
#include <iostream>
#include <string>

class Ingredient {
    std::string nume;
    double cantitate;
    std::string unitate;

public:
    Ingredient(std::string n = "", double c = 0.0, std::string u = "ml");

    [[nodiscard]] const std::string& getNume()    const;
    [[nodiscard]] double             getCantitate() const;
    [[nodiscard]] const std::string& getUnitate()  const;

    Ingredient scalat(double factor) const;

    friend std::ostream& operator<<(std::ostream& os, const Ingredient& i);
};
