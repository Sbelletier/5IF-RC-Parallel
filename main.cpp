#include <iostream>
#include "src/World.h"
#include "src/Common.h"
#include <chrono>

using namespace std;

int main() {
  printf("Init binding matrix\n");
  Common::init_binding_matrix(897685687);

  printf("Create World\n");
  World* world = new World(32, 32, 897986875);

  printf("Initialize environment\n");
  world->init_environment();

  bool test = false;
  if (test) {
    world->test_mutate();
  } else {
    printf("Initialize random population\n");
    world->random_population();

    auto t1 = chrono::high_resolution_clock::now();
    printf("Run evolution\n");
    world->run_evolution();
    auto t2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds> (t2 - t1).count();
    cout << "Time run evolution : " << duration/1000000.0 << "s" << endl;
  }
}
