#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
//#include <vector>
#include <cmath>

#include "gestionTab.h"
#include "rectangle.h"

double gestionTab::modulo(double itinairaire, double occurance){
  return (itinairaire)/800;
 }


double gestionTab::distance(int i, int j, int occ){
  // return ((pow((float)(pixelToRepereX(i)),2) +pow((float)(pixelToRepereY(j)),2) + ((float)((int)(occ%100))/100) ));
  float a = pow((double)(cadre.pixelToRepereX(i)),2);
  float b = pow((double)(cadre.pixelToRepereY(j)),2);
  float c = ((double)((int)(occ%100))/100);
  return (sqrt(a + b)/100 + c);
}


double gestionTab::distance(double i, double j){
  return sqrt(pow(i,2) + pow(j,2));
}


void gestionTab::dessine(){

  if(couleur==2)
	remplirTabDernierPoint();
  
    
  glBegin(GL_POINTS); 	//mode affichage de points  
  for(int i=0;i<800;i++){ //double boucle pour parcourir les points étudié
    for(int  j=0;j<800;j++){     
     
      if (tab[i][j]==-1){
	if (couleur==2){
	  
	  
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
	case 974:	  
	  //vert -> bleu -> rouge
	  float tabCouleur[10][3]={
	    {0,1,0}, {0,1,0.85},
	    {0,0.8,1}, {0,0.95,1},
	    {0,0,1}, {0.8,0,1},
	    {1,0,1}, {1,0,0.5},
	    {1,0,0}, {1,0.5,0}};
	    
	  //rouge ->vert->bleu
	  // float tabCouleur[10][3]={{1,0,0}, {1,0.5,0},
	  // 			     {1,1,0}, {0.5,1,0},
	  // 			     {0,1,0}, {0,1,0.5},
	  // 			     {0,1,1}, {0,0.5,1},
	  // 			     {0,0,1}, {1,0,1}};
	    
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


void gestionTab::remplirTab(){
  for (int i=0 ; i<800 ; i++) {
    tab.push_back(std::vector<int>(800));
    for (int j=0 ; j<800 ; j++) {
      tab[i][j]=point::diverge((cadre.getTailleX() / 800)
			       * i + cadre.getXmin(),
			       (cadre.getTailleY() / 800)
			       * j + cadre.getYmin()); 
    }
  }
}

void gestionTab::remplirTabDernierPoint(){
  for (int i=0 ; i<800 ; i++) {
    tabC.push_back(std::vector<point>(800));
    for (int j=0 ; j<800 ; j++) {
      tabC[i][j]=point::converge((cadre.getTailleX() / 800) * i + cadre.getXmin(),
				 (cadre.getTailleY() / 800) * j + cadre.getYmin()); 
    }
  }
}


void gestionTab::completeTab( rectangle aRemplir){
  for (int i=aRemplir.getXmin() ; i<aRemplir.getXmax() ; i++) {  
    for (int j=aRemplir.getYmin() ; j<aRemplir.getYmax(); j++) {
      tab[i][j]=point::diverge(cadre.pixelToRepereX(i),
			       cadre.pixelToRepereY(j));
    }
  }
}

void gestionTab::newTab(int move, int dir){
  //dir de 1 a 4;
  std::vector< std::vector<int> > tabcopie(800,std::vector<int>(800,0));

  //suivant la valeur de dir, on ne complète pas le tableau au meme endroit.


  //il n'est pas possible de déclarer une variable dans un switch
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
      }
    } 
    tab.swap(tabcopie);
    completeTab(aRemplir1);
    break;
    
    //droite
  case 2:
    for (int i=0 ; i<800-move ; i++) {
      for (int j=0 ; j<800 ; j++){
	tabcopie[i][j]=tab[i+move][j]; 
      }
    }
    tab.swap(tabcopie);
    completeTab(aRemplir2);
    break;
  case 3:
    for (int i=0 ; i<800; i++) {
      for (int j=move; j<800 ; j++){
	tabcopie[i][j]=tab[i][j-move];
      }
    }
    tab.swap(tabcopie);
    completeTab(aRemplir3);
    break;
    
  case 4:
    for (int i=0 ; i<800 ; i++) {
      for (int j=0 ; j<800-move ; j++){
	tabcopie[i][j]=tab[i][j+move]; 
      }
    }
    tab.swap(tabcopie);
     completeTab(aRemplir4);
    break;
  }
}


void gestionTab::occuranceDiv(){
  for(int i=0;i<100; i++)
    tabOcc[i]=0;

  
  for(int i=0; i<800; i++)
    for(int j=0; j<800; j++)
      tabOcc[tab[i][j]]++;

  }

void gestionTab::Rafraichir(void){
  glClear(GL_COLOR_BUFFER_BIT);	// Effacer la surface graphique
   remplirTab();

    //si la couleur utilise le nombre d'occurance pour chaque temps de divergence:
  occuranceDiv();

   dessine();
}




//gere les touche basique du clavier
void gestionTab::clavier(unsigned char key, int x, int y)  // glutKeyboardfuncS(clavier)
{
  printf("Touche : %c = %d \n", key, key);
  // test, permet de savoir quelle touche est tapé
   switch (key) {
   case 97: //touche a 
 
     std::cout << "couleur par défaut"<<std::endl;
      couleur=0;
      dessine();
      break;
   case 122: //touche z
     
     std::cout << "couleur en fonction du nombre d'occurence pour chaque temps de divergence."<<std::endl;
     couleur=1;
     dessine();
     break;

   case 101: //touche e
     std::cout << "Couleurs par intervalles"<<std::endl;
     couleur=974;
     dessine();
     break;
   
   case 114: //touche a
     std::cout << "Couleur test" << std::endl;
     couleur = 2;
     dessine();
     break; 
     
   case 13: //touche entrer
     std::cout << "Fractale par défaut"<<std::endl;
     couleur=0;//réinitialise la couleur
     glLoadIdentity(); //réinitialise le repère
     //cadre.reinitialise();
     //gluOrtho2D( xmin=-2.15,xmax=0.55, ymax=1.3,ymin=-1.3);//zoom du repère
     cadre.resetRepere();
  
     Rafraichir();
     break;
   case 113:
     std::cout << "Affichage du repère"<<std::endl;

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
     std::cout << "Supression du repère"<<std::endl;
     dessine();
     break;
     //ajout ici des autre evenement du clavier
   }
}



void gestionTab::touche(int key, int x, int y){
  /*  cout<<"xmin = "<< xmin
      <<"xmax = "<< xmax
      <<"ymin = "<< ymin
      <<"ymax = "<< ymax<<endl<<endl;*/
  
  printf("Touche spécial: %c = %d \n", key, key);

  double distMoveX=cadre.distPixToRepX(20);
  
 double distMoveY=cadre.distPixToRepY(20);

 
 std::cout<<"distmoveX = "<<distMoveX<<" distmoveY = "<<distMoveY<<std::endl;
  switch(key){
  case GLUT_KEY_DOWN :
    
    glLoadIdentity(); //réinitialise le repère

    cadre.setYmax(cadre.getYmax()-distMoveY);
    cadre.setYmin(cadre.getYmin()-distMoveY); 
    gluOrtho2D(cadre.getXmin(), cadre.getXmax(), cadre.getYmax(),cadre.getYmin());
    //gluOrtho2D( xmin,xmax,ymax=ymax-distMoveY,ymin=ymin-distMoveY);
    newTab(20,4);
    dessine();
    break;
		
  case GLUT_KEY_UP :
    glLoadIdentity(); //réinitialise le repère

        cadre.setYmax(cadre.getYmax()+distMoveY);
    cadre.setYmin(cadre.getYmin()+distMoveY); 
    gluOrtho2D(cadre.getXmin(), cadre.getXmax(), cadre.getYmax(),cadre.getYmin());
    // gluOrtho2D( xmin,xmax,ymax=ymax+distMoveY,ymin=ymin+distMoveY);
    newTab(20,3);
    dessine();  
    break;

    
  case GLUT_KEY_LEFT :

    glLoadIdentity(); //réinitialise le repère

      cadre.setXmax(cadre.getXmax()-distMoveX);
    cadre.setXmin(cadre.getXmin()-distMoveX); 
    gluOrtho2D(cadre.getXmin(), cadre.getXmax(), cadre.getYmax(),cadre.getYmin());
    
    //gluOrtho2D( xmin=xmin-distMoveX,xmax=xmax-distMoveX, ymax,ymin);
    newTab(20,1);
    dessine();       
    break;

    
  case GLUT_KEY_RIGHT:
        
    glLoadIdentity(); //réinitialise le repère

      cadre.setXmax(cadre.getXmax()+distMoveX);
    cadre.setXmin(cadre.getXmin()+distMoveX); 
    gluOrtho2D(cadre.getXmin(), cadre.getXmax(), cadre.getYmax(),cadre.getYmin());
    
    //gluOrtho2D( xmin=xmin+distMoveX,xmax=xmax+distMoveX, ymax,ymin);
    newTab(20,2);
    dessine();    
    break; 
  }
}
