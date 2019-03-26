
//compiler avec g++ graphique.cpp -o graphique -lglut -lGLU -lGL
#include "Point.h"

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <ctime> //pour calculer le temps du programme
#include <vector>

#include <cmath>

#include <iostream>
using namespace std;

double xmin=-2.15;
double xmax=0.55;
double ymin=-1.3;
double ymax=1.3;
/*
  float xmin = -0.7;
  float xmax = -0.5;
  float ymin = -0.7;
  float ymax = -0.5;
*/
double xmin1;
double ymin1;
double xmax1;
double ymax1;


//variable globale pour déssiner le carré:
//coordonné temporaire qui permet d'effacer les traits non utile
int tempX;
int tempY;
vector< vector<int> > tab;

int cliqX;
int cliqY;


//pour le redimentionnement de la fenetre


  int fenetreX;
  int fenetreY;


int tabOcc[100]={0};

int couleur=0;



double pixelToRepereX(int pixel){
  double tailleX=abs(xmax-xmin);
  return (tailleX/800)*pixel+xmin;   
}

double pixelToRepereY(int pixel){
  double tailleY=abs(ymax-ymin);
  return -((tailleY/800)*pixel+ymin); 
}







void dessine(){

  double tailleX=abs(xmax-xmin);
  double tailleY=abs(ymax-ymin);

  glBegin(GL_POINTS); 	//mode affichage de points

  for(int i=0;i<800;i++){ //double boucle pour parcourir les points étudier
    for(int  j=0;j<800;j++){

      if (tab[i][j]==-1)
    glColor3f(0.2, 0.2, 0.2);  
  
      else
	if(couleur==0)
	  glColor3f(cos(exp(5*(0.01*tab[i][j]))+4),
		    cos(exp(5*(0.01*tab[i][j]))+2),
		    cos(exp(5*(0.01*tab[i][j]))));
	else{
	  if(couleur==1){
	    
	    glColor3f(0.00001*tabOcc[tab[i][j]],
		      1-0.0001*tabOcc[tab[i][j]],
		      0.5-0.00001*tabOcc[tab[i][j]]);
	  }
	  else{
	    //vert -> bleu -> rouge
	    float tabCouleur[10][3]={
	      {0,1,0}, {0,1,0.85},
	      {0,0.8,1}, {0,0.95,1},
	      {0,0,1}, {0.8,0,1},
	      {1,0,1}, {1,0,0.5},
	      {1,0,0}, {1,0.5,0}};

	    //rouge ->vert->bleu
	    // float tabCouleur[10][3]={{1,0,0}, {1,0.5,0},
	    // 			   {1,1,0}, {0.5,1,0},
	    // 			   {0,1,0}, {0,1,0.5},
	    // 			   {0,1,1}, {0,0.5,1},
	    // 			   {0,0,1}, {1,0,1}};

	    
	    glColor3f(tabCouleur[(tab[i][j]/10)][0] ,
		      tabCouleur[(tab[i][j]/10)][1],
		      tabCouleur[(tab[i][j]/10)][2]  );
    

	  }
	  
	}
  glVertex2f((tailleX/800)*i+xmin,(tailleY/800)*j+ymin);
    }
  }
  glEnd(); 		       	// Fermer le polygone
  glFlush(); 
}


void remplirTab(){
  double tailleX=abs(xmax-xmin);
  double tailleY=abs(ymax-ymin);
  for (int i=0 ; i<800 ; i++) {
    tab.push_back(vector<int>(800));
    for (int j=0 ; j<800 ; j++) {
      tab[i][j]=point::diverge((tailleX / 800) * i + xmin,
       (tailleY / 800) * j + ymin); 
    }
  }
}




/*  NE FONCTIONNE PAS
 */






void completeTab(int imin, int imax, int jmin,int jmax){

  for (int i=imin ; i<imax ; i++) {
   
    for (int j=jmin ; j<jmax; j++) {
      tab[i][j]=point::diverge(pixelToRepereX(i), pixelToRepereY(j));
    }
  }
}

void newTab(int move, int dir){
  //dir de 1 a 4;
  
  vector< vector<int> > tabcopie(800,vector<int>(800,0));

  //suivant la valeur de dir, boucle ne commence/finis pas au meme endrois
  
  switch(dir){
  case 1:
    //vers la gauche
    for (int i=move ; i<800 ; i++) {
      for (int j=0 ; j<800 ; j++) {
	tabcopie[i][j]=tab[i-move][j];
      }
    }
 
    tab.swap(tabcopie);
    completeTab(0,move,0,800);
    break;
    
    //droite
  case 2:
    for (int i=0 ; i<800-move ; i++) {
      for (int j=0 ; j<800 ; j++){
	tabcopie[i][j]=tab[i+move][j]; 
      }
    }

    tab.swap(tabcopie);
    completeTab(800-move,800,0,800);
    
    break;
  case 3:
    for (int i=0 ; i<800; i++) {
      for (int j=move; j<800 ; j++){
	tabcopie[i][j]=tab[i][j-move];
      }
    }
    tab.swap(tabcopie);
    completeTab(0,800,0,move);
    break;
    
  case 4:
    for (int i=0 ; i<800 ; i++) {
      for (int j=0 ; j<800-move ; j++){
	tabcopie[i][j]=tab[i][j+move]; 
      }
    }

    tab.swap(tabcopie);
    completeTab(0,800,0,0);
    break;
  }
}


void deplaceTab(int move, int dir){
  newTab(move, dir);
  
  //on supprime les cases
  
}






void occuranceDiv(){

  for(int i=0; i<800; i++)
    for(int j=0; j<800; j++)
      tabOcc[tab[i][j]]++;
}

void Rafraichir(void) {
  glClear(GL_COLOR_BUFFER_BIT);	// Effacer la surface graphique

  // ----------------- Tableaux de pixels (entier correspondant à la couleur) ------------------
  // vector<vector<int>> tab(glutGet(GLUT_WINDOW_WIDTH)); // créer le tableau avec la taille de la fenêtre
 
  //cout<<"taille fenetre :"<<glutGet(GLUT_WINDOW_WIDTH)<<glutGet(GLUT_WINDOW_HEIGHT)<<endl;

  //innitiallisation du tableau:
  /*
  int** tab=new int*[glutGet(GLUT_WINDOW_WIDTH)];
*/

  
  //int fenetreX=glutGet(GLUT_WINDOW_WIDTH);
  //int fenetreY=glutGet(GLUT_WINDOW_HEIGHT);

  //int tailleTabX;
  //int tailleTabY;
  /*
  if(tab.size()>0){


  	//tab.push_back()


  	tab[0].size();
}
*/



  double tailleX=abs(xmax-xmin);
  double tailleY=abs(ymax-ymin);


  

  glColor3f(1,1,1);
  
  glBegin(GL_LINES);
  glVertex2f((tailleX/800)*-1+xmin,ymin);
  glVertex2f((tailleX/800)*-1+xmin,ymax);
  glEnd();      	// Fermer le polygone
  glFlush();


  remplirTab();

  //si la couleur utilise le nombre d'occurance pour chaque temps de divergence:
  occuranceDiv();
  
  
  //----------- fonction affiche ---------
  dessine();

  
  // -----------------------------------------------------------------
 
  glBegin(GL_LINES);
  glColor3f(1,1,1);
  glVertex2f(0, 0);
  glVertex2f(0, 1);
  glEnd();
  glFlush();

  glBegin(GL_LINES);
  glColor3f(1,1,1);
  glVertex2f(0, 0);
  glVertex2f(1, 0);
  glEnd();
  glFlush();

}


//gere les touche basique du clavier
void clavier(unsigned char key, int x, int y)  // glutKeyboardfuncS(clavier)
{
  printf("Touche : %c = %d \n", key, key);
  // test, permet de savoir quelle touche est tapé
   switch (key) {
   case 97: //touche a 
 
      cout << "couleur par défaut"<<endl;
      couleur=0;
      dessine();
      break;
   case 122: //touche z
     
     cout << "couleur en fonction du nombre d'occurence pour chaque temps de divergence."<<endl;
     couleur=1;
     dessine();
     break;

   case 101: //touche e
     cout << "Couleurs par intervalles"<<endl;
     couleur=974;
     dessine();
     break;

     
   case 13: //touche entrer
     cout << "Fractale par défaut"<<endl;
     couleur=0;//réinitialise la couleur
     glLoadIdentity(); //réinitialise le repère
     gluOrtho2D( xmin=-2.15,xmax=0.55,ymin=-1.3, ymax=1.3);//zoom du repère
     Rafraichir();
     break;


     //ajout ici des autre evenement du clavier
   }
}


//gère les touche dite "spéciale" du clavier (comme les touche directionnelle)
void touche(int key, int x, int y){
  double tailleX=abs(xmax-xmin);
  double tailleY=abs(ymax-ymin);

  
  printf("Touche spécial: %c = %d \n", key, key);

  double distMoveX=pixelToRepereX(20);
 double distMoveY=pixelToRepereY(20);
  switch(key){
  case GLUT_KEY_UP :
    
    glLoadIdentity(); //réinitialise le repère
    gluOrtho2D( xmin,xmax,ymin=ymin+distMoveY,ymax=ymax+distMoveY); 
    deplaceTab(20,4);
    dessine();
    break;
		
  case GLUT_KEY_DOWN :
    glLoadIdentity(); //réinitialise le repère
    gluOrtho2D( xmin,xmax,ymin=ymin-distMoveY,ymax=ymax-distMoveY);
    deplaceTab(20,3);
    dessine();
    
    break;

  case GLUT_KEY_LEFT :

    glLoadIdentity(); //réinitialise le repère
    gluOrtho2D( xmin=xmin-distMoveX,xmax=xmax-distMoveX,ymin, ymax);
    deplaceTab(20,1);
    dessine();
    
    
    break;
    
  case GLUT_KEY_RIGHT :
        
    glLoadIdentity(); //réinitialise le repère
    gluOrtho2D( xmin=xmin+distMoveX,xmax=xmax+distMoveX,ymin, ymax);
    deplaceTab(20,2);
    dessine();
    
    break;
 
  }

}




template<typename T>
void inverse(T &min, T &max) {
  if (max < min) {
    T a = min;
    min = max;
    max = a;

  }
}




void carre( int x, int y) {
  float tailleX = abs(xmax - xmin);
  float tailleY = abs(ymax - ymin);

  //dessine();
 

  /*
  glBegin(GL_LINES);
  glVertex2f(xmin1,-ymin1);
  //affiche le point de la position de la souris:
  glVertex2f((tailleX / 800) * x + xmin,-((tailleY / 800) * y + ymin));
  glEnd(); 		       	// Fermer le polygone
  glFlush();

  */

  
  /*
  //on enlève les trait parasite:
   glBegin(GL_POINTS);


   
   //////////////////////////POSE PROBLEMMMMMMMMEEE////////////////////:
   //int k=(ymin1-ymin)*(800/tailleY);
   int k=cliqY;

   
   int Imin=x;
   int Imax=tempX;
   inverse(Imin,Imax);

   cout<<endl<<endl<<endl<<"cliqX= "<<x<<"cliqY ="<<y<<endl<<endl;

 
   //enleve le surplus de la ligne horizontale du haut
   for(int i=Imin; i<=Imax; i++){
     if((0<=i) && (800 >=i)){
       
       if (tab[i][k]==-1)    { 
	 glColor3f(0.2, 0.2, 0.2);
	 
	  // glColor3f(0,0,0);
	 
       }
	   
       else{
	 	 glColor3f(cos(exp(5*(0.01*tab[i][k]))+4),
	    cos(exp(5*(0.01*tab[i][k]))+2),
	    cos(exp(5*(0.01*tab[i][k]))));
	    
  //	 glColor3f(0,0,0);
	 
       }

       glVertex2f((tailleX/800)*i+xmin,(tailleY/800)*k+ymin);

     }   
   }

   int Jmin=y;
   int Jmax=tempY;
   inverse(Jmin,Jmax);

   //int l=(xmin1-xmin)*(800/tailleX);
     int l=cliqX;
   //enlève le surplus de la ligne verticale de gauche
   for(int j=Jmin; j<=Jmax; j++){
     if((0<=j) && (800 >=j)){
       
       if   (tab[l][j]==-1) {    
	 glColor3f(0.2, 0.2, 0.2);
	 
// glColor3f(0,0,0);
	 
       }
	   
       else{
	 	  glColor3f(cos(exp(5*(0.01*tab[l][j]))+4),
	cos(exp(5*(0.01*tab[l][j]))+2),
	 	   cos(exp(5*(0.01*tab[l][j]))));
	 
		  //  glColor3f(0,0,0);
	 
       }

       glVertex2f((tailleX/800)*l+xmin,(tailleY/800)*j+ymin);

       
     }   
   }
   

   //permet de gerer le cas ou j est plus grand que Jmin
   /*  inverse(k,Jmax);
   
   //enleve la ligne droite verticale de l'encien cadre
   for(int i=j; i<=Jmax;i++){
     if((0<=i) && (800 >=i)){
	if (tab[tempX][i]==-1)     
	 glColor3f(0.2, 0.2, 0.2);
	 
       else
	 glColor3f(cos(exp(5*(0.01*tab[tempX][i]))+4),
		   cos(exp(5*(0.01*tab[tempX][i]))+2),
		   cos(exp(5*(0.01*tab[tempX][i]))));
		   glVertex2f((tailleX/800)*tempX+xmin,(tailleY/800)*i+ymin);
	  }   
	  }
   
   glEnd(); 		       	// Fermer le polygone
   glFlush();  
  */
   //////////////////////////POSE PROBLEMMMMMMMMEEE////////////////////:
  

  //on retient la coordonné de la souris pour pouvoir effacer les trait en trop plus tard
  tempX=x;
  tempY=y;
  
  //on trace le carré:
  glColor3f(1,1,1);
  //trace la ligne verticale partant du point de départ
  glBegin(GL_LINES);
  glVertex2f(xmin1,ymin1);
  glVertex2f(xmin1,((tailleY / 800) * y + ymin));
  glEnd(); 		       	// Fermer le polygone

  //ligne horizontale partant du point de départ
  glBegin(GL_LINES);
  glVertex2f(xmin1,ymin1);
  glVertex2f((tailleX / 800) * x + xmin,ymin1);
  glEnd(); 		       	// Fermer le polygone
  glFlush();

  ////
  /*
  glBegin(GL_LINES);
  glVertex2f((tailleX / 800) * x + xmin,ymin1);
  glVertex2f((tailleX / 800) * x + xmin,((tailleY / 800) * y + ymin));
  glEnd(); 		       	// Fermer le polygone
  glFlush();
  */  

 
  
}

void clique (int button, int state, int x, int y) {

  // réinitialisation de temp pour le tracer du carré
  tempX=x;
  tempY=y;

  cliqX=x;
  cliqY=y;
  cout<<endl<<endl<<"clique"<<endl<<"cliqX= "<<x<<"clqY ="<<y<<endl<<endl;
  
  switch (button) {
     case 4: //roulette vers le bas
       if (state == GLUT_DOWN){ //la roulette est vu comme un bouton,
	 //on evite donc d'avoir l'evenement "commence roulette", finis a roulette"
       cout<<"miaou"<<endl<<endl;

    //dezoom
       xmin=xmin*(xmin<0?1.1:0.9);
       xmax=xmax*(xmax<0?0.9:1.1);
       ymin=ymin*(ymin<0?1.1:0.9);
       ymax=ymax*(ymax<0?0.9:1.1);
 
    glLoadIdentity();




    
    gluOrtho2D(xmin,xmax,ymax, ymin);	      	//zoom du repère


    Rafraichir(); 		// Callback de la fenêtre

       }
    
    break;

 case 3: //roulette vers le haut
    //zoom
     if (state == GLUT_DOWN){ 
        xmin=xmin*(xmin>0?1.1:0.9);
	xmax=xmax*(xmax>0?0.9:1.1);
       ymin=ymin*(ymin>0?1.1:0.9);
       ymax=ymax*(ymax>0?0.9:1.1);
 
    glLoadIdentity();
    gluOrtho2D(xmin,xmax,ymax,ymin);	      	//zoom du repère

    Rafraichir(); 		// Callback de la fenêtre
     }
    break;
    
  case GLUT_LEFT_BUTTON:
    
    float tailleX = abs( xmax - xmin);
    float tailleY = abs(ymax - ymin);
    if(state == GLUT_DOWN) {


      
      
      cout << "coordonnées en pixel:" << x << ", " << y << endl
	   << "coordonnée en par rapport a l'axe " << (tailleX / 800) * x + xmin
	   << "; " << (tailleY / 800) * y + ymin << endl;

      xmin1=(tailleX/800)*x+xmin;
      ymin1=((tailleY/800)*y+ymin);
    }
      

      
    if(state == GLUT_UP)	  {

      cout<<"coordonnées en pixel:"<<x<<", "<<y<<endl
	  <<"coordonnée par rapport à l'axe "
	  <<(tailleX/800)*x+xmin<<"; "<<(tailleY/800)*y+ymin<<endl;
	
      xmax1=(tailleX/800)*x+xmin;
      ymax1=((tailleY/800)*y+ymin);
	
      inverse(xmin1,xmax1);
      inverse(ymin1,ymax1);
	
      xmin=xmin1;
      ymin=ymin1;
      xmax=xmin1+(abs(xmax1-xmin1)+abs(ymax1-ymin1))/2;
      ymax=ymin1+(abs(xmax1-xmin1)+abs(ymax1-ymin1))/2;

      cout<<endl<<"xmin= "<<xmin<<" xmax= "<<xmax<<" ymin= "<<ymin<<" ymax= "<<ymax<<endl<<endl;

      glLoadIdentity();
      gluOrtho2D(xmin,xmax,ymax, ymin);	      	//zoom du repère

      Rafraichir(); 		// Callback de la fenêtre

      
      
    }
    break;

  }
  
}




int main(int argc, char* argv[]) {
  time_t start, stop;
  start = clock();
  
  glutInit(&argc, argv); 
  glutInitWindowSize(800, 800); // taille fenetre
  glutInitDisplayMode(GLUT_RGB); // On travaille en RGB
  int win = glutCreateWindow("Fractale de Mandelbrot"); // nomme la fenêtre


  fenetreX=glutGet(GLUT_WINDOW_WIDTH);
  fenetreY=glutGet(GLUT_WINDOW_HEIGHT);



  
  gluOrtho2D(xmin, xmax, ymin, ymax);	// zoom du repère  
  glutDisplayFunc(Rafraichir); // Callback de la fenêtre

  //glPointSize(2); //changer taille point

  
  glutMouseFunc(clique);
  glutMotionFunc(carre);
  
  stop = clock();

  //evenement clavier basique
  glutKeyboardFunc(clavier);

  //evenement touche clavier "spécial"
  glutSpecialFunc(touche);
  

  cout << "durer du programme: " << difftime(stop, start) << " milliseconde" << endl;

  glutMainLoop(); //permet un "arret sur image"
}
