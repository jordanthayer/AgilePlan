/**
 * \file global_corrected_ff.h
 *
 * Global corrections for the ff heuristic
 *
 * \author seabass
 * \date 22-07-2013
 */


#ifndef GLOBAL_FF
#define GLOBAL_FF

#include "global_ss_correction.h"
#include "ff_heuristic.h"

class FFHeuristic;
class GlobalSSCorrection;

class GlobalCorrectedFF: public FFHeuristic, protected GlobalSSCorrection{

protected:
        int get_heuristic();
        void observe(SearchNode parent, SearchNode child);

public:
        GlobalCorrectedFF(const Options &options);
        ~GlobalCorrectedFF();
};

#endif

