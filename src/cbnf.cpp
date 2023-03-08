#include "bnf/grammar.h"

#define EXPORT __attribute__ ((visibility ("default")))

extern "C" {

EXPORT void* createGrammar(const char* file) {
    return new Grammar(file);
}

EXPORT void deleteGrammar(void* gptr) {
    delete (Grammar*)gptr;
}

EXPORT void* getNonTerminal(void* gptr, const char* name) {
    return &((Grammar*)gptr)->getNonTerminal(name);
}

EXPORT void* getValue(void* ntptr, bool raw) {
    std::string str = ((NonTerminal*)ntptr)->getValue(raw);
    return strdup(str.c_str());
}

EXPORT void* getCardinality(void* ntptr, unsigned int n) {  
    big_int i = ((NonTerminal*)ntptr)->getCardinality(n);
    return big_int_to_cstr(i);
}

EXPORT void* getElement(void* ntptr, unsigned int n, const char* id) { 
    big_int i(id, 10);
    std::string str = ((NonTerminal*)ntptr)->getElement(n, i);
    return strdup(str.c_str());
}

EXPORT void* getRandomElement(void* ntptr, unsigned int n) { 
    std::string str = ((NonTerminal*)ntptr)->getRandomElement(n);
    return strdup(str.c_str());
}

EXPORT void* getElements(void* ntptr, unsigned int n) {
    auto elements = ((NonTerminal*)ntptr)->getElements(n);
    void** ptrArray = new void*[elements.size() + 1];
    unsigned int i = 0;
    for (const auto& element : elements) {
        ptrArray[i++] = strdup(element.c_str());
    }
    ptrArray[i++] = NULL;
    return ptrArray;
}

EXPORT void freePtr(void* ptr) {  
    free(ptr);
}

EXPORT void freePtrArray(void** ptrArray) {  
    for (void** ptr = ptrArray; *ptr != NULL; ptr++) {
        free(*ptr);
    }
    free(ptrArray);
}

EXPORT void* getPtrArrayElement(void** ptrArray, unsigned int i) {  
    return ptrArray[i];
}

}