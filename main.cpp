#include <iostream>
#include <string>
#include <chrono>

#include <mpi.h>

#include "src/World.h"
#include "src/Common.h"
#include "src/MpiSlave.h"

using namespace std;

int main() {

  MPI_Init(NULL, NULL); 
  
  //------ BASE MPI commands
  int mpi_comm_size;//quantity of processes requested
  int mpi_comm_rank;//rank of the current process
  //proc name infos
  char mpi_processor_name[MPI_MAX_PROCESSOR_NAME];
  int mpi_name_len;
  // MPI calls 
  MPI_Comm_size(MPI_COMM_WORLD, &mpi_comm_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &mpi_comm_rank);
  MPI_Get_processor_name(mpi_processor_name, &mpi_name_len);
  // Display base infos
  cout << "Processor " << mpi_processor_name << " start of process rank " << mpi_comm_rank
		<< " (" << mpi_comm_size << " processes requested)" << endl;
  //------ END OF BASE MPI commands
  
  //------- DEFINITION OF CUSTOM MPI DATATYPE
  MPI_Datatype dt_msg;
  MPI_Type_contiguous(MSG_SIZE, MPI_BYTE, &dt_msg);
   //a message is a string (list of char) closest type is vector of MPI_BYTE
  MPI_Type_commit(&dt_msg);
 //------- END OF DEFINITION OF CUSTOM MPI DATATYPE
  
  
  //Main Process Run All
  if( mpi_comm_rank == 0 )
  {
		printf("Init binding matrix\n");
		Common::init_binding_matrix(897685687);

		printf("Create World\n");
		World* world = new World(32, 32, 897986875);

		printf("Initialize environment\n");
		world->init_environment();

		auto t1 = chrono::high_resolution_clock::now();
		//
		bool test = false;
		if (test) {
			world->test_mutate();
		} else {
			printf("Initialize random population\n");
			world->random_population();

			printf("Run evolution\n");
			world->run_evolution();
		}
		//
		auto t2 = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds> (t2 - t1).count();
		cout << "Time run evolution : " << duration/1000000.0 << "s" << endl;
		//kill all remaining processes
		char msg[MSG_SIZE] = "END";//Note : outside of init, use strcpy( msg, "str")
		for( int comm_id=1; comm_id<mpi_comm_size; comm_id++){
			MPI_Send( &msg, MSG_SIZE, MPI_CHAR, comm_id, 0, MPI_COMM_WORLD); 
		}
  }
  //Subprocesses obey
  else
  {
		MpiSlave slave( mpi_comm_rank, 0);
		slave.run();

  }
  MPI_Finalize();
  cout << "Processor " << mpi_processor_name << " end of process rank " << mpi_comm_rank
		<< " (" << mpi_comm_size << " processes requested)" << endl;
  
}
