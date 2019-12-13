//----------------------------------------------------------------------
//  Copyright (c) 2007-2008 by Doulos Ltd.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//----------------------------------------------------------------------

// Version 2  19-June-2008 - updated for TLM-2.0


// Getting Started with TLM-2.0, Example 4

// Shows the non-blocking transport interface with the generic payload and simple sockets
// Shows nb_transport used with the forward and backward paths
// Both components are able to accept transactions on the return path,
// although neither component actually uses the return path (TLM_UPDATED)

// Shows the Approximately Timed coding style
// Models processing delay of initiator, latency of target, and request and response accept delays
// Uses payload event queues to manage both timing annotations and internal delays

// Shows the BEGIN_REQ exclusion rule at the initiator and BEGIN_RESP exclusion rule at the target
// In this example, the target allows two pipelined transactions in-flight

// Shows an explicit memory manager and reference counting

// No use of temporal decoupling, DMI or debug transport
// Nominal use of the blocking transport interface just to show the simple socket b/nb adapter

#define DEBUG

#include "top.h"

int sc_main(int argc, char* argv[])
{
  Top top("top");
  sc_start();
  
  cout << "\n***** Messages have been written to file output.txt                    *****\n";
  cout << "***** Select 'Download files after run' to read file in EDA Playground *****\n\n";

  return 0;
}
