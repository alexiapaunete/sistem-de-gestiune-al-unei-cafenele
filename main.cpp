#include <iostream>
#include <vector>
#include <string>

class Ingredient {
    std::string nume;
    double cantitate;
public:
    Ingredient(std::string n = "", double c = 0) : nume(n), cantitate(c) {}

    // Operatorul << cerut pentru compunere
    friend std::ostream& operator<<(std::ostream& os, const Ingredient& i) {
        os << i.nume << ": " << i.cantitate;
        return os;
    }
};

class Reteta {
    std::string numeBautura;
    std::vector<Ingredient> ingrediente; // Compunere

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
    Reteta reteta; // Compunere
    double pret;
    static int TVA; // Un mic plus pentru complexitate

public:
    // Constructor cu parametri
    Produs(const Reteta& r, double p) : reteta(r), pret(p) {}

    // Regula celor 3 (Rule of Three) implementata pe o clasa (ex: Produs sau Cafenea)
    // Daca folosim std::vector si std::string, compilatorul le genereaza bine,
    // dar cerinta cere sa le scrii tu explicit pentru o clasa.
    Produs(const Produs& other) : reteta(other.reteta), pret(other.pret) {}

    Produs& operator=(const Produs& other) {
        if (this != &other) {
            reteta = other.reteta;
            pret = other.pret;
        }
        return *this;
    }

    ~Produs() {} // Destructor

    // Functie netriviala 1: Calcul pret cu reducere si taxe
    double calculeazaPretFinal(double discount) const {
        return (pret - (pret * discount / 100)) * 1.19;
    }

    friend std::ostream& operator<<(std::ostream& os, const Produs& p) {
        os << "Produs: " << p.reteta << " | Pret baza: " << p.pret;
        return os;
    }
};