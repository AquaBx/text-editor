
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
= Intro
faire (max 5 lignes)

= V1

Dans la première version, les fonctionnalités présentes sont :
- La sélection du texte
- L'écriture de texte
- L'effacement du texte
- Le déplacement du curseur
- La copie de la sélection (sauvegardée dans le presse-papier)
- Le coupage de la sélection (sauvegardée dans le presse-papier)
- Le collage de la sélection qui fut au préalable stockée dans le presse-papier. Il y a deux cas possibles selon si la sélection en cours est vide ou non :
  - Si vide : cette fonctionnalité insère le contenu du presse-papier à l'endroit où le curseur se situe. présent dans le presse-papier
  - Si non vide : cette fonctionnalité remplace la sélection en cours par le contenu

== Diagramme de cas d'utilisation

Au vu des fonctionnalités que doit proposer la première version de l'éditeur de texte, voici un diagramme de cas d'utilisation envisageable :

#figure(
  image("../V1/conception/cas-utilisation/usecase.png", width: 7cm),
  caption: [
    Diagramme de cas d'utilisation V1
  ],
)

== Diagramme de classe 

Au vu du problème que nous avons à modéliser, après avoir consulté le #link("https://refactoring.guru/design-patterns/catalog")[catalogue] des design pattern présent sur #link("https://refactoring.guru/")[Refactoring GURU], nous avons décidé de nous baser sur le design pattern nommé #link("https://refactoring.guru/design-patterns/command")[Command].

Ce design pattern est de type comportemental, c'est-à-dire qu'ils concernent les algorithmes et l'attribution des responsabilités entre les objets. Plus précisément, le design-pattern Command permet de transformer une requête en un objet qui contient toutes les informations relatives à la requête. Cette transformation est utile car elle permet de transmettre des requêtes en tant qu'arguments de méthode, de retarder ou de mettre en file d'attente l'exécution d'une requête et de prendre en charge des opérations annulables. C'est exactement le type de structure que l'on recherche pour notre mini-éditeur.

Voici la structure exposée par ce design pattern : 

#figure(
  image("../V1/conception/design-pattern/command.png"),
  caption: [
    Diagramme de cas d'utilisation V1
  ],
)

Cette structure est très générale. Nous devons l'adapter à notre problème. Pour ce faire, nous devons comprendre la structure ci-dessus. Une fois cela fait, nous pourrons la customiser pour produire notre diagramme de classe.

Dans le cas de notre problème, nous avons :
- ...

== Diagramme de séquence

pour bien voir commment ça marche avec les interactions avec les classes


=== Couper la sélection



=== Entrer du texte


= V2

== Diagramme de cas d'utilisation

== Design pattern

https://refactoring.guru/design-patterns
https://refactoring.guru/design-patterns/catalog

https://refactoring.guru/design-patterns/memento

== Diagramme de classe 

= Conclusion
faire (max 10 lignes)
