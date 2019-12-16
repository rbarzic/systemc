#include <systemc.h>
#include <tlm_utils/simple_initiator_socket.h>

SC_MODULE (hello_world) {
    SC_CTOR (hello_world)
    {
        SC_THREAD(say_hello);
    }

    void say_hello()
    {
        cout << "Hello World SystemC" << endl;
    }

};

int sc_main(int argc, char* argv[])
{
    hello_world hello("HELLO");
    sc_start();

    return (0);
}
