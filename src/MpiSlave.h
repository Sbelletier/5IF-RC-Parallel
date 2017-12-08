//
// Created by sbelletier on 8/12/2017
//
#ifndef PDC_EVOL_MODEL_MPISLAVE_H
#define PDC_EVOL_MODEL_MPISLAVE_H

#include <mpi.h>

static const int MSG_SIZE=20;

static MPI_Datatype dt_msg;

class MpiSlave {

	public:
	
		/*
		 * Constructor for the parallelisation slave
		 * id : the comm_id of the slave
		 * masterId : the comm_id of the main process (normally 0)
		 */
		MpiSlave( int id, int masterId );
		
		/*
		 * Launch the main execution loop of the slave
		 */
		int run();
		
	protected:
		
		int id_;
		int masterId_;
	
};

#endif //PDC_EVOL_MODEL_MPISLAVE_H

