/**
 * Tests des fonctionnalités de grammar.h sur fibo.bnf et par.bnf
 */

#include <iostream>
#include <cassert>

#include "bnf/grammar.h"

void testCardinality() {

    Grammar fibo("data/fibo.bnf");

    assert(fibo["F"].getCardinality(0)  ==   0);
    assert(fibo["F"].getCardinality(1)  ==   2);
    assert(fibo["F"].getCardinality(2)  ==   3);
    assert(fibo["F"].getCardinality(3)  ==   5);
    assert(fibo["F"].getCardinality(4)  ==   8);
    assert(fibo["F"].getCardinality(5)  ==  13);
    assert(fibo["F"].getCardinality(6)  ==  21);
    assert(fibo["F"].getCardinality(7)  ==  34);
    assert(fibo["F"].getCardinality(8)  ==  55);
    assert(fibo["F"].getCardinality(9)  ==  89);
    assert(fibo["F"].getCardinality(10) == 144);

    Grammar par("data/par.bnf");

    assert(par["W"].getCardinality(0)  ==     1);
    assert(par["W"].getCardinality(1)  ==     0);
    assert(par["W"].getCardinality(2)  ==     1);
    assert(par["W"].getCardinality(3)  ==     0);
    assert(par["W"].getCardinality(4)  ==     2);
    assert(par["W"].getCardinality(5)  ==     0);
    assert(par["W"].getCardinality(6)  ==     5);
    assert(par["W"].getCardinality(7)  ==     0);
    assert(par["W"].getCardinality(8)  ==    14);
    assert(par["W"].getCardinality(9)  ==     0);
    assert(par["W"].getCardinality(10) ==    42);
    assert(par["W"].getCardinality(11) ==     0);
    assert(par["W"].getCardinality(12) ==   132);
    assert(par["W"].getCardinality(13) ==     0);
    assert(par["W"].getCardinality(14) ==   429);
    assert(par["W"].getCardinality(15) ==     0);
    assert(par["W"].getCardinality(16) ==  1430);
    assert(par["W"].getCardinality(17) ==     0);
    assert(par["W"].getCardinality(18) ==  4862);
    assert(par["W"].getCardinality(19) ==     0);
    assert(par["W"].getCardinality(20) == 16796);
}

void testElements(const std::string& file, const std::string& nonTerminal, unsigned int nmax) {

    Grammar g(file);

    for (unsigned int n = 0; n <= nmax; n++) {

        auto elements = g[nonTerminal].getElements(n);
        auto cardinality = g[nonTerminal].getCardinality(n);

        assert(elements.size() == cardinality);

        for (decltype(cardinality) id = 0; id < cardinality; id++) {

            auto element = g[nonTerminal].getElement(n, id);

            assert(elements.count(element) == 1);

            elements.erase(element);
        }
    }
}

int main() {

    testCardinality();
    testElements("data/fibo.bnf", "F", 14);
    testElements("data/par.bnf", "W", 16);

    std::cout << "tests passed" << std::endl;

    return 0;
}