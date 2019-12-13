#ifndef TARGET_H
#define TARGET_H

// Needed for the simple_target_socket
#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "utilities.h"
#include "tlm_utils/simple_target_socket.h"


// **************************************************************************************
// Target module able to handle two pipelined transactions
// **************************************************************************************

DECLARE_EXTENDED_PHASE(internal_ph);

struct Target: sc_module
{
  // TLM-2 socket, defaults to 32-bits wide, base protocol
  tlm_utils::simple_target_socket<Target> socket;

  SC_CTOR(Target)
  : socket("socket")
  , n_trans(0)
  , response_in_progress(false)
  , next_response_pending(0)
  , end_req_pending(0)
  , m_peq(this, &Target::peq_cb)
  {
    // Register callbacks for incoming interface method calls
    socket.register_nb_transport_fw(this, &Target::nb_transport_fw);
  }

  // TLM-2 non-blocking transport method

  virtual tlm::tlm_sync_enum nb_transport_fw( tlm::tlm_generic_payload& trans,
                                              tlm::tlm_phase& phase, sc_time& delay )
  {
    sc_dt::uint64    adr = trans.get_address();
    unsigned int     len = trans.get_data_length();
    unsigned char*   byt = trans.get_byte_enable_ptr();
    unsigned int     wid = trans.get_streaming_width();

    // Obliged to check the transaction attributes for unsupported features
    // and to generate the appropriate error response
    if (byt != 0) {
      trans.set_response_status( tlm::TLM_BYTE_ENABLE_ERROR_RESPONSE );
      return tlm::TLM_COMPLETED;
    }
    if (len > 4 || wid < len) {
      trans.set_response_status( tlm::TLM_BURST_ERROR_RESPONSE );
      return tlm::TLM_COMPLETED;
    }

    // Now queue the transaction until the annotated time has elapsed
    m_peq.notify( trans, phase, delay);
    return tlm::TLM_ACCEPTED;
  }

  void peq_cb(tlm::tlm_generic_payload& trans, const tlm::tlm_phase& phase)
  {
    tlm::tlm_sync_enum status;
    sc_time delay;

    switch (phase) {
    case tlm::BEGIN_REQ:

      #ifdef DEBUG
        fout << hex << trans.get_address() << " BEGIN_REQ at " << sc_time_stamp() << endl;
      #endif

      // Increment the transaction reference count
      trans.acquire();

      // Put back-pressure on initiator by deferring END_REQ until pipeline is clear
      if (n_trans == 2)
        end_req_pending = &trans;
      else
      {
        status = send_end_req(trans);
        if (status == tlm::TLM_COMPLETED) // It is questionable whether this is valid
          break;
      }

      break;

    case tlm::END_RESP:
      // On receiving END_RESP, the target can release the transaction
      // and allow other pending transactions to proceed

      #ifdef DEBUG
        fout << hex << trans.get_address() << " END_RESP at " << sc_time_stamp() << endl;
      #endif

      if (!response_in_progress)
        SC_REPORT_FATAL("TLM-2", "Illegal transaction phase END_RESP received by target");

      trans.release();
      n_trans--;

      // Target itself is now clear to issue the next BEGIN_RESP
      response_in_progress = false;
      if (next_response_pending)
      {
        send_response( *next_response_pending );
        next_response_pending = 0;
      }

      // ... and to unblock the initiator by issuing END_REQ
      if (end_req_pending)
      {
        status = send_end_req( *end_req_pending );
        end_req_pending = 0;
      }

      break;

    case tlm::END_REQ:
    case tlm::BEGIN_RESP:
      SC_REPORT_FATAL("TLM-2", "Illegal transaction phase received by target");
      break;

    default:
      if (phase == internal_ph)
      {
        // Execute the read or write commands

        tlm::tlm_command cmd = trans.get_command();
        sc_dt::uint64    adr = trans.get_address();
        unsigned char*   ptr = trans.get_data_ptr();
        unsigned int     len = trans.get_data_length();

        if ( cmd == tlm::TLM_READ_COMMAND )
        {
          *reinterpret_cast<int*>(ptr) = rand();
          fout << hex << adr << " Execute READ, data = " << *reinterpret_cast<int*>(ptr) << endl;
        }
        else if ( cmd == tlm::TLM_WRITE_COMMAND )
          fout << hex << adr << " Execute WRITE, data = " << *reinterpret_cast<int*>(ptr) << endl;

        trans.set_response_status( tlm::TLM_OK_RESPONSE );

        // Target must honor BEGIN_RESP/END_RESP exclusion rule
        // i.e. must not send BEGIN_RESP until receiving previous END_RESP or BEGIN_REQ
        if (response_in_progress)
        {
          // Target allows only two transactions in-flight
          if (next_response_pending)
            SC_REPORT_FATAL("TLM-2", "Attempt to have two pending responses in target");
          next_response_pending = &trans;
        }
        else
          send_response(trans);
        break;
      }
    }
  }

  tlm::tlm_sync_enum send_end_req(tlm::tlm_generic_payload& trans)
  {
    tlm::tlm_sync_enum status;
    tlm::tlm_phase bw_phase;
    tlm::tlm_phase int_phase = internal_ph;
    sc_time delay;

    // Queue the acceptance and the response with the appropriate latency
    bw_phase = tlm::END_REQ;
    delay = sc_time(rand_ps(), SC_PS); // Accept delay
    status = socket->nb_transport_bw( trans, bw_phase, delay );
    if (status == tlm::TLM_COMPLETED)
    {
      // Transaction aborted by the initiator
      // (TLM_UPDATED cannot occur at this point in the base protocol, so need not be checked)
      trans.release();
      return status;
    }

    // Queue internal event to mark beginning of response
    delay = delay + sc_time(rand_ps(), SC_PS); // Latency
    m_peq.notify( trans, int_phase, delay );
    n_trans++;

    return status;
  }

  void send_response(tlm::tlm_generic_payload& trans)
  {
    tlm::tlm_sync_enum status;
    tlm::tlm_phase bw_phase;
    sc_time delay;

    response_in_progress = true;
    bw_phase = tlm::BEGIN_RESP;
    delay = SC_ZERO_TIME;
    status = socket->nb_transport_bw( trans, bw_phase, delay );

    if (status == tlm::TLM_UPDATED)
    {
      // The timing annotation must be honored
      m_peq.notify( trans, bw_phase, delay);
    }
    else if (status == tlm::TLM_COMPLETED)
    {
      // The initiator has terminated the transaction
      trans.release();
      n_trans--;
      response_in_progress = false;
    }
  }

  int   n_trans;
  bool  response_in_progress;
  tlm::tlm_generic_payload*  next_response_pending;
  tlm::tlm_generic_payload*  end_req_pending;
  tlm_utils::peq_with_cb_and_phase<Target> m_peq;
};

#endif
