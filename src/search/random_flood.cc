 /**
 * \file random_flood.cc
 *
 *
 *
 * \author seabass
 * \date 12-07-2013
 */

#define _POSIX_C_SOURCE 200112L

#include "random_flood.h"

#include "globals.h"
#include "option_parser.h"
#include "successor_generator.h"
#include "g_evaluator.h"
#include "plugin.h"

#include <cassert>
#include <cstdlib>
#include <set>

using namespace std;

RandomFlood::RandomFlood(const Options &opts)
  : SearchEngine(opts),
    flood_size(opts.get<int>("flood_size")){
        current = new State(*g_initial_state);
}

// initialize the search
void RandomFlood::initialize(){
        SearchNode first = search_space.get_node(*g_initial_state);
        first.open_initial(0);
        *current = first.get_state();
        cout << "Random Flood Initialized" << endl;
}


pair<int,vector<vector<State> > > RandomFlood::flood(){
        assert(frontier.size() == 0);
        vector<State> next_front;
        vector<State>::const_iterator s;
        vector<vector <State> >opens;
        vector<const Operator *>::const_iterator op;
        map<State, bool> local_closed;
        pair<map<State,bool>::iterator, bool> is_it_in;

        frontier.push_back(*current);
        for(int i = 0; i < flood_size; i++){
                for(s = frontier.begin(); s != frontier.end(); s++){
                        SearchNode prev = search_space.get_node(*s);
                        prev.close();
                        if(check_goal_and_set_plan(*s))
                                return make_pair(SOLVED, opens);
                        vector<const Operator *> succ_ops;
                        g_successor_generator->generate_applicable_ops(*s,
                                                                       succ_ops);
                        for(op = succ_ops.begin(); op != succ_ops.end(); op++){
                                State next(*s, **op);
                                search_progress.inc_generated();

                                is_it_in =
                                        local_closed.insert(make_pair
                                                            (next, true));
                                if(is_it_in.second != false){ // NEW ENTRY!
                                        SearchNode next_node = search_space.get_node(next);
                                        if (next_node.is_new())
                                                next_node.open(0, prev, *op);
                                        next_front.push_back(next);
                                        }
                        }
                }
                opens.push_back(next_front);
                frontier = next_front;
        }
        local_closed.clear();
        return make_pair(IN_PROGRESS,opens);
}

int RandomFlood::step(){
        int choices;
        int selection;
        pair<int, vector<vector<State> > > flood_ret = flood();
        flood_ret.second.clear();
        switch(flood_ret.first){
        case IN_PROGRESS:
                //select random element of the frontier, move to it
                choices = frontier.size();
                selection = rand() % choices;
                *current = frontier[selection];
                frontier.clear();
                return IN_PROGRESS;
        case FAILED:
                // possible restart
                return FAILED;
        case SOLVED:
                // just return solved
                return SOLVED;
        default:
                return flood_ret.first;
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
    RandomFlood *engine = 0;
    if (!parser.dry_run()) {
        opts.set<bool>("mpd", false);
        engine = new RandomFlood(opts);
    }
    return engine;
}


static Plugin<SearchEngine> _plugin("random_flood", _parse);

