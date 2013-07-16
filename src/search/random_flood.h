/**
 * \file random_flood.h
 *
 * Flood, pick something along the frontier, go again
 *
 * \author seabass
 * \date 12-07-2013
 */

#ifndef RANDOM_FLOOD_H
#define RANDOM_FLOOD_H

#include "search_engine.h"
#include "search_space.h"
#include "state.h"
#include "timer.h"
#include "evaluator.h"
#include "search_progress.h"
#include "state_var_t.h"

class RandomFlood : public SearchEngine {

protected:
        vector<State> frontier;
        int flood_size;

        int step();
        pair<int,vector<vector<State> > > flood();
        virtual void initialize();

public:
        RandomFlood(const Options &opts);
};

#endif
