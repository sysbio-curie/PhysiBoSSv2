/*
###############################################################################
# If you use PhysiCell in your project, please cite PhysiCell and the version #
# number, such as below:                                                      #
#                                                                             #
# We implemented and solved the model using PhysiCell (Version x.y.z) [1].    #
#                                                                             #
# [1] A Ghaffarizadeh, R Heiland, SH Friedman, SM Mumenthaler, and P Macklin, #
#     PhysiCell: an Open Source Physics-Based Cell Simulator for Multicellu-  #
#     lar Systems, PLoS Comput. Biol. 14(2): e1005991, 2018                   #
#     DOI: 10.1371/journal.pcbi.1005991                                       #
#                                                                             #
# See VERSION.txt or call get_PhysiCell_version() to get the current version  #
#     x.y.z. Call display_citations() to get detailed information on all cite-#
#     able software used in your PhysiCell application.                       #
#                                                                             #
# Because PhysiCell extensively uses BioFVM, we suggest you also cite BioFVM  #
#     as below:                                                               #
#                                                                             #
# We implemented and solved the model using PhysiCell (Version x.y.z) [1],    #
# with BioFVM [2] to solve the transport equations.                           #
#                                                                             #
# [1] A Ghaffarizadeh, R Heiland, SH Friedman, SM Mumenthaler, and P Macklin, #
#     PhysiCell: an Open Source Physics-Based Cell Simulator for Multicellu-  #
#     lar Systems, PLoS Comput. Biol. 14(2): e1005991, 2018                   #
#     DOI: 10.1371/journal.pcbi.1005991                                       #
#                                                                             #
# [2] A Ghaffarizadeh, SH Friedman, and P Macklin, BioFVM: an efficient para- #
#     llelized diffusive transport solver for 3-D biological simulations,     #
#     Bioinformatics 32(8): 1256-8, 2016. DOI: 10.1093/bioinformatics/btv730  #
#                                                                             #
###############################################################################
#                                                                             #
# BSD 3-Clause License (see https://opensource.org/licenses/BSD-3-Clause)     #
#                                                                             #
# Copyright (c) 2015-2018, Paul Macklin and the PhysiCell Project             #
# All rights reserved.                                                        #
#                                                                             #
# Redistribution and use in source and binary forms, with or without          #
# modification, are permitted provided that the following conditions are met: #
#                                                                             #
# 1. Redistributions of source code must retain the above copyright notice,   #
# this list of conditions and the following disclaimer.                       #
#                                                                             #
# 2. Redistributions in binary form must reproduce the above copyright        #
# notice, this list of conditions and the following disclaimer in the         #
# documentation and/or other materials provided with the distribution.        #
#                                                                             #
# 3. Neither the name of the copyright holder nor the names of its            #
# contributors may be used to endorse or promote products derived from this   #
# software without specific prior written permission.                         #
#                                                                             #
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" #
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE   #
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE  #
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE   #
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR         #
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF        #
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS    #
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN     #
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)     #
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE  #
# POSSIBILITY OF SUCH DAMAGE.                                                 #
#                                                                             #
###############################################################################
*/
#ifndef __Custom_h__
#define __Custom_h__

#include "custom_cell.h"
#include "../core/PhysiCell.h"
#include "../modules/PhysiCell_standard_modules.h" 
#include "custom_main.h"

using namespace BioFVM; 
using namespace PhysiCell;

struct init_record
{
	float x;
	float y;
	float z;
	float radius;
	int phase;
	double elapsed_time;
};

///std::string ecm_file;
// setup functions to help us along 
void create_cell_types( void );
void setup_tissue( void ); 
//std::vector<std::string> conc_names;
// set up the BioFVM microenvironment 
void setup_microenvironment( void ); 
// custom pathology coloring function 
std::vector<std::string> my_coloring_function( Cell* );
std::vector<std::string> ECM_coloring_function( Cell* );
std::vector<std::string> pMotility_coloring_function( Cell* );
std::vector<std::string> migration_coloring_function( Cell* );

// custom cell phenotype functions could go here 
void tumor_cell_phenotype_with_signaling( Cell* pCell, Phenotype& phenotype, double dt );
/** \brief Write Density values to output file */
void set_input_nodes(Custom_cell* pCell); 
void from_nodes_to_cell(Custom_cell* pCell, Phenotype& phenotype, double dt);
std::vector<init_record> read_init_file(std::string filename, char delimiter, bool header);
void build_ecm_shape();
std::vector<std::vector<double>> create_cell_sphere_positions(double cell_radius, double sphere_radius);
/** \brief Go to proliferative phase if proliferation ON and in G0 phase */
void do_proliferation(Cell* pCell, Phenotype& phenotype, double dt);

inline float sphere_volume_from_radius(float radius) {return 4.0/3.0 * PhysiCell_constants::pi * std::pow(radius, 3);}

bool touch_ECM(Custom_cell* pCell);
void enough_to_node( Custom_cell* pCell, std::string nody, std::string field );
void color_node(Custom_cell* pCell);
inline void static_volume_function( Cell* pCell, Phenotype& phenotype, double dt ){return ;}; // do not update volume
#endif