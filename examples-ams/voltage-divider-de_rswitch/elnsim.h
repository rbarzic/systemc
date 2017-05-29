/*
 * elnsim.h
 *
 *  Created on: Feb 22, 2016
 *      Author: lexy
 */

#ifndef ELNSIM_H_
#define ELNSIM_H_

#include <systemc-ams>
SC_MODULE (simeln){
    sca_eln::sca_terminal term1, term2;
    //sca_eln::sca_r r1, r2;
    sca_eln::sca_r r1;
    sca_eln::sca_de_r r2;
    sc_core::sc_in<double> ctrl;

SC_CTOR(simeln):term1("term1"),term2("term"), gnd("gnd"), r1("r1", 1e3), r2("r2", 100){
	r1.p(term1);
	r1.n(term2);
	r2.p(term2);
	r2.n(gnd);
	r2.inp(ctrl);

    }
private:
	sca_eln::sca_node_ref gnd;

};



#endif /* ELNSIM_H_ */
