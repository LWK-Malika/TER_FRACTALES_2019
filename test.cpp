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

  int Zn=0;
  
  int cmp=100;
  while(sqrt(pow(r,2)+pow(i,2))>2 || cmp>100){

    //zn=pow(Zn,2)+
    
    cmp++;
  }

  if (sqrt(pow(r,2)+pow(i,2))>2)
    cout<<"la fonction diverge a partir de n= "<<cmp<<endl;
  else
    cout<<"la fonction converse"<<endl;

}
