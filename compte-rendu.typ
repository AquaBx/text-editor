
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
  image("resources/V1/cas-utilisation/cas-utilisation.png", width: 7cm),
  caption: [
    Diagramme de cas d'utilisation pour la première version.
  ],
)

_Remarque :_ Nous avons ajouté une fonctionnalité supplémentaire qui est le zoom/dezoom de la fenêtre pour rendre notre éditeur plus confortable pour l'utilisateur.

#pagebreak()
== Description des cas d'utilisation

Voici la description de chaque cas d'utilisation. Nous ne détaillerons pas les acteurs puisque nous pensons qu'il n'y a qu'un acteur qui est l'utilisateur de l'application.

#set text(8.49pt)
#table(
  columns: (78pt, 170pt, auto, auto),
  inset: 3pt,
  
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
    3. La zone de texte est mise à jour.
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
  ],

  [Zoomer/dézoomer la fenêtre], [
    1. L'utilisateur sélectionne appuie sur Ctrl+ ou Ctrl-.
    2. Le zoom de la fenêtre est mis à jour.
    3. L'affichage de la fenêtre est mis à jour.
  ], [
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
  image("resources/V1/design-pattern/design-pattern.png", height: 5cm),
  caption: [
    Design Pattern Command
  ],
)

Cette structure est très générale. Nous devons l'adapter à notre problème. Pour ce faire, nous avons du comprendre la structure ci-dessus. Une fois cela fait, nous avons pu la customiser pour produire notre propre diagramme de classes modélisant notre problème. Voici comment nous l'avons adapté :

#figure(
  image("resources/V1/diagramme-classes/diagramme-classes.png"),
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

La classe Client sera le point d'entrée pour l'application car elle gèrera la boucle principale de l'éditeur, surveillera les événements, et interagira avec l'éditeur de texte pour lui demander d'exécuter des actions spécifiques.

Le Renderer s'occupera de l'affichage visuel (texte, curseur et redimensionnement de la fenêtre) grâce à la bibliothèque SDL. Il utilisera la classe Texture pour gérer les surfaces et textures SDL.

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
  image("resources/V1/diagramme-sequence/diagramme-sequence-couper/diagramme-sequence-couper.png"),
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
  image("resources/V1/diagramme-sequence/diagramme-sequence-ecrire/diagramme-sequence-ecrire.png"),
  caption: [
    Diagramme de séquence pour entrer du texte
  ],
)

#pagebreak()
== Implémentation du code

Conformément aux consignes et aux diagrammes que nous avons pu établir, nous avons réalisé la première version de l'éditeur de texte. Vous pourrez la trouver dans la branche nommée "V1" du dépôt Gitlab. Nous avons également réalisé des tests pour s'assurer du bon fonctionnement de l'éditeur de texte.

#pagebreak()
= Version 2

Dans la seconde version, les fonctionnalités ajoutées par rapport à la première version sont les suivantes :
- enregistrement des actions de l'utilisateur (ctrl s)
- annulation de la dernière action de l'utilisateur (ctrl z)
- réajout de la dernière annulée action de l'utilisateur (ctrl y)
- écoute/arrêt de l'écoute des actions de l’utilisateur (ctrl m)
- rééxécution de la combinaison d'actions de l'utilisateur (alt m)

#pagebreak()
== Diagramme des cas d'utilisation

Au vu des fonctionnalités supplémentaires que doit proposer la seconde version de l'éditeur de texte, voici un diagramme de cas d'utilisation envisageable. A noter que le diagramme d'utilisation de la première version vient s'y ajouter. Nous avons ajouté les nouveaux cas d'utilisation en bleu :

#figure(
  image("resources/V2/cas-utilisation/cas-utilisation.png", width: 7cm),
  caption: [
    Diagramme de cas d'utilisation pour la seconde version.
  ],
)

#pagebreak()
== Description des cas d'utilisation

Voici la description de chaque cas d'utilisation. A noter que la description des cas d'utilisation de la première version vient s'y ajouter. Nous avons ajouté les nouvelles description de cas d'utilisation en bleu :

#set text(7.25pt)
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
  ],

  [Zoomer/dézoomer la fenêtre], [
    1. L'utilisateur sélectionne appuie sur Ctrl+ ou Ctrl-.
    2. Le zoom de la fenêtre est mis à jour.
    3. L'affichage de la fenêtre est mis à jour.
  ], [
  ], [
  ],

  [#text(blue)[Refaire les actions]], [
    #text(blue)[
      1. L'utilisateur active la fonction de réexécution (Ctrl+Y).
      2. Le système réapplique l'action précédemment annulée.
    ]
    ], [
    #text(blue)[
    ]
    ], [
    #text(blue)[
      1. Aucune action à refaire : ne rien faire, nous sommes revenus à l'état final. 
    ]
    ],

  [#text(blue)[Défaire les actions]], [
    #text(blue)[
      1. L'utilisateur active la fonction d'annulation (Ctrl+Z).
      2. Le système revient à l'état précédent l'action la plus récente.
      3. Le fichier de script est mis à jour (ajout de la fonction d'annulation)
    ]
    ], [
    #text(blue)[
    ]
    ], [
    #text(blue)[
      1. Il n'y a plus d'actions à annuler : ne rien faire, nous sommes rendus à l'état initial.
    ]
    ],

  [#text(blue)[Réexécuter les actions]], [
    #text(blue)[
      1. L'utilisateur appuie sur Alt+M.
      2. Le système exécute de manière séquentielle les actions enregistrées dans l'historique de la macro.
    ]
    ], [
    #text(blue)[
    ]
    ], [
    #text(blue)[
      1. Aucune action dans l'historique : aucune action n'est exécutée.
    ]
    ],

  [#text(blue)[Ecouter les actions]], [
    #text(blue)[
      1. L'utilisateur appuie sur Ctrl+M pour démarrer l'écoute.
      2. Toutes les actions de l'utilisateur sont enregistrées dans l'historique de la macro jusqu'à ce que l'écoute soit arrêtée.
    ]
    ], [
    #text(blue)[
        1. L'écoute démarre automatiquement en vidant l'historique précédent.
    ]
    ], [
    #text(blue)[
    ]
    ],

  [#text(blue)[Arrêter l'écoute des actions]], [
    #text(blue)[
      1. L'utilisateur appuie de nouveau sur Ctrl+M.
      2. L'écoute s'arrête et les actions de l'utilisateur ne sont plus enregistrées.
    ]
    ], [
    #text(blue)[
    ]
    ], [
    #text(blue)[
    ]
    ],

)

_Remarque:_ A noter que si l'utilisateur défait (ctrl z) puis écrit du texte, alors la file des actions à refaire (ctrl y) est vidée.

#set text(11pt)

#pagebreak()
== Diagramme de classes

Dans cette seconde version du mini-éditeur de texte, nous avons repris la structure de la première version tout en l’enrichissant pour intégrer les nouvelles fonctionnalités demandées. 

Voici les principales nouveautés :
- Nous avons introduit les classes `UndoCommand` et `RedoCommand`, qui permettent de revenir en arrière ou d’avancer dans l’historique des actions. Elles utilisent des snapshots (classe `Snapshot`) pour sauvegarder les états du texte et de la sélection pour chaque action effectuée par l'utilisateur.
- Pour gérer l'état d'enregistrement des actions de l’utilisateur, nous avons introduit un champ `macroRecord` dans la classe `TextEditor`, ainsi qu'un vecteur `macroHistory` qui stocke l’historique des macros est stocké pour pouvoir rejouer les macros ultérieurement. De plus, elle possède une référence à la commande en cours (pointeur de Command) pour déléguer les actions à une commande via la méthode executeCommand().

Pour ce faire, nous avons conservé la structure de base de la première version, c'est-à-dire le design pattern Command. Nous l'avons simplement étendu pour intégrer les commandes `Undo` et `Redo`. Cependant, nous y avons également incorporé le design pattern Memento pour stocker l’état du texte et des sélections pour permettre de pouvoir défaire/refaire comme demandé. Ce dernier est représenté par la classe `Snapshot`.

Voici le diagramme de classes en conséquence.

#figure(
  image("resources/V2/diagramme-classes/diagramme-classes.png", height:12cm),
  caption: [
    Diagramme de classe basé sur le Design Pattern Command pour la Version 2
  ],
)

#pagebreak()
== Diagramme de séquence

Pour bien comprendre commment vont se produire les interactions avec les classes lors de l'utilisation de l'application, nous avons produit trois diagrammes de séquences.

=== Faire/défaire

Voici un scénario que nous avons inventé pour modéliser les actions de faire/défaire : 

#figure(
  image("resources/V2/diagramme-sequence/diagramme-sequence-faire_defaire/diagramme-sequence-faire_defaire.png"),
  caption: [
    Diagramme de séquence pour faire et défaire les actions
  ],
)

#pagebreak()
=== Réxectuter les actions

Voici un scénario que nous avons inventé pour modéliser l'action de réxecution des actions : 

#figure(
  image("resources/V2/diagramme-sequence/diagramme-sequence-reexecution/diagramme-sequence-reexecution.png"),
  caption: [
    Diagramme de séquence pour réxécuter les actions
  ],
)

#pagebreak()
=== Ecouter/Arrêter l'écoute

Voici un scénario que nous avons inventé pour modéliser les actions d'écoute/arrêt de l'écoute : 

#figure(
  image("resources/V2/diagramme-sequence/diagramme-sequence-reexecution/diagramme-sequence-reexecution.png"),
  caption: [
    Diagramme de séquence pour écouter/arrêter l'écoute des actions
  ],
)

#pagebreak()
== Implémentation du code

Conformément aux consignes et aux diagrammes que nous avons pu établir, nous avons réalisé la seconde version de l'éditeur de texte. Vous pourrez la trouver dans la branche nommée "V2" du dépôt Gitlab.

#pagebreak()
= Conclusion

Pour conclure, ce projet d'éditeur de texte nous a permis de comprendre l'importance de concevoir un code dès la version initiale en prévision des évolutions futures, afin de garantir qu'il soit maintenable.

Grâce à cette approche en spirale, nous avons avoir un code factorisé et optimisé dès le début, mais facilitant tout de même les ajustements. Finalement, elle permet l’amélioration continue tout en conservant une version finale plus stable et robuste.
