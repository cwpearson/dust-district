#include <algorithm> // sort
#include <array>
#include <cstdint> // uint8_t
#include <cstdlib> // abs
#include <stdexcept>

using enum_type = uint8_t;

// clang-format off
enum : enum_type {
  NATSIOU, CONTEE, FINCH, MARCOLLA, WINSLOW,
  RED, WHITE, GREEN, BLUE, PURPLE,
  MEDAL, TIN, PENDANT, RING, DIAMOND,
  FRAEPORT, DUNWALL, BALETON, DABOKVA, KARNACA,
  WINE, RUM, ABSINTHE, BEER, WHISKEY
};
// clang-format on

const char *to_string(enum_type e) {
#define CASE(x)                                                                \
  case x:                                                                      \
    return #x;

  switch (e) {
    CASE(NATSIOU)
    CASE(CONTEE)
    CASE(FINCH)
    CASE(MARCOLLA)
    CASE(WINSLOW)
    CASE(RED)
    CASE(WHITE)
    CASE(GREEN)
    CASE(BLUE)
    CASE(PURPLE)
    CASE(MEDAL)
    CASE(TIN)
    CASE(PENDANT)
    CASE(RING)
    CASE(DIAMOND)
    CASE(FRAEPORT)
    CASE(DUNWALL)
    CASE(BALETON)
    CASE(DABOKVA)
    CASE(KARNACA)
    CASE(WINE)
    CASE(RUM)
    CASE(ABSINTHE)
    CASE(BEER)
    CASE(WHISKEY)
  default:
    throw std::logic_error("Missed an enum in to_string");
  }
}

// clang-format off
std::array<enum_type, 5> WOMEN  = {NATSIOU, CONTEE, FINCH, MARCOLLA, WINSLOW};
std::array<enum_type, 5> COLORS = {RED, WHITE, GREEN, BLUE, PURPLE};
std::array<enum_type, 5> ITEMS  = {MEDAL, TIN, PENDANT, RING, DIAMOND};
std::array<enum_type, 5> CITIES = {FRAEPORT, DUNWALL, BALETON, DABOKVA, KARNACA};
std::array<enum_type, 5> DRINKS = {WINE, RUM, ABSINTHE, BEER, WHISKEY};
// clang-format on

void dump_state(size_t perm) {
  printf("== PERMUTATION %zu ==\n", perm);
  for (auto e : WOMEN) {
    printf("%9s", to_string(e));
  }
  printf("\n");
  for (auto e : ITEMS) {
    printf("%9s", to_string(e));
  }
  printf("\n");
  for (auto e : CITIES) {
    printf("%9s", to_string(e));
  }
  printf("\n");
  for (auto e : DRINKS) {
    printf("%9s", to_string(e));
  }
  printf("\n");
  for (auto e : COLORS) {
    printf("%9s", to_string(e));
  }
  printf("\n");
}

int pos(const std::array<enum_type, 5> &v, enum_type u) {
  return std::find(v.begin(), v.end(), u) - v.begin();
}

bool rule0() {
  // contee wore purple
  return pos(WOMEN, CONTEE) == pos(COLORS, PURPLE);
}

bool rule1() {
  // natsiou in position 0//
  return pos(WOMEN, NATSIOU) == 0;
}

bool rule2() {
  // natsiou next to person wearing blue
  return std::abs(pos(WOMEN, NATSIOU) - pos(COLORS, BLUE)) == 1;
}

bool rule3() {
  // green to the left of red//
  // if green can be anywhere to the left of red, there are 7 solutions
  // return pos(COLORS, GREEN) + 1 == pos(COLORS, RED);

  // if green is immediately left of red, there is only 1 solution
  return pos(COLORS, GREEN) + 1 == pos(COLORS, RED);
}

bool rule4() {
  // Green woman has a beer//
  return pos(COLORS, GREEN) == pos(DRINKS, BEER);
}

bool rule5() {
  // dabokva wearing white//
  return pos(CITIES, DABOKVA) == pos(COLORS, WHITE);
}

bool rule6() {
  // War Medal next to Dabokva//
  return std::abs(pos(ITEMS, MEDAL) - pos(CITIES, DABOKVA)) == 1;
}

bool rule7() {
  // winslow has the ring
  return pos(WOMEN, WINSLOW) == pos(ITEMS, RING);
}

bool rule8() {
  // from baleton has pendant//
  return pos(CITIES, BALETON) == pos(ITEMS, PENDANT);
}

bool rule9() {
  // fraeport next to tin//
  return std::abs(pos(CITIES, FRAEPORT) - pos(ITEMS, TIN)) == 1;
}

bool rule10() {
  // fraeport next to absinthe//
  return std::abs(pos(CITIES, FRAEPORT) - pos(DRINKS, ABSINTHE)) == 1;
}

bool rule11() {
  // finch has wine//
  return pos(WOMEN, FINCH) == pos(DRINKS, WINE);
}

bool rule12() {
  // from karnaca has rum//
  return pos(CITIES, KARNACA) == pos(DRINKS, RUM);
}

bool rule13() {
  // whiskey in the center//
  return pos(DRINKS, WHISKEY) == 2;
}

bool rule14() {
  // marcolla is from dunwall//
  return pos(CITIES, DUNWALL) == pos(WOMEN, MARCOLLA);
}

auto RULES = {
    // simplest rules
    rule1, rule13,
    // intermediate rules
    rule0, rule3, rule4, rule5, rule7, rule8, rule11, rule12, rule14,
    // least restrictive rules
    rule2, rule6, rule9, rule10};

int main(void) {

  // next_permutation goes in lexicographical order, so start sorted
  std::sort(WOMEN.begin(), WOMEN.end());
  std::sort(COLORS.begin(), COLORS.end());
  std::sort(ITEMS.begin(), ITEMS.end());
  std::sort(CITIES.begin(), CITIES.end());
  std::sort(DRINKS.begin(), DRINKS.end());

  size_t n = 0;
  do {
    do {
      do {
        do {
          do {
            bool violated = false;
            for (auto rule : RULES) {
              if (!rule()) {
                violated = true;
                break;
              }
            }

            if (!violated) {
              printf("\n");
              dump_state(n);
              printf("\n");
            }

            ++n;
            if (n % 100000000 == 0) {
              printf(" %zu", n / 100000000);
              fflush(stdout);
            }

          } while (std::next_permutation(DRINKS.begin(), DRINKS.end()));
        } while (std::next_permutation(CITIES.begin(), CITIES.end()));
      } while (std::next_permutation(ITEMS.begin(), ITEMS.end()));
    } while (std::next_permutation(COLORS.begin(), COLORS.end()));
  } while (std::next_permutation(WOMEN.begin(), WOMEN.end()));
}
