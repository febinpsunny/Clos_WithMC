#ifndef __GLOBAL_STATS_H__
#define __GLOBAL_STATS_H__

//---------------------------------------------------------------------------

#include <iostream>
#include <vector>
#include "noc.h"
#include "gitile.h"

//---------------------------------------------------------------------------

class TGlobalStats
{
public:
  TGlobalStats(const TNoC* _noc);
  
  // Returns the aggragated average delay (cycles)
  double getAverageDelay();
  
  double getSCAverageDelay();

  // Returns the aggragated average delay (cycles) for communication
  // src_id->dst_id
  double getAverageDelay(const int src_id, const int dst_id);

  // Returns the max delay
  double getMaxDelay();

  // Returns the max delay (cycles) experimented by destination
  // node_id. Returns -1 if node_id is not destination of any
  // communication
  double getMaxDelay(const int node_id);

  // Returns the max delay (cycles) for communication src_id->dst_id
  double getMaxDelay(const int src_id, const int dst_id);
  
  // Returns tha matrix of max delay for any node of the network
  vector<vector<double> > getMaxDelayMtx();

  // Returns the aggragated average throughput (flits/cycles)
  double getAverageThroughput();

  // Returns the aggragated average throughput (flits/cycles) for
  // communication src_id->dst_id
  double getAverageThroughput(const int src_id, const int dst_id);

  // Returns the total number of received packets
  unsigned int getReceivedPackets();

  unsigned int getReceivedFloatPackets();

  unsigned int getReceivedSCPackets();

  // Returns the total number of received flits
  unsigned int getReceivedFlits();

  // Returns the maximum value of the accepted traffic
  double getThroughput();

  // Returns the number of routed flits for each router
  vector<vector<unsigned long> > getRoutedFlitsMtx();



  // Returns the total power
  double getPower();


  double getEnergyPerBit();

  double getTxRxPower();

  double getPhotonicFlits();

  double getTotalFlitsGenerated();

  double getFlitsThroughHubs();

  double getflitsGenerated();

  // Shows global statistics
  void showStats(std::ostream& out = std::cout, bool detailed = false);

#ifdef TESTING
  unsigned int drained_total;
#endif

private:
  const TNoC* noc;
};

#endif

