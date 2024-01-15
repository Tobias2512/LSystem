#include "LSystemFunctions.hpp"
// isValidProduction function implementation
// Function that checks if a production is valid (which means that all symbols in successor and predecessor are in the alphabet)
template <typename SymbolType>
bool isValidProduction(const Production<SymbolType> &production, const unordered_set<SymbolType> &alphabet) {
    // Check if Predecessor is valid:
    // O(1)
    if (alphabet.count(production.getPredecessor()) == 0) { // if Predecessor not in alphabet
        return false; // then instantly return false
    }
    //Check if Successor is valid:
    // O(n)
    for(const auto &succ : production.getSuccessor()){ // iterate through all Production's successors
        if (alphabet.count(succ) == 0){  // if the 'iterator' is not in Alphabet
            return false; // then instantly return false
        }
    }
    return true; // if both successor and predecessor are valid then production is valid
    // Total runs in O(n) time :)
}

// explicitly instantiate the template with necessary types:
template bool isValidProduction(const Production<char>& production, const unordered_set<char>& alphabet);
template bool isValidProduction(const Production<string>& production, const unordered_set<string>& alphabet);
template bool isValidProduction(const Production<int>& production, const unordered_set<int>& alphabet);