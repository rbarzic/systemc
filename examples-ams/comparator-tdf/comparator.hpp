#include <systemc-ams>


SCA_TDF_MODULE( comparator ) {
    sca_tdf::sca_in<double> vplus;
    sca_tdf::sca_in<double> vminus;

    sca_tdf::sca_de::sca_out<bool> comp;


    void set_attributes() {};

    void initialize() {

    };

    void processing() {
        if(vplus.read() > vminus.read()) {
            comp.write(1);
        } else {
            comp.write(0);
        }

    }


    void ac_processing() {};


    SCA_CTOR( comparator) : vplus("vplus"), vminus("vminus"){}



};
