#include <stdlib.h>
#include "ServerNetwork.h"
#include "SimulationExecutive.h"

class Server::DoneServeEA : public EventAction
{
public:
	DoneServeEA(Server *server)
	{
		_server = server;
	};

	void Execute()
	{
		_server->DoneServe();
	};

private:
	Server *_server;
};

Server::Server(ServerNetwork *servers, Distribution *serviceTime)
{
	_servers = servers;
	_serviceTime = serviceTime;
}

void Server::Arrive()
{
	_Q++;
	if (_S > 0) {
		StartServe();
	}
}

void Server::StartServe()
{
	_Q--;
	_S--;
	SimulationExecutive::ScheduleEventIn(_serviceTime->GetRV(), new DoneServeEA(this));
}

void Server::DoneServe()
{
	_S++;
	_servers->GetNextServer()->Arrive();
	if (_Q > 0) {
		StartServe();
	}
}

ServerNetwork::ServerNetwork(int numServers, int numEntitiesPerServer)
{
	_numServers = numServers;
	_servers = new Server*[numServers];
	_serviceTime = new Exponential(1.0);
	for (int i = 0; i < numServers; i++) {
		_servers[i] = new Server(this, _serviceTime);
		for (int j = 0; j < numEntitiesPerServer; j++) {
			_servers[i]->Arrive();
		}
	}
}

Server *ServerNetwork::GetNextServer()
{
	return _servers[rand() % _numServers];
}
