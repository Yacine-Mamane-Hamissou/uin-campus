#include "calculs.hpp"
#include <cmath>
namespace uin {
double moyenne(const std::vector<double>& notes) {
    double somme{0.0};
    for (double n : notes) {
        somme += n;
    }
    return notes.empty() ? 0.0 : somme / static_cast<double>(notes.size());
}
bool estValide(double note) {
    return note >= 0.0 && note <= 20.0;
}
double arrondir(double valeur, int decimales) {
    const double facteur = std::pow(10.0, decimales);
    return std::round(valeur * facteur) / facteur;
}
}
