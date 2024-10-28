# Éditeur de texte (OMD-TP2)
<img src="resources/readme.png" alt="Description de l'image" width="200"/>

## Description

Ce projet est un éditeur de texte **ascii** basique. Il est décomposé en 2 versions.
- Une première version sur la branche `V1` de ce dépôt.
- Une seconde version améliorant la première version sur la branche `V2` de ce dépôt.

La première version implémente des commandes de base :
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

Finalement, voici un récapitulatif des commandes disponibles :
```
ctrl m : commence / arrête l'écoute des macros
alt m  : joue la macro
ctrl z : revient en arrière
ctrl y : revient en avant
ctrl a : sélectionne tout
shift ← / shift → : sélectionne à gauche / droite
↑ / ↓ : va au début / à la fin
← / → : déplacement à gauche / à droite
ctrl + / ctrl - : zoom / dézoom
```

⚠️ Comme mentionné précedemment, seuls les caractères ascii sont supportés, il se peut de ce fait que tous vos caractères ne soient pas affichés correctement.

## Build et tests

### Windows

Les outils nécessaires sont : 
- MSVC C++ (Visual Studio)
- CMake

#### Pour importer le projet avec la SDL
```
git clone --recurse-submodules -b V1 https://gitlab.istic.univ-rennes1.fr/cejosso/omd-tp2
cd omd-tp2
git checkout V2
git submodule update --init --recursive
```

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