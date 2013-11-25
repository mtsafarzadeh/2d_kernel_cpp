#include <iostream>
#include <math.h>
#include <complex>
#include <fftw3.h> 
#include <stdlib.h>
#include <fstream>
using namespace std;

int main ()
{
  ofstream myfile;
  myfile.open("test.txt");
  fftw_plan p;
  fftw_complex *B, *C, *A;
  A = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 1000);
  B = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 1000);
  C = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 1000);
  for (int i=0; i<1000 ;i++) {A[i][0]=sin(2*3.14*i);A[i][1]=(0.0);};
  p=fftw_plan_dft_1d(1000,A,C, FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(p); 
  for (int i=0; i<1000 ;i++) {myfile<<A[i][0]<<'\t'<<C[i][0]<<'\t'<<C[i][1]<<endl;};
  myfile.close();
/*
  
  fftw_complex *in, *out;
  int N = 10;
  int M = 10;
  in =  (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N * M);
  out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N * M);
  p = fftw_plan_dft_2d(N,M, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
//  fftw_execute(p);  repeat as needed 
//  fftw_destroy_plan(p);
//  fftw_free(in); fftw_free(out);
*/
  return 0;
}
