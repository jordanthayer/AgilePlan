/**
 * \file global_ss_correction.cc
 *
 *
 *
 * \author seabass
 * \date 22-07-2013
 */

#include "path_ss_correction.h"

PathSSCorrection::PathSSCorrection(){
        seen_error = new NodeAssoc();
        cached_correction_factor = 0;
}

PathSSCorrection::~PathSSCorrection(){
        delete seen_error;
}

int PathSSCorrection::get_correction_factor(SearchNode *node){
        int *cumulative_error =
                static_cast<int*>(seen_error->get_associated_data(node->get_state()));
        cached_correction_factor = *cumulative_error;
        return cached_correction_factor;
}

int PathSSCorrection::get_correction_factor(const State &state){
        int *cumulative_error =
                static_cast<int*>(seen_error->get_associated_data(state));
        cached_correction_factor =  *cumulative_error;
        return cached_correction_factor;
}
