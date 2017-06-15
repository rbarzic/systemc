#include <systemc-ams>


SCA_TDF_MODULE( diode_ctrl_tdf ) {
    sca_tdf::sca_in<double> vdiode;


    sca_tdf::sca_de::sca_out<bool> diodectrl;


    void set_attributes() {
        set_timestep(Tm);
    };

    void initialize() {

    };

    void processing() {
        if(vdiode.read() > 0.0)  {
                diodectrl.write(1); // Diode is conducting
        } else {
                diodectrl.write(0); // Diode is "open"
        }

    }


    void ac_processing() {};


    // SCA_CTOR( diode_ctrl_tdf ) : vint("vint"), vout("vout"), gain("gain"), vref("vref"),
    //     sca_core::sca_time Tm_ = sca_core::sca_time(1, sc_core::SC_NS)){}

    diode_ctrl_tdf( sc_core::sc_module_name nm, sca_core::sca_time Tm_ = sca_core::sca_time(10, sc_core::SC_NS)) :
        vdiode("vdiode"),
        Tm(Tm_) {}

private:
    sca_core::sca_time Tm; // module time step

};
