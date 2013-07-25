/**
 * \file node_assoc.h
 *
 *
 *
 * \author seabass
 * \date 25-07-2013
 */

#ifndef NODE_ASSOC_H
#define NODE_ASSOC_H

#include <ext/hash_map>
#include "state.h" // for state_var_t

class NodeAssoc {
    class HashTable;
    HashTable *nodeData;

public:
    NodeAssoc();
    ~NodeAssoc();

    void* get_associated_data(const State &state);
    void add_associated_data(const State &state, void* data);

};

#endif
