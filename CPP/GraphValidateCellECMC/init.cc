#include "Checker.h"
#include <iostream>
#include <fstream>
using namespace std;

void Checker::init_cell() {
//*********************************************************************!
// 
// Establish the cell-scheme and put the inital configuration in the cells
// Restart from last valid conf of 'pos.dat'
//
//*********************************************************************!
  	int n_1, n_2, i, j, c_1, c_2, i_2, j_2;
  	init_pos(); //intial condition
 //*** create the neighbor table ***!
  	for (j = 0; j < Param::number_cell[1]; j++){
	  	for (i = 0; i < Param::number_cell[0]; i++){
        	for (c_2 = -1; c_2 < 2; c_2++){
           		for (c_1 = -1; c_1 < 2; c_1++){
			  		n_1 = i + j* Param::number_cell[0];
			  		i_2 = (i + c_1 + Param::number_cell[0]) % Param::number_cell[0];
			  		j_2 = (j + c_2 + Param::number_cell[1]) % Param::number_cell[1];
			  		n_2 = i_2 + j_2*Param::number_cell[0];
              		cell_neighbour[n_1][c_1 + 1 + (c_2 + 1)*3] = n_2;
           		}
        	}
     	}
  	}
  //*** end neighbor table ***!

  //*** put the initial condition in the Cells ***!
  	int i_cell[2];
  	for (i = 0; i < Param::number_spheres; i++) {
     	for (j = 0; j < 2; j++) {
	  		i_cell[j] = floor((positions[i][j] + Param::box[j]/2)/Param::cell_size[j]);
	  		if (i_cell[j] == Param::number_cell[j]) {
	  			i_cell[j] = 0;
	  			positions[i][j] -= Param::box[j];
	        }
     	}
     	n_1 = i_cell[0] + i_cell[1]*Param::number_cell[0];
     	if (i == 0) {
     		cell_cur = n_1;
     		k_cur = cell_ocp[n_1];
     	}
     	for (j = 0; j < 2; j++) {
	  		cell[n_1][cell_ocp[n_1]][j] = positions[i][j] + Param::box[j]/2 -
	  				((double)(i_cell[j]) + 0.5)*Param::cell_size[j];
     	}
		plist[n_1][ cell_ocp[n_1]  ] = i;
     	cell_ocp[n_1]++;
  	}
  //*** end fill cells ***!
}


void Checker::init_pos(){
//******************************************************************!                
// 
// Creates an initial condition for a squared number of disks
// 
// Works with square or rectangular box
//
//******************************************************************!
	int number_points = 0;
	cout<<"Open\t"<<Param::position_file<<endl;
  	ifstream init (Param::position_file);
  	if (init.is_open()) {
	    for (string line; getline(init, line); number_points++) {
	    	istringstream in(line);
	    	in >> positions[number_points][0] >> positions[number_points][1];
	    }
	cout << "Reads " << number_points << " points.\n"; 
    } else {
    	cout << "Error: no valid initial configuration.\n";
    }
}
