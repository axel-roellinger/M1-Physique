# TP 1

L'objet principal de ce TP est d'étudier deux méthodes d'intégration : l'intégration de Riemann et l'algorithme de convergence de Richardson.

Pour ce faire, 3 exercices ont été prévus :

1. Vases communicants (exercice d'entraînement pour les graphes)

On utilise 3 vases, contenant chacun une quantité d'eau prédéfinie. À chaque cycle, on transfère une fraction alpha du contenu
du vase A vers le vase B, puis une fraction du contenu du vase B vers le vase C, et enfin une fraction du contenu du vase C vers le vase A.
Ensuite, on étudie si la somme du contenu des vases est constante, et comment elle évolue. L'opération est répétée N fois. 

L'objectif de l'exercice est d'étudier l'impact de deux paramètres : le nombre de cycles N et la fraction alpha, ainsi que les quantités contenues dans les vases.

J'ai donc créé 4 tableaux, un pour chaque vase, avec un nombre de lignes correspondant au nombre de cycles N voulus,
et 10 colonnes, correspondant chacune à une valeur de alpha (entre 0 et 1).

Pour remplir ces tableaux, j'ai créé une fonction "vases". Cette fonction est insérée dans une boucle itérative, allant de 0 à N-1 (donc N cycles), permettant alors d'opérer un cycle de transfert à la fois.
Cependant, pour rendre la fonction plus pratique, il serait préférable d'insérer cette boucle itérative dans la fonction "vases".
Pour ce qui est du reste des arguments de la fonction, on retrouvera les tableaux associés aux vases, ainsi que 3 variables permettant d'exploiter les valeurs contenues dans les tableaux au rang précédent.
Cependant, ces trois derniers arguments sont inutiles, étant que ces variables ne jouent aucun rôle. Utiliser directement les valeurs du tableau serait plus logique.

J'ai inclus une ligne supplémentaire dans le tableau comportant les valeurs d'alpha (étant donné que chaque colonne correspond à N cycles régis par un alpha donné)
Ceci nous permet d'employer cette valeur pour la légende des graphes à venir pour afficher l'évolution des valeurs contenues dans les vases ainsi que la somme du contenus
des vases.

Nous obtenons donc pour chaque vase ainsi que pour la somme du contenu des vases:

alpha_initial | alpha_initial + 0.05 (modifiable) |.....| alpha_final 
--------------|-----------------------------------|-----|------------
   Valeur 1   |              Valeur 1             |.....|  Valeur 1
    .....     |               .....               |.....|   .....
   Valeur N   |              Valeur N             |.....|  Valeur N
   
Un script gnuplot est ensuite employé en fin de programme pour afficher 4 graphes : un par vase ainsi qu'un pour la somme du contenu des vases

2. Intégration de Riemann

L'intégration de Riemann est considérée comme telle :

Soit f(x) une fonction que l'on souhaite intégrer. L'intégration, d'un point de vue géométrique, correspond au calcul de l'aire entre l'axe des abscisses, la fonction f(x) 
et les bornes d'intégration. 
Une approximation possible est de scinder l'aire concernée en une multitude de rectangles. Un peu à la manière de l'anti-aliasing dans un jeu vidéo : on approxime n'importe quelle courbe pas un escalier, plus ou moins raffiné.
La formule employée pour décrire l'algorithme est la suivante :

 



