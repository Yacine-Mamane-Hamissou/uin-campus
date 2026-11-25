module;
#include <string_view>
module uin.regles;
namespace uin {
std::string_view libelle(double moyenne) {
    return moyenne >= 10.0 ? "Bien" : "Ajourn‚";
}
}
