# TP 2

L'objet principal de ce TP est d'étudier deux méthodes d'intégration : la règle trapézoïdale et la méthode de Simpson.

2 exercices sont prévus à cet effet : 

1. La règle trapézoïdale

Deux fonctions à intégrer nous sont données : 

<p align="center">
  <img src="https://user-images.githubusercontent.com/73199800/121445255-64972500-c991-11eb-8323-2957289a519a.png">
</p>

La règle trapézoïdale peut être comprise comme une variation de l'intégration de Riemann : au lieu de se baser sur une multitude de rectangles, le polygone employé est un trapèze. L'intervalle d'intégration [a,b] est toujours subdivisé en N intervalles de longueur h = (b-a)/N.

La formule à implémenter est la suivante : 

<p align="center">
  <img src="https://user-images.githubusercontent.com/73199800/121445874-9e1c6000-c992-11eb-807f-bd4da7a45e4f.png">
</p>

La somme s'arrête à N-1, car on emploierait alors le point x[N+1] = b+h, qui est hors de notre intervalle d'intégration.
Pour faciliter mes calculs, j'ai donc implémenté une fonction intitulée <em>trapez_solver</em>, qui prend en argument un pointeur vers une fonction à intégrer, les bornes d'intégration a et b, ainsi que N, le nombre d'intervalles d'intégration.

Le coeur de la fonction consiste en une boucle for, permettant d'implémenter la somme décrite ci-dessus. La fonction renvoie alors un double.
En utilisant une boucle for englobant la fonction <em>trapez_solver</em>, j'ai pu remplir un fichier avec les erreurs numériques entre la valeur analytique et le résultat de la fonction, selon la taille de l'échantillonnage N. 

Cette étude m'a permis de déterminer que l'erreur pour la fonction f(x) décroît de manière linéaire en fonction de N.
Cependant, aucun pattern n'est reconnaissable pour la fonction g(x), possiblement dû à sa nature trigonométrique, mais je n'ai pas vérifié cette hypothèse. On observe cependant que cet algorithme est fiable pour un grand nombre de pas d'intégration, notamment pour les polynomes.

<p align="center">
  <img src="https://user-images.githubusercontent.com/73199800/121446583-1b94a000-c994-11eb-895c-6fb37bd46a2b.png">
  <br/>Ce graphe représente l'évolution de l'erreur en fonction de la valeur de h, qui dépend directement de N.
</p>

Concernant la complexité temporelle de cette méthode, cette dernière est linéaire. En effet, elle ne dépend que de la taille de l'échantillon initial.
L'occupation mémoire quant à elle est réduite : pour chaque intégration, 3 entiers sont requis (N, a et b), un float (h), et un double (résultat de la somme). L'usage d'un double est motivé par le fait qu'une intégration nécessitant l'usage de valeurs importantes soit possible.

2. Méthode de Simpson

Cette méthode est basée sur l'idée qu'une fonction donnée f(x) peut être approximée par un polynome P(x), plus simpel à intégrer. Le schéma numérique est le suivant : 

<p align="center">
  <img src="https://user-images.githubusercontent.com/73199800/121446808-ad9ca880-c994-11eb-8cfa-6d67fbb87358.png">
</p>

On explicite donc l'intégrale par une série de sommes, en distinguant les valeurs de x[i] avec i pair et i impair.
Pour implémenter cette méthode, j'ai créé une fonction intitulée <em>Simpson_solver</em> qui prend en argument un pointeur vers la fonction à intégrer, les bornes d'intégration ainsi que le nombre de subdivisions N. h a la même valeur que précédemment.

Le coeur de la fonction est une boucle for, avec une condition if à chaque tour de boucle vis-à-vis de la parité de i. Cela permet d'obtenir deux sommes partielles, qui sont additionnées à f(a) et f(b) pour former la valeur de retour. 
Pour étudier l'erreur, le procédé est le même que précédemment.

L'erreur croît avec le nombre de subdivisions, mais reste extrêmement faible, et permet de constituer un résultat fiable.

<p align="center">
  <img src="https://user-images.githubusercontent.com/73199800/121447282-a9bd5600-c995-11eb-807a-0364792fb7b4.png">
  <br/>Ce graphe représente l'évolution de l'erreur en fonction de la valeur de h. On observe une erreur croissante, mais faible.
</p>

Je n'ai pas d'explication pour la croissance de l'erreur, qui pourrait être liée à un empilement d'erreurs de calcul, ou bien à la méthode elle-même.

L'occupation mémoire de cette fonction est plus importante que précédemment, car elle nécessite non pas un mais deux doubles pour stocker les sommes liées aux i pairs et i impairs.

La complexité temporelle est linéaire également, car elle dépend uniquement de N.
