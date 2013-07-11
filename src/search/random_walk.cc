/**
 * \file eager_random_walk.cc
 *
 *
 *
 * \author seabass
 * \date 11-07-2013
 */

#include "random_walk.h"

#include "globals.h"
#include "option_parser.h"
#include "successor_generator.h"
#include "g_evaluator.h"
#include "plugin.h"

#include <cassert>
#include <cstdlib>
#include <set>
using namespace std;

RandomWalk::RandomWalk(
        const Options &opts)
        : SearchEngine(opts){
        current = new State(*g_initial_state);
}

// initialize the search
void RandomWalk::initialize(){
        SearchNode first = search_space.get_node(*current);
        first.open_initial(0);
}


int RandomWalk::step(){
        SearchNode prev = search_space.get_node(*current);
        prev.close();

        if(check_goal_and_set_plan(*current))
                return SOLVED;

        vector<const Operator *> applicable_ops;
        g_successor_generator->generate_applicable_ops(*current,
                                                       applicable_ops);
        int choices = applicable_ops.size();
        if(choices > 0){
                int selection = rand() % choices;
                const Operator *op = applicable_ops[selection];
                State next(*current,*op);
                SearchNode next_node = search_space.get_node(next);
                next_node.open(0,prev,op);
                search_progress.inc_generated();
                *current = next;
        }else{
                return FAILED;
        }
        return IN_PROGRESS;
}

static SearchEngine *_parse(OptionParser &parser) {
    //open lists are currently registered with the parser on demand,
    //because for templated classes the usual method of registering
    //does not work:
    SearchEngine::add_options_to_parser(parser);
    Options opts = parser.parse();

    RandomWalk *engine = 0;
    if (!parser.dry_run()) {
        opts.set<bool>("mpd", false);
        engine = new RandomWalk(opts);
    }
    return engine;
}

static Plugin<SearchEngine> _plugin("random_walk", _parse);

