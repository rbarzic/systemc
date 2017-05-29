#include <systemc.h>



SC_MODULE( muller2 ) {
    sc_in<bool> a;
    sc_in<bool> b;
    sc_in<bool> rstn;
    sc_out<bool> z;

    void func() {
        if(rstn.read() == 0) {
            z.write(0);
        } else
            if(a.read() & b.read()) {
                z.write(1);
            } else
                if ((!a.read()) & (!b.read())){
                    z.write(0);
                }


    }
    SC_CTOR( muller2 ) {
        SC_METHOD( func );
        sensitive << a << b << rstn;
    }

};
