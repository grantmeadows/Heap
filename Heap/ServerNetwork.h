#pragma once

#include "SimulationExecutive.h"
#include "Distribution.h"

class ServerNetwork;

class Server
{
public:
	Server(ServerNetwork *servers, Distribution *serviceTime);
	void Arrive();
private:
	int _Q = 0;
	int _S = 1;
	ServerNetwork *_servers;
	Distribution *_serviceTime;

	class DoneServeEA;

	void StartServe();
	void DoneServe();
};

class ServerNetwork
{
public:
	ServerNetwork(int numServers, int numEntitiesPerServer);
	Server *GetNextServer();
private:
	int _numServers;
	Server **_servers;
	Exponential *_serviceTime;
};
