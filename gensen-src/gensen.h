/*********************************************************************
 *
 * AUTHORIZATION TO USE AND DISTRIBUTE
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that: 
 *
 * (1) source code distributions retain this paragraph in its entirety, 
 *  
 * (2) distributions including binary code include this paragraph in
 *     its entirety in the documentation or other materials provided 
 *     with the distribution, and 
 *
 * (3) all advertising materials mentioning features or use of this 
 *     software display the following acknowledgment:
 * 
 *      "This product includes software written and developed 
 *       by Tiago Camilo Laboratory of Communication and Telematics (LCT)
 *       Coimbra University ." 
 *         
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 ********************************************************************/
 
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <list>

#include "tools.hh"

using std::list;

// Deployment Strategies
#define GRID 		0
#define RANDOM 		1
#define ONE_BY_ONE 	2
#define TWO_BY_TWO 	3
#define THREE_BY_THREE 	4
#define PROPERLANT 	5    
#define CLIF 		6

// Energy Levels
#define CONSTANT_ENERGY 0
#define TWO_LEVELS 	1
#define THREE_LEVELS 	2
#define FOUR_LEVELS 	3

//Sensor Node Position
#define ONE_POSITION	0
#define TWO_POSITIONS	1
#define FOUR_POSITIONS	2

#define POSITION_UP     0
#define POSITION_DOWN   1
#define POSITION_LEFT   2
#define POSITION_RIGHT  3

// MAP Limits
#define MAP_MIN_X 10
#define MAP_MAX_X 1000
#define MAP_MIN_Y 10
#define MAP_MAX_Y 1000

//Sensor Nodes
#define MAP_MIN_NUM_NODES 1
#define MAP_MAX_NUM_NODES 300


#define MIN_SINKS MIN_NODES
#define MAX_SINKS MAX_NODES - 1
#define MIN_SOURCES MIN_NODES
#define MAX_SOURCES MAX_NODES - 1


class SensorNode{
public:
  int id;
  double map_x;
  double map_y;
  double initial_energy;
  int position;

  SensorNode(int num, double loc_x, double loc_y, double ener, int pos) :
    id(num), map_x(loc_x), map_y(loc_y), initial_energy(ener), position(pos)
  {
  };
  SensorNode(){};
};

class CostInfo{
public:
  int node_id_;
  int cost_;

  CostInfo(int node_id, int cost) : node_id_(node_id), cost_(cost) {};
};

typedef list<SensorNode *> MAP;
typedef list<int> TopoList;


class GenSeN{
public:
  GenSeN(int argc, char **argv);
  void Generate_topology();
private:

	int num_sensor_nodes;
  	int map_max_x;
  	int map_max_y;
	int seed;
  	int deployment_strategy;
	int sensor_node_position;
	int energy_model;
	char *tcl_file_name;
	char topology_file_name_[50];
	double max_node_energy;
	double idle_node_energy;
	double dist_in_grid;
	
	int limit_key;
	
	//possition map probability
	double probability[4][4];
	double acumulute_probability[4][4];
	int out[4][4];
  	MAP Topology;
  
  SensorNode topology_;
  TopoList connected_;

  	// Node placement functions
  	void Generate_Sensor_Nodes();
  
	//Deployment Strategies
	void Grid_Topology(double& loc_x,double& loc_y, int i);
	void Random_Topology(double& loc_x,double& loc_y, int i);
	void Build_Topology(double& loc_x,double& loc_y, int i); //Its the same for all the others
		
	//Topology map probability
	void Create_Map_OneByOne();
	void Create_Map_TwoByTwo();
	void Create_Map_ThreeByThree();
	void Create_Map_Propellant();
	void Create_Map_Clif();
	void Make_Acumulator_Probability();
	
	//Node Energy
	double Two_Levels_Get_Energy(int element);
	double Three_Levels_Get_Energy(int element);
	double Four_Levels_Get_Energy(int element);
	
	//Node Position
	int Get_Postion_Two(int element);
	int Get_Postion_Four(int element);
  
  	SensorNode * Find_Node_by_Id(MAP *topology, int id);
  
  	//Program
  	void GetUserParameters(int argc, char **argv);
  	void help(char *s);
  	void ClearLists();
	
	
	//Print
	void Print_Topology_File();
	void Print_Tcl_File();
	void Found_Placement(double loc_x,double loc_y);
};
