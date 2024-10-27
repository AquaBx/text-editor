# Éditeur de texte (OMD-TP2)
![resources/readme.png](img.png)
## Description

Ce projet est un éditeur de texte **ascii** basique, implémentant des commandes de base :
- déplacement (flèches directionnelles)
- sélection (shift + flèches directionnelles)
- copier (ctrl c)
- couper (ctrl x)
- coller (ctrl v)
- zoom / dézoom (ctrl + / ctrl -)

La version 2 obtient ces ajouts:
- annulation de la dernière action de l'utilisateur (ctrl z)
- réajout de la dernière annulée action de l'utilisateur (ctrl y)
- écoute des actions de l’utilisateur (ctrl m)
- arrêt de l'écoute des actions de l’utilisateur (ctrl m)
- rééxécution de la combinaison d'actions de l'utilisateur (alt m)

⚠️ Comme mentionné précedemment, seuls les caractères ascii sont supportés, il se peut de ce fait que tous vos caractères ne soient pas affichés correctement.

## Build et tests

### Windows

Les outils nécessaires sont : 
- MSVC C++ (Visual Studio)
- CMake

#### Pour génerer le projet
```
cmake -S . -B ./build
```

#### Pour build
```
cd ./build
cmake --build .
```

#### Pour lancer les tests
```
cd ./build
ctest build -C Debug --output-on-failure
```

### Linux

Pas supporté :(

### macOS

Pas supporté :(