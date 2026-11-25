#pragma once
#include <vector>
namespace uin {
double moyenne(const std::vector<double>& notes);
bool estValide(double note);
double arrondir(double valeur, int decimales);
}
