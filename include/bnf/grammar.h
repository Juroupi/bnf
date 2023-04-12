/**
 * bnf
 */

#ifndef _GRAMMAR_H_
#define _GRAMMAR_H_

#include <iostream>
#include <istream>
#include <ostream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <set>
#include <utility>
#include <memory>
#include <optional>

#include "big_int.h"

struct Symbol {
    virtual std::string getValue(bool raw = false) const = 0;
    virtual void getCardinality(big_int& res, unsigned int n) const = 0;
    virtual bool getExists(unsigned int n) const = 0;
    virtual void getElements(std::set<std::string>& elements, unsigned int n) const = 0;
    virtual void getElement(std::string& element, unsigned int n, big_int& id) const = 0;
    virtual void getNURandomElement(std::string& element, unsigned int n) const = 0;
    virtual void getRandomElementOfHeight(std::string& element, unsigned int totaln, unsigned int n = 0) const = 0;
    virtual unsigned int getMinLength() const = 0;
};


class Terminal;
class NonTerminal;

/**
 * Règle de production d'un symbole non terminal
 */
class ProductionRule {

    unsigned int terminalsLength, minLength;
    std::vector<NonTerminal*> nonTerminals;
    std::vector<Symbol*> symbols;

    void getCardinality(big_int& res, unsigned int totaln, unsigned int n, unsigned int ntpos) const;
    
    bool getExists(unsigned int totaln, unsigned int n, unsigned int ntpos) const;

    bool getExists(unsigned int totaln, unsigned int n, unsigned int ntpos, std::vector<unsigned int> ntposes) const;

    void getNURandomElement(std::string& element, unsigned int totaln, unsigned int n, unsigned int spos, unsigned int ntpos, std::vector<unsigned int> ntposes) const;

    void getElements(std::set<std::string>& elements, unsigned int totaln, unsigned int n, unsigned int spos, std::string cur) const;
    
    unsigned int getSymbolMaxLength(unsigned int n, unsigned int totaln, unsigned int minLength) const;

public:

    float startProbability, endProbability;

    ProductionRule();

    /**
     * Ajouter un symbole terminal à la règle de production.
     * @param terminal le symbole à ajouter
     */
    void addSymbol(Terminal& terminal);

    /**
     * Ajouter un symbole non terminal à la règle de production.
     * @param nonTerminal le symbole à ajouter
     */
    void addSymbol(NonTerminal& nonTerminal);

    void getCardinality(big_int& res, unsigned int n) const;

    bool getExists(unsigned int n) const;

    void getElements(std::set<std::string>& elements, unsigned int n) const;

    void getElement(std::string& element, unsigned int n, big_int& id) const;

    void getNURandomElement(std::string& element, unsigned int n) const;

    void getRandomElementOfHeight(std::string& element, unsigned int totaln, unsigned int n = 0) const;

    unsigned int getMinLength() const;
    bool updateMinLength();

    float getProbability(float x = 0) const;

    void print(bool detailed = false, std::ostream& stream = std::cout) const;
};

/**
 * Symbole terminal.
 */
struct Terminal : public Symbol {

    const std::string value;

    Terminal(const std::string& value);

    /**
     * Récupérer la valeur du terminal.
     * @param raw si la valeur est délimitée par des guillemets
     */
    std::string getValue(bool raw = false) const override;

    void getCardinality(big_int& res, unsigned int n) const override;

    bool getExists(unsigned int n) const override;

    void getElements(std::set<std::string>& elements, unsigned int n) const override;

    void getElement(std::string& element, unsigned int n, big_int& id) const override;

    void getNURandomElement(std::string& element, unsigned int n) const override;

    void getRandomElementOfHeight(std::string& element, unsigned int totaln, unsigned int n = 0) const override;

    unsigned int getMinLength() const override;
};

/**
 * Symbole non terminal.
 */
class NonTerminal : public Symbol {

    unsigned int minLength;
    std::vector<ProductionRule> productionRules;
    mutable std::vector<std::unique_ptr<big_int>> cardinalities;
    mutable std::vector<std::optional<bool>> existences;

public:

    const std::string name;

    NonTerminal(const std::string& name);

    /**
     * Ajouter une règle de production à ce non terminal.
     * @return une référence vers la règle de production créée
     */
    ProductionRule& addProductionRule();

    /**
     * Récupérer le nom du non terminal.
     * @param raw si le nom contient les caractères '<' et '>'
     */
    std::string getValue(bool raw = false) const override;

    /**
     * Récupérer le nombre d'éléments qui peuvent être générés par ce non terminal pour une longueur donnée.
     * @param n la longueur des éléments
     */
    big_int getCardinality(unsigned int n) const;
    void getCardinality(big_int& res, unsigned int n) const override;
    bool getExists(unsigned int n) const;
    void reserveMemory(unsigned int n) const;
    void clearMemory() const;

    /**
     * Récupérer tous les éléments qui peuvent être générés par ce non terminal pour une longueur donnée.
     * @param n la longueur des éléments
     */
    std::set<std::string> getElements(unsigned int n) const;
    void getElements(std::set<std::string>& elements, unsigned int n) const override;

    /**
     * Récupérer un élément précis qui peut être généré par ce non terminal pour une longueur donnée.
     * @param n la longueur de l'élément
     * @param id l'identifiant de l'élément : dans [0 ; `getCardinality(n)`[
     */
    std::string getElement(unsigned int n, const big_int& id) const;
    void getElement(std::string& element, unsigned int n, big_int& id) const override;

    unsigned int getMinLength() const override;
    bool updateMinLength();

    /**
     * Générer un élément aléatoire uniforme à partir de ce non terminal.
     * @param n la longueur de l'élément
     */
    std::string getRandomElement(unsigned int n) const;
    void getRandomElement(std::string& element, unsigned int n) const;

    /**
     * Générer un élément aléatoire non uniforme à partir de ce non terminal.
     * @param n la longueur de l'élément
     */
    std::string getNURandomElement(unsigned int n) const;
    void getNURandomElement(std::string& element, unsigned int n) const override;
    float getProbabilitySum(unsigned int n) const;

    /**
     * Générer un élément aléatoire non uniforme à partir de ce non terminal.
     * @param n la hauteur de l'arbre
     */
    std::string getRandomElementOfHeight(unsigned int n) const;
    void getRandomElementOfHeight(std::string& element, unsigned int totaln, unsigned int n = 0) const override;
    float getProbabilitySum(float x) const;

    void print(bool detailed = false, std::ostream& stream = std::cout) const;
};

/**
 * Grammaire.
 */
class Grammar {

    std::list<Terminal> terminals;
    std::map<std::string, NonTerminal> nonTerminals;

public:
    
    static const unsigned int maxLength;

    /**
     * Constructeur par défaut.
     */
    Grammar();

    /**
     * Constructeur à partir d'un fichier au format bnf.
     * @param fileName le nom du fichier
     */
    Grammar(const std::string& fileName);

    /**
     * Ajouter un symbole terminal à la grammaire.
     * @param value la valeur du terminal
     * @return une référence vers le terminal créé
     */
    Terminal& addTerminal(const std::string& value);

    /**
     * Récupérer un symbole non terminal à partir de son nom.
     * L'ajoute s'il n'existe pas.
     * @param name le nom du non terminal
     * @return une référence vers le non terminal
     */
    NonTerminal& getNonTerminal(const std::string& name);
    NonTerminal& operator[](const std::string& name);

    /**
     * Réserver de la mémoire pour les calculs de cardinalité.
     * @param n la taille maximale des mots
     */
    void reserveMemory(unsigned int n) const;

    /**
     * Libérer la mémoire allouée pour les calculs de cardinalité.
     */
    void clearMemory() const;

    /**
     * Calculer les longueurs minimales des symboles non terminaux.
     */
    void updateMinLengths();
    
    void parse(std::istream& stream);
    void parseFile(const std::string& name);
    void parseLine(const std::string& line, unsigned int pos = 0);

    /**
     * Afficher la grammaire.
     * @param detailed afficher les détails
     * @param stream le flux de sortie
     */
    void print(bool detailed = false, std::ostream& stream = std::cout) const;
};

#endif