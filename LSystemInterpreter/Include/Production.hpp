#ifndef MINIPROJECT_PRODUCTION_HPP
#define MINIPROJECT_PRODUCTION_HPP
#include <vector>
#include <iostream>
using namespace std;

template <typename SymbolType>
class Production{
    /*  Predecessor => Successor
    Example:
        F           =>  F[+F]-F   */
public:
    Production(const SymbolType& Predecessor, const vector<SymbolType>& Successor); // Constructor
    SymbolType getPredecessor() const;
    vector<SymbolType> getSuccessor() const;
    bool operator==(const Production<SymbolType> &rhs) const; // Is needed for unordered_set hashing
private:
    SymbolType Predecessor;
    vector<SymbolType> Successor;
};

#endif //MINIPROJECT_PRODUCTION_HPP