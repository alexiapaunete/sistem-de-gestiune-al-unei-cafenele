#include <iostream>
#include <map>
#include <string>

class Inventar {
private:
    std::map<std::string, double> stoc;
    std::map<std::string, double> praguri;

public:
    void consuma(std::string ingredient, double cantitate) {
        if (stoc[ingredient] >= cantitate) {
            stoc[ingredient] -= cantitate;
            if (stoc[ingredient] < praguri[ingredient]) {
                std::cout << "ALERTA: Trebuie restock la " << ingredient << "!" << std::endl;
            }
        } else {
            std::cout << "Eroare: Stoc insuficient de " << ingredient << std::endl;
        }
    }
};

