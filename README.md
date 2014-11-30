Quadricopter
============

A project I am working on for my university.

## To do (logs from 2013-2014's project)
1. Intégrer les gyroscopes, de manière à calculer la déviation angulaire. Pour ça, il faut faire le zéro avant le décollage (±15dps d'erreur absolue).  On intègre les 16 bits, le bruit sera moyenné par l'intégration.

2. Accéléromètre : Quand l'intégration du gyroscope indique l'horizontale, (elle est forcément un peu fausse au bout d'un moment à cause du zéro pas parfait- ceci devrait être fait avant le décollage pour partir avec une intégration qui ne dérive pas : l'assiette doit rester nulle) on corrige le résultat de celle-ci avec le moyennage de l'assiette sur 10s au lieu de corriger directement par l'assiette. (il faut ajouter un offset à l'intégration des Gyro pour stopper la dérive ; ceci peut se tester facilement en position arrêtée).

3. Filtrage des données : on active aucun filtrage puisqu'on le fait après pour l'assiette et par intégration pour la position des gyros. A voir si on peut passer à 800Hz pour le gyro et 1k pour l'accéléromètre?

4. Syncronisation sur les capteurs : le faire sur le gyro. (pour l'accéléromètre, on se contente d'intégrer donc peu importe la date des échantillons) Ça se fait avec le CTRL_REG3 : bit 3 I2_DRDY qui génère IT sur INT2 quand l'échantillon est prêt.

5. Correction de position XY : GPS avec calcul différentiel donne précision très bonne toutes les secondes ? => A utiliser pour corriger l'intégration de l'acceléromêtre sur axes XY sur le même principe que la position angulaire