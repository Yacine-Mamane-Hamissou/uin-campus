module;
#include <string_view>
export module uin.regles;
export namespace uin {
constexpr bool estNoteValide(double note) { return note >= 0.0 && note <= 20.0; }
std::string_view libelle(double moyenne);
}
