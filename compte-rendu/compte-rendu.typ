
#let title = "TP2"
#let course_id = "OMD-S7"
#let instructor = "FEUILLATRE Hélène"
#let due_time = "A rendre pour le 28/10/2024"
#set enum(numbering: "a)")

#let prob(body) = {
  block(fill:rgb(250, 255, 250),
   width: 100%,
   inset:8pt,
   radius: 4pt,
   stroke:rgb(31, 199, 31),
   body)
  }

#let to-string(content) = {
  if content.has("text") {
    content.text
  } else if content.has("children") {
    content.children.map(to-string).join("")
  } else if content.has("body") {
    to-string(content.body)
  } else if content == [ ] {
    " "
  }
}

// Initiate the document title, author...
#let assignment_class(title, course_id, professor_name, due_time, body) = {
  set document(title: title)
  set heading(numbering: "1.")
  set page(
    paper:"us-letter", 
    header: locate( 
        loc => if (
            counter(page).at(loc).first()==1) { none } 
        else if (counter(page).at(loc).first()==2) { align(right, 
              [*#course_id: #title*  ]
            ) }
        else { 
          align(right, 
            [*#course_id: #title* ]
          ) 
        }
    ),
    footer: locate(
      loc => {
        if counter(page).at(loc).first() != 1 {
          let page_number = counter(page).at(loc).first()-1
          let total_pages = counter(page).final(loc).last()-1
          align(center)[#page_number/#total_pages]
        }
      }
    )
  )

  align(center, [
    #grid(
      columns: (30%,30%)
  )])
  block(height:25%,fill:none)
  align(center, text(25pt)[
    *#course_id: #title*])
  align(center, text(20pt)[
    #due_time])
  align(center, text(15pt)[_Responsable: #professor_name _])
  block(height:35%,fill:none)
  
  pagebreak(weak: false)

  body
}

#show: assignment_class.with(title, course_id, instructor, due_time)
#set par(justify: true)

#import "@preview/codelst:2.0.0": sourcecode
#import "@preview/algo:0.3.3": algo, i, d, comment, code

#import "@preview/ctheorems:1.1.2": *
#show: thmrules.with(qed-symbol: $square$)
#let theorem = thmbox("theorem", "Théorème", fill: rgb("#EEEEEE"))

#show raw.where(block: false): box.with(
  fill: luma(240),
  inset: (x: 3pt, y: 0pt),
  outset: (y: 3pt),
  radius: 2pt,
)

#show raw.where(block: true): block.with(
  fill: luma(240),
  inset: 10pt,
  radius: 4pt,
) 

#outline(
  title: [Sommaire],
  indent: auto,
  depth: 3,
)
#show link: underline

#pagebreak()
= Introduction
Ce deuxième travail pratique consiste à concevoir un mini-éditeur de texte. Tout comme pour le premier travail, il débutera par la création des différents diagrammes, mais contrairement à lui, ce projet est plus complet avec deux versions à réaliser et l'implémentation du code. Pour commencer, nous allons analyser différents design patterns et en choisir un qui correspond le mieux à notre problème. Une fois ce design pattern adapté à notre problématique, nous implémenterons la première version. Ensuite, nous ajusterons notre architecture pour intégrer les fonctionnalités supplémentaires de la seconde version, que nous implémenterons à son tour.

#pagebreak()
= Version 1

Dans la première version, les fonctionnalités présentes sont :
- La sélection du texte
- L'écriture de texte
- L'effacement du texte
- Le déplacement du curseur
- La copie de la sélection (sauvegardée dans le presse-papier)
- Le coupage de la sélection (sauvegardée dans le presse-papier)
- Le collage de la sélection qui fut au préalable stockée dans le presse-papier.

== Diagramme de cas d'utilisation

Au vu des fonctionnalités que doit proposer la première version de l'éditeur de texte, voici un diagramme de cas d'utilisation envisageable :

#figure(
  image("../V1/conception/cas-utilisation/usecase.png", width: 7cm),
  caption: [
    Diagramme de cas d'utilisation pour la première version.
  ],
)

#pagebreak()
== Description des cas d'utilisation

Voici la description de chaque cas d'utilisation. Nous ne détaillerons pas les acteurs puisque nous pensons qu'il n'y a qu'un acteur qui est l'utilisateur de l'application.

#set text(8.49pt)
#table(
  columns: (78pt, 170pt, auto, auto),
  inset: 3pt,
  
  // Headers
  [*Cas \d'utilisation*], [*Scénario nominal*], [*Scénario alternatif*], [*Scénario exception*],

  [Déplacer le curseur], [
    1. L'utilisateur appuie sur les touches directionnelles.
      - gauche/droite pour aller à gauche/droite
      - bas/haut pour aller à début/à la fin
    2. Le curseur se déplace
    3. Sa nouvelle position est affichée.
  ], [
  ], [
    1. La position cible du curseur est invalide (en dehors du texte) : le curseur s'arrête à la limite valide.
  ],

  [Entrer du texte], [
    1. L'utilisateur saisit des caractères.
    2. Les caractères sont ajoutés à la position du curseur
    3. La zone de texte est mise à jour.
  ], [
    1. Le texte est ajouté à une sélection existante : remplace la sélection.
  ], [
    1. Caractère non autorisé (caractères spéciaux) : remplacement par dièse
  ],

  [Effacer du texte], [
    1. L'utilisateur appuie sur la touche "Supprimer" ou "Backspace".
    2. Le caractère ou le texte sélectionné est supprimé
    3. a zone de texte est mise à jour.
  ], [
    1. Aucun texte à supprimer (curseur au début du texte).
  ], [
    
  ],

  [Sélectionner du texte], [
    1. L'utilisateur utilise Shift + touches directionnelles. (gauche/droite : selectionne à gauche/droite)
    2. La portion du texte souhaitée est sélectionnée.
  ], [
    1. L'utilisateur peut sélectionner tout le texte avec Ctrl + A
  ], [
    1. Tentative de sélectionner au-delà des limites du texte : sélection seulement jusqu'aux limites autorisées
  ],

  [Copier la sélection], [
    1. L'utilisateur sélectionne du texte.
    2. L'utilisateur appuie sur Ctrl+C.
  ], [
    1. Aucun texte sélectionné : vide le presse-papier et rien n'est copié.
  ], [
    1. Le presse-papier est plein.
  ],

  [Coller la sélection], [
    1. L'utilisateur positionne le curseur à l'endroit souhaité.
    2. L'utilisateur appuie sur Ctrl+V.
    3. Le contenu du presse-papier est inséré à la position du curseur.
  ], [
    1. Le contenu du presse-papier est ajouté à une sélection existante : remplace la sélection.
  ], [
    1. Le presse-papier est vide : rien ne se passe
  ],

  [Couper la sélection], [
    1. L'utilisateur sélectionne du texte.
    2. L'utilisateur appuie sur Ctrl+X.
    3. Le texte est supprimé de la zone de texte et copié dans le presse-papier.
  ], [
    1. Aucun texte sélectionné : vide le presse-papier et rien n'est copié.
  ], [
  ]
)

#set text(11pt)

#pagebreak()
== Diagramme de classe 

Au vu du problème que nous avons à modéliser, après avoir consulté le #link("https://refactoring.guru/design-patterns/catalog")[catalogue] des design pattern présent sur #link("https://refactoring.guru/")[Refactoring GURU], nous avons décidé de nous baser sur le design pattern nommé #link("https://refactoring.guru/design-patterns/command")[Command]. 

Ce design pattern est de type comportemental, c'est-à-dire qu'ils concernent les algorithmes et l'attribution des responsabilités entre les objets. Plus précisément, le design-pattern Command permet de transformer une requête en un objet qui contient toutes les informations relatives à la requête. Cette transformation est utile car elle encapsule chaque action sous forme d'objet, ce qui permet au client de les transmettre en tant qu'arguments de méthode, de les retarder, de les mettre en file d'attente ou bien de les prendre en charge des opérations annulables. C'est exactement le type de structure que l'on recherche pour notre mini-éditeur.

Voici la structure exposée par ce design pattern : 

#figure(
  image("../V1/conception/design-pattern/command.png", height: 6cm),
  caption: [
    Design Pattern Command
  ],
)

Cette structure est très générale. Nous devons l'adapter à notre problème. Pour ce faire, nous avons du comprendre la structure ci-dessus. Une fois cela fait, nous avons pu la customiser pour produire notre propre diagramme de classes modélisant notre problème. Voici comment nous l'avons adapté :

#figure(
  image("../V1/conception/diagramme-classes/class.png"),
  caption: [
    Diagramme de classe basé sur le Design Pattern Command pour la Version 1
  ],
)

Comme vous pouvez le constater, nous avons repris la même structure que le Design Pattern Command, adapté au langage de programmation choisi. Nous avons choisi C++ qui nous semblait être un bon choix étant donné que nous pouvons utiliser la SDL.

Chaque action spécifique de l'éditeur sera modélisée sous forme de classes dérivées de la classe abstraite Command. Cette abstraction nous permettra de nous assurer que toutes les commandes disposent d'une méthode execute() qui est appelée par l'éditeur lorsque l'utilisateur effectue une action.

Chacune de ces classes dérivées encapsulera des détails spécifiques à une commande particulière. Par exemple, la classe CopyCommand contiendra des attributs pour indiquer la portion de texte à copier. Elles seront créées avec un lien vers l'éditeur de texte (TextEditor&), pour pouvoir manipuler directement le contenu du buffer de texte, de la position du curseur, ou du presse-papier.

La classe TextEditor sera le centre de l'application et maintiendra l'état du texte et de gérer les interactions de l'utilisateur. Elle contiendra :
- Un buffer de texte (textBuffer)
- Un presse-papier (clipboard)
- La position du curseur (position)
- La sélection de texte (selectionStart, selectionEnd)
- Une référence à la commande en cours (pointeur de Command) pour déléguer les actions à une commande via la méthode executeCommand().

La classe Client sera point d'entrée pour l'application car elle gèrera la boucle principale de l'éditeur, surveillera les événements, et interagira avec l'éditeur de texte pour lui demander d'exécuter des actions spécifiques.

Le Renderer s'occupera de l'affichage visuel (texte, curseur et redimensionnement de la fenêtre) grâce à la bibliothèque SDL. Il utilisera la classe Texture pour gérer les surfaces et textures SDL.

Nous avons également choisi de définir les classes de commande comme amies de TextEditor pour qu'elles puissent accéder directement aux données privées de l'éditeur. Cela permettra également d'améliorer la sécurité et évitera d'exposer des méthodes publiques qui pourraient être mal utilisées ailleurs dans le code.

#pagebreak()
== Diagrammes de séquence

Pour bien comprendre commment vont se produire les interactions avec les classes lors de l'utilisation de l'application, nous avons produit deux diagrammes de séquences.

=== Couper la sélection

Le cas d'utilisation "Couper la sélection" a été décrit ainsi dans la partie précédente :
- Scénario nominal :
  - 1. L'utilisateur sélectionne du texte.
  - 2. L'utilisateur appuie sur Ctrl+X.
  - 3. Le texte est supprimé de la zone de texte et copié dans le presse-papier.
- Scénarios alternatifs :
  - 1. Aucun texte sélectionné : vide le presse-papier et rien n'est copié.

Un diagramme de séquence correspondant pourrait être illustré comme suit :

#figure(
  image("../V1/conception/diagramme-sequence/sequence-couper/couper.png", width:10cm),
  caption: [
    Diagramme de séquence pour couper la sélection
  ],
)
#pagebreak()
=== Entrer du texte

Le cas d'utilisation "Entrer du texte" a été décrit ainsi dans la partie précédente :
- Scénario nominal :
  - 1. L'utilisateur saisit des caractères.
  - 2. Les caractères sont ajoutés à la position du curseur
  - 3. La zone de texte est mise à jour.
- Scénarios alternatifs :
  - 1. Caractère non autorisé (caractères spéciaux) : remplacement par dièse
- Scénarios d'exception :
  - 1. Le texte est ajouté à une sélection existante : remplace la sélection.

Un diagramme de séquence correspondant pourrait être illustré comme suit :

#figure(
  image("../V1/conception/diagramme-sequence/sequence-ecrire/ecrire.png", width:10cm),
  caption: [
    Diagramme de séquence pour entrer du texte
  ],
)

#pagebreak()
== Implémentation du code

Conformément aux consignes et aux diagrammes que nous avons pu établir, nous avons réalisé la première version de l'éditeur de texte. Vous pourrez le trouver #highlight("dire où")

#highlight("il faudra pas non plus oublier de séparer les deux versions et de revoir les diagrammes si besoin -> surtout le diagramme des classes")


#pagebreak()
= Version 2

Dans la seconde version, les fonctionnalités ajoutées par rapport à la première version sont les suivantes :
- L'enregistrement des actions de l'utilisateur pour pouvoir les rejouer, par exemple dans un script
- L'enregitrement de ses actions
- L'annulation possiblité d'annuler de ses actions

#pagebreak()
== Diagramme de cas d'utilisation

#pagebreak()
== Description des cas d'utilisation

#highlight("ceux de base + les autres")

#pagebreak()
== Diagramme de classe 

#pagebreak()
== Diagramme de séquence


#pagebreak()
== Implémentation du code


= Conclusion
faire (max 10 lignes)
il fallait bien penser dès la v1 à la v2 pour avoir un code maintenable

https://refactoring.guru/design-patterns
https://refactoring.guru/design-patterns/catalog

https://refactoring.guru/design-patterns/memento
