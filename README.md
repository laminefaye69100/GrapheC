README - TP Noté

Ce TP a été réalisé par Malick Sow et Amadou Lamine Faye, ensemble du début à la fin. Nous nous sommes réunis à trois reprises, chaque réunion durant environ 5 heures, pour travailler intensément sur le projet. En complément, nous avons également travaillé en ligne via Discord, ce qui nous a permis d'avancer efficacement sur les fonctionnalités et de résoudre les problèmes rencontrés.

Instructions pour la compilation et l'exécution
Étapes pour compiler et exécuter le programme :

    Pour compiler le programme :
    make

    Pour exécuter le programme :
    make run

    Pour nettoyer les fichiers temporaires (.o, .d) :
    make clean


Fichiers concernés :

    Les fichiers .o (fichiers objets) sont générés lors de la compilation.
    Les fichiers .d (dépendances) sont créés pour suivre les modifications des fichiers source.

Fonctionnalités implémentées avec succès

    Chargement d'images au format PGM :
        Notre programme peut charger des images en niveaux de gris depuis un fichier PGM.

    Calcul des distances :
        Nous avons implémenté l'algorithme de Dijkstra pour calculer l'image des distances à partir des pixels noirs.

    Sauvegarde des distances et des prédécesseurs :
        Les distances calculées peuvent être sauvegardées dans un fichier PGM.
        Les prédécesseurs des pixels sont sauvegardés dans un fichier texte pour analyser les chemins optimaux.

    Affichage des images et des distances :
        Les graphes (images ou distances) peuvent être affichés directement dans la console pour une visualisation rapide.

    Projection de pixels :
        Notre programme trouve le pixel noir le plus proche à partir d'un pixel donné.

    Fusion de graphes (union de formes) :
        Nous avons réussi à implémenter l'union de deux graphes en prenant les distances minimales des pixels correspondants.

    Projection d’un point sur l’union des deux formes :
        Une fonctionnalité avancée a été ajoutée pour projeter un point sur l’union de deux formes, sans réexécuter l’algorithme de Dijkstra. Cette projection s’appuie sur les distances déjà calculées.

Fonctionnalité spéciale : Projection sur l'union des deux formes

Cette fonctionnalité représente un défi technique que nous avons surmonté avec succès. Voici comment elle fonctionne :

    Elle prend deux formes, pour lesquelles les distances et prédécesseurs ont été préalablement calculés.
    Elle projette un point donné sur l’union des deux formes en comparant uniquement les distances calculées, évitant ainsi de réexécuter l’algorithme de Dijkstra.

Cela nous a permis de répondre pleinement aux exigences du sujet, tout en optimisant le temps de calcul.

Pour générer la documentation :

    Assurez-vous que Doxygen est installé :

sudo apt install doxygen graphviz

Exécutez Doxygen dans le répertoire contenant le fichier Doxyfile :

    doxygen Doxyfile

    Une fois la documentation générée :
        Ouvrez le fichier docs/html/index.html dans un navigateur pour consulter la documentation HTML.
        Si activé, vous pouvez également compiler la version PDF via LaTeX en naviguant dans le dossier docs/latex.

Importance pour le projet :

    Clarté : Les commentaires Doxygen permettent de comprendre rapidement le rôle de chaque composant.
    Maintenance : Facilite l'ajout ou la modification de fonctionnalités grâce à une documentation centralisée.
    Collaboration : Utile pour les membres de l'équipe ou d'autres développeurs qui veulent contribuer au projet.


Organisation du travail

Nous avons travaillé ensemble sur ce projet, en adoptant une méthodologie efficace :

    Réunions en présentiel : Nous nous sommes réunis à trois reprises, pour une durée de 5 heures par session, ce qui nous a permis de structurer le travail et de résoudre les problèmes complexes.
    Travail en ligne via Discord : En complément des réunions, nous avons collaboré en ligne pour avancer sur le code, partager des idées et tester les fonctionnalités.

Cette combinaison de travail en présentiel et en ligne nous a permis de progresser rapidement et de produire un programme fonctionnel et robuste.
Notes finales

Ce projet a été pour nous une excellente opportunité de mettre en pratique nos compétences et d'apprendre à collaborer efficacement sur un projet technique. Nous avons mis tout notre sérieux et nos efforts pour répondre aux exigences du sujet.

Si vous rencontrez des problèmes pour tester le programme, n'hésitez pas à consulter ce fichier.

Merci pour votre correction et bonne évaluation !