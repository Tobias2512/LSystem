#include "LSystem.hpp"
#include "LSystemFunctions.hpp"
#include <iostream>

// Method implementations
template <typename SymbolType>
LSystemInterpreter<SymbolType>::LSystemInterpreter(const unordered_set<SymbolType>& Alphabet, const vector<SymbolType>& Axiom, const unordered_set<Production<SymbolType>> &Productions) :
        Alphabet(Alphabet), Axiom(Axiom), Productions(Productions), internal_state(Axiom) {
    // Check if all productions valid
    unordered_set<SymbolType> uniquePredecessors; // unordered_set so we can easily see if all predecessors are unique
    for(const auto &prod : Productions){
        if(! isValidProduction(prod, Alphabet)){
            throw invalid_argument("One of the productions is invalid, check if every production has symbols which are in the alphabet.");
        }
        if(! uniquePredecessors.insert(prod.getPredecessor()).second){ // .insert returns a pair (iterator, bool) so with .second we acces the bool which is false when the insertion wasn't succesful
            throw invalid_argument("All productions must have a unique predecessor."); // when insert not succesful -> object already in unordered_set -> not a unique precessor.
        }
    }
    for(const auto &symbol : Alphabet){ // Iterate through all symbols in Alphabet
        if(uniquePredecessors.count(symbol) == 0){ // we can use same set to see if the symbol has a production already
            const auto newProduction = Production<SymbolType>(symbol, {symbol}); // If the symbol doesn't have a production -> add an identity production
            this->Productions.insert(newProduction);
        }
    }
}

template <typename SymbolType>
unordered_set<SymbolType> LSystemInterpreter<SymbolType>::getAlphabet() const {
    return this->Alphabet;
}

template <typename SymbolType>
unordered_set<Production<SymbolType>> LSystemInterpreter<SymbolType>::getProductions() const {
    return this->Productions;
}

template <typename SymbolType>
vector<SymbolType> LSystemInterpreter<SymbolType>::getInternal_state() const {
    return this->internal_state;
}

template <typename SymbolType>
void LSystemInterpreter<SymbolType>::setInternal_state(vector<SymbolType> &newInternal_state) {
    this->internal_state = newInternal_state;
}

template <typename SymbolType>
void LSystemInterpreter<SymbolType>::reset() {
    setInternal_state(this->Axiom);
}

template <typename SymbolType> // In the 'template' u gave us this function was const, but we can't update internal_state if that's the case so -> no const function anymore.
vector<SymbolType> LSystemInterpreter<SymbolType>::operator() () {
    vector<SymbolType> next_state;
    // Loop through all symbols in previous internal_state
    for(const SymbolType &Symbol : getInternal_state()){
        // With this Symbol Loop through every production and see if this symbol == Predecessor of that production
        for(const Production<SymbolType> &Prod : getProductions()){
            if (Prod.getPredecessor() == Symbol){
                const auto &successor = Prod.getSuccessor();
                // If they are equal -> insert all symbols of successor at the end of our next_state vector.
                next_state.insert(next_state.end(), successor.begin(), successor.end());
            }
        }
    }
    // update the internal state with next_state and then return the next_state
    setInternal_state(next_state);
    return next_state;
}

// explicitly instantiate the template with necessary types:
template class LSystemInterpreter<char>;
template class LSystemInterpreter<string>;