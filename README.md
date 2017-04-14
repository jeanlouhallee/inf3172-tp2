# Travail pratique 2

## Description

Conception d'un shell.

Dans le cadre du cours Système d'exploitation (INF3172).

Université du Québec à Montréal, hiver 2017.

## Auteurs

Étienne Bergeron (BERE08089101)

Jean-Lou Hallée (HALJ05129309)

## Fonctionnement

Le shell offre l'invite de commande `tsh>` pour indiquer qu'il est prêt à recevoir une nouvelle tâche.

Le shell supporte directement 3 commandes : `cd`, `cdir` et `exit`.

Pour tout autre commande, l'executable doit se trouver dans le répertoire `~/inf3172/bin`.

## Contenu du projet

* tsh.c : Fichier source du Turbo-Shell.
* new.c : Fichier source de l'executable new.
* newdir.c : Fichier source de l'executable newdir.
* list.c : Fichier source de l'executable list.
* rmall.c : Fichier source de l'executable rmall.
* size.c : Fichier source de l'executable size.
* fin.c : Fichier source de l'executable fin.
* Makefile : Fichier générant la compilation à l'aide de la commande "make" et nettoyage des fichiers non désirés à l'aide de la commande "make clean".
* README.md : Fichier décrivant la totalité du projet.

## Références

* [Jacques Berger - Atelier sur la mise en place d'un shell](https://github.com/jacquesberger/exemplesINF3172/blob/master/ateliers/shell/enonce.md) : Laboratoire du cours.

## Statut

Projet complété : aucun bogue reconnu pour l'instant.