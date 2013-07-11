/**
 * \file eager_random_walk.h
 *
 * We're sort of doing a local search thing -- Random walks make for a great
 * baseline
 *
 * \author seabass
 * \date 11-07-2013
 */

#ifndef RANDOM_WALK_H
#define RANDOM_WALK_H

#include "search_engine.h"
#include "search_space.h"
#include "state.h"
#include "timer.h"
#include "evaluator.h"
#include "search_progress.h"
#include "state_var_t.h"

class Operator;
class Options;
class SearchNode;

class RandomWalk : public SearchEngine {
private:
        State * current;

protected:
        int step();
        virtual void initialize();

public:
        RandomWalk(const Options &opts);
};

#endif
