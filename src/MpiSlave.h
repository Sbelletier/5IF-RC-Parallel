//
// Created by sbelletier on 8/12/2017
//
#ifndef PDC_EVOL_MODEL_MPISLAVE_H
#define PDC_EVOL_MODEL_MPISLAVE_H

#include <mpi.h>

#include "Protein.h"
#include "Pump.h"

static const int MSG_SIZE=50;

static MPI_Datatype dt_msg;

/*
 * Note: Requires delete once over
 */
Protein* rcvProtein(int rank_src);
void sendProtein(Protein* p, int rank_dest, bool broadcast);

/*
 * Note: Requires delete once over
 */
Pump* rcvPump(int rank_src);
void sendPump(Pump* p, int rank_dest, bool broadcast);

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
		void compute_protein_concentration_rna_deltas();
		
		void activate_pump();
		
		int id_;
		int masterId_;
	
};

#endif //PDC_EVOL_MODEL_MPISLAVE_H

