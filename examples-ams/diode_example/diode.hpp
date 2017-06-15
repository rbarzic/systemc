/* diode.h */

// A diode implemented as a switch - with some
// resitor in front of it to make the testbench easier (just a voltage source)

#ifndef _DIODE_H_
#define _DIODE_H_

#include <systemc-ams>

SC_MODULE (diode_and_r){
    sca_eln::sca_terminal vin, n;
    sca_eln::sca_terminal p;

    sc_core::sc_in<bool> diodectrl;

    sca_tdf::sca_out<double> vdiode;
    sca_eln::sca_r r1;




    sca_eln::sca_de_rswitch sw;
    sca_eln::sca_tdf::sca_vsink  vsink;

    SC_CTOR(diode_and_r):r1("r1",100),p("p"),n("n"), sw("sw",0.1,10e12),vsink("vsink") {

        r1.p(vin);
        r1.n(p);
	sw.p(p);
	sw.n(n);
        sw.ctrl(diodectrl);

        vsink.n(n);
        vsink.p(p);
        vsink.outp(vdiode);

    }



};



#endif /* _DIODE_H_ */
