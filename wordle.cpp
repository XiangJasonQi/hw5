#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <string>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

void wordle_helper(std::string& in, std::string floating, int index, set<string>& result);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here

    string temp_in = in;
    set<string> result;
    wordle_helper(temp_in, floating, 0, result);

    set<string> correct_result;

    set<string>::iterator it;

    for(it = result.begin(); it != result.end(); ++it){
        if(dict.find(*it) != dict.end()){
            correct_result.insert(*it);
        }   
    }

    return correct_result;
}

// Define any helper functions here
void wordle_helper(std::string& in, std::string floating, int index, set<string>& result){

    if(index == in.size()){
        if(floating.empty()){
            result.insert(in);
        }

        return; 
    }

    if(index < in.size() && in[index] != '-'){
        wordle_helper(in, floating, index +1, result);
        return;
    }

    for(int i = 0; i < floating.size(); i++){
        in[index] = floating[i];
        string novel_floating = floating.substr(0, i) + floating.substr(i + 1, floating.size());
        wordle_helper(in, novel_floating, index + 1, result);
        in[index] = '-';
    }
    for(char i = 'a'; i <= 'z'; i++){
        in[index] = i; 
        wordle_helper(in, floating, index + 1, result);
        in[index] = '-';
    }

    return;

}
