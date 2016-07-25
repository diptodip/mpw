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
 *
 * tandre@dei.uc.pt
 ********************************************************************/
 

#include "gensen.h"
#include <cstdlib>  // For srand() and rand

double Distance(double x1, double y1, double x2, double y2)
{
  return sqrt((x1 - x2) * (x1 -x2) + (y1 - y2) * (y1 - y2));
}

SensorNode * GenSeN::Find_Node_by_Id(MAP *topology, int id)
{
  	MAP::iterator node_iterator;
  	SensorNode *finded_node;

  	for (node_iterator = topology->begin(); node_iterator != topology->end(); ++node_iterator)
  	{
    		finded_node = *node_iterator;

    		if (finded_node->id == id)
      			return finded_node;
  	}

  	// The does not exist???
  	return NULL;
}

void GenSeN::Generate_Sensor_Nodes()
{
  	SensorNode *sensor_node; 
  	double loc_x, loc_y, energy;
	int position;

	switch (deployment_strategy)
	{

		case ONE_BY_ONE:
			Create_Map_OneByOne();
			Make_Acumulator_Probability();
			break;
		case TWO_BY_TWO:
			Create_Map_TwoByTwo();
			Make_Acumulator_Probability();
			break;
		case THREE_BY_THREE:
			Create_Map_ThreeByThree();
			Make_Acumulator_Probability();
			break;
		case PROPERLANT:
			Create_Map_Propellant();
			Make_Acumulator_Probability();
			break;
		case CLIF:
			Create_Map_Clif();
			Make_Acumulator_Probability();
			break;
	}
	
  	// Create nodes
  	for (int i = 0; i < num_sensor_nodes; i++)
	{
		switch (deployment_strategy)
		{
    			case GRID:
				Grid_Topology( loc_x,loc_y, i);
				break;
			case RANDOM:
				Random_Topology(loc_x, loc_y, i);
				break;
			case ONE_BY_ONE:
				Build_Topology(loc_x,loc_y, i);
				break;
			case TWO_BY_TWO:
				Build_Topology(loc_x,loc_y,i);
				break;
			case THREE_BY_THREE:
				Build_Topology(loc_x,loc_y,i);
				break;
			case PROPERLANT:
				Build_Topology(loc_x,loc_y,i);
				break;
			case CLIF:
				Build_Topology(loc_x,loc_y,i);
				break;
		}
		
		switch (energy_model)
		{
    			case CONSTANT_ENERGY:
				energy = max_node_energy;
				break;
			case TWO_LEVELS:
				energy = Two_Levels_Get_Energy(i);
				break;
			case THREE_LEVELS:
				energy = Three_Levels_Get_Energy(i);
				break;
			case FOUR_LEVELS:
				energy = Four_Levels_Get_Energy(i);
				break;
		}
		
		switch (sensor_node_position)
		{
    			case ONE_POSITION:
				position = POSITION_UP;
				break;
			case TWO_POSITIONS:
				position = Get_Postion_Two(i);
				break;
			case FOUR_POSITIONS:
				position = Get_Postion_Four(i);
				break;
		}

		// Add this node to the topology
    		sensor_node = new SensorNode(i, loc_x, loc_y, energy, position);
    		Topology.push_back(sensor_node);
      	}
}

void GenSeN::Grid_Topology(double &loc_x,double &loc_y, int num)
{
 	 loc_x=0.0;
	 loc_y=0.0;

	if(dist_in_grid*(num+1)-(dist_in_grid/2)<map_max_x)
	{
		loc_y=dist_in_grid/2;
		loc_x=dist_in_grid*(num+1)-(dist_in_grid/2);
		limit_key=num+1;
		return;
	}
	
	int map_limit=map_max_x;
	int counter=0;
	while(dist_in_grid*(num+1)-(dist_in_grid/2)>map_limit)
	{
		map_limit +=map_max_x;
		counter++;
	}
	
	loc_y = counter*dist_in_grid + (dist_in_grid/2);
	loc_x = dist_in_grid*(num-(counter*limit_key)+1)-(dist_in_grid/2);
	
	//Only "y" will pass map limit
	if (loc_y>map_max_y)
	{
		loc_y=map_max_y-1;
		loc_x=map_max_x-1;
		
		//warn user only once
		if(limit_key !=-1)
		{
			fprintf(stderr,"WARNING: Due to the grid limite there is no space to insert all nodes in grid\n");
			limit_key =-1;
		}
		
		return;
	}
}
void GenSeN::Random_Topology(double &loc_x,double &loc_y, int num)
{
 	srand(seed+num);  // Initialize random number generator.

	loc_x=0.0;
	while(loc_x<1)
		loc_x=(double)(rand() % map_max_x) + 1;
	
	loc_y=0.0;
	while(loc_y<1)
		loc_y=(double)(rand() % map_max_y) + 1;;
	
	fprintf(stderr,"\n%f....",loc_x);
	fprintf(stderr,"%f\n",loc_y);
	Found_Placement(loc_x,loc_y);
}

void GenSeN::Build_Topology(double &loc_x,double &loc_y, int num)
{
	srand(seed+num);  // Initialize random number generator.

	double roulete =0.0;
	int i,j;
	roulete=(double)(rand() % 10000)/10000;

	for(i=0; i<4;i++)
	{
		bool found=false;
		for(j=0; j<4;j++)	
		{
			if (roulete<acumulute_probability[i][j])
			{
				found=true;
				break;
			}
		}
		if (found) break;
	}

	
	double probability_max_limit_x = (double)map_max_x;
	probability_max_limit_x=probability_max_limit_x/4.0;
	probability_max_limit_x=probability_max_limit_x*(double)(i+1.0);
	double probability_max_limit_y = (double)map_max_y/4.0*(double)(j+1.0);
	
	double probability_mim_limit_x = probability_max_limit_x - (double)map_max_x/4.0;	
	double probability_mim_limit_y = probability_max_limit_y - (double)map_max_y/4.0;
	
	loc_x=-1.0;
	loc_y=-1.0;
	int aux = (int)probability_max_limit_x*1000;
	while(loc_x<probability_mim_limit_x)
	{
		loc_x=(double)(rand() % aux);
		loc_x=loc_x/1000.0;
	}
	
	aux = (int)probability_max_limit_y*1000;
	while(loc_y<probability_mim_limit_y)
	{
		loc_y=(double)(rand() % aux);
		loc_y=loc_y/1000.0;
	}
	
	Found_Placement(loc_x,loc_y);
}



void GenSeN::Create_Map_OneByOne()
{
	probability[0][0]=0.0625;
	probability[0][1]=0.0625;
	probability[0][2]=0.0417;
	probability[0][3]=0.0625;
	probability[1][0]=0.0833;
	probability[1][1]=0.0833;
	probability[1][2]=0.0625;
	probability[1][3]=0.0833;
	probability[2][0]=0.0833;
	probability[2][1]=0.0625;
	probability[2][2]=0.0625;
	probability[2][3]=0.0625;
	probability[3][0]=0.0625;
	probability[3][1]=0.0417;
	probability[3][2]=0.0417;
	probability[3][3]=0.0417;
}


void GenSeN::Create_Map_TwoByTwo()
{
	probability[0][0]=0.0417;
	probability[0][1]=0.0417;
	probability[0][2]=0.0625;
	probability[0][3]=0.0417;
	probability[1][0]=0.0625;
	probability[1][1]=0.0833;
	probability[1][2]=0.0208;
	probability[1][3]=0.0625;
	probability[2][0]=0.0625;
	probability[2][1]=0.0833;
	probability[2][2]=0.1042;
	probability[2][3]=0.0833;
	probability[3][0]=0.0833;
	probability[3][1]=0.0625;
	probability[3][2]=0.0625;
	probability[3][3]=0.0417;
}


void GenSeN::Create_Map_ThreeByThree()
{
	probability[0][0]=0.0833;
	probability[0][1]=0.0625;
	probability[0][2]=0.0625;
	probability[0][3]=0.0500;
	probability[1][0]=0.1042;
	probability[1][1]=0.1042;
	probability[1][2]=0.0833;
	probability[1][3]=0.0417;
	probability[2][0]=0.0125;
	probability[2][1]=0.0417;
	probability[2][2]=0.0833;
	probability[2][3]=0.0833;
	probability[3][0]=0.0208;
	probability[3][1]=0.0625;
	probability[3][2]=0.0417;
	probability[3][3]=0.0625;
}

void GenSeN::Create_Map_Propellant()
{
	probability[0][0]=0.0833;
	probability[0][1]=0.0625;
	probability[0][2]=0.0625;
	probability[0][3]=0.0250;
	probability[1][0]=0.1250;
	probability[1][1]=0.1250;
	probability[1][2]=0.1042;
	probability[1][3]=0.0313;
	probability[2][0]=0.0833;
	probability[2][1]=0.0833;
	probability[2][2]=0.0833;
	probability[2][3]=0.0625;
	probability[3][0]=0.0208;
	probability[3][1]=0.0208;
	probability[3][2]=0.0208;
	probability[3][3]=0.0063;
}

void GenSeN::Create_Map_Clif()
{
	probability[0][0]=0.0625;
	probability[0][1]=0.0625;
	probability[0][2]=0.0625;
	probability[0][3]=0.0063;
	probability[1][0]=0.1042;
	probability[1][1]=0.1250;
	probability[1][2]=0.0833;
	probability[1][3]=0.0500;
	probability[2][0]=0.1042;
	probability[2][1]=0.1042;
	probability[2][2]=0.1042;
	probability[2][3]=0.0625;
	probability[3][0]=0.0208;
	probability[3][1]=0.0208;
	probability[3][2]=0.0208;
	probability[3][3]=0.0063;
}

void GenSeN::Make_Acumulator_Probability()
{
	double acumulator=0.0;
	for(int i=0; i<4;i++)
	{
		for(int j=0; j<4;j++)
		{
			acumulator += probability[i][j];
			acumulute_probability[i][j]=acumulator;
		}
	}
}


double GenSeN::Two_Levels_Get_Energy(int num)
{
  	srand(seed+num);  // Initialize random number generator.

	int roulete =0;
	roulete=(rand() % 10);
	
	if(roulete>5)
		return (max_node_energy);
	else
		return (max_node_energy/2);
}
double GenSeN::Three_Levels_Get_Energy(int num)
{
  	srand(seed+num);  // Initialize random number generator.

	int roulete =0;
	roulete=(rand() % 10);
	
	if(roulete>6)
		return (max_node_energy);
	else if(roulete>3)
		return ((max_node_energy/3)*2);  
	     else
	     	return(max_node_energy/3);
}
double GenSeN::Four_Levels_Get_Energy(int num)
{
	srand(seed+num);  // Initialize random number generator.

	double roulete =0;
	roulete=(rand() % 100);
	roulete =roulete /10;
	if(roulete>7.5)
		return (max_node_energy);
	else 	
		if(roulete>5)
			return ((max_node_energy/4)*3);  
	     	else 
			if (roulete>2.5)
	     			return((max_node_energy/4)*2);
			else 
				return (max_node_energy/4);
}

int GenSeN::Get_Postion_Two(int num)
{
    	srand(seed+num);  // Initialize random number generator.

	int roulete =0;
	roulete=(rand() % 10);
	
	if(roulete>5)
		return POSITION_UP;
	else
		return POSITION_DOWN;
}

int GenSeN::Get_Postion_Four(int num)
{
	srand(seed+num);  // Initialize random number generator.

	double roulete =0;
	roulete=(rand() % 100);
	roulete =roulete /10;
	if(roulete>7.5)
		return POSITION_UP;
	else 	
		if(roulete>5)
			return POSITION_DOWN;  
	     	else 
			if (roulete>2.5)
	     			return POSITION_LEFT;
			else 
				return POSITION_RIGHT;
}


void GenSeN::Generate_topology()
{
  	struct timeval tmv;
    
    	// Initialize
    	ClearLists();
        
    	// Create all nodes
    	Generate_Sensor_Nodes();


	Print_Topology_File();

	Print_Tcl_File();
    

}

void GenSeN::ClearLists()
{
 // sensor_nodes.clear();
  
  Topology.clear();
//  connected_.clear();
}

GenSeN::GenSeN(int argc, char **argv)
{ 	

	struct timeval tmv;

  	// Initialize default values
  	map_max_x = 60;
  	map_max_y = 100;
  	num_sensor_nodes = 32;
  	deployment_strategy = CLIF;
  	seed = 0;
  	tcl_file_name = "random";
  	max_node_energy = 40.0;
	idle_node_energy=0.0001;
	energy_model = FOUR_LEVELS;
	sensor_node_position = ONE_POSITION;
	dist_in_grid=25.0;
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			out[i][j]=0;
			
  // Parse command line options
  GetUserParameters(argc, argv);

  // Initialize Topology Generator
  GetTime(&tmv);

  if (seed == 0){
    SetSeed(&tmv);
    seed = tmv.tv_usec;
  }
  else
    srand(seed);
}

void GenSeN::GetUserParameters(int argc, char **argv)
{
	int parameter;
  	opterr = 0;

  	while (1){//para ler parametros... kanto tem : seguido significa que fica á espera de um input
    	//TODO: actualizar esta lista
    		parameter = getopt(argc, argv, "htegicdza:b:m:x:y:f:n:s:r:k:p:");

    		switch (parameter)
		{

    			case 'x':
      				map_max_x = atoi(optarg);
      				if (map_max_x < MAP_MIN_X || map_max_x > MAP_MAX_X)
				{
        				fprintf(stderr, "Error on parameter (X): Please enter a value between %d and %d\n", MAP_MIN_X, MAP_MAX_X);
        				help(argv[0]);
      				}
      				break;

    			case 'y':
      				map_max_y = atoi(optarg);
      				if (map_max_y < MAP_MIN_Y || map_max_y > MAP_MAX_Y)
				{
        				fprintf(stderr, "Error on parameter (Y): Please enter a value between %d and %d\n", MAP_MIN_Y, MAP_MAX_Y);
        				help(argv[0]);
      				}
      				break;

    			case 'n':
      				num_sensor_nodes = atoi(optarg);
      				if (num_sensor_nodes < MAP_MIN_NUM_NODES || num_sensor_nodes > MAP_MAX_NUM_NODES)
				{
        				fprintf(stderr, "Error on parameter (n): Please enter a value between %d and %d\n", MAP_MIN_NUM_NODES, MAP_MAX_NUM_NODES);
        				help(argv[0]);
      				}
      				break;

    			case 's':
      				seed = atoi(optarg);
      				if (seed < 0)
				{
        				fprintf(stderr, "Error on parameter (s): Please enter a value bigger then zero\n");
        				help(argv[0]);
      				}
      				break;
    
			case 'e':
				max_node_energy= atoi(optarg);
				if(max_node_energy<0)
				{
        				fprintf(stderr, "Error on parameter (e): Please enter a value bigger then zero\n");
        				help(argv[0]);
      				}
      				break;
				
			case 'i':
				idle_node_energy= atoi(optarg);
				if(idle_node_energy<0)
				{
        				fprintf(stderr, "Error on parameter (i): Please enter a value bigger then zero\n");
        				help(argv[0]);
      				}
      				break;
			case 'k':
				dist_in_grid= atoi(optarg);
				if(dist_in_grid<0)
				{
        				fprintf(stderr, "Error on parameter (k): Please enter a value bigger then zero\n");
        				help(argv[0]);
      				}
      				break;
			
			case 'w':
				energy_model=atoi(optarg);
				if (energy_model < 1 || energy_model > 4)
				{
        				fprintf(stderr, "Error on parameter (w): Please entre a value between 1 and 4 !\n");
        				help(argv[0]);
					energy_model = CONSTANT_ENERGY;
      				}
				
				if (energy_model == 1)
        				energy_model = CONSTANT_ENERGY;
      				else if (energy_model == 2)
        				energy_model = TWO_LEVELS;
      				else if (energy_model == 3)
        				energy_model = THREE_LEVELS;
      				else if (energy_model == 4)
        				energy_model = FOUR_LEVELS;
      				break;
				
			case 'p':
				sensor_node_position=	atoi(optarg);
				if (sensor_node_position < 1 || sensor_node_position > 4)
				{
        				fprintf(stderr, "Error on parameter (p): Please entre a value between 1 and 4 !\n");
        				help(argv[0]);
					sensor_node_position = ONE_POSITION;
      				}
				if (sensor_node_position == 1)
        				sensor_node_position = ONE_POSITION;
      				else if (sensor_node_position == 2)
        				sensor_node_position = TWO_POSITIONS;
      				else if (sensor_node_position == 3)
        				sensor_node_position = FOUR_POSITIONS;
      				break;

    			case 'd':
      				deployment_strategy = atoi(optarg);
      				if (deployment_strategy < 1 || deployment_strategy > 7)
				{
        				fprintf(stderr, "Error on parameter (d): Please entre a value between 1 and 7 !\n");
        				help(argv[0]);
					deployment_strategy = RANDOM;
      				}
      				if (deployment_strategy == 1)
        				deployment_strategy = GRID;
      				else if (deployment_strategy == 2)
        				deployment_strategy = RANDOM;
      				else if (deployment_strategy == 3)
        				deployment_strategy = ONE_BY_ONE;
      				else if (deployment_strategy == 4)
        				deployment_strategy = TWO_BY_TWO;
      				else if (deployment_strategy == 5)
        				deployment_strategy = THREE_BY_THREE;
				else if (deployment_strategy == 6)
        				deployment_strategy = PROPERLANT;
				else if (deployment_strategy == 7)
        				deployment_strategy = CLIF;
      				break;
    			case 'f':
      				if (!strncasecmp(optarg, "-", 1))
				{
        				fprintf(stderr, "ERROR: Please check if file name is missing !\n");
        				help(argv[0]);
      				}
      				tcl_file_name = strdup(optarg);
      				break;
    
    			case 'h':
      				help(argv[0]);
      				break;

    			case ':':
      				fprintf(stderr, "ERROR: Please check if parameters are missing !\n");
      				help(argv[0]);
      				break;
    		}

    		if (parameter == -1)
      			break;
  	}

  	if (map_max_x == 0 || map_max_y == 0 || num_sensor_nodes == 0 )
    		help(argv[0]);
}

void GenSeN::Print_Topology_File()
{
  	FILE *file;
  
	char topology_file_name[50];

  	if (tcl_file_name){
  		strcpy(topology_file_name, tcl_file_name);
  		strcat(topology_file_name, "_topology");
  	}
  	else{
 		sprintf(topology_file_name, "topology");
    	}
	
	strcat(topology_file_name, ".tcl");
  	strcpy(topology_file_name_,topology_file_name);
	
	file = fopen(topology_file_name, "w");
  
  	if (!file)
	{
    		fprintf(stderr, "ERROR:Cannot create topology file: %s, check for permisions...\n", topology_file_name);
    		exit(-1);
  	}
  
	fprintf(file, "# Redistribution and use in source and binary forms are permitted\n");
	fprintf(file, "# provided that the above copyright notice and this paragraph are\n");
	fprintf(file, "# duplicated in all such forms and that any documentation, advertising\n");
	fprintf(file, "# materials, and other materials related to such distribution.\n");
	fprintf(file, "# \n");
	fprintf(file, "# THIS SOFTWARE IS PROVIDED AS IS AND WITHOUT ANY EXPRESS OR IMPLIED\n");
	fprintf(file, "# WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF\n");
	fprintf(file, "# MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.\n");
	fprintf(file, "#\n#\n# ");
	
  	// Print Heather File
  	fprintf(file, "# This file was automaticaly generated by GenSeN\n");
  	fprintf(file, "# It express the node's position\n#\n#\n");
	fprintf(file, "# Number of Nodes	: %d\n", num_sensor_nodes);
  	fprintf(file, "# Simulation Area	: %d x %d \n", map_max_x, map_max_y );
	switch (deployment_strategy)
		{
    			case GRID:
				fprintf(file, "# Deployment Strategy	: Grid\n");
				break;
			case RANDOM:
				fprintf(file, "# Deployment Strategy	: Random\n");
				break;
			case ONE_BY_ONE:
				fprintf(file, "# Deployment Strategy	: One-by-one\n");
				break;
			case TWO_BY_TWO:
				fprintf(file, "# Deployment Strategy	: Two-by-two\n");
				break;
			case THREE_BY_THREE:
				fprintf(file, "# Deployment Strategy	: Three-by-three\n");
				break;
			case PROPERLANT:
				fprintf(file, "# Deployment Strategy	: Properlant\n");
				break;
			case CLIF:
				fprintf(file, "# Deployment Strategy	: Clif\n");
				break;
		}
  	
  	fprintf(file, "# Seed           	: %d\n\n", seed);
		
	//Print node's location  
	MAP::iterator node_element;
  	SensorNode *current_node;	
	for (node_element = Topology.begin();node_element != Topology.end(); node_element++)
	{
		current_node = *node_element;
		fprintf(file, "$node_(%d) set X_ %f \n", current_node->id, current_node->map_x);
    		fprintf(file, "$node_(%d) set Y_ %f \n", current_node->id, current_node->map_y);
    		//fprintf(file, "$node_(%d) set Z_ 0.000000\n\n", current_node->id);
	}
	
	fprintf(file, "\n\n\n\nPRINTING FOUNDINGS...\n");
	
	for(int i=0;i<4;i++)
	{
		
		for(int j=0;j<4;j++)
			fprintf(file, " %i",out[i][j]);
		fprintf(file, "\n");
	}
		
  	fclose(file);
}

void GenSeN::Print_Tcl_File()
{
	FILE *file;
	char file_name[50];
	
  	if (tcl_file_name)
	{
  		strcpy(file_name, tcl_file_name);
  	}
  	else
	{
 		sprintf(file_name, "gensen_out");
    	}
	
	strcat(file_name, ".tcl");
	file = fopen(file_name, "w");
  
  	if (!file)
	{
    		fprintf(stderr, "ERROR:Cannot create tcl file: %s, check for permisions...\n", file_name);
    		exit(-1);
  	}
  
	
 	fprintf(file,"# THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ''AS IS'' AND\n");
 	fprintf(file,"# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE\n");
 	fprintf(file,"# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE\n");
 	fprintf(file,"# ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE\n");
 	fprintf(file,"# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL\n");
 	fprintf(file,"# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS\n");
 	fprintf(file,"# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)\n");
 	fprintf(file,"# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT\n");
 	fprintf(file,"# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY\n");
 	fprintf(file,"# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF\n");
 	fprintf(file,"# SUCH DAMAGE.\n");
  	fprintf(file, "#");
	fprintf(file, "# Maintainer: Tiago Camilo <tandre@dei.uc.pt>\n");
	fprintf(file, "# Version Date: 2006/05/15 \n");
	fprintf(file, "#\n");
	
	fprintf(file, "#\n");
	fprintf(file, "# ======================================================================\n");
	fprintf(file, "# Define options\n");
	fprintf(file, "# =====================================================================\n");
	fprintf(file, "#");
	
	fprintf(file, "set val(chan)           Channel/WirelessChannel    ;#Channel Type\n");
	fprintf(file, "set val(prop)           Propagation/TwoRayGround   ;# radio-propagation model\n");
	fprintf(file, "set val(netif)          Phy/WirelessPhy            ;# network interface type\n");
	fprintf(file, "set val(mac)            Mac/802_11                 ;# MAC type\n");
	fprintf(file, "set val(ifq)            Queue/DropTail/PriQueue    ;# interface queue type\n");
	fprintf(file, "set val(ll)             LL                         ;# link layer type\n");
	fprintf(file, "set val(ant)            Antenna/OmniAntenna        ;# antenna model\n");
	fprintf(file, "set val(ifqlen)         50                         ;# max packet in ifq\n");
	fprintf(file, "set val(nn)             %d                          ;# number of mobilenodes\n", num_sensor_nodes);
	fprintf(file, "set val(rp)             AODV                       ;# choose your routing protocol\n");
	fprintf(file, "set val(x)	        %d\n", map_max_x);
	fprintf(file, "set val(y)	        %d\n", map_max_y);
	fprintf(file, "set val(engmodel)       EnergyModel ;\n");
	fprintf(file, "set val(stop)           300      ;# time of simulation end\n");
	fprintf(file, "set ns                  [new Simulator]\n");
	fprintf(file, "set tracefd             [open traceout.tr w]\n");
	fprintf(file, "set namtrace            [open nameout.nam w]\n\n");

	
	fprintf(file, "$ns trace-all $tracefd\n");
	fprintf(file, "$ns use-newtrace\n");
	fprintf(file, "$ns namtrace-all-wireless $namtrace $val(x) $val(y)\n\n");
	
	fprintf(file, "# set up topography object\n");
	fprintf(file, "set topo       [new Topography]\n");

	fprintf(file, "$topo load_flatgrid $val(x) $val(y)\n\n");

	fprintf(file, "create-god $val(nn)\n");

	//TODO:
	//Phy/WirelessPhy set CSThresh_ 9.74527e-09
	//Phy/WirelessPhy set RXThresh_ 9.74527e-09
	MAP::iterator node_element;
  	SensorNode *current_node;
	node_element = Topology.begin();
	current_node = *node_element;
	fprintf(file, "set chan_1_ [new $val(chan)]\n");
	fprintf(file, "# configure the nodes\n");
        fprintf(file, "$ns node-config \
			-adhocRouting $val(rp) \
			-llType $val(ll) \
			-macType $val(mac) \
			-ifqType $val(ifq) \
			-ifqLen $val(ifqlen)\
			-antType $val(ant) \
			-propType $val(prop) \
			-phyType $val(netif)  \
			-topoInstance $topo  \
			-agentTrace ON \
			-routerTrace ON  \
			-macTrace OFF  \
			-movementTrace ON  \
			-energyModel $val(engmodel) \
			-initialEnergy %f \
			-idlePower %f \
			-channel $chan_1_\n"
			, current_node->initial_energy, idle_node_energy);
			 
		
	
	fprintf(file, "       set node_(0) [$ns node]\n");
	
	//Print node's location  
	node_element++;
	for (;node_element != Topology.end(); node_element++)
	{
		current_node = *node_element;
		fprintf(file, "$ns node-config -initialEnergy %f \n", current_node->initial_energy);
		fprintf(file, "       set node_(%d) [$ns node]\n\n", current_node->id);
	}
	
	fprintf(file, "source ./%s\n\n",topology_file_name_);
	fprintf(file, "# Define node initial position in nam\n");
	fprintf(file, "$ns initial_node_pos $node_(0) 50\n");
	fprintf(file, "for {set i 1} {$i < $val(nn)} { incr i } {\n");
	fprintf(file, "# defines the node size for nam\n");
	fprintf(file, "$ns initial_node_pos $node_($i) 30\n");
	fprintf(file, "}\n\n");

	fprintf(file, "# Telling nodes when the simulation ends\n");
	fprintf(file, "for {set i 0} {$i < $val(nn) } { incr i } {\n");
    	fprintf(file, "$ns at $val(stop) \"$node_($i) reset\";\n");
	fprintf(file, "}\n\n");

	
	fprintf(file, "# ending nam and the simulation \n");
	fprintf(file, "$ns at $val(stop) \"$ns nam-end-wireless $val(stop)\"\n");
	fprintf(file, "$ns at $val(stop) \"stop\"\n");
	fprintf(file, "$ns at $val(stop) \"puts \\\"end simulation\\\" ; $ns halt\"\n\n");

	fprintf(file, "proc print {} {\n");
	fprintf(file, "global ns \n");
	fprintf(file, "}\n\n");

	fprintf(file, "proc stop {} {\n");
    	fprintf(file, "global ns tracefd namtrace\n");
    	fprintf(file, "$ns flush-trace\n");
    	fprintf(file, "close $tracefd\n");
    	fprintf(file, "close $namtrace\n");
	fprintf(file, "}\n\n");

	fprintf(file, "$ns run\n");

	fclose(file);
}
 
void GenSeN::help(char *s)
{
  fprintf(stderr, "usage: %s -x int_size -y int_size -n int_nodes [-d 1-7] [-p 1-4] [-e double_energy] [-w 1-4] [-s int_seed] [-f tcl_name_file] [-h] \n\n", s);
  fprintf(stderr, "\tx : Sets map maximum X size (REQUIRED)\n");
  fprintf(stderr, "\ty : Sets map maximum Y size (REQUIRED)\n");
  fprintf(stderr, "\tn : Sets number of sensor nodes (REQUIRED)\n");
  fprintf(stderr, "\td : Sets deployment: 1 - Grid (You need to set distance)\n");
  fprintf(stderr, "\t                     2 - Random (DEFAULT)\n");
  fprintf(stderr, "\t                     3 - One-by-one\n");
  fprintf(stderr, "\t                     4 - Two-by-two\n");
  fprintf(stderr, "\t                     5 - Three-by-three\n");
  fprintf(stderr, "\t                     6 - Properlant\n");
  fprintf(stderr, "\t                     7 - Cliff\n");
  fprintf(stderr, "\tk : Sets the distance between nodes (GRID)\n");
  fprintf(stderr, "\tp : Sets nodes position: 1 - ONE Position (DEFAULT)\n");
  fprintf(stderr, "\t                         2 - Two Positions\n");
  fprintf(stderr, "\t                         3 - Three Positions\n");
  fprintf(stderr, "\t                         4 - Four Positions\n");
  fprintf(stderr, "\te : Sets maximum energy (DEFAULT=50.0)\n");
  fprintf(stderr, "\ti : Sets idle energy (DEFAULT=0.0001)\n");
  fprintf(stderr, "\tw : Sets number of energy levels : 1 - All nodes with same energy (DEFAULT)\n");
  fprintf(stderr, "\t                                   2 - Two energy levels\n");
  fprintf(stderr, "\t                                   3 - Three energy levels\n");
  fprintf(stderr, "\t                                   4 - Four energy levels\n");
  fprintf(stderr, "\ts : Sets random seed \n");
  fprintf(stderr, "\tf : Sets tcl file name \n");
  fprintf(stderr, "\th : Prints this help file\n");
  fprintf(stderr, "\n");
  exit(0);
}
void GenSeN::Found_Placement(double loc_x,double loc_y)
{
	if(loc_x<(map_max_x/4))
	{
		if(loc_y<(map_max_y/4))
			++out[0][0];
		else if(loc_y<(map_max_y/4*2))
			++out[0][1];
		else if(loc_y<(map_max_y/4*3))
			++out[0][2];
		else if(loc_y<(map_max_y))
			++out[0][3];
	}else if(loc_x<(map_max_x/4*2))
	{
		if(loc_y<(map_max_y/4))
			++out[1][0];
		else if(loc_y<(map_max_y/4*2))
			++out[1][1];
		else if(loc_y<(map_max_y/4*3))
			++out[1][2];
		else if(loc_y<(map_max_y))
			++out[1][3];
	}else if(loc_x<(map_max_x/4*3))
	{
		if(loc_y<(map_max_y/4))
			++out[2][0];
		else if(loc_y<(map_max_y/4*2))
			++out[2][1];
		else if(loc_y<(map_max_y/4*3))
			++out[2][2];
		else if(loc_y<(map_max_y))
			++out[2][3];
	}else if(loc_x<(map_max_x))
	{
		if(loc_y<(map_max_y/4))
			++out[3][0];
		else if(loc_y<(map_max_y/4*2))
			++out[3][1];
		else if(loc_y<(map_max_y/4*3))
			++out[3][2];
		else if(loc_y<(map_max_y))
			++out[3][3];
	}
}


int main(int argc, char **argv)
{
  GenSeN *gensen;

  gensen = new GenSeN(argc, argv);
  gensen->Generate_topology();

  return 0;
}
