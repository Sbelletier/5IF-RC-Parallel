//
// Created by sbelletier on 8/12/2017
//
#include <iostream>
#include <string>
#include <mpi.h>

#include "MpiSlave.h"

using namespace std;




MpiSlave::MpiSlave(int id, int masterId ){
	id_ = id;
	masterId_ = masterId;
}

int MpiSlave::run(){
	 //------- DEFINITION OF CUSTOM MPI DATATYPES
	  MPI_Type_contiguous(MSG_SIZE, MPI_BYTE, &dt_msg);
	   //a message is a string (list of char) closest type is vector of MPI_BYTE
	  MPI_Type_commit(&dt_msg);
	 //------- END OF DEFINITION OF CUSTOM MPI DATATYPES
	
	bool run = true;
	
	while( run ){
		char* msg;
		MPI_Recv(&msg, 1, dt_msg, masterId_, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		//convert to String for easier manipulation
		string msgString = msg;
		
		if(msgString == "END"){
			run = false;
		}
		
		
	}
}
