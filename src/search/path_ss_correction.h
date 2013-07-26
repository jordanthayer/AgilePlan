/**
 * \file path_ss_corrections.h
 *
 * Handled like global_ss_correction.  One hash-table per heuristic
 * used, which is of course incredibly inefficient. * We'll write
 * another version later that aggergates all of the corrected
 * heuristics into a vector.
 *
 * \author seabass
 * \date 26-07-2013
 */

#ifndef PATH_SS_CORRECTION
#define PATH_SS_CORRECTION

#include "search_space.h"
#include "node_assoc.h"

class SearchNode;

class PathSSCorrection {

protected:
        NodeAssoc *seen_error;

        int get_correction_factor(SearchNode *node);
        virtual void observe(SearchNode parent, SearchNode child) = 0;

public:
        PathSSCorrection();
        ~PathSSCorrection();
};

#endif
