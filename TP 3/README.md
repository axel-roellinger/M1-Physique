# TP 3

L'objectif de ce 3è TP est d'employer la méthode von Neumann/Ulam pour calculer l'intégrale d'une fonction.

Tput d'abord, il faut déterminer le maximum de la fonction, pour définir un rectangle de dimension h x L.
Ici, L représente la longueur de l'intervalle d'intégration et h le maximum de la fonction.

La prochaine étape est de générer N coordonnées (x, y) de manière aléatoire, qui sont dans l'intervalle d'intégration. 
On distingue alors deux jeux de points : N[good], qui se trouvent à l'intérieur de la courbe à intégrer, et N[bad], qui se
trouve en dehors.

On peut alors approximer l'intervalle par cette formule :

<p align="center">
  <img src="https://user-images.githubusercontent.com/73199800/121447788-b2faf280-c996-11eb-915d-c48af04ce945.png">
</p>

Cette fonction correspond alors à la fraction de l'aire du rectangle qui se confond avec l'aire sous la courbe à intégrer.

La fonction à intégrer est la suivante :

<p align="center">
  <img src="https://user-images.githubusercontent.com/73199800/121448065-34528500-c997-11eb-88ed-37d601802403.png">
</p>

La première étape fut donc de déterminer le maximum de cette fonction. Pour se faire, j'ai employé une boucle for, qui sonde toutes les ordonnées de la fonction 
(donc, les points y =  f(x)), et qui remplace la valeur d'un double appelé <em>max</em>, qui a pour valeur ce maximum.

L'intervalle d'intégration quant à lui va de 0 à 2\*pi inclus. On obtient donc un rectangle de dimension 2\*pi\*max.

L'étape suivante est de générer aléatoirement N coordonnées de points, afin de calculer l'intégrale.

Pour cela, j'ai implémenté une fonction rdm(double N), et j'ai exploité le twister de Mersenne. J'ai utilisé une distribution
uniforme réelle, qui me renvoie un double compris entre 0 et la valeur N. 
Pour chaque point généré, j'utilise donc la fonction rdm avec comme argument 2\*pi en x, et le maximum de la fonction en y. Chaque point est ensuite stocké dans un 
tableau de dimension 2\*N.

Pour distinguer les bons points des mauvais, j'ai créé une fonction de tri, qui balaye un array 2D contenant l'ensemble des
points générés. Dans un couple (x,y), si y est inférieur à f(x), alors le point est considéré comme valide.

Ensuite, l'objectif est de comparer cette méthode de calcul à l'intégration de Riemann, et de l'étudier pour différentes 
fonctions données. Un tableau récapitulatif est disponible à la page 10 du document <a href="https://github.com/axel-roellinger/M1-Physique/blob/main/Rapport%20TP%201%20%C3%A0%203.pdf">Rapport TP 1 à 3.pdf</a>*

Concernant la complexité de cette méthode de calcul, elle est linéaire vis-à-vis du nombre de points aléatoires à calculer. 
Pour l'occupation en mémoire, le point qui serait à optimiser serait de ne pas recueillir tous les points aléatoires dans un tableau, mais d'étudier directement 
la condition (y < f(x)) pour un couple, ce qui permet de s'affranchir du stockage mémoire du tableau de taille 2\*N, qui s'avère inutile.
