/**
 * \file global_ss_correction.h
 *
 *
 *
 * \author seabass
 * \date 22-07-2013
 */

#ifndef GLOBAL_SS_CORRECTION
#define GLOBAL_SS_CORRECTION

#include "search_space.h"

class SearchNode;

class GlobalSSCorrection {
protected:
        int seen_error;
        int num_samples;

        int get_correction_factor();
        virtual void observe(SearchNode parent, SearchNode child) = 0;

public:
        GlobalSSCorrection();
};

#endif
