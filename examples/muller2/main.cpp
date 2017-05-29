#include <systemc.h>
#include "muller2.hpp"


int sc_main (int argc, char* argv[]) {

    sc_signal<bool> a;
    sc_signal<bool> b;
    sc_signal<bool> rstn;

    sc_signal<bool> z;

    muller2 muller2("MULLER2");
    muller2.a(a);
    muller2.b(b);
    muller2.z(z);
    muller2.rstn(rstn);


    // Open VCD file
    sc_trace_file *wf = sc_create_vcd_trace_file("muller2");
    wf->set_time_unit(1, SC_NS);
    // Dump the desired signals
    sc_trace(wf, a, "a");
    sc_trace(wf, b, "b");
    sc_trace(wf, rstn, "rstn");
    sc_trace(wf, z, "z");

    a = 0;
    b = 0;
    rstn = 0;
    sc_start(10,SC_NS);
    a = 0;
    b = 0;
    rstn = 1;
    sc_start(10,SC_NS);
    a = 1;
    b = 0;
    sc_start(10,SC_NS);
    a = 1;
    b = 1;
    sc_start(10,SC_NS);
    a = 0;
    b = 1;


    sc_start(10,SC_NS);
    a = 0;
    b = 0;
    sc_start(10,SC_NS);
    a = 1;
    b = 1;
    sc_start(10,SC_NS);
    a = 1;
    b = 1;
    sc_start(10,SC_NS);
    rstn=0;
    sc_start(10,SC_NS);
    a = 0;
    b = 0;
    rstn=0;
    sc_start(10,SC_NS);
    rstn=1;
    sc_start(10,SC_NS);

    sc_close_vcd_trace_file(wf);


    return 0;// Terminate simulation


}
