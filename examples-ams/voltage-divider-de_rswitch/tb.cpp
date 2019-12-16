/*
 * tb.cpp
 *
 *  Created on: Feb 22, 2016
 *      Author: lexy
 *      Modified byt rbarzic2gmail.com
 */

#include <systemc>
#include <systemc-ams>
#include "elnsim.h"

int sc_main (int argc, char* argv[])

{
    sca_eln::sca_node sigInput;
    sca_eln::sca_node sigOutput;
    sca_eln::sca_node_ref gnd;




    sc_core::sc_signal<double> ctrl;

    sca_eln::sca_vsource src("src",0.0, 0.0, 3.3, 1e3);
    src.set_timestep(5, sc_core::SC_US);

    src.p(sigInput);
    src.n(gnd);

    simeln nu("nu_obj");

    nu.term1(sigInput);
    nu.term2(sigOutput);
    nu.ctrl(ctrl);

    sca_util::sca_trace_file *eln= sca_util::sca_create_vcd_trace_file("voltage-divider-eln.vcd");
    sca_trace(eln, sigInput, "signal");
    sca_trace(eln, sigOutput, "signalInput");

    ctrl = 1.0;
    sc_start(5, sc_core::SC_MS);
    ctrl = 10.0;
    sc_start(5, sc_core::SC_MS);
    ctrl = 2.0;
    sc_start(5, sc_core::SC_MS);
    sca_util::sca_close_vcd_trace_file(eln);



    return 0;
}
