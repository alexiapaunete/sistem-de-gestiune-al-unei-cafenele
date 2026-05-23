#include "Bautura.h"
#include <iomanip>
#include <sstream>

int Bautura::totalBauturiVandute = 0;

Bautura::Bautura(const Reteta& r, std::string cat, double pret,
                 std::string temp, bool cofeina)
    : Produs(r, std::move(cat), pret),
      temperatura(std::move(temp)),
      contineCofeina(cofeina)
{}

Bautura* Bautura::clone() const {
    return new Bautura(*this);
}

double Bautura::pretFinal(double discount) const {
    if (discount < 0.0 || discount > 100.0)
        throw DiscountInvalidException(discount);
    return pretBaza * (1.0 - discount / 100.0);
}

std::string Bautura::rezumatMeniu() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << getNume() << " (" << temperatura << ")"
        << " - " << pretBaza << " RON"
        << (contineCofeina ? " [cu cofeina]" : " [fara cofeina]");
    return oss.str();
}

std::string Bautura::tip() const { return "Bautura"; }

int Bautura::timpServire() const {
    return (temperatura == "rece") ? reteta.getTimpPreparare() / 2
                                   : reteta.getTimpPreparare();
}

bool        Bautura::areCofeina()      const { return contineCofeina; }
const std::string& Bautura::getTemperatura() const { return temperatura; }

int  Bautura::getTotalBauturiVandute()  { return totalBauturiVandute; }
void Bautura::inregistreazaVanzare()    { ++totalBauturiVandute; }

void Bautura::afiseaza(std::ostream& os) const {
    Produs::afiseaza(os);
    os << " | Temp: " << temperatura
       << " | Cofeina: " << (contineCofeina ? "da" : "nu");
}

std::ostream& operator<<(std::ostream& os, const Bautura& b) {
    b.afiseaza(os);
    return os;
}
