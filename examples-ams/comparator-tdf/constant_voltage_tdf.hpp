#include <systemc-ams>

SCA_TDF_MODULE (constant_voltage_tdf) {
    sca_tdf::sca_out<double> out; // output port

    constant_voltage_tdf( sc_core::sc_module_name nm, double ampl_= 1.0)
        : out("out"), ampl(ampl_) {}
    void set_attributes() {

    }
    void processing() {
        out.write( ampl);
    }
private:
    double ampl; // amplitude

};
