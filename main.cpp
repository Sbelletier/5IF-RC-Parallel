#include <iostream>
#include "src/World.h"
#include "src/Common.h"
#include <omp.h>
#include <chrono>


using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[]) {
    printf("Set OpenMp\n");
    printf("%s", argv[1]);
    int nThreads = atoi(argv[1]);
    if(nThreads != 0){
        omp_set_num_threads(nThreads);
        printf("Init binding matrix\n");
        Common::init_binding_matrix(897685687);
//    Common::init_time_indicator();

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
            auto t1 = high_resolution_clock::now();
            printf("Run evolution\n");
            world->run_evolution();
            auto t2 = high_resolution_clock::now();
            auto duration =  duration_cast<microseconds>(t2-t1).count();
            cout << "Time run evolution : " << duration << endl;
//            cout << "nb_prot : " << nb_prot << endl;
        }
    } else {
        printf("Parameter 1 should be greater than 0\n");
    }

}