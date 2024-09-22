// add your imports here
#include <fstream>
#include <iostream>
#include <istream>
#include <unordered_set>

const std::string TEST_FOLDER = "\\tests\\";
unsigned int xorShift(unsigned int seed, int r1, int r2);

struct State {
  unsigned int x, y;

  bool operator==(const State& other) const {
    return x == other.x && y == other.y;
  }
};

// Defining name space
namespace std {
  // Specializing template
  template <>
  struct hash<State> {
    // Defining hash value funciton
    std::size_t operator()(const State& state) const {
      // Computing hash value
      return state.x ^ state.y;
    }
  };
}

int main(){
  int cycles = 0;
  int warmUps = 0;
  int statesCount = 0;
  std::unordered_set<State> states;
  State state = {0,0};

  unsigned int seed, N, min, max;
  std::cin >> seed >> N >> min >> max;
  unsigned int i;

  for (i = N; i >= 1; i--) {
    states.insert({seed,xorShift(seed, min, max)});

    if (!states.contains(state)) {
      warmUps++;
    }

    statesCount = states.count(state);
    if (statesCount == 2) {
      cycles++;
    }
  }
  warmUps -= cycles;

  std::cout << "Cycle period: " << cycles << std::endl;
  std::cout << "Warm up period: " << warmUps << std::endl;
}
//The purpose of this function is to take the number and xor shift it to output a pseudo-random number
unsigned int xorShift(unsigned int seed, int r1, int r2)
{
  seed = seed xor (seed << 13);
  seed = seed xor (seed >> 17);
  seed = seed xor (seed << 5);
  int value = r1 + (seed % (r2 - r1 + 1)); //clamps the value to between r1 and r2
          //output the new values
          std::cout << value << std::endl;
  return seed;
}
