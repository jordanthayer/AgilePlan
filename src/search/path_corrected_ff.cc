/**
 * \file global_corrected_ff.cc
 *
 *
 *
 * \author seabass
 * \date 22-07-2013
 */

#include "path_corrected_ff.h"
#include "option_parser.h"
#include "plugin.h"

PathCorrectedFF::PathCorrectedFF(const Options &options)
        : FFHeuristic(options){
}

int PathCorrectedFF::get_heuristic(){
        return (1 + cached_correction_factor) * FFHeuristic::get_heuristic();
}

void PathCorrectedFF::observe(SearchNode parent, SearchNode child){
        int trans_cost = -1;
        int parent_h = -1;
        int child_h = -1;

        trans_cost = child.get_g() - parent.get_g();
        this->evaluate(parent.get_state());
        parent_h = FFHeuristic::get_heuristic();
        this->evaluate(child.get_state());
        child_h = FFHeuristic::get_heuristic();

        // I'm assuming trans_cost is greater than 0 here.
        int step_error = (parent_h - child_h - trans_cost) / trans_cost;
        int *parent_error = static_cast<int*>(seen_error->get_associated_data(parent.get_state()));
        int *total = new int;
        *total = step_error + *parent_error;
        seen_error->add_associated_data(child.get_state(), total);
}

void PathCorrectedFF::evaluate(const State &state){
        cached_correction_factor = get_correction_factor(state);
        FFHeuristic::evaluate(state);
}

PathCorrectedFF::~PathCorrectedFF(){
}


static ScalarEvaluator *_parse(OptionParser &parser) {
    Heuristic::add_options_to_parser(parser);
    Options opts = parser.parse();
    if (parser.dry_run())
        return 0;
    else
        return new PathCorrectedFF(opts);
}

static Plugin<ScalarEvaluator> _plugin("ff-path-correction", _parse);
