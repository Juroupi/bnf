# BNF

 ## Compilation

Pour générer toutes les cibles :

```bash
make
```

Dépendances :

- La bibliothèque [GMP](https://gmplib.org/) (la version C++) pour gérer les grands nombres.

## Fichiers générés

- `bnf` : un programme qui permet de tester toutes les fonctionnalités du projet en ligne de commande.
- `bnf.o` : la bibliothèque compilée du projet avec toutes les fonctionnalités.
- `cbnf.so` : une bibliothèque dynamique qui permet au binding Python de fonctionner.
- `tests` : un exécutable qui contient les tests unitaires et qui peut être exécuté avec `make test`.
- `doc.md` : la documentation du projet (a besoin de `mdoc`).

## Exemple

```c++
Grammar g("data/fibo.bnf");
NonTerminal& nt = g["F"];
nt.getCardinality(2); // = 3
nt.getElements(2);    // = { "aa", "ab", "ba" }
```

## Binding Python

Un petit binding Python se trouve dans `python/` et est accompagné d'un test qui peut être exécuté avec `make test_python`.