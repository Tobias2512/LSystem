#ifndef MINIPROJECT_LSYSTEM_HPP
#define MINIPROJECT_LSYSTEM_HPP
#include <unordered_set>
#include <Production.hpp>

template <typename SymbolType>
class LSystemInterpreter{
public:
    LSystemInterpreter(const unordered_set<SymbolType> &Alphabet, const vector<SymbolType> &Axiom, const unordered_set<Production<SymbolType>> &Productions); // Constructor
    unordered_set<SymbolType> getAlphabet() const;
    unordered_set<Production<SymbolType>> getProductions() const;
    vector<SymbolType> getInternal_state() const;
    void setInternal_state(vector<SymbolType> &newInternal_state);
    void reset();
    vector<SymbolType> operator() ();
private:
    unordered_set<SymbolType> Alphabet;
    vector<SymbolType> Axiom;
    unordered_set<Production<SymbolType>> Productions;
    vector<SymbolType> internal_state;
};

#endif //MINIPROJECT_LSYSTEM_HPP