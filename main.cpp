#include <iostream>
#include "src/World.h"
#include "src/Common.h"
#include <omp.h>

#define NTHREADS 4

using namespace std;

int main() {
  printf("Set OpenMp\n");
  omp_set_num_threads(NTHREADS);
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

    printf("Run evolution\n");
    world->run_evolution();
  }
}
