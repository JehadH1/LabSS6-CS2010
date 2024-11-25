#include <iostream>
#include "code.h"
using namespace std;

long int clock_tick = 0;
int main() {
    initializeMemory();
    srand(0);

    do {


        cleanMemory(clock_tick);
        if (clock_tick % REQUEST_INTERVAL == 0) {
            size_t size = rand() % (MAX_SIZE - MIN_SIZE + 1) + MIN_SIZE;
            size_t expiry = rand() % (MAX_LEASE - MIN_LEASE + 1) + MIN_LEASE;
            cout <<" size "<< size << " " <<"time "<< expiry << " clock " << clock_tick;
            cout << endl;
            getMemory(size, expiry);
            print();

        }
        clock_tick++;
    } while (clock_tick != TIME_LIMIT);
    printStats();
}
