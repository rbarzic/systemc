#include <systemc.h>



SC_MODULE( and2 ) {
    sc_in<bool> a;
    sc_in<bool> b;
    sc_out<bool> z;

    void func() {
        z.write( a.read() & b.read());
    }
    SC_CTOR( and2 ) {
        SC_METHOD( func );
        sensitive << a << b;
    }

};
