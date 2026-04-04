#include <iostream>
#include <vector>
#include <string>

class Ingredient {
    std::string nume;
    double cantitate;
public:
    Ingredient(std::string n = "", double c = 0) : nume(n), cantitate(c) {}

    friend std::ostream& operator<<(std::ostream& os, const Ingredient& i) {
        os << i.nume << ": " << i.cantitate;
        return os;
    }
};

class Reteta {
    std::string numeBautura;
    std::vector<Ingredient> ingrediente;

public:
    Reteta(std::string nume = "") : numeBautura(nume) {}

    void adaugaIngredient(const Ingredient& ing) {
        ingrediente.push_back(ing);
    }

    friend std::ostream& operator<<(std::ostream& os, const Reteta& r) {
        os << "Reteta pentru " << r.numeBautura << " contine: ";
        for(const auto& ing : r.ingrediente) os << "[" << ing << "] ";
        return os;
    }
};

class Produs {
    Reteta reteta;
    double pret;
    static int TVA;
public:
    Produs(const Reteta& r, double p) : reteta(r), pret(p) {}

    Produs(const Produs& other) : reteta(other.reteta), pret(other.pret) {}

    Produs& operator=(const Produs& other) {
        if (this != &other) {
            reteta = other.reteta;
            pret = other.pret;
        }
        return *this;
    }

    ~Produs() {}

    double calculeazaPretFinal(double discount) const {
        return (pret - (pret * discount / 100)) * 1.19;
    }

    friend std::ostream& operator<<(std::ostream& os, const Produs& p) {
        os << "Produs: " << p.reteta << " | Pret baza: " << p.pret;
        return os;
    }
};