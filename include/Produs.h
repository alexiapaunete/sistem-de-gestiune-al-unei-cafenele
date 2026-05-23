#pragma once
#include <iostream>
#include <string>
#include "Reteta.h"
#include "Inventar.h"
#include "Exceptii.h"

class Produs {
protected:
    Reteta      reteta;
    std::string categorie;
    double      pretBaza;
    bool        disponibil;

    static int totalProduseCréate;

public:
    Produs(const Reteta& r, std::string cat, double pret);

    [[nodiscard]] virtual Produs* clone() const = 0;

    [[nodiscard]] virtual double      pretFinal(double discount = 0.0) const = 0;
    [[nodiscard]] virtual std::string rezumatMeniu() const = 0;
    [[nodiscard]] virtual std::string tip() const = 0;

    [[nodiscard]] virtual int timpServire() const;
    virtual bool prepara(Inventar& inv) const;

    [[nodiscard]] const std::string& getCategorie() const;
    [[nodiscard]] std::string        getNume()       const;
    void                             setDisponibil(bool stare);
    [[nodiscard]] bool               esteDisponibil() const;
    [[nodiscard]] double             getPretBaza()    const;
    [[nodiscard]] const Reteta&      getReteta()      const;

    static int getTotalProduseCréate();

    virtual ~Produs() = default;

    friend std::ostream& operator<<(std::ostream& os, const Produs& p);

protected:
    virtual void afiseaza(std::ostream& os) const;
};
