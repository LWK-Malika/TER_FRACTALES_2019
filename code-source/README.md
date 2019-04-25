
		------ Visualisation et Exploration de l'ensemble de Mandelbrot ------

Groupe du Projet de Programmation :
- Alexandre Canton Condes
- Malika Lin-Wee-Kuan
- Ambre Lamouchi
- Melvin Bardin

Pour compiler en ligne de commande, un Makefile est fourni.
Nous vous proposons notre commande : 

clear && make && ./main

(Le makefile supprime les fichier.o pour plus de clarté dans le dossier)

Lors de l'execution du programme, deux fenetre s'ouvre :
- l'une pour l'affichage des suites de Mandelbrot, 
- l'autre pour l'affichage de l'ensemble de Mandelbrot et les fractales de Julia.


		MANUEL D'UTILISATION DU PROGRAMME :


		1) Utilisation de la fenêtre de Mandelbrot / Julia

> [Touche I]: Affiche l'aide dans le terminal." << std::endl << std::endl

		--- ZOOM ---
> [Clique Gauche (cliquer-glisser)]: Zoom dans le carre. << std::endl 
> [Roulette avant]: Zoom avant.
> [Roulette arriere]: Zoom arriere.
> [Entree]: Reinitialise la fractale.

		--- COLORISATION ---
> [Touche A]: Affiche la couleur predefinie:
	          Definie par une sinusoidale amortie 
	          une vue d'ensemble de la fractale.

> [Touche Z]: Affiche la couleur definie par:
		        le nombre d'occurence afficher a l'ecran
		        une vue zoome de la fractale.

> [Touche E]: Affiche la couleur definie par
		        intervalle de couleurs.
		        une vue tres zoome de la fractale.

> [Touche R]: Affiche la couleur definie par
		        le module par rapport a l'occurence 
		        une vue peu zoome de la fractale.

> [Touche T]: Affiche la couleur definie par
		        le modulo par rapport au dernier element de la suite de chaque point
		        tout type de zoom de la fractale.

		--- REPERE ---
> [Touche Q]: Affiche le repere.
> [Touche S]: Enleve le repere.

		--- FRACTALE DE JULIA ---
> [Touche J]: Mode fractale de Julia et vice versa.
	       
> [Clique droit]: Si mode fractale de Julia active : dessine la fractale de Julia par rapport à se point. 
> Les autres fonctionnalité fonctionne avec les fractales de Julia.


		2) Utilisation de la fenêtre de l'animation des suites de Mandelbrot

> [Touche I]: Affiche l'aide dans le terminal.
> [Clique Gauche]: Affiche la suite.
> [Clique Droit]: Efface, puis affiche la suite.
> [Entrée]: Efface.
> [Touche Q]: Affiche des suites prédéfinies.
		
		
		
		RAPPEL : 
Lorsque le programme est en cours d'execution, à tout moment il est possible de consulter l'aide en appuyant sur la touche "I" pour la fenêtre concernée.
