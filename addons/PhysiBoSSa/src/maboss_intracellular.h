#ifndef _MaBoSS_Intracellular_h_
#define _MaBoSS_Intracellular_h_

#include <string>
#include <map>
#include "../../../core/PhysiCell_phenotype.h"
#include "../../../core/PhysiCell_cell.h"
#include "../../../modules/PhysiCell_pugixml.h"
#include "maboss_network.h"

class MaBoSSIntracellular : public PhysiCell::Intracellular {
 private:
 public:
	
	static long counter;
	
	std::string bnd_filename;
	std::string cfg_filename;
	
	double time_step = 12;
	bool discrete_time = false;
	double time_tick = 0.5;
	double scaling = 1.0;
	
	std::map<std::string, double> initial_values;
	std::map<std::string, double> mutations;
	std::map<std::string, double> parameters;
	
	MaBoSSNetwork maboss;

	double next_physiboss_run = 0;

	MaBoSSIntracellular();
	
	MaBoSSIntracellular(pugi::xml_node& node);
	
	MaBoSSIntracellular(MaBoSSIntracellular* copy);
	
	Intracellular* clone() {
		return static_cast<Intracellular*>(new MaBoSSIntracellular(this));
	}
	Intracellular* getIntracellularModel() {
		return static_cast<Intracellular*>(this);
	}
	
	void initialize_intracellular_from_pugixml(pugi::xml_node& node);
	
	void start() {
		this->maboss.restart_node_values();
	}
	
	void update() {
		this->maboss.run_simulation();
		this->next_physiboss_run += this->maboss.get_time_to_update();
	}
	
	bool need_update() {
		return PhysiCell::PhysiCell_globals.current_time >= this->next_physiboss_run;
	}
	
	bool has_node(std::string name) {
		return this->maboss.has_node(name);
	}
	
	bool get_boolean_node_value(std::string name) {
		return this->maboss.get_node_value(name);
	}
	
	void set_boolean_node_value(std::string name, bool value) {
		this->maboss.set_node_value(name, value);
	}
};

#endif