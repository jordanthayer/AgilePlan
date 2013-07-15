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
        int choices;
        int selection;
        pair<int, vector<vector<State> > > flood_ret = flood();

        flood_ret.second.clear();
        switch(flood_ret.first){
        case IN_PROGRESS:
                choices = frontier.size();
                selection = rand() % choices;
                *current = frontier[selection];
                frontier.clear();
                return IN_PROGRESS;
        default: return flood_ret.first;
        }
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

