#include <iostream>
//#include <iomanip>
#include <cmath>
#include <ctime>
using namespace std;

int frequency_of_primes (int n) {
  int i,j;
  int freq=n-1;
  for (i=2; i<=n; ++i) for (j=sqrt(i);j>1;--j) if (i%j==0) {--freq; break;}
  return freq;
}

int test ()
{
  clock_t t;
  int f;
  t = clock();
  cout << "Calculating..." << endl;
  f = frequency_of_primes (99999);
  cout << "The number of primes lower than 100,000 is: " << f << endl;
  t = clock() - t;
  cout << "It took me " << t << 
  " clicks (" << (float)t / CLOCKS_PER_SEC << " seconds)." << endl;
}