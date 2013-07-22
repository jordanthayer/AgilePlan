/**
 * \file global_ss_correction.cc
 *
 *
 *
 * \author seabass
 * \date 22-07-2013
 */

#include "global_ss_correction.h"

GlobalSSCorrection::GlobalSSCorrection(){
        seen_error = 0;
        num_samples = 0;
}

int GlobalSSCorrection::get_correction_factor(){
        if(num_samples == 0){
                return 1;
        }else{
                return seen_error / num_samples;
        }
}
