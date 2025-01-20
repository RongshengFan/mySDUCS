#pragma once
template <class K, class T>
struct pairNode
{
    typedef pair<const K, T> pairType;
    pairType element;
    pairNode<K, T>* next;

    pairNode(const pairType& thePair) :element(thePair) {}
    pairNode(const pairType& thePair, pairNode<K, T>* theNext)
        :element(thePair) {
        next = theNext;
    }
};