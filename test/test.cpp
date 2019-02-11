#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

using namespace std;


int main(int argv, char** argc){
  
  float r;
  cin>>r;
  float i;
  cin>>i;
  std::cout<<"le nombre complexe entré est: "<<r<<"+i("<<i<<")"<<endl;

  //Zn=0
  //Zn+1=Zn²+c

  int ZnR=0;
  int ZnI=0;
  
  int cmp=0;
  while(sqrt(pow(ZnR,2)+pow(ZnI,2))<2 && cmp<1000){
    
   
    ZnR=pow(ZnR,2)-pow(ZnI,2)+r;
    ZnI=2*ZnR*ZnI;
    cmp++;
  }

  if (sqrt(pow(r,2)+pow(i,2))>2)
    cout<<"la fonction diverge a partir de n= "<<cmp<<endl;
  else
    cout<<"la fonction converge"<<endl;

}
