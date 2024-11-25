#ifndef code_h
#define code_h

#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <utility>

// Constants for simulation
const int MIN_LEASE = 40;
const int MAX_LEASE = 70;
const int MIN_SIZE = 50;
const int MAX_SIZE = 350;
const int TIME_LIMIT = 100;
const int REQUEST_INTERVAL = 10;
const int MEMORY_SIZE = 1000;

// Type Definitions
using range = std::pair<int, int>; // Represents a memory range [start, size]
using alloc = std::pair<range, int>; // Represents an allocated memory block with expiry time

// Global variables
extern std::vector<alloc> alloc_list; // List of allocated memory blocks
extern std::vector<range> free_list;  // List of free memory blocks


// Function Declarations
void initializeMemory();

void print();
void getMemory(int sizeMem, int expiration);
void cleanMemory(int clock);
void printStats();

#endif
