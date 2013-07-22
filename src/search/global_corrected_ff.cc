/**
 * \file global_corrected_ff.cc
 *
 *
 *
 * \author seabass
 * \date 22-07-2013
 */

#include "global_corrected_ff.h"

GlobalCorrectedFF::GlobalCorrectedFF(const Options &options)
        : FFHeuristic(options){
}

int GlobalCorrectedFF::get_heuristic(){
        return this->get_correction_factor() * FFHeuristic::get_heuristic();
}

void GlobalCorrectedFF::observe(SearchNode parent, SearchNode child){
        int trans_cost = -1;
        int parent_h = -1;
        int child_h = -1;

        trans_cost = child.get_g() - parent.get_g();
        this->evaluate(parent.get_state());
        parent_h = FFHeuristic::get_heuristic();
        this->evaluate(child.get_state());
        child_h = FFHeuristic::get_heuristic();

        // I'm assuming trans_cost is greater than 0 here.
        this->seen_error += (parent_h - child_h - trans_cost) / trans_cost;
        this->num_samples++;
}

GlobalCorrectedFF::~GlobalCorrectedFF(){
}


