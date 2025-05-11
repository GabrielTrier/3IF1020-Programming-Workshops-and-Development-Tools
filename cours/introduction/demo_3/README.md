
### Cursus CentraleSupélec - Dominante Informatique et numérique
### 3IF1020 - Concepts des langages de programmation - Chapitre n°1
### Dominique Marcadet - 2022-23 - CC BY-SA

---

## Fichiers dans ce répertoire :
- [A.hpp](A.hpp), [B.hpp](B.hpp), [C.hpp](C.hpp), [C.cpp](C.cpp) : 
trois modules. Les modules `A` et `B` n'ont que leur fichier d'entête, `B` utilise `A`. 
`C` utilise `A` aussi pour son fichier d'entête, et utilise `B` pour son fichier d'implémentation.

## Démonstrations
### Problème de l'inclusion multiple
1. Compilation du module `C` :
```shell
c++ -c C.cpp
```
&nbsp;&nbsp;Une erreur de redéfinition du type `A` est signalée. 

2. Correction avec la technique standard : dans le fichier [A.hpp](A.hpp), décommenter les 
lignes
```cpp
//#ifndef A_HPP
//#define A_HPP
```
&nbsp;&nbsp;et 
```cpp
//#endif
```
&nbsp;&nbsp;puis vérifier que l'erreur de compilation a disparue. 

3. Correction avec le pragma : remettre en commentaires les lignes précédemment 
décommentées et décommenter la ligne
```cpp
//#pragma once
```
&nbsp;&nbsp;puis vérifier que l'erreur de compilation a aussi disparue. 
