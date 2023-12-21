#include <algorithm> // sort
#include <array>
#include <cstdint> // uint8_t
#include <cstdlib> // abs
#include <stdexcept>

using enum_type = uint8_t;

// clang-format off
enum : enum_type {
  UNKNOWN,

  CONTEE, FINCH, MARCOLLA, NATSIOU, WINSLOW,
  BLUE, GREEN, RED, PURPLE, WHITE,
  DIAMOND, MEDAL, PENDANT, RING, TIN,
  BALETON, DABOKVA, DUNWALL, FRAEPORT, KARNACA,
  ABSINTHE, BEER, RUM, WHISKEY, WINE
};
// clang-format on

const char *to_string(enum_type e) {
#define CASE(x)                                                                \
  case x:                                                                      \
    return #x;

  switch (e) {
    CASE(UNKNOWN)
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

struct Move {
  enum_type value;
  int pos;

  Move(enum_type _value, int _pos) : value(_value), pos(_pos) {}
};

struct State {
  std::array<enum_type, 5> women;
  std::array<enum_type, 5> colors;
  std::array<enum_type, 5> items;
  std::array<enum_type, 5> cities;
  std::array<enum_type, 5> drinks;

  State() {
    women = {UNKNOWN};
    colors = {UNKNOWN};
    items = {UNKNOWN};
    cities = {UNKNOWN};
    drinks = {UNKNOWN};
  }

  void apply(const Move &move) {
    if (move.value <= WINSLOW) {
      women[move.pos] = move.value;
    } else if (move.value <= WHITE) {
      colors[move.pos] = move.value;
    } else if (move.value <= TIN) {
      items[move.pos] = move.value;
    } else if (move.value <= KARNACA) {
      cities[move.pos] = move.value;
    } else if (move.value <= WINE) {
      drinks[move.pos] = move.value;
    }
  }

  void unapply(const Move &move) {
    if (move.value <= WINSLOW) {
      women[move.pos] = UNKNOWN;
    } else if (move.value <= WHITE) {
      colors[move.pos] = UNKNOWN;
    } else if (move.value <= TIN) {
      items[move.pos] = UNKNOWN;
    } else if (move.value <= KARNACA) {
      cities[move.pos] = UNKNOWN;
    } else if (move.value <= WINE) {
      drinks[move.pos] = UNKNOWN;
    }
  }

  std::vector<enum_type> unset_women() const {
    std::vector<enum_type> ret;
    for (enum_type e = CONTEE; e <= WINSLOW; ++e) {
      if (std::find(women.begin(), women.end(), e) == women.end()) {
        ret.push_back(e);
      }
    }
    return ret;
  }
  std::vector<enum_type> unset_colors() const {
    std::vector<enum_type> ret;
    for (enum_type e = BLUE; e <= WHITE; ++e) {
      if (std::find(colors.begin(), colors.end(), e) == colors.end()) {
        ret.push_back(e);
      }
    }
    return ret;
  }
  std::vector<enum_type> unset_items() const {
    std::vector<enum_type> ret;
    for (enum_type e = DIAMOND; e <= TIN; ++e) {
      if (std::find(items.begin(), items.end(), e) == items.end()) {
        ret.push_back(e);
      }
    }
    return ret;
  }
  std::vector<enum_type> unset_cities() const {
    std::vector<enum_type> ret;
    for (enum_type e = BALETON; e <= KARNACA; ++e) {
      if (std::find(cities.begin(), cities.end(), e) == cities.end()) {
        ret.push_back(e);
      }
    }
    return ret;
  }
  std::vector<enum_type> unset_drinks() const {
    std::vector<enum_type> ret;
    for (enum_type e = ABSINTHE; e <= WINE; ++e) {
      if (std::find(drinks.begin(), drinks.end(), e) == drinks.end()) {
        ret.push_back(e);
      }
    }
    return ret;
  }

  std::vector<Move> moves() const {
    std::vector<Move> ret;
    // all unused women in the first unset spot
    for (size_t i = 0; i < 5; ++i) {
      if (women[i] == UNKNOWN) {
        for (enum_type e : unset_women()) {
          ret.push_back(Move(e, i));
        }
        return ret;
      }
    }
    // items
    for (size_t i = 0; i < 5; ++i) {
      if (items[i] == UNKNOWN) {
        for (enum_type e : unset_items()) {
          ret.push_back(Move(e, i));
        }
        return ret;
      }
    }
    // city
    for (size_t i = 0; i < 5; ++i) {
      if (cities[i] == UNKNOWN) {
        for (enum_type e : unset_cities()) {
          ret.push_back(Move(e, i));
        }
        return ret;
      }
    }
    // drink
    for (size_t i = 0; i < 5; ++i) {
      if (drinks[i] == UNKNOWN) {
        for (enum_type e : unset_drinks()) {
          ret.push_back(Move(e, i));
        }
        return ret;
      }
    }
    // all remaning color
    for (size_t i = 0; i < 5; ++i) {
      if (colors[i] == UNKNOWN) {
        for (enum_type e : unset_colors()) {
          ret.push_back(Move(e, i));
        }
        return ret;
      }
    }
    return ret;
  }
};

void dump_state(const State &state) {
  for (auto e : state.women) {
    printf("%9s", to_string(e));
  }
  printf("\n");
  for (auto e : state.items) {
    printf("%9s", to_string(e));
  }
  printf("\n");
  for (auto e : state.cities) {
    printf("%9s", to_string(e));
  }
  printf("\n");
  for (auto e : state.drinks) {
    printf("%9s", to_string(e));
  }
  printf("\n");
  for (auto e : state.colors) {
    printf("%9s", to_string(e));
  }
  printf("\n");
}

int pos(const std::array<enum_type, 5> &v, enum_type u) {
  return std::find(v.begin(), v.end(), u) - v.begin();
}

bool pos_same(const std::array<enum_type, 5> &a1, enum_type e1,
              const std::array<enum_type, 5> &a2, enum_type e2) {

  auto p1 = pos(a1, e1);
  auto p2 = pos(a2, e2);
  if (p1 != a1.size() && p2 != a2.size()) {
    return p1 == p2;
  } else if (p1 != a1.size()) {
    return a2[p1] == UNKNOWN || a2[p1] == e2;
  } else if (p2 != a2.size()) {
    return a1[p2] == UNKNOWN || a1[p2] == e1;
  }
  return true;
}

bool rule0(const State &state) {
  // contee wore purple
  return pos_same(state.colors, PURPLE, state.women, CONTEE);
}

bool rule1(const State &state) {
  // natsiou in position 0//
  if (state.women[0] == UNKNOWN) {
    // natsiou shouldn't be anywhere else
    return pos(state.women, NATSIOU) == 5;
  }
  return state.women[0] == NATSIOU;
}

bool rule2(const State &state) {
  // natsiou next to person wearing blue
  auto p1 = pos(state.women, NATSIOU);
  auto p2 = pos(state.colors, BLUE);
  if (p1 != 5 && p2 != 5) {
    return std::abs(p1 - p2) == 1;
  } else if (p1 != 5) {
    // we know where natsiou is
    // check that unknown is next to her
    if (p1 + 1 < 5) {
      return state.colors[p1 + 1] == UNKNOWN;
    } else if (p1 - 1 > 0) {
      return state.colors[p1 - 1] == UNKNOWN;
    }
  } else if (p2 != 5) {
    // we know where blue is
    // check that unknown person is next to it
    if (p2 + 1 < 5) {
      return state.women[p2 + 1] == UNKNOWN;
    } else if (p2 - 1 > 0) {
      return state.women[p2 - 1] == UNKNOWN;
    }
  }
  return true;
}

bool rule3(const State &state) {
  // green to the left of red//
  // if green can be anywhere to the left of red, there are 7 solutions
  // return pos(state.colors, GREEN) + 1 == pos(state.colors, RED);

  // if green is immediately left of red, there is only 1 solution
  auto p1 = pos(state.colors, GREEN);
  auto p2 = pos(state.colors, RED);
  if (p1 != 5 && p2 != 5) {
    return p1 + 1 == p2;
  } else if (p2 == 0) {
    return false;
  } else if (p1 == 4) {
    return false;
  } else if (p1 < 4) {
    return state.colors[p1 + 1] == RED || state.colors[p1 + 1] == UNKNOWN;
  } else if (p2 > 0) {
    return state.colors[p2 - 1] == GREEN || state.colors[p2 - 1] == UNKNOWN;
  }
  return true;
}

bool rule4(const State &state) {
  // Green woman has a beer//
  return pos_same(state.colors, GREEN, state.drinks, BEER);
}

bool rule5(const State &state) {
  // dabokva wearing white//
  return pos_same(state.cities, DABOKVA, state.colors, WHITE);
}

bool rule6(const State &state) {
  // War Medal next to Dabokva//
  auto p1 = pos(state.items, MEDAL);
  auto p2 = pos(state.cities, DABOKVA);
  if (p1 == 5 || p2 == 5) {
    return true;
  }
  return std::abs(p1 - p2) == 1;
}

bool rule7(const State &state) {
  // winslow has the ring
  return pos_same(state.women, WINSLOW, state.items, RING);
}

bool rule8(const State &state) {
  // from baleton has pendant
  return pos_same(state.cities, BALETON, state.items, PENDANT);
}

bool rule9(const State &state) {
  // fraeport next to tin//
  auto p1 = pos(state.cities, FRAEPORT);
  auto p2 = pos(state.items, TIN);
  if (p1 == 5 || p2 == 5) {
    return true;
  }
  return std::abs(p1 - p2) == 1;
}

bool rule10(const State &state) {
  // fraeport next to absinthe//
  auto p1 = pos(state.cities, FRAEPORT);
  auto p2 = pos(state.drinks, ABSINTHE);
  if (p1 == 5 || p2 == 5) {
    return true;
  }
  return std::abs(p1 - p2) == 1;
}

bool rule11(const State &state) {
  // finch has wine//
  return pos_same(state.women, FINCH, state.drinks, WINE);
}

bool rule12(const State &state) {
  // from karnaca has rum//
  return pos_same(state.cities, KARNACA, state.drinks, RUM);
}

bool rule13(const State &state) {
  // whiskey in the center//
  if (state.drinks[2] == UNKNOWN) {
    // whiskey should not be anywhere else
    return pos(state.drinks, WHISKEY) == 5;
  }
  return state.drinks[2] == WHISKEY;
}

bool rule14(const State &state) {
  // marcolla is from dunwall//
  return pos_same(state.cities, DUNWALL, state.women, MARCOLLA);
}

// clang-format off
auto RULES = {
    rule0, rule1, rule2, 
    rule3, rule4, rule5,
    rule6, rule7, rule8,
    rule9, rule10, rule11,
    rule12, rule13, rule14};
// clang-format off

static size_t nChecked = 0;
static size_t nExcluded = 0;

void search(State &state) {

  ++nChecked;

  // if this state breaks a rule, no need to consider children
  for (auto rule : RULES) {
    if (!rule(state)) {
      ++nExcluded;
      return;
    }
  }

  // if this state is okay so far, consider all children
  auto moves = state.moves();
  // printf("%zu moves\n", moves.size());
  if (moves.empty()) {
    printf("SUCCESS! (checked %zu arrangements, exluded %zu subtrees)\n", nChecked, nExcluded);
    dump_state(state);
  } else {
    for (const Move &move : moves) {
      state.apply(move);
      search(state);
      state.unapply(move);
    }
  }
}

int main(void) {
  State state;
  search(state);
  printf("DONE (checked %zu arrangements, exluded %zu subtrees)\n", nChecked, nExcluded);
}
