/**
 * \file flood_hillclimber.h
 *
 *
 *
 * \author seabass
 * \date 15-07-2013
 */

#ifndef FLOOD_HILLCLIMBER
#define FLOOD_HILLCLIMBER

#include "random_flood.h"
#include "heuristic.h"

class Heuristic;

class FloodHillclimber : public RandomFlood{

protected:
        vector<Heuristic *> heuristics;

        int step();

public:
        FloodHillclimber(const Options &opts);
};

#endif

