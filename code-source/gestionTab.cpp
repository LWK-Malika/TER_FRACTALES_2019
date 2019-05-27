#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
//#include <vector>
#include <cmath>

#include "gestionTab.h"
#include "rectangle.h"


//pour julia, les coordonnée de la suite choisis:
double Jreel=0;
double Jimag=0;



double modulo(double itinairaire, double occurance){
  return (itinairaire)/800;
 }


double distance(int i, int j, int occ){
  float a = pow((double)(cadre.pixelToRepereX(i)),2);
  float b = pow((double)(cadre.pixelToRepereY(j)),2);
  float c = ((double)((int)(occ%100))/100);
  return (sqrt(a + b)/100 + c);
}


double distance(double i, double j){
  return sqrt(pow(i,2) + pow(j,2));
}

//dessine la fractale par rapport a la couleur définie et le tableau tab
void dessine(){
  glBegin(GL_POINTS); 	//mode affichage de points  
  for(int i=0;i<800;i++){ //double boucle pour parcourir les points etudie
    for(int  j=0;j<800;j++){     
     
      if (tab[i][j]==-1){
	if ( couleur == 3){
   	  
	  glColor3f(0.2+distance(tabC[i][j].getX(),tabC[i][j].getY()),
		    0.1,
		    0.2); 
	}
	else	
	  glColor3f(0, 0, 0);
      }     
      else
	switch(couleur){
	case 0:
	  glColor3f(cos(exp(5*(0.01*tab[i][j]))+4),
		    cos(exp(5*(0.01*tab[i][j]))+2),
		    cos(exp(5*(0.01*tab[i][j]))));
	  break;
	case 1:
	  
	  glColor3f(0.00001*tabOcc[tab[i][j]],
		    1-0.0001*tabOcc[tab[i][j]],
		    0.5-0.00001*tabOcc[tab[i][j]]);
	  break;
	case 2:
	  {
	    glColor3f(0.2 + distance(i, j, tabOcc[tab[i][j]]),
		      distance(i, j, tabOcc[tab[i][j]]),
		      distance(i, j, tabOcc[tab[i][j]]));
	  }
	  
	  break;
	case 3:
	  glColor3f( 0.4+distance(tabC[i][j].getX(),tabC[i][j].getY())/10,
		     0.1,
	  	     0.2);
	  
	  break;
      
	case 974:	  
	  //vert -> bleu -> rouge
	  float tabCouleur[10][3]={
	    {0,1,0}, {0,1,0.85},
	    {0,0.8,1}, {0,0.95,1},
	    {0,0,1}, {0.8,0,1},
	    {1,0,1}, {1,0,0.5},
	    {1,0,0}, {1,0.5,0}};
	  
	  
	  glColor3f(tabCouleur[(tab[i][j]/10)][0] ,
		    tabCouleur[(tab[i][j]/10)][1],
		    tabCouleur[(tab[i][j]/10)][2]  );
	}
      glVertex2f((cadre.getTailleX()/800)*i+cadre.getXmin(),
		 (cadre.getTailleY()/800)*j+cadre.getYmin()); 
    }      
  }
  glEnd(); 		       	// Fermer le polygone
  glFlush(); 
}


//permet de remplir le tableau
void remplirTab(){  
  for (int i=0 ; i<800 ; i++) {
    tab.push_back(std::vector<int>(800));
    for (int j=0 ; j<800 ; j++) {
      if(Fjulia){
	point a((cadre.getTailleX() / 800)
			  * i + cadre.getXmin(),
			  (cadre.getTailleY() / 800)
		* j + cadre.getYmin());

	  
	tab[i][j]=a.julia(Jreel, Jimag);	
      }
      else{     
	tab[i][j]=diverge((cadre.getTailleX() / 800)
			  * i + cadre.getXmin(),
			  (cadre.getTailleY() / 800)
			  * j + cadre.getYmin());
      }
    }
  }
}

void remplirTabDernierPoint(){
  
  for (int i=0 ; i<800 ; i++) {
    tabC.push_back(std::vector<point>(800));
    for (int j=0 ; j<800 ; j++) {
      if (Fjulia){
	point a((cadre.getTailleX() / 800)
		* i + cadre.getXmin(),
		(cadre.getTailleY() / 800)
		* j + cadre.getYmin());
	tabC[i][j]=a.julia2(Jreel,Jimag);
      }
      else{
	
      tabC[i][j]=converge((cadre.getTailleX() / 800) * i + cadre.getXmin(),
				 (cadre.getTailleY() / 800) * j + cadre.getYmin());
      }
    }
  }
}


void completeTab( rectangle aRemplir){  
  for (int i=aRemplir.getXmin() ; i<aRemplir.getXmax() ; i++) { 
    for (int j=aRemplir.getYmin() ; j<aRemplir.getYmax(); j++) {
      if(Fjulia){
	point a((cadre.getTailleX() / 800)
		* i + cadre.getXmin(),
		(cadre.getTailleY() / 800)
		* j + cadre.getYmin());	  
	tab[i][j]=a.julia(Jreel, Jimag);
	tabC[i][j]=a.julia2(Jreel,Jimag);
      }
      else{   
	tab[i][j]=diverge(cadre.pixelToRepereX(i),
			  cadre.pixelToRepereY(j));
	tabC[i][j]=converge((cadre.getTailleX() / 800) * i + cadre.getXmin(),
			    (cadre.getTailleY() / 800) * j + cadre.getYmin());
      }      
    }
  }
}

//permet le deplacement latterale
void newTab(int move, int dir){
  glClear(GL_COLOR_BUFFER_BIT);
  
  //dir de 1 a 4;

  //copie du tableau contenant les rangs de divergences de chaques suite
  std::vector< std::vector<int> > tabcopie(800,std::vector<int>(800,0));

  //copie du tableau spécifique a la couleur T
  std::vector< std::vector<point> > tabCcopie(800,std::vector<point>(800,0));

  
  //suivant la valeur de dir, on ne déplace pas le tableau au meme endroit


  //il n'est pas possible de declarer une variable dans un switch, on les déclare donc avant
  rectangle aRemplir1(0,0,move,800);
  rectangle aRemplir2(800-move,0,800,800);
  rectangle aRemplir3(0,0,800,move);
  rectangle aRemplir4(0,800-move,800,800);


  switch(dir){
  case 1:
    //vers la gauche
    for (int i=move ; i<800 ; i++) {
      for (int j=0 ; j<800 ; j++) {
	tabcopie[i][j]=tab[i-move][j];
	tabCcopie[i][j]=tabC[i-move][j];	
      }
    } 
    tab.swap(tabcopie);
    tabC.swap(tabCcopie);
    completeTab(aRemplir1);
    break;
    
    //droite
  case 2:
    for (int i=0 ; i<800-move ; i++) {
      for (int j=0 ; j<800 ; j++){
	tabcopie[i][j]=tab[i+move][j];
	tabCcopie[i][j]=tabC[i+move][j];;
      }
    }
    tab.swap(tabcopie);
    tabC.swap(tabCcopie);
    completeTab(aRemplir2);
    break;
  case 3:
    for (int i=0 ; i<800; i++) {
      for (int j=move; j<800 ; j++){
	tabcopie[i][j]=tab[i][j-move];
	tabCcopie[i][j]=tabC[i][j-move];
      }
    }
    tab.swap(tabcopie);
    tabC.swap(tabCcopie);
    completeTab(aRemplir3);
    break;
    
  case 4:
    for (int i=0 ; i<800 ; i++) {
      for (int j=0 ; j<800-move ; j++){
	tabcopie[i][j]=tab[i][j+move];
	tabCcopie[i][j]=tabC[i][j+move];				
      }
    }
    tab.swap(tabcopie);
    tabC.swap(tabCcopie);
    completeTab(aRemplir4);
    break;
  }
}


void occuranceDiv(){
  for(int i=0;i<100; i++)
    tabOcc[i]=0;
  
  for(int i=0; i<800; i++)
    for(int j=0; j<800; j++)
      tabOcc[tab[i][j]]++;

}

void Rafraichir(void){
  glClear(GL_COLOR_BUFFER_BIT);	// Effacer la surface graphique
  remplirTab();
  remplirTabDernierPoint();
  //si la couleur utilise le nombre d'occurance pour chaque temps de divergence:
  occuranceDiv();
  dessine();
}




//gere les touche basique du clavier
void clavier(unsigned char key, int x, int y)  // glutKeyboardfuncS(clavier)
{
  printf("Touche : %c = %d \n", key, key);
  // test, permet de savoir quelle touche est tape
  switch (key) 
    {
    case 97: //touche a 
      std::cout << "Colorisation A : sinusoïdale."<<std::endl;
      couleur=0;
      dessine();
      break;

    case 122: //touche z
      std::cout << "Colorisation Z : en fonction du nombre d'occurences pour chaque temps de divergence."<<std::endl;
      couleur=1;
      dessine();
      break;

    case 101: //touche e
      std::cout << "Colorisation E : Couleurs par intervalles"<<std::endl;
      couleur=974;
      dessine();
      break;
   
    case 114: //touche r
      std::cout << "Colorisation R : Modulo" << std::endl;
      couleur = 2;
      dessine();
      break;

    case 116: //touche t
      std::cout << "Colorisation T : Dernier Element" << std::endl;
      couleur = 3;
      dessine();
      break; 
     
    case 13: //touche entrer
      std::cout << "Fractale par defaut"<<std::endl;
      couleur=0;//reinitialise la couleur
      glLoadIdentity(); //reinitialise le repere
      if(Fjulia)
        cadre.resetRepereJulia();
      else
        cadre.resetRepere();
      Rafraichir();
      break;

    case 113:
      std::cout << "Affichage du repere"<<std::endl;
      glBegin(GL_LINES);
      glColor3f(1,1,1);
      glVertex2f(0, 0);
      glVertex2f(0, -1);
      glEnd();
      glFlush();
     
      glBegin(GL_LINES);
      glColor3f(1,1,1);
      glVertex2f(0, 0);
      glVertex2f(1, 0);
      glEnd();
      glFlush();
      break;
  
    case 115:
      std::cout << "Supression du repere"<<std::endl;
      dessine();
      break;

    case 106: //touche j
      Fjulia=!(Fjulia);
      if(Fjulia)
        std::cout << "mode Fractale de julia active, veuiller cliquer sur le repère pour afficher une fractale"<<std::endl;
      else
	{
	  std::cout << "mode Fractale de julia desactive"<<std::endl;
	  if(cadre.repereBaseJ())
	    {
	      glLoadIdentity(); //reinitialise le repere
	      cadre.resetRepere();
	    }
	  Rafraichir();
	}
      break;

    case 105: //TOUCHE INFORMATION I
      std::cout << std::endl<< std::endl
		<< "--- AIDE ---" << std::endl
		<< " > [Touche I]: Affiche l'aide dans le terminal." << std::endl << std::endl

		<< "--- ZOOM ---" << std::endl
		<< " > [Clique Gauche (cliquer-glisser)]: Zoom dans le carre." << std::endl 
		<< " > [Roulette avant]: Zoom avant." << std::endl
		<< " > [Roulette arriere]: Zoom arriere." <<  std::endl
		<< " > [Entree]: Reinitialise la fractale." << std::endl << std::endl

		<< "--- COLORISATION ---" << std::endl
		<< " > [Touche A]: Affiche la couleur predefinie:" << std::endl
		<< "        definie par une sinusoidale amortie " << std::endl
		<< "        une vue d'ensemble de la fractale." << std::endl << std::endl   

		<< " > [Touche Z]: Affiche la couleur definie par:" << std::endl
		<< "        le nombre d'occurence afficher a l'ecran " << std::endl
		<< "        une vue zoome de la fractale." << std::endl << std::endl   

		<< " > [Touche E]: Affiche la couleur definie par" << std::endl
		<< "          intervalle de temps de calculs." << std::endl
		<< "        une vue tres zoome de la fractale." << std::endl << std::endl   

		<< " > [Touche R]: Affiche la couleur definie par" << std::endl     
		<< "        le module par rapport a l'occurence " << std::endl       
		<< "        une vue peu zoome de la fractale." << std::endl << std::endl  

		<< " > [Touche T]: Affiche la couleur definie par" << std::endl
		<< "        le modulo par rapport au dernier element de la suite de chaque point "<<  std::endl
		<< "        tout type de zoom de la fractale." << std::endl << std::endl

		<< "--- REPERE ---" << std::endl     
		<< " > [Touche Q]: Affiche le repere." << std::endl
		<< " > [Touche S]: Enleve le repere." << std::endl << std::endl

		<< "--- FRACTALE DE JULIA ---" << std::endl
		<< " > [touche J]: mode fractale de julia et vice versa " << std::endl
	       
		<< " > [clique droit] si mode fractale de julia active, dessine la fractale de julia par rapport a se point " <<  std::endl
		<< " > les autres fonctionnalité fonctionne avec les fractales de Julia "
		<< std::endl << std::endl;
      break;
    }
}

//fonction qui gère les evenement clavier des touches directionnelle
void touche(int key, int x, int y)
{
  double distMoveX=cadre.distPixToRepX(20);
  double distMoveY=cadre.distPixToRepY(20);
   
  switch(key)
    {
    case GLUT_KEY_DOWN:
      glLoadIdentity(); // Réinitialise le repère
      cadre.setYmax(cadre.getYmax() - distMoveY);
      cadre.setYmin(cadre.getYmin() - distMoveY); 
      gluOrtho2D(cadre.getXmin(), cadre.getXmax(), cadre.getYmax(), cadre.getYmin());
      newTab(20, 4);
      dessine();
      break;
		
    case GLUT_KEY_UP:
      glLoadIdentity(); 
      cadre.setYmax(cadre.getYmax() + distMoveY);
      cadre.setYmin(cadre.getYmin() + distMoveY); 
      gluOrtho2D(cadre.getXmin(), cadre.getXmax(), cadre.getYmax(), cadre.getYmin());
      newTab(20, 3);
      dessine();  
      break;

    case GLUT_KEY_LEFT:
      glLoadIdentity(); 
      cadre.setXmax(cadre.getXmax() - distMoveX);
      cadre.setXmin(cadre.getXmin() - distMoveX); 
      gluOrtho2D(cadre.getXmin(), cadre.getXmax(), cadre.getYmax(), cadre.getYmin());
      newTab(20, 1);
      dessine();       
      break;
  
    case GLUT_KEY_RIGHT:
      glLoadIdentity();
      cadre.setXmax(cadre.getXmax() + distMoveX);
      cadre.setXmin(cadre.getXmin() + distMoveX);
      gluOrtho2D(cadre.getXmin(), cadre.getXmax(), cadre.getYmax(), cadre.getYmin());
      newTab(20, 2);
      dessine();    
      break; 
    }
}

void clique (int button, int state, int x, int y) 
{
  zoomTmp.setXmax(x);
  zoomTmp.setYmax(y);
  zoomTmp.setXmin(x);
  zoomTmp.setYmin(y);

  switch (button) 
    {
    case 4: // Roulette vers le bas
      if (state == GLUT_DOWN) // La roulette est vu comme un bouton,
	{ // on evite donc d'avoir l'evenement "commence roulette" et "finis roulette"
	  cadre.zoomArriere(); // Dezoom	 
	  Rafraichir(); // Callback de la fenetre
	}
      break;
    
    case 3: // Roulette vers le haut
      if (state == GLUT_DOWN) // Zoom
	{ 
	  cadre.zoomAvant();
	  Rafraichir(); // Callback de la fenetre
	}
      break;
    
    case GLUT_LEFT_BUTTON:
      if (state == GLUT_DOWN) 
	{
	  zoom.setXmin(cadre.pixelToRepereX(x));
	  zoom.setYmin(-cadre.pixelToRepereY(y));
	}  
      if (state == GLUT_UP)
	{
	  zoom.setXmax(cadre.pixelToRepereX(x));
	  zoom.setYmax(-cadre.pixelToRepereY(y));

	  if (!((zoom.getXmax()==zoom.getXmin()) &&(zoom.getYmax()==zoom.getYmin())))
	    {
	      zoom.inverse();
	      double temp=(zoom.getXmin()+
			   (abs(zoom.getXmax()-zoom.getXmin())+
			    abs(zoom.getYmax()-zoom.getYmin()))/2);

	      zoom.setYmax(zoom.getYmin()+
			   (abs(zoom.getXmax()-zoom.getXmin())+
			    abs(zoom.getYmax()-zoom.getYmin()))/2);

	      zoom.setXmax(temp);
	      cadre=zoom;    
	      std::cout<<std::endl<<"xmin= "<<cadre.getXmin()<<" xmax= "<<cadre.getXmax()
		       <<" ymin= "<<cadre.getYmin()<<" ymax= "<<cadre.getYmax()<<std::endl<<std::endl;
    
	      glLoadIdentity();
	      gluOrtho2D(cadre.getXmin(), cadre.getXmax(), cadre.getYmax(), cadre.getYmin());
   
	      Rafraichir(); // Callback de la fenetre   
	    }
	}
      break;

    case GLUT_RIGHT_BUTTON:
      // Permet de supprimer quelques trait parasite lors d'un tirer glisser clique droit
      zoom.setXmin(cadre.pixelToRepereX(x));
      zoom.setYmin(-cadre.pixelToRepereY(y));

      
      if(state == GLUT_UP) 
	{
	  if(Fjulia)
	    {
	      Jreel=cadre.pixelToRepereX(x);
	      Jimag=cadre.pixelToRepereY(y);
	      std::cout<< "Jreel : "<<Jreel <<" Jimag: "<< Jimag<<std::endl;
	      if(cadre.repereBaseM())
		{
	          glLoadIdentity(); //reinitialise le repere
	          cadre.resetRepereJulia();
	        }
	      Rafraichir();
	    }     
	}
    }
}

void carre( int x, int y) {

  
  glBegin(GL_POINTS);

  //trait horizontal
  for(int a=std::min((double)x, zoomTmp.getXmax()); a < std::max((double)x, zoomTmp.getXmax()); a++){
    for(int b=zoomTmp.getYmin()-1;b<zoomTmp.getYmin()+1; b++){

      if(((0<=a) && (a<800))&&((0<=b) && (b<800))){
	if (tab[a][b]==-1){
	  if ( couleur == 3){		  
	    glColor3f(0.2+distance(tabC[a][b].getX(),tabC[a][b].getY()),
		      0.1,
		      0.2); 
	  }	
	  else	
	    glColor3f(0, 0, 0);
	}     
	else
	  switch(couleur){
	  case 0:
	    glColor3f(cos(exp(5*(0.01*tab[a][b]))+4),
		      cos(exp(5*(0.01*tab[a][b]))+2),
		      cos(exp(5*(0.01*tab[a][b]))));
	    break;
	  case 1:
	  
	    glColor3f(0.00001*tabOcc[tab[a][b]],
		      1-0.0001*tabOcc[tab[a][b]],
		      0.5-0.00001*tabOcc[tab[a][b]]);
	    break;
	  case 2:
	    {
	      glColor3f(0.2 + distance(a,b, tabOcc[tab[a][b]]),
			distance(a,b, tabOcc[tab[a][b]]),
			distance(a, b, tabOcc[tab[a][b]]));
	    }	  
	    break;
	  case 3:
	    glColor3f( 0.4+distance(tabC[a][b].getX(),tabC[a][b].getY())/10,
		       0.1,
		       0.2);
	    break;     
	  case 974:	  
	    //vert -> bleu -> rouge
	    float tabCouleur[10][3]={
	      {0,1,0}, {0,1,0.85},
	      {0,0.8,1}, {0,0.95,1},
	      {0,0,1}, {0.8,0,1},
	      {1,0,1}, {1,0,0.5},
	      {1,0,0}, {1,0.5,0}};
	    
	    glColor3f(tabCouleur[(tab[a][b]/10)][0] ,
		      tabCouleur[(tab[a][b]/10)][1],
		      tabCouleur[(tab[a][b]/10)][2]  );
	  }
	glVertex2f(cadre.pixelToRepereX(a),-cadre.pixelToRepereY(b));

      }   
    }}


  //trait vertical 
  for(int b=zoomTmp.getXmax()-1;b<zoomTmp.getXmax()+1; b++){
    for(int a=std::min( zoomTmp.getYmin(), zoomTmp.getYmax())-1; a < std::max(zoomTmp.getYmin(), zoomTmp.getYmax())+1; a++){
 
      if(((0<=a) && (a<800))&&((0<=b) && (b<800))){
	if (tab[b][a]==-1){
	  if ( couleur == 3){	  
	    glColor3f(0.2+distance(tabC[b][a].getX(),tabC[b][a].getY()),
		      0.1,
		      0.2); 
	  }	
	  else	
	    glColor3f(0, 0, 0);
	}     
	else
	  switch(couleur){
	  case 0:
	    glColor3f(cos(exp(5*(0.01*tab[b][a]))+4),
		      cos(exp(5*(0.01*tab[b][a]))+2),
		      cos(exp(5*(0.01*tab[b][a]))));
	    break;
	  case 1:
	  
	    glColor3f(0.00001*tabOcc[tab[b][a]],
		      1-0.0001*tabOcc[tab[b][a]],
		      0.5-0.00001*tabOcc[tab[b][a]]);
	    break;
	  case 2:
	    {
	      glColor3f(0.2 + distance(b, a, tabOcc[tab[b][a]]),
			distance(b, a, tabOcc[tab[b][a]]),
			distance(b, a, tabOcc[tab[b][a]]));
	    }	  
	    break;
	  case 3:
	    glColor3f( 0.4+distance(tabC[b][a].getX(),tabC[b][a].getY())/10,
		       0.1,
		       0.2);
	    break;    
	  case 974:	  
	    //vert -> bleu -> rouge
	    float tabCouleur[10][3]={
	      {0,1,0}, {0,1,0.85},
	      {0,0.8,1}, {0,0.95,1},
	      {0,0,1}, {0.8,0,1},
	      {1,0,1}, {1,0,0.5},
	      {1,0,0}, {1,0.5,0}};	    
	    glColor3f(tabCouleur[(tab[b][a]/10)][0] ,
		      tabCouleur[(tab[b][a]/10)][1],
		      tabCouleur[(tab[b][a]/10)][2]  );
	  }
	glVertex2f(cadre.pixelToRepereX(b),-cadre.pixelToRepereY(a));

      }   
    }
  }



   
  //trait vertical.2
  for(int b=zoomTmp.getXmin()-1;b<zoomTmp.getXmin()+1; b++){
    for(int a=std::min((double)y, zoomTmp.getYmax())-1;
	a < std::max((double)y, zoomTmp.getYmax())+1; a++){
      
      if(((0<=a) && (a<800))&&((0<=b) && (b<800))){

	if (tab[b][a]==-1){
	  if ( couleur == 3){
	  	  
	    glColor3f(0.2+distance(tabC[b][a].getX(),tabC[b][a].getY()),
		      0.1,
		      0.2); 
	  }	
	  else	
	    glColor3f(0, 0, 0);
	}
      	else
	  switch(couleur){
	  case 0:
	    glColor3f(cos(exp(5*(0.01*tab[b][a]))+4),
		      cos(exp(5*(0.01*tab[b][a]))+2),
		      cos(exp(5*(0.01*tab[b][a]))));
	    break;
	  case 1:
	  
	    glColor3f(0.00001*tabOcc[tab[b][a]],
		      1-0.0001*tabOcc[tab[b][a]],
		      0.5-0.00001*tabOcc[tab[b][a]]);
	    break;
	  case 2:
	    {
	      glColor3f(0.2 + distance(b, a, tabOcc[tab[b][a]]),
			distance(b,a, tabOcc[tab[b][a]]),
			distance(b,a, tabOcc[tab[b][a]]));
	    }
	  
	    break;
	  case 3:
	    glColor3f( 0.4+distance(tabC[b][a].getX(),tabC[b][a].getY())/10,
		       0.1,
		       0.2);
	    break;      
	  case 974:	  
	    //vert -> bleu -> rouge
	    float tabCouleur[10][3]={
	      {0,1,0}, {0,1,0.85},
	      {0,0.8,1}, {0,0.95,1},
	      {0,0,1}, {0.8,0,1},
	      {1,0,1}, {1,0,0.5},
	      {1,0,0}, {1,0.5,0}};

	    
	    glColor3f(tabCouleur[(tab[b][a]/10)][0] ,
		      tabCouleur[(tab[b][a]/10)][1],
		      tabCouleur[(tab[b][a]/10)][2]  );
	  }


	glVertex2f(cadre.pixelToRepereX(b),-cadre.pixelToRepereY(a));

      }   
    }}
  
  //trait horizontal.2
  for(int a=std::min(zoomTmp.getXmin(), zoomTmp.getXmax())-1;
      a < std::max(zoomTmp.getXmin(), zoomTmp.getXmax())+1; a++){
    for(int b=zoomTmp.getYmax()-1;b<zoomTmp.getYmax()+1; b++){
       
      if(((0<=a) && (a<800))&&((0<=b) && (b<800))){
	if (tab[a][b]==-1){
	  if ( couleur == 3){
	     
	     
	    glColor3f(0.2+distance(tabC[a][b].getX(),tabC[a][b].getY()),
		      0.1,
		      0.2); 
	  }
	
	  else	
	    glColor3f(0, 0, 0);
	}
      
	else
	  switch(couleur){
	  case 0:
	    glColor3f(cos(exp(5*(0.01*tab[a][b]))+4),
		      cos(exp(5*(0.01*tab[a][b]))+2),
		      cos(exp(5*(0.01*tab[a][b]))));
	    break;
	  case 1:
	  
	    glColor3f(0.00001*tabOcc[tab[a][b]],
		      1-0.0001*tabOcc[tab[a][b]],
		      0.5-0.00001*tabOcc[tab[a][b]]);
	    break;
	  case 2:
	    {
	      glColor3f(0.2 + distance(a,b, tabOcc[tab[a][b]]),
			distance(a, b, tabOcc[tab[a][b]]),
			distance(a, b, tabOcc[tab[a][b]]));
	    }
	  
	    break;
	  case 3:
	    glColor3f( 0.4+distance(tabC[a][b].getX(),tabC[a][b].getY())/10,
		       0.1,
		       0.2);
	    break;
      
	  case 974:	  
	    //vert -> bleu -> rouge
	    float tabCouleur[10][3]={
	      {0,1,0}, {0,1,0.85},
	      {0,0.8,1}, {0,0.95,1},
	      {0,0,1}, {0.8,0,1},
	      {1,0,1}, {1,0,0.5},
	      {1,0,0}, {1,0.5,0}};

	    
	    glColor3f(tabCouleur[(tab[a][b]/10)][0] ,
		      tabCouleur[(tab[a][b]/10)][1],
		      tabCouleur[(tab[a][b]/10)][2]  );
	  }

	glVertex2f(cadre.pixelToRepereX(a),-cadre.pixelToRepereY(b));
	  
      }   
    }}
   
  glEnd(); 		       	// Fermer le polygone
  glFlush();

 
  glColor3f(1,1,1);
  //trace la ligne verticale partant du point de depart
  glBegin(GL_LINES);

  
  glVertex2f(zoom.getXmin(),zoom.getYmin());
  glVertex2f(zoom.getXmin(),-cadre.pixelToRepereY(y));

  //ligne horizontale partant du point de depart

  glVertex2f(zoom.getXmin(),zoom.getYmin());
  glVertex2f(cadre.pixelToRepereX(x),zoom.getYmin());
  
  
  //ligne verticale droite
  glVertex2f(cadre.pixelToRepereX(x),zoom.getYmin());
  glVertex2f(cadre.pixelToRepereX(x),-cadre.pixelToRepereY(y));

    
  //ligne horizontale
  glVertex2f(zoom.getXmin(),-cadre.pixelToRepereY(y));
  glVertex2f(cadre.pixelToRepereX(x),-cadre.pixelToRepereY(y));
  
  glEnd(); 		       	// Fermer le polygone
  glFlush();

  zoomTmp.setXmax(x);
  zoomTmp.setYmax(y);

}
