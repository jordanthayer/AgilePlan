/**
 * \file flood_hillclimber.cc
 *
 *
 *
 * \author seabass
 * \date 15-07-2013
 */

#include "flood_hillclimber.h"

#include "globals.h"
#include "option_parser.h"
#include "successor_generator.h"
#include "g_evaluator.h"
#include "plugin.h"


#include <cassert>
#include <cstdlib>
#include <set>

using namespace std;


FloodHillclimber::FloodHillclimber(const Options &opts)
  : RandomFlood(opts){
        current = new State(*g_initial_state);
}

int FloodHillclimber::step(){
        pair<int, vector<vector<State> > > flood_ret = flood();
        vector<State>::const_iterator fs;
        State best = frontier[0];
        SearchNode bnode = search_space.get_node(best);
        int best_h = bnode.get_h();
        int current_h = 42;

        flood_ret.second.clear();

        switch(flood_ret.first){
        case IN_PROGRESS:

                // not sure how we're going to do the heuristic computation
                // it would be nice to do it right here, but we *may* have
                // to do it in the flooding step due to landmark sensitive
                // heuristics -- JTT

                for(fs = frontier.begin(); fs != frontier.end(); fs++){
                        State cstate = *fs;
                        SearchNode current_sn = search_space.get_node(cstate);
                        current_h = current_sn.get_h();
                        if(current_h < best_h){
                                best_h = current_h;
                                best = cstate;
                        }
                }

                *current = best;
                frontier.clear();
                return IN_PROGRESS;

        default:
                return flood_ret.first;
        }
        return flood_ret.first;
}


static SearchEngine *_parse(OptionParser &parser) {
    //open lists are currently registered with the parser on demand,
    //because for templated classes the usual method of registering
    //does not work:
    SearchEngine::add_options_to_parser(parser);
    parser.add_option<int>("flood_size", 10,
                           "number of steps before picking frontier node");
    Options opts = parser.parse();
    FloodHillclimber *engine = 0;
    if (!parser.dry_run()) {
        opts.set<bool>("mpd", false);
        engine = new FloodHillclimber(opts);
    }
    return engine;
}


static Plugin<SearchEngine> _plugin("flood_hc", _parse);

