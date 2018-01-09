//
// Created by sbelletier on 8/12/2017
//
#include <iostream>
#include <string>
#include <map>
#include <vector>

#include <mpi.h>



#include "MpiSlave.h"

using namespace std;

Protein* rcvProtein(int rank_src, bool fromBroadcast){
	int type;
	float binding_pattern;
	float value;
	float concentration;
	
	if( fromBroadcast ){
		MPI_Bcast( &type, 1, MPI_INT, rank_src, MPI_COMM_WORLD);
		MPI_Bcast( &binding_pattern, 1, MPI_FLOAT, rank_src, MPI_COMM_WORLD);
		MPI_Bcast( &value, 1, MPI_FLOAT, rank_src, MPI_COMM_WORLD);
		MPI_Bcast( &concentration, 1, MPI_FLOAT, rank_src, MPI_COMM_WORLD);
	}
	else {
		MPI_Recv(&type, 1, MPI_INT, rank_src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(&binding_pattern, 1, MPI_FLOAT, rank_src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(&value, 1, MPI_FLOAT, rank_src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(&concentration, 1, MPI_FLOAT, rank_src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
	
	Protein* p = new Protein(type, binding_pattern, value);
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



Pump* rcvPump(int rank_src, bool fromBroadcast){
	int int_outward;
	float start_range;
	float end_range;
	int speed;
	
	if( fromBroadcast ){
		MPI_Bcast( &int_outward, 1, MPI_INT, rank_src, MPI_COMM_WORLD);
		MPI_Bcast( &start_range, 1, MPI_FLOAT, rank_src, MPI_COMM_WORLD);
		MPI_Bcast( &end_range, 1, MPI_FLOAT, rank_src, MPI_COMM_WORLD);
		MPI_Bcast( &speed, 1, MPI_INT, rank_src, MPI_COMM_WORLD);
	}
	else {
		MPI_Recv(&int_outward, 1, MPI_INT, rank_src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(&start_range, 1, MPI_FLOAT, rank_src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(&end_range, 1, MPI_FLOAT, rank_src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(&speed, 1, MPI_INT, rank_src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
	
	bool outward = int_outward != 0 ? true : false;
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
	 MPI_Datatype dt_msg;
	 MPI_Type_contiguous(MSG_SIZE, MPI_BYTE, &dt_msg);
	 //a message is a string (list of char) closest type is vector of MPI_BYTE
	 MPI_Type_commit(&dt_msg);
	 //------- END OF DEFINITION OF CUSTOM MPI DATATYPE
	
	bool run = true;
	
	while( run ){
		char msg[MSG_SIZE];
		MPI_Recv(&msg, MSG_SIZE, MPI_CHAR, masterId_, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		//convert to String for easier manipulation
		string msgString = msg;
		
		if(msgString == "END"){
			run = false;
		}
		else if( msgString == "ORGA::CMPT_PRT_CONC/RNA_DELTAS" ){
			
		}
		else if( msgString == "ORGA::ACT_PUMP" ){
			activate_pump();
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
	
	/************************************************
	*  STEP 1.A : Receive organism protein_list_map
	********************************************** */
	// initialize
	std::map<float,Protein*> orga_protein_list_map = std::map<float,Protein*>();
	int count;
	//receive count
	MPI_Bcast(&count, 1, MPI_INT, 0, MPI_COMM_WORLD);
	//receiving loop
	for(int i=0; i < count; i++){
		//receive attributes
		float key;
		MPI_Bcast(&key, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
		Protein* prot = rcvProtein(0, true);
		//insert in map
		orga_protein_list_map.insert( std::pair<float,Protein*>(key, prot) );
	}
	/************************************************
	*  STEP 1.B : Receive gridcell protein_list_map
	********************************************** */
	// initialize
	std::map<float,Protein*> grid_protein_list_map = std::map<float,Protein*>();
	//receive count (initialized above)
	MPI_Bcast(&count, 1, MPI_INT, 0, MPI_COMM_WORLD);
	//receiving loop
	for(int i=0; i < count; i++){
		//receive attributes
		float key;
		MPI_Bcast(&key, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
		Protein* prot = rcvProtein(0, true);
		//insert in map
		grid_protein_list_map.insert( std::pair<float,Protein*>(key, prot) );
	}
	/************************************************
	*  STEP 1.C : Receive pumps
	********************************************** */
	//initialize
	std::vector<Pump*> slave_pumps = {};
	int read;
	//receiving loop
	MPI_Recv(&read, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);//wait for first signal from master
	while( read ){
		slave_pumps.push_back( rcvPump(0, false) );
		MPI_Recv(&read, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);//when 0 received, will end reading
	}
	
	/************************************************
	*  STEP 1.D : Initialize return
	********************************************** */
	std::map<float,float> grid_prot_concentration_change = std::map<float,float>();
	std::map<float,float> orga_prot_concentration_change = std::map<float,float>();

	
	/************************************************
	*  STEP 2 : Activate pumps
	********************************************** */
	for (auto pump_it = slave_pumps.begin(); pump_it != slave_pumps.end(); pump_it++) { 
		//Check for pumping direction
		if ((*pump_it)->in_out_) {
			//pump from inside
			for (auto & prot : orga_protein_list_map) {
				if ( (*pump_it)->start_range_ >= prot.second->value_ && (*pump_it)->end_range_ <= prot.second->value_) 
				{
					float remove = prot.second->concentration_*( (*pump_it)->speed_/100 );
					//update local values
					prot.second->concentration_-=remove;//orga
					//grid
					if ( grid_protein_list_map.find(prot.second->value_) == grid_protein_list_map.end() ) 
					{
							Protein* prot_n = new Protein(prot.second->type_,
														prot.second->binding_pattern_,
														  prot.second->value_);
							prot_n->concentration_ = remove;
							grid_protein_list_map[prot.second->value_] = prot_n;
					} 
					else 
					{
						grid_protein_list_map[prot.second->value_]->concentration_ += remove;
					}
					//update return value
					//orga
					if ( orga_prot_concentration_change.find(prot.second->value_) == orga_prot_concentration_change.end() ) 
					{
						  orga_prot_concentration_change.insert( std::pair<float,float>( prot.second->value_ , -remove ) );
					}
					else
					{
						orga_prot_concentration_change[ prot.second->value_ ] -= remove;
					}
					//grid
					if ( grid_prot_concentration_change.find(prot.second->value_) == grid_prot_concentration_change.end() ) 
					{
						  grid_prot_concentration_change.insert( std::pair<float,float>( prot.second->value_ , remove ) );
					}
					else
					{
						grid_prot_concentration_change[ prot.second->value_ ] += remove;
					}
					//
				}
			  }
		  
		} 
		else {
			//pump from outside
			for (auto & prot : grid_protein_list_map) {
				  
				if ( (*pump_it)->start_range_ >= prot.first && (*pump_it)->end_range_ <= prot.first) 
				{
					float remove = prot.second->concentration_ * ( (*pump_it)->speed_/100 );
					//update local values
					prot.second->concentration_-=remove;//grid
					//orga
					if ( orga_protein_list_map.find(prot.first)  == orga_protein_list_map.end() ) {
						Protein* prot_n = new Protein(prot.second->type_,
													  prot.second->binding_pattern_,
													  prot.second->value_);
						prot_n->concentration_ = remove;
						orga_protein_list_map[prot_n->value_] = prot_n;
					} 
					else 
					{
						orga_protein_list_map[prot.first]->concentration_ += remove;
					}
					//update return values
					//orga
					if ( orga_prot_concentration_change.find(prot.second->value_) == orga_prot_concentration_change.end() ) 
					{
						  orga_prot_concentration_change.insert( std::pair<float,float>( prot.second->value_ , remove ) );
					}
					else
					{
						orga_prot_concentration_change[ prot.second->value_ ] += remove;
					}
					//grid
					if ( grid_prot_concentration_change.find(prot.second->value_) == grid_prot_concentration_change.end() ) 
					{
						  grid_prot_concentration_change.insert( std::pair<float,float>( prot.second->value_ , -remove ) );
					}
					else
					{
						grid_prot_concentration_change[ prot.second->value_ ] -= remove;
					}
					//
				}
				
			  }
			  
		}
		
		delete (*pump_it);
		
	}
	MPI_Barrier( MPI_COMM_WORLD );
	
	/************************************************
	*  STEP 3.A : Define delta type for reception
	********************************************** */
    //------- DEFINITION OF CUSTOM MPI DATATYPE
    MPI_Datatype dt_cDelta;
	MPI_Type_contiguous(2, MPI_FLOAT, &dt_cDelta);
	MPI_Type_commit(&dt_cDelta);
	//------- END OF DEFINITION OF CUSTOM MPI DATATYPE
	
	/************************************************
	*  STEP 3.B : Gather organism protein deltas
	********************************************** */
	int write;
	auto itOrga = grid_prot_concentration_change.begin();
	MPI_Bcast(&write, 1, MPI_INT, 0, MPI_COMM_WORLD);//wait for first signal from master
	while( write ){
		if( itOrga != grid_prot_concentration_change.end() ){
			float delta[2] = {itOrga->first, itOrga->second};
			MPI_Gather(&delta, 1, dt_cDelta, NULL, 1, dt_cDelta, 0, MPI_COMM_WORLD); 
			itOrga++;
		}
		else{
			float empty[2] = {-1.0, 0.0};//value is position on DNA therefore negative value doesn't exist
			MPI_Gather(&empty, 1, dt_cDelta, NULL, 1, dt_cDelta, 0, MPI_COMM_WORLD); 
		}
		MPI_Bcast(&write, 1, MPI_INT, 0, MPI_COMM_WORLD);//when 0 received, will end reading
	}
	
	/************************************************
	*  STEP 3.C : Gather gridcell protein deltas
	********************************************** */
	auto itGrid = orga_prot_concentration_change.begin();
	MPI_Bcast(&write, 1, MPI_INT, 0, MPI_COMM_WORLD);//wait for first signal from master, write already initialised
	while( write ){
		if( itGrid != orga_prot_concentration_change.end() ){
			float delta[2] = {itGrid->first, itGrid->second};
			MPI_Gather(&delta, 1, dt_cDelta, NULL, 1, dt_cDelta, 0, MPI_COMM_WORLD); 
			itOrga++;
		}
		else{
			float empty[2] = {-1.0, 0.0};//value is position on DNA therefore negative value doesn't exist
			MPI_Gather(&empty, 1, dt_cDelta, NULL, 1, dt_cDelta, 0, MPI_COMM_WORLD); 
		}
		MPI_Bcast(&write, 1, MPI_INT, 0, MPI_COMM_WORLD);//when 0 received, will end reading
	}
	
	/************************************************
	*  STEP 4 : Clear memory
	********************************************** */
	//clear prots maps
	for (auto & prot : orga_protein_list_map) {
		delete prot.second;
	}
	for (auto & prot : grid_protein_list_map) {
		delete prot.second;
	}

}

