// add your imports here
#include <fstream>
#include <iostream>
#include <istream>
#include <unordered_set>

const std::string TEST_FOLDER = "\\tests\\";
unsigned int xorShift(unsigned int seed, int r1, int r2);

struct State {
  unsigned int x, y;
  // Operator overloading
  bool operator==(const State& other) const {
    return x == other.x && y == other.y;
  }
};

// Defining name space
namespace std {
  // Specializing template
  template <>
  struct hash<State> {
    // Defining hash value function
    std::size_t operator()(const State& state) const {
      // Computing hash value
      return state.x ^ state.y;
    }
  };
}

int main(){
  // Variable declaration
  int cycles = 0;
  int warmUps = 0;
  int statesCount = 0;
  std::unordered_set<State> states;
  State state = {1,2};

  // User input
  unsigned int seed, N, min, max;
  std::cin >> seed >> N >> min >> max;
  unsigned int i;

  // Sets state x to the seed
  state.x = seed;

  // Creates N number of random numbers
  for (i = N; i >= 1; i--) {
    // Creates 1 random number
    unsigned int randNum = xorShift(seed, min, max);
    // Sets state y and seed to the generated number
    state.y = randNum;
    seed = randNum;

    // If state has not been encountered, the warmup variable is incremented
    if (!states.contains(state)) {
      warmUps++;
    }
    states.insert({state});

    // If state has been encountered, the cycle variable is incremented
    statesCount = states.count(state);
    if (statesCount == 2) {
      cycles++;
    }
  }
  warmUps -= cycles;
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
