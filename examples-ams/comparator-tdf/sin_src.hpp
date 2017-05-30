#include <systemc-ams>

SCA_TDF_MODULE (sin_src) {
    sca_tdf::sca_out<double> out; // output port

    sin_src( sc_core::sc_module_name nm, double ampl_= 1.0, double freq_ = 1.0e3,
             sca_core::sca_time Tm_ = sca_core::sca_time(0.125, sc_core::SC_MS))
        : out("out"), ampl(ampl_), freq(freq_), Tm(Tm_) {}
    void set_attributes() {
        set_timestep(Tm);
    }
    void processing() {
        double t = get_time().to_seconds(); // actual time
        out.write( ampl * std::sin( 2.0 * M_PI * freq * t ) );
    }
private:
    double ampl; // amplitude
    double freq; // frequency
    sca_core::sca_time Tm; // module time step
};
