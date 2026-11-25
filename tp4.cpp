#include <algorithm>
#include <cassert>
#include <format>
#include <iostream>
#include <print>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

namespace {

std::string lireLigne(std::string_view invite) {
    std::cout << invite;
    std::string ligne;
    std::getline(std::cin, ligne);
    return ligne;
}

bool estEntierStrict(const std::string& texte, int& valeur) {
    std::istringstream flux{texte};
    char reste{};
    return (flux >> valeur) && !(flux >> reste);
}

bool estReelStrict(std::string texte, double& valeur) {
    for (char& c : texte) {
        if (c == ',') c = '.';
    }
    std::istringstream flux{texte};
    char reste{};
    return (flux >> valeur) && !(flux >> reste);
}

} // namespace

int lireEntier(std::string_view invite, int min, int max) {
    while (std::cin) {
        const std::string ligne = lireLigne(invite);
        int valeur{};
        if (!estEntierStrict(ligne, valeur)) {
            std::cout << "Entree invalide, tape un entier.\n";
        } else if (valeur < min || valeur > max) {
            std::cout << "Choisis entre " << min << " et " << max << ".\n";
        } else {
            return valeur;
        }
    }
    return min;
}

double lireNote(std::string_view invite) {
    while (std::cin) {
        const std::string ligne = lireLigne(invite);
        double note{};
        if (!estReelStrict(ligne, note)) {
            std::cout << "Entree invalide, tape un nombre.\n";
        } else if (note < 0.0 || note > 20.0) {
            std::cout << "La note doit etre entre 0 et 20.\n";
        } else {
            return note;
        }
    }
    return 0.0;
}

namespace carnet {

enum class Ordre { Croissant, Decroissant };

struct Statistiques {
    double minimum{};
    double maximum{};
    double moyenne{};
    int nbValidees{};
};

[[nodiscard]] Statistiques calculerStatistiques(const std::vector<double>& notes) {
    assert(!notes.empty());
    const auto [mini, maxi] = std::ranges::minmax(notes);
    double somme{0.0};
    int validees{0};
    for (double n : notes) {
        somme += n;
        if (n >= 10.0) ++validees;
    }
    const double moy = somme / static_cast<double>(notes.size());
    return Statistiques{mini, maxi, moy, validees};
}

void appliquerBonus(std::vector<double>& notes, double bonus) {
    std::ranges::for_each(notes, [bonus](double& n) {
        n = std::clamp(n + bonus, 0.0, 20.0);
    });
}

void trier(std::vector<double>& notes, Ordre ordre) {
    if (ordre == Ordre::Croissant) {
        std::ranges::sort(notes);
    } else {
        std::ranges::sort(notes, [](double a, double b) { return a > b; });
    }
}

void afficherNotes(const std::vector<double>& notes) {
    if (notes.empty()) {
        std::println("Aucune note.");
        return;
    }
    for (std::size_t i{0}; i < notes.size(); ++i) {
        std::println("{:^>3}. {:6.2f}", i + 1, notes[i]);
    }
}

void ajouter(std::vector<double>& notes) {
    notes.push_back(lireNote("Note a ajouter : "));
}

void modifier(std::vector<double>& notes) {
    if (notes.empty()) {
        std::println("Aucune note a modifier.");
        return;
    }
    afficherNotes(notes);
    const int rang = lireEntier("Numero de la note : ", 1, static_cast<int>(notes.size()));
    notes[static_cast<std::size_t>(rang - 1)] = lireNote("Nouvelle note : ");
}

void supprimer(std::vector<double>& notes) {
    if (notes.empty()) {
        std::println("Aucune note a supprimer.");
        return;
    }
    afficherNotes(notes);
    const int rang = lireEntier("Numero de la note : ", 1, static_cast<int>(notes.size()));
    notes.erase(notes.begin() + (rang - 1));
}

void afficherStatistiques(const std::vector<double>& notes) {
    if (notes.empty()) {
        std::println("Aucune note.");
        return;
    }
    const auto [mini, maxi, moyenne, validees] = calculerStatistiques(notes);
    std::println("Min: {:.2f} | Max: {:.2f} | Moyenne: {:.2f} | Validees: {}/{}", mini, maxi, moyenne, validees, notes.size());
}

[[nodiscard]] int afficherMenu() {
    std::println("\n=== Carnet de notes ===");
    std::println("1. Ajouter une note");
    std::println("2. Afficher les notes");
    std::println("3. Modifier une note");
    std::println("4. Supprimer une note");
    std::println("5. Trier les notes");
    std::println("6. Statistiques");
    std::println("7. Appliquer un bonus");
    std::println("0. Quitter");
    return lireEntier("Choix : ", 0, 7);
}

} // namespace carnet

int main() {
    std::vector<double> notes;
    int choix{};
    do {
        choix = carnet::afficherMenu();
        switch (choix) {
            case 1: carnet::ajouter(notes); break;
            case 2: carnet::afficherNotes(notes); break;
            case 3: carnet::modifier(notes); break;
            case 4: carnet::supprimer(notes); break;
            case 5: {
                const int sens = lireEntier("1. Croissant  2. Decroissant : ", 1, 2);
                carnet::trier(notes, sens == 1 ? carnet::Ordre::Croissant : carnet::Ordre::Decroissant);
                break;
            }
            case 6: carnet::afficherStatistiques(notes); break;
            case 7: carnet::appliquerBonus(notes, lireNote("Bonus : ")); break;
            default: break;
        }
    } while (choix != 0);
}
