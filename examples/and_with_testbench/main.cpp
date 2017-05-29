#include <systemc.h>
#include "and2.hpp"


int sc_main (int argc, char* argv[]) {

    sc_signal<bool> a;
    sc_signal<bool> b;

    sc_signal<bool> z;

    and2 and2("AND");
    and2.a(a);
    and2.b(b);
    and2.z(z);


    // Open VCD file
    sc_trace_file *wf = sc_create_vcd_trace_file("and2");
    wf->set_time_unit(1, SC_NS);
    // Dump the desired signals
    sc_trace(wf, a, "a");
    sc_trace(wf, b, "b");
    sc_trace(wf, z, "z");

    a = 0;
    b = 0;
    sc_start(10,SC_NS);
    a = 1;
    b = 0;
    sc_start(10,SC_NS);
    a = 1;
    b = 1;
    sc_start(10,SC_NS);
    a = 0;
    b = 0;
    sc_start(10,SC_NS);

    sc_close_vcd_trace_file(wf);
    return 0;// Terminate simulation


}
