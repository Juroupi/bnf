# BNF

 ## Compilation

Pour générer toutes les cibles :

```bash
make
```

Dépendances :

- La bibliothèque [GMP](https://gmplib.org/) pour gérer les grands nombres.

## Fichiers générés

- `bnf` : un programme qui permet de tester toutes les fonctionnalités du projet en ligne de commande.
- `bnf.o` : la bibliothèque compilée du projet avec toutes les fonctionnalités.
- `cbnf.so` : une bibliothèque dynamique qui permet au binding Python de fonctionner.
- `tests` : un exécutable qui contient les tests unitaires et qui peut être exécuté avec `make test`.
- `doc.md` : la documentation du projet (a besoin de `mdoc`).

