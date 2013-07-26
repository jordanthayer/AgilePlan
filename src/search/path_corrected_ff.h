/**
 * \file path_corrected_ff.h
 *
 *
 *
 * \author seabass
 * \date 26-07-2013
 */

#ifndef PATH_FF
#define PATH_FF

#include "path_ss_correction.h"
#include "ff_heuristic.h"

class FFHeuristic;
class PathSSCorrection;

class PathCorrectedFF: public FFHeuristic, protected PathSSCorrection {

protected:
        void evaluate(const State &state);
        int get_heuristic();
        void observe(SearchNode parent, SearchNode child);

public:
        PathCorrectedFF(const Options &options);
        ~PathCorrectedFF();
};

#endif


