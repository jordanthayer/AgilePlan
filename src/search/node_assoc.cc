/**
 * \file node_assoc.cc
 *
 *
 *
 * \author seabass
 * \date 25-07-2013
 */

#define _POSIX_C_SOURCE 200112L

#include "node_assoc.h"
#include <ext/hash_map>
#include "state_proxy.h"

using namespace std;
using namespace __gnu_cxx;

class NodeAssoc::HashTable
        : public __gnu_cxx::hash_map<StateProxy, void*> {
// monkeying what I see being done in searchSpace without any understanding
// JTT
};


NodeAssoc::NodeAssoc(){
        nodeData = new HashTable;
}


NodeAssoc::~NodeAssoc(){
        delete nodeData;
}


void* NodeAssoc::get_associated_data(const State &state){
        return (*nodeData)[StateProxy(&state)];
}


void NodeAssoc::add_associated_data(const State &state, void* data){
        if(nodeData->find((StateProxy(&state))) == nodeData->end()){
                cout <<"Tried adding to existing entry." << endl;
        }else{
                nodeData->insert(make_pair(StateProxy(&state), data));
        }
}
