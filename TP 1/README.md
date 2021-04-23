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

| alpha_initial  |        alpha_initial + 0.05         |  ...  |  alpha_final |
|:--------------:|:-----------------------------------:|:-----:|:------------:|
|    Valeur 1    |              Valeur 1               |  ...  |   Valeur 1   |
|       ...      |               ...                   |  ...  |      ...     |
|    Valeur N    |              Valeur N               |  ...  |   Valeur N   |
   
Un script gnuplot est ensuite employé en fin de programme pour afficher 4 graphes : un par vase ainsi qu'un pour la somme du contenu des vases

2. Intégration de Riemann

L'intégration de Riemann est considérée comme telle :

Soit f(x) une fonction que l'on souhaite intégrer. L'intégration, d'un point de vue géométrique, correspond au calcul de l'aire entre l'axe des abscisses, la fonction f(x) 
et les bornes d'intégration. 
Une approximation possible est de scinder l'aire concernée en une multitude de rectangles. Un peu à la manière de l'anti-aliasing dans un jeu vidéo : on approxime une courbe ou une pente par un escalier, plus ou moins détaillé.

La formule employée pour décrire l'algorithme est la suivante :
<p align=center>
   <img src ="https://github.com/axel-roellinger/M1-Physique/blob/main/Images/integrale-riemann.svg">
</p>

Ici h représente la largeur de notre rectangle. Ceci nous sert donc de pas d'intégration, qui sera la valeur déterminante quant à la précision de notre valeur.
h est déterminée comme étant : (borne finale - borne initiale)/ nombre d'itérations.

Pour clarifier le calcul, on peut sortir h de la somme par factorisation de tous les termes selon h et multiplier uniquement la somme finale par ce pas.

L'implémentation se fait via une boucle itérative, dans laquelle on invoque une fonction fx avec comme argument un double, qui représente notre f(a + i x h).

Pour ce qui est de la complexité temporelle : 
   - implémenter cette formule revenant à créer une boucle itérative comportant une somme sur une variable
   - on observe alors une linéarité dans le nombre d'opérations requises (un pas = une itération)
   - la complexité est donc O(N), avec N le nombre de pas

Concernant l'emplacement mémoire, cette méthode nécessite N\*32 bits au minimum en cas d'utilisation de floats pour stocker les résultats, jusqu'à N\*64 bits en cas d'utilisation de doubles.

3. Convergence accélérée de Richardson

Cet algorithme s'inscrit dans la continuité du travail sur l'intégration de Riemann. Son principe est le suivant : On exploite l'algorithme d'intégration de Riemann pour 4 pas différents. Le premier pas est défini comme h/(2^0) = h. Le pas suivant est égal à h/2, le prochain à h/4 et le dernier à h/8. Ces 4 valeurs d'intégrales sont compilées dans un tableau de taille 4 x 4.
De là, une formule est à appliquer pour remplir les éléments suivants du tableau, suivant une diagonale :

|      <!-- -->      |       <!---->        |       <!---->        |       <!---->        |
|--------------------|----------------------|----------------------|----------------------|
| Riemann pour h = h | Riemann pour h = h/2 | Riemann pour h = h/4 | Riemann pour h = h/8 |
|      Valeur 1      |       Valeur 2       |       Valeur 3       |         Vide         |
|      Valeur 4      |       Valeur 5       |         Vide         |         Vide         |
|      Valeur 6      |        Vide          |         Vide         |         Vide         |

Les valeurs intitulées "valeur [1-6]" sont obtenues à l'aide de la formule suivante : 
<p align="center">
<img src="https://user-images.githubusercontent.com/73199800/115788797-677b8d80-a3c4-11eb-8287-5efb27f34c7c.png">
</p>

L'indice j correspond à la ligne du tableau, et l'indice k la colonne. on voit ainsi que chaque bloc du tableau est obtenu en utilisant le bloc au-dessus de lui de coordonnées [j][k], ainsi que celui au-dessus dans la colonne à côté, de coordonnées [j][k+1].

Il faut tout de même noter que la valeur j = 1 n'est pas permise, ou le dénominateur vaudra 0. De ce fait, il faut considérer un offset de 1 lors de l'utilisation de cette formule. À ce moment-là, on désignera la ligne au-dessus de la ligne de calcul par j-1.

La valeur 6, dernière valeur calculée par l'algorithme, représente la valeur finale de l'intégrale issue de ce calcul. L'objectif a donc été de comparer la précision de l'intégration de Riemann et celle de cet algorithme, pour déterminer si le gain de temps est profitable ou non.

Pour cela, j'ai analysé les résultats contenus dans la table en étudiant l'erreur entre chaque valeur de cette dernière et la valeur réelle de l'intégrale. J'en suis parvenu à la conclusion qu'il était rarement nécessaire de calculer les valeurs au-delà de la 2è ligne pour obtenir une erreur plus faible que 0.1%.

Également, en supposant l'intervalle d'intégration égal à [0,25], et un nombre de subdivisions initial de subdivisions h = 100 pour exploiter l'algorithme de convergence, mes résultats ont montré qu'il fallait une intégrale Riemannienne comprenant environ 160000 subdivisions pour obtenir un taux de précision de 0.1%. Or, considérant h, il aura fallu 4 intégrales riemanniennes de 100, 200, 400 et 800 subdivisions, pour obtenir le même taux de précision (les calculs suivant étant négligeables en terme d'espace mémoire) à l'aide de l'algorithme de Richardson. On peut donc en conclure que celui-ci est une alternative plus qu'intéressante à l'intégrale de Riemann, tant en terme de mémoire que de temps de calcul.
