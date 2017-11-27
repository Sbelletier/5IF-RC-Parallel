#include <iostream>
#include "src/World.h"
#include "src/Common.h"
#include <omp.h>


using namespace std;

int main(int argc, char *argv[]) {
  printf("Set OpenMp\n");
  int nThreads = atoi(argv[1]);
  if(nThreads != 0){
    omp_set_num_threads(nThreads);
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
  } else {
    printf("Parameter 1 should be greater than 0\n");
  }

}
