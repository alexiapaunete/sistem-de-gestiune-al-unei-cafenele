#pragma once
#include <stdexcept>
#include <string>

class CafeneaException : public std::exception {
    std::string mesaj;
public:
    explicit CafeneaException(std::string msg) : mesaj(std::move(msg)) {}
    [[nodiscard]] const char* what() const noexcept override { return mesaj.c_str(); }
};

class PretInvalidException : public CafeneaException {
public:
    explicit PretInvalidException(double pret)
        : CafeneaException("Pret invalid: " + std::to_string(pret) + " RON (trebuie sa fie > 0)") {}
};

class DiscountInvalidException : public CafeneaException {
public:
    explicit DiscountInvalidException(double discount)
        : CafeneaException("Discount invalid: " + std::to_string(discount) + "% (trebuie sa fie intre 0 si 100)") {}
};

class StocInsuficientException : public CafeneaException {
public:
    explicit StocInsuficientException(const std::string& ingredient)
        : CafeneaException("Stoc insuficient pentru ingredientul: " + ingredient) {}
};

class ProdusDuplicatException : public CafeneaException {
public:
    explicit ProdusDuplicatException(const std::string& numeProdus)
        : CafeneaException("Produsul '" + numeProdus + "' exista deja in meniu") {}
};
