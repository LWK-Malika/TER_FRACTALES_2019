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

  if( couleur ==3)
	remplirTabDernierPoint();
  
    
  glBegin(GL_POINTS); 	//mode affichage de points  
  for(int i=0;i<800;i++){ //double boucle pour parcourir les points �tudi�
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
  std::cout<<"xmin "<<aRemplir.getXmin()
      <<"xmax "<<aRemplir.getXmax()
	   <<"ymin "<<aRemplir.getYmin()
	   <<"ymax "<<aRemplir.getYmax()
      <<std::endl;
 
  for (int i=aRemplir.getXmin() ; i<aRemplir.getXmax() ; i++) {

    for (int j=aRemplir.getYmin() ; j<aRemplir.getYmax(); j++) {

      tab[i][j]=point::diverge(cadre.pixelToRepereX(i),
			       cadre.pixelToRepereY(j));
    }
  }
}

void gestionTab::newTab(int move, int dir){

  glClear(GL_COLOR_BUFFER_BIT);
  
  //dir de 1 a 4;
  std::vector< std::vector<int> > tabcopie(800,std::vector<int>(800,0));

  //suivant la valeur de dir, on ne compl�te pas le tableau au meme endroit.


  //il n'est pas possible de d�clarer une variable dans un switch
  rectangle aRemplir1(0,0,move,800);
  rectangle aRemplir2(800-move,0,800,800);
  rectangle aRemplir3(0,0,800,move);
  rectangle aRemplir4(0,800-move,800,800);
  
  /* rectangle aRemplir1(0,move,0,800);
  rectangle aRemplir2(800-move,800,0,800);
  rectangle aRemplir3(0,800,0,move);
  rectangle aRemplir4(0,800,800-move,800);
  */
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
  // test, permet de savoir quelle touche est tap�
   switch (key) {
   case 97: //touche a 
 
     std::cout << "couleur par d�faut"<<std::endl;
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
   
   case 114: //touche r
     std::cout << "Couleur test" << std::endl;
     couleur = 2;
     dessine();
     break;

   case 116: //touche t
     std::cout << "Couleur test" << std::endl;
     couleur = 3;
     dessine();
     break; 
     
   case 13: //touche entrer
     std::cout << "Fractale par d�faut"<<std::endl;
     couleur=0;//r�initialise la couleur
     glLoadIdentity(); //r�initialise le rep�re
     //cadre.reinitialise();
     //gluOrtho2D( xmin=-2.15,xmax=0.55, ymax=1.3,ymin=-1.3);//zoom du rep�re
     cadre.resetRepere();
  
     Rafraichir();

     std::cout<<"xmin = "<< cadre.getXmin()
	 <<"xmax = "<< cadre.getXmax()
	 <<"ymin = "<< cadre.getYmin()
	 <<"ymax = "<< cadre.getYmax()<<std::endl<<std::endl;
     break;
   case 113:
     std::cout << "Affichage du rep�re"<<std::endl;

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
     std::cout << "Supression du rep�re"<<std::endl;
     dessine();
     break;
     //ajout ici des autre evenement du clavier
   }
}



void gestionTab::touche(int key, int x, int y){
  printf("Touche sp�cial: %c = %d \n", key, key);

  double distMoveX=cadre.distPixToRepX(20);
  double distMoveY=cadre.distPixToRepY(20);
  
 
 std::cout<<"distmoveX = "<<distMoveX<<" distmoveY = "<<distMoveY<<std::endl;
  switch(key){
  case GLUT_KEY_DOWN :
    
    glLoadIdentity(); //r�initialise le rep�re

    cadre.setYmax(cadre.getYmax()-distMoveY);
    cadre.setYmin(cadre.getYmin()-distMoveY); 
    gluOrtho2D(cadre.getXmin(), cadre.getXmax(), cadre.getYmax(),cadre.getYmin());
    //gluOrtho2D( xmin,xmax,ymax=ymax-distMoveY,ymin=ymin-distMoveY);
    newTab(20,4);
    dessine();
    break;
		
  case GLUT_KEY_UP :
    glLoadIdentity(); //r�initialise le rep�re

        cadre.setYmax(cadre.getYmax()+distMoveY);
    cadre.setYmin(cadre.getYmin()+distMoveY); 
    gluOrtho2D(cadre.getXmin(), cadre.getXmax(), cadre.getYmax(),cadre.getYmin());
    // gluOrtho2D( xmin,xmax,ymax=ymax+distMoveY,ymin=ymin+distMoveY);
    newTab(20,3);
    dessine();  
    break;

    
  case GLUT_KEY_LEFT :

    glLoadIdentity(); //r�initialise le rep�re

      cadre.setXmax(cadre.getXmax()-distMoveX);
    cadre.setXmin(cadre.getXmin()-distMoveX); 
    gluOrtho2D(cadre.getXmin(), cadre.getXmax(), cadre.getYmax(),cadre.getYmin());
    
    //gluOrtho2D( xmin=xmin-distMoveX,xmax=xmax-distMoveX, ymax,ymin);
    newTab(20,1);
    dessine();       
    break;

    
  case GLUT_KEY_RIGHT:
        
    glLoadIdentity(); //r�initialise le rep�re

    cadre.setXmax(cadre.getXmax()+distMoveX);
    cadre.setXmin(cadre.getXmin()+distMoveX);
    gluOrtho2D(cadre.getXmin(), cadre.getXmax(), cadre.getYmax(),cadre.getYmin());
    
    //gluOrtho2D( xmin=xmin+distMoveX,xmax=xmax+distMoveX, ymax,ymin);
    newTab(20,2);
    dessine();    
    break; 
  }
}







void gestionTab::clique (int button, int state, int x, int y) {

  

  zoomTmp.setXmax(x);
  zoomTmp.setYmax(y);
  zoomTmp.setXmin(x);
  zoomTmp.setYmin(y);

  
  
  switch (button) {
  case 4: //roulette vers le bas
    if (state == GLUT_DOWN){ //la roulette est vu comme un bouton,
      //on evite donc d'avoir l'evenement "commence roulette", finis a roulette"
      
      //dezoom	 
      cadre.zoomArriere();
      Rafraichir(); 		// Callback de la fen�tre
    }
    
    break;
    
  case 3: //roulette vers le haut
    //zoom
    if (state == GLUT_DOWN){ 

      cadre.zoomAvant();
      Rafraichir(); 		// Callback de la fen�tre
    }
    break;
    
  case GLUT_LEFT_BUTTON:
    
    if(state == GLUT_DOWN) {


      
      
      std::cout << "coordonn�es en pixel:" << x << ", " << y << std::endl
	   << "coordonn�e en par rapport a l'axe " <<cadre.pixelToRepereX(x)
		<<cadre.pixelToRepereX(x)<<std::endl;

      zoom.setXmin(cadre.pixelToRepereX(x));
      zoom.setYmin(-cadre.pixelToRepereY(y));

    }
      

        
    if(state == GLUT_UP){
      
      std::cout << "coordonn�es en pixel:" << x << ", " << y << std::endl
	   << "coordonn�e en par rapport a l'axe " <<cadre.pixelToRepereX(x)
		<<cadre.pixelToRepereX(x)<<std::endl;


    zoom.setXmax(cadre.pixelToRepereX(x));
    zoom.setYmax(-cadre.pixelToRepereY(y));    
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
    //gluOrtho2D(xmin,xmax,ymax, ymin);	      	//zoom du rep�re

    gluOrtho2D(cadre.getXmin(), cadre.getXmax(), cadre.getYmax(), cadre.getYmin());
   
    Rafraichir(); 		// Callback de la fen�tre   
    }
    break;    
  }
}


/*
double gestionTab::couleur0(double i,double j,double cst){

  return cos(exp(5*(0.01*tab[i][j]))+cst);
}

double gestionTab::couleur1(double i,double j, double cst){
  return cst*tabOcc[tab[i][j]];
}
double gestionTab::couleur2(double i,double j, double cst){
  return cst + distance(i, j, tabOcc[tab[i][j]]);
}
double gestionTab::couleur3(double i,double j, double cst){
    return cst+distance(tabC[i][j].getX(),tabC[i][j].getY())/10;
}
double gestionTab::couleur974(double i,double j, double cst){
   float tabCouleur[10][3]={
	    {0,1,0}, {0,1,0.85},
	    {0,0.8,1}, {0,0.95,1},
	    {0,0,1}, {0.8,0,1},
	    {1,0,1}, {1,0,0.5},
	    {1,0,0}, {1,0.5,0}};
   return tabCouleur[(tab[i][j]/10)][(int)cst];
 } 
*/


void gestionTab::carre( int x, int y) {
  /*
  double (*ptrF)(double, double, double);

  double rouge;
  double vert;
  double bleu;

  

  switch (couleur){
  case 0:
    ptrF=couleur0;
    rouge=4;
    vert=2;
    bleu=0;
    break;
  case 1:
      ptrF=couleur1;
    rouge=0;
    vert=1;
    bleu=0.5;
    break;
  case 2:
    ptrF=couleur2;
    break;
  case 3:
      ptrF=couleur3;
    break;
  case 974:
  ptrF=couleur974;
    break;
  }
  */

  
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
    }}



   
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
   for(int a=std::min(zoomTmp.getXmin(), zoomTmp.getXmax());
       a < std::max(zoomTmp.getXmin(), zoomTmp.getXmax()); a++){
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
  //trace la ligne verticale partant du point de d�part
  glBegin(GL_LINES);

  
  glVertex2f(zoom.getXmin(),zoom.getYmin());
  glVertex2f(zoom.getXmin(),-cadre.pixelToRepereY(y));

  //ligne horizontale partant du point de d�part

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

  // zoomTmp.inverse();

}
