#include <iostream>
#include <array>
#include <vector>

#include "include/Example.h"
// This also works if you do not want `include/`, but some editors might not like it
// #include "Example.h"

class panou_iluminare {
    bool aprins;
    int brightness;
    std::string firma;
};

class grup_iluminare {
    std::vector<panou_iluminare> panouri;
};

class cuier {
    int nr_haine;
    int nr_randuri;
public:
    int get_nr_randuri() { return nr_randuri;}
    int get_nr_haine() {
        if (nr_randuri == 0)
            return -1;
        return nr_haine;
    }

    void set_nr_randuri(int nr) {
        if (nr < 1)
            return;
        nr_randuri = nr;
    }

    void set_nr_haine(int nr) {nr_haine = nr;}
};


class sala {
    std::vector<grup_iluminare> grupLumina;
    int numar;
    double zgomot;
    cuier cuier;
};


int main() {
    cuier c1;
    //c1.nrhaine = 2;
    c1.set_nr_haine(2);
    std::cout << c1.nr_haine << '\n';

    std::cout << "lalala\n";
    Example e1;
    e1.g();
    std::array<int, 100> v{};
    int nr;
    std::cout << "Introduceți nr: ";
    /////////////////////////////////////////////////////////////////////////
    /// Observație: dacă aveți nevoie să citiți date de intrare de la tastatură,
    /// dați exemple de date de intrare folosind fișierul tastatura.txt
    /// Trebuie să aveți în fișierul tastatura.txt suficiente date de intrare
    /// (în formatul impus de voi) astfel încât execuția programului să se încheie.
    /// De asemenea, trebuie să adăugați în acest fișier date de intrare
    /// pentru cât mai multe ramuri de execuție.
    /// Dorim să facem acest lucru pentru a automatiza testarea codului, fără să
    /// mai pierdem timp de fiecare dată să introducem de la zero aceleași date de intrare.
    ///
    /// Pe GitHub Actions (bife), fișierul tastatura.txt este folosit
    /// pentru a simula date introduse de la tastatură.
    /// Bifele verifică dacă programul are erori de compilare, erori de memorie și memory leaks.
    ///
    /// Dacă nu puneți în tastatura.txt suficiente date de intrare, îmi rezerv dreptul să vă
    /// testez codul cu ce date de intrare am chef și să nu pun notă dacă găsesc vreun bug.
    /// Impun această cerință ca să învățați să faceți un demo și să arătați părțile din
    /// program care merg (și să le evitați pe cele care nu merg).
    ///
    /////////////////////////////////////////////////////////////////////////
    std::cin >> nr;
    /////////////////////////////////////////////////////////////////////////
    for(int i = 0; i < nr; ++i) {
        std::cout << "v[" << i << "] = ";
        std::cin >> v[i];
    }
    std::cout << "\n\n";
    std::cout << "Am citit de la tastatură " << nr << " elemente:\n";
    for(int i = 0; i < nr; ++i) {
        std::cout << "- " << v[i] << "\n";
    }
    ///////////////////////////////////////////////////////////////////////////
    /// Pentru date citite din fișier, NU folosiți tastatura.txt. Creați-vă voi
    /// alt fișier propriu cu ce alt nume doriți.
    /// Exemplu:
    /// std::ifstream fis("date.txt");
    /// for(int i = 0; i < nr2; ++i)
    ///     fis >> v2[i];
    ///
    ///////////////////////////////////////////////////////////////////////////
    return 0;
}
