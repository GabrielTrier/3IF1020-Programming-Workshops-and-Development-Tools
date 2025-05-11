
### Cursus CentraleSupélec - Dominante Informatique et numérique
### 3IF1020 - Concepts des langages de programmation - Chapitre n°1
### Dominique Marcadet - 2022-23 - CC BY-SA

---

## Fichiers dans ce répertoire :
- [Hello.hpp](Hello.hpp) : Fichier d'entête du module `Hello`, il déclare le service offert pas ce module.
- [Hello.cpp](Hello.cpp) : Fichier d'implémentation du module `Hello`, il définit le service offert pas ce module.
- [CallHello.cpp](Hello.cpp) : Programme principal utilisant le module `Hello`.

## Démonstrations
### Création de l'exécutable en une seule étape
1. Exécution sur les 2 fichiers source du préprocesseur, puis du compilateur, enfin de l'éditeur de liens ; 
Les fichiers intermédiaires ne sont pas conservés, l'option `-o` permet de fixer le nom de 
l'exécutable :
```shell
c++ -o CallHello CallHello.cpp Hello.cpp
```

2. L'exécutable nommé `CallHello` a été créé, il est visible dans le répertoire courant, il peut 
être exécuté ainsi :
```shell
./CallHello
```

3. Si une erreur est détectée par le compilateur, l'étape d'édition de liens n'est pas effectuée ; 
par exemple, supprimer l'exécutable actuel : 
```shell
rm CallHello
```
&nbsp;&nbsp;modifier temporairement dans le fichier 
[Hello.cpp](Hello.cpp) la ligne 
```cpp
#include "Hello.hpp"
```
&nbsp;&nbsp;par
```cpp
#include "Hello.hpp1"
```
&nbsp;&nbsp;et relancer la commande ci-dessus. 
L'erreur est affichée, et l'exécutable n'est pas créé. Annuler la modification faite.

### Séparation de l'étape de l'édition de liens
1. Exécution sur les 2 fichiers source du préprocesseur, puis du compilateur ; l'option `-c` indique de 
ne pas faire l'étape d'édition de liens, donc les fichiers objets résultant de la compilation, 
`CallHello.o` et `Hello.o` sont conservés et présents dans le répertoire :
```shell
c++ -c CallHello.cpp Hello.cpp
```
&nbsp;&nbsp;Il est possible de le faire en 2 étapes, 
une pour chaque fichier.

2. Exécution sur les 2 fichiers objets de l'éditeur de liens :
```shell
c++ -o CallHello CallHello.o Hello.o
```

### Observation du résultat du préprocesseur
1. L'option `-E` permet de n'exécuter que l'étape du préprocesseur, le résultat s'affiche sur la sortie 
standard :
```shell
c++ -E Hello.cpp
```
&nbsp;&nbsp;On voit tout à la fin le contenu du 
fichier [Hello.cpp](Hello.cpp) sans les commentaires et où la ligne 
```cpp
#include "Hello.hpp"
```
&nbsp;&nbsp;a été remplacée par le contenu de ce fichier :
```cpp
void hello();
```
