#ifndef __STATS_H__
#define __STATS_H__

//---------------------------------------------------------------------------
#include <vector>
#include "power.h"

using namespace std;

class TStats
{
public:

  TStats() {}

  void configure(const int node_id, const double _warm_up_time);

  // Access point for stats update
  void receivedFlit(const double arrival_time,
		    const TFlit& flit);

  // Returns the average delay (cycles) for the current node as
  // regards to the communication whose source is src_id
  double getAverageDelay(const int src_id);

  double getSCAverageDelay(const int src_id);

  // Returns the average delay (cycles) for the current node
  double getAverageDelay();

  double getSCAverageDelay();

  // Returns the max delay for the current node as regards the
  // communication whose source node is src_id
  double getMaxDelay(const int src_id);

  // Returns the max delay (cycles) for the current node
  double getMaxDelay();

  // Returns the average throughput (flits/cycle) for the current node
  // and for the communication whose source is src_id
  double getAverageThroughput(const int src_id);

  // Returns the average throughput (flits/cycle) for the current node
  double getAverageThroughput();

  // Returns the number of received packets from current node
  unsigned int getReceivedPackets();

  unsigned int getReceivedFloatPackets();

  unsigned int getSameClustPackets();

  // Returns the number of received flits from current node
  unsigned int getReceivedFlits();

  // Returns the number of communications whose destination is the
  // current node
  unsigned int getTotalCommunications();

  // Returns the energy consumed for communication src_id-->dst_id
  // under the following assumptions: (i) Minimal routing is
  // considered, (ii) constant packet size is considered (as the
  // average between the minimum and the maximum packet size).
  double getCommunicationEnergy(int src_id, int dst_id);

  // Shows statistics for the current node
  void showStats(int curr_node, std::ostream& out = std::cout, bool header = false);


public:
  
  TPower              power;


private:

  int                 id;
  vector<CommHistory> chist;  
  double              warm_up_time;

  int searchCommHistory(int src_id);
};

//---------------------------------------------------------------------------

#endif
