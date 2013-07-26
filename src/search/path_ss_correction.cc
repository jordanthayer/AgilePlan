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
}

PathSSCorrection::~PathSSCorrection(){
        delete seen_error;
}

int PathSSCorrection::get_correction_factor(SearchNode *node){
        int *cumulative_error =
                static_cast<int*>(seen_error->get_associated_data(node->get_state()));
        return *cumulative_error / node->get_g();
}
