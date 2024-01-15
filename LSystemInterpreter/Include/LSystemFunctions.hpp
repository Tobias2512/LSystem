#ifndef MINIPROJECT_LSYSTEMFUNCTIONS_HPP
#define MINIPROJECT_LSYSTEMFUNCTIONS_HPP
#include "Production.hpp"
#include <unordered_set>
#include <string>
using namespace std;

// Hash function for when we use unordered_set with Production class:
// Because every production has to have a unique predecessor, we can just use this in our hash function.
template <typename SymbolType>
struct hash<Production<SymbolType>>{
    size_t operator()(const Production<SymbolType> &Prod) const{
        return hash<SymbolType>{}(Prod.getPredecessor());
    }};

// isValidProduction function declaration
template <typename SymbolType>
bool isValidProduction(const Production<SymbolType> &production, const unordered_set<SymbolType> &alphabet);

#endif //MINIPROJECT_LSYSTEMFUNCTIONS_HPP
