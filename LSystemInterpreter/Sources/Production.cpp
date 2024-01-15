#include "Production.hpp"

// Method implementations
template <typename SymbolType>
Production<SymbolType>::Production(const SymbolType& Predecessor, const vector<SymbolType>& Successor) :
        Predecessor(Predecessor), Successor(Successor) {}

template <typename SymbolType>
SymbolType Production<SymbolType>::getPredecessor() const {
    return this->Predecessor;
}

template <typename SymbolType>
vector<SymbolType> Production<SymbolType>::getSuccessor() const {
    return this->Successor;
}

template <typename SymbolType>
bool Production<SymbolType>::operator==(const Production<SymbolType> &rhs) const{
    return (this->getPredecessor() == rhs.getPredecessor()); // && (this->getSuccessor() == rhs.getSuccessor()); <- this is unnecessary because every production has a unique predecessor.
}

// explicitly instantiate the template with necessary types:
template class Production<char>;
template class Production<string>;
template class Production<int>;