#include "pch.h"
#include <iostream>
#include <fstream>
#include <future>
#include <thread>
#include <chrono>
#include "corefunc.h"
#include "userfunc.h"
#include <string>
#include <direct.h>

using namespace std;

vector<thread> threads;

void botxd() {
    GrowtopiaBot bot;
    bot.userInit();
    bot.eventLoop();
    bot.userLoop();
}

int main() {
    init();

    //simple bot loading and sending packets instantly

    for(int i = 0;i < 100;i++) threads.push_back(std::thread(botxd));
    
    while(true) {}
}
