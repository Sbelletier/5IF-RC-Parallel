//
// Created by sbelletier on 8/12/2017
//
#include <iostream>
#include <string>
#include <map>

#include <mpi.h>



#include "MpiSlave.h"

using namespace std;

Protein* rcvProtein(int rank_src){
	int type;
	MPI_Recv(&type, 1, MPI_INT, rank_src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	float binding_pattern;
	MPI_Recv(&binding_pattern, 1, MPI_FLOAT, rank_src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	float value;
	MPI_Recv(&value, 1, MPI_FLOAT, rank_src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	
	Protein* p = new Protein(type, binding_pattern, value);
	
	float concentration;
	MPI_Recv(&concentration, 1, MPI_FLOAT, rank_src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	p->concentration_ = concentration;
	
	return p;
}

/*
 * rank is src if broadcast, dest otherwise
 * 
 */
void sendProtein(Protein* p, bool broadcast, int rank){
	if( broadcast ){
		MPI_Bcast( &(p->type_), 1, MPI_INT, rank, MPI_COMM_WORLD);
		MPI_Bcast( &(p->binding_pattern_), 1, MPI_FLOAT, rank, MPI_COMM_WORLD);
		MPI_Bcast( &(p->value_), 1, MPI_FLOAT, rank, MPI_COMM_WORLD);
		MPI_Bcast( &(p->concentration_), 1, MPI_FLOAT, rank, MPI_COMM_WORLD);
	}
	else {
		MPI_Send( &(p->type_), 1, MPI_INT, rank, 0, MPI_COMM_WORLD);
		MPI_Send( &(p->binding_pattern_), 1, MPI_FLOAT, rank, 0, MPI_COMM_WORLD);
		MPI_Send( &(p->value_), 1, MPI_FLOAT, rank, 0, MPI_COMM_WORLD);
		MPI_Send( &(p->concentration_), 1, MPI_FLOAT, rank, 0, MPI_COMM_WORLD);
	}
	
}



Pump* rcvPump(int rank_src){
	int int_outward;
	MPI_Recv(&int_outward, 1, MPI_INT, rank_src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	bool outward = int_outward != 0 ? true : false;
	float start_range;
	MPI_Recv(&start_range, 1, MPI_FLOAT, rank_src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	float end_range;
	MPI_Recv(&end_range, 1, MPI_FLOAT, rank_src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	int speed;
	MPI_Recv(&speed, 1, MPI_INT, rank_src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	
	Pump* p = new Pump( outward, start_range, end_range, speed);
	
	return p;
}

/*
 * rank is src if broadcast, dest otherwise
 * 
 */
void sendPump(Pump* p, bool broadcast, int rank){
	if( broadcast ){
		MPI_Bcast( &(p->in_out_), 1, MPI_INT, rank, MPI_COMM_WORLD);
		MPI_Bcast( &(p->start_range_), 1, MPI_FLOAT, rank, MPI_COMM_WORLD);
		MPI_Bcast( &(p->end_range_), 1, MPI_FLOAT, rank, MPI_COMM_WORLD);
		MPI_Bcast( &(p->speed_), 1, MPI_INT, rank, MPI_COMM_WORLD);
	}
	else {
		MPI_Send( &(p->in_out_), 1, MPI_INT, rank, 0, MPI_COMM_WORLD);
		MPI_Send( &(p->start_range_), 1, MPI_FLOAT, rank, 0, MPI_COMM_WORLD);
		MPI_Send( &(p->end_range_), 1, MPI_FLOAT, rank, 0, MPI_COMM_WORLD);
		MPI_Send( &(p->speed_), 1, MPI_INT, rank, 0, MPI_COMM_WORLD);
	}
	
}



MpiSlave::MpiSlave(int id, int masterId ){
	id_ = id;
	masterId_ = masterId;
}

int MpiSlave::run(){
	 //------- DEFINITION OF CUSTOM MPI DATATYPE
	  MPI_Type_contiguous(MSG_SIZE, MPI_BYTE, &dt_msg);
	   //a message is a string (list of char) closest type is vector of MPI_BYTE
	  MPI_Type_commit(&dt_msg);
	 //------- END OF DEFINITION OF CUSTOM MPI DATATYPE
	
	bool run = true;
	
	while( run ){
		char* msg;
		MPI_Recv(&msg, 1, dt_msg, masterId_, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		//convert to String for easier manipulation
		string msgString = msg;
		
		if(msgString == "END"){
			run = false;
		}
		else if( msgString == "ORGA::CMPT_PRT_CONC/RNA_DELTAS" ){
			
		}
		else if( msgString == "ORGA::ACT_PUMP" ){
			
		}
		
	}
}

void MpiSlave::compute_protein_concentration_rna_deltas(){
	//------- DEFINITION OF CUSTOM MPI DATATYPE
	  MPI_Type_contiguous(MSG_SIZE, MPI_BYTE, &dt_msg);
	   //a message is a string (list of char) closest type is vector of MPI_BYTE
	  MPI_Type_commit(&dt_msg);
	 //------- END OF DEFINITION OF CUSTOM MPI DATATYPE
	
	
}


void MpiSlave::activate_pump(){
	//receive organism prot_list_map
	std::map<float,Protein*> org_protein_list_map();
	
	//clear all
	
	
}

