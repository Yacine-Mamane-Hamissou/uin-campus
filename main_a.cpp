#include "calculs.hpp"
#include <print>
#include <vector>
int main() {
    const std::vector<double> notes{12.5, 15.0, 9.25};
    const double m = uin::arrondir(uin::moyenne(notes), 2);
    std::println("Moyenne arrondie : {:.2f}, valide : {}", m, uin::estValide(m));
}
