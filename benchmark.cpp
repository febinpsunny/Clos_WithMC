#include <string.h>
#include "benchmark.h"

void benchmark::packet_injection_nodeindex()
{
	if(!reset.read())
	{
		node_id.clear(); // clearing previous cycle's node entries
		float_flag.clear();// clearing previous cycle's floatflag entries
		int lineNumber=v.size();
		if((lineNumber-2) > count)
		{

			double _current_cycle= sc_time_stamp().to_double()/1000;
			double cc= _current_cycle;
			//cout<< "current time: "<< cc << endl;
			std::string stringitem[4];
			int i=0;

			while(i<16)
			{
				std:: string str = v[count];
				std::istringstream myline(str);
				int word_no = 0;
				while(std::getline(myline, str, ' '))
				{
					stringitem[word_no] = str;
					word_no++;
				}
				double temp =  double(atof(stringitem[0].c_str()));
				if(temp == cc )
				{
					const char* temp2 = stringitem[1].c_str();
					int temp_nid = atoi(temp2);
					for(int k=0; k<4; k++)
					{
						for(int cl=0; cl<4; cl++)
						{
							//cout<<"Node Pushback"<<endl;
							node_id.push_back(temp_nid+ cl*16 + k*64); // Pushing ids of nodes that inject packets in the current cycle
							if(word_no>=4)//stringitem[word_no].compare("F"))
							{
								//cout<<"Floatflag 1 push back to float_flag vector"<<endl;
								float_flag.push_back(1);
							}
							else
							{
								//cout<<"Floatflag 0 push back to float_flag vector"<<endl;
								float_flag.push_back(0);
							}
						}
					}
					count++;
					i++;
				}
				else
				{
					i=17;
				}
			}
		}
		//for(int i=0; i < node_id.size(); i++)
		//{
		//cout<< sc_time_stamp().to_double()/1000<<" : node id"<< node_id[i]<<endl;
		//}
	}

}

//This function provides response to the processing element, whether to inject traffic or not 
int benchmark::packet_injection_response(int nodeid_request)
{
	std::vector<int>::iterator iter;
	int pos;

	iter = std::find(node_id.begin(), node_id.end(), nodeid_request);
	if( iter!= node_id.end()  )
	{
		pos = distance(node_id.begin(),iter);
		int floatVer = float_flag.at(pos);
		//cout<<float_flag.at(pos)<<endl;
		//cout<<"Position is:"<<pos<<endl;
		if(floatVer)
		{
			//cout<<"Response with float in packet"<<endl;
			return 2;
		}
		else
			return 1;
	}
	else
	{
		return 0;
	}
}

void benchmark::clear_vector()
{
	//v.clear();

}










