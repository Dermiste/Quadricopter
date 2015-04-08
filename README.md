Quadricopter
============

## Cartes
Contient les schémas et empruntes de la carte mère (celle qui se trouve directement au dessus du Coldfire) ainsi que des 4 cartes mezzanines:
- le gyroscope                LG4200D
- l'accéléromètre             LIS331DLH
- l'accéléromètre + boussole  LMS303D
- le capteur de pression      LPS25h

## Controleur
Les sources du projet phonegap permettant de réaliser une télécommande sur smartphone/tablette

## Datasheet
Les datasheet de tous les capteurs utilisés + certains .pdf qui se sont avérés utiles

## Scilab Scripts
Tout le nécessaire pour pouvoir recevoir des données depuis la liaison série et ensuite les afficher dans un graph
À noter que l'installation d'une extension est nécessaire pour pouvoir faire fonctionner le script, disponible ici:
https://atoms.scilab.org/toolboxes/serialport


## Sources
Le code C utilisé dans le quadcopter.
Pour travailler sur un nouveau fichier basé sur l'existant, copier et renommer Sandbox.c qui contient le minimum vital (lecture capteur + filtrage) puis ajouter dans le makefile le nom du fichier dans la variable PGMs de la manière indiquée dans le commentaire juste au dessus. Noter que le makefile utilise un memory.x pour répartir certaines librairies entre la ROM et la RAM, d'ou les deux .s19 en sortie. Le "rom" est à uploader avec la sonde et ne change normalement pas (un seul upload donc, mais véto sur le "ne change pas") et le "ram" est à uploader avec dBug via un terminal.



