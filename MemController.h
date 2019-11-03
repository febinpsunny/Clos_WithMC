#ifndef __MEMCONTROLLER_H__
#define __MEMCONTROLLER_H__

//---------------------------------------------------------------------------

#define GI_BUFFER_DEPTH 2
#define GLOBAL_TX_INDEX 1
#define RESET_REQ_QUEUE 200
#define ONE_CYCLE 0.5

#include <systemc.h>
#include <vector>
#include <algorithm>
#include "buffer.h"
#include "status.h"
//#include "reservationtable.h"
#include "GlobalTypeDefs.h"
extern unsigned int lambda[];

SC_MODULE(TMemController)
{
  // I/O Ports
  sc_in_clk          clock;      // The input clock for the router
  sc_in_clk          photonic_clock;
  sc_in<bool>        reset;               // The reset signal for the router

  /** Ports for the bottom electrical layer connect with Hub1 and Hub2- START **/
  sc_in<TFlit>       flit_rx [NOC_GWI_COUNT];
  sc_in<bool>          req_rx[NOC_GWI_COUNT];
  sc_out<bool>         ack_rx[NOC_GWI_COUNT];

  sc_out<TFlit>      flit_tx[NOC_GWI_COUNT];
  sc_out<bool>       req_tx[NOC_GWI_COUNT];
  sc_in<bool>        ack_tx[NOC_GWI_COUNT];

  sc_out<int>        free_slots[NOC_GWI_COUNT];
  sc_in<int>         free_slots_neighbor[NOC_GWI_COUNT];


  /** Ports for the bottom electrical layer - END **/

  /** Ports for optical communication  - START **/

  sc_out<TFlit>                  clos_data_tx[DEFAULT_CLOS_WAVEGUIDES];
  sc_in<TFlit>                   clos_data_rx[DEFAULT_CLOS_WAVEGUIDES];

  /** Ports for optical communication  - END **/

  int cycle_count;

  TBuffer            buffer_local[NOC_GWI_COUNT];         // Buffer for input channel from the electrical side
  TBuffer            buffer_receive;         // Buffer for input channel from the optical side
  bool               current_level_rx[NOC_GWI_COUNT];    // Current level for Alternating Bit Protocol (ABP)
  bool               current_level_tx[NOC_GWI_COUNT];    // Current level for Alternating Bit Protocol (ABP)
  bool               current_level_tx_local[NOC_GWI_COUNT];    // Local Current level for Alternating Bit Protocol (ABP)

  TStats             stats;                           // Statistics

  int 				 cluster_id;
  unsigned long routed_flits;

//  static long flitsThroughGWI;


  // Threads and Functions
  void 				 delayCount();
  void               clos_rx_process(); // The receive data from clos network to local buffer
  void 				 clos_tx_process(); // Tx process to respond to memory read requests
  unsigned long     getRoutedFlits();       // Returns the number of routed flits
  double            getPower();
  // Constructor

  SC_CTOR(TMemController)
  {
	  buffer_receive.SetMaxBufferSize(PHOTONIC_BUFFER_DEPTH);

	  SC_METHOD(delayCount);
	  sensitive << reset;
	  sensitive << clock.pos();

	  SC_METHOD(clos_rx_process);
      sensitive << reset;
      sensitive << clock.pos();

      SC_METHOD(clos_tx_process);
      sensitive << reset;
      sensitive << clock.pos();

  }

  private:

  vector<int>        data_ack_queue;
  sc_uint<2>         req_source_id;
  int                prev_winner;
  int 				 prev_srcid;
  int                prev_dstid;
  double 			 previous_transfer;
  double 			 previous_transfer_photonic[DEFAULT_CLOS_WAVEGUIDES];
  int 			 previous_transfer_srcid[DEFAULT_CLOS_WAVEGUIDES];
  bool               safe_to_reserve; // safe to send reservation to arbiter
  bool               safe_to_send;    // safe to send data to crossbar
  public:
  unsigned int local_drained;
};

#endif

