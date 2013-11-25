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
//  myfile.open("2d.txt");

  fftw_plan p;
  fftw_complex A[10][10];
  fftw_complex B[10][10]; 
  fftw_complex C[10][10];
  fftw_complex D[10][10];
  fftw_complex E[10][10];
  fftw_complex F[10][10];
//  A = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) *100);
//  B = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) *100);
//  C = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) *100);
  for (int row=0; row<10 ;row++) 
    for (int column=0;column<10;column++)
	{A[row][column][0]=exp(-1*( pow( pow(abs(row-5.),2.) + pow(abs(column-5.),2.) ,0.5 ) ) );A[row][column][1]=(0.0);
	};

for (int row=0; row<10 ;row++)
    for (int column=0;column<10;column++)
        {B[row][column][0]=0;B[row][column][1]=(0.0);
        };

  B[2][3][0]=10;
  for(int i=0; i<10; i++)    //This loops on the rows.
	{
		for(int j=0; j<10; j++) //This loops on the columns
		{
			cout << A[i][j][0]  << "  ";
		}
		cout << endl;
	}
  p=fftw_plan_dft_2d(10,10,&A[0][0],&C[0][0], FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(p); 
  fftw_destroy_plan(p);

  p=fftw_plan_dft_2d(10,10,&B[0][0],&D[0][0], FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(p); 
  fftw_destroy_plan(p);
cout<<"printing IFFT, D================="<<endl;
  for(int i=0; i<10; i++)    //This loops on the rows.
        {
                for(int j=0; j<10; j++) //This loops on the columns
                {
                        cout << D[i][j][0]  << "  ";
                }
                cout << endl;
        }


// MATRIX MULTIPLICATION ************//

  for(int i=0; i<10; i++)    //This loops on the rows.
        {
                for(int j=0; j<10; j++) //This loops on the columns
                {
                E[i][j][0]=0;
                for(int k=0;k<10;k++)
			E[i][j][0]=E[i][j][0]+(C[i][k][0] * D[k][j][0]);
                }
                cout << endl;
        }

cout<<"printing IFFT, E================="<<endl;
  for(int i=0; i<10; i++)    //This loops on the rows.
        {
                for(int j=0; j<10; j++) //This loops on the columns
                {
                        cout << E[i][j][0]  << "  ";
                }
                cout << endl;
        }


p=fftw_plan_dft_2d(10,10,&E[0][0],&F[0][0], FFTW_BACKWARD, FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);

cout<<"printing IFFT, F================="<<endl;
  for(int i=0; i<10; i++)    //This loops on the rows.
        {
                for(int j=0; j<10; j++) //This loops on the columns
                {
                        cout << F[i][j][0]  << "  ";
                }
                cout << endl;
        }
//  myfile.close();
/*
  
  fftw_complex *in, *out;
  int N = 10;
  int M = 10;
  in =  (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N * M);
  out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N * M);
  p = fftw_plan_dft_2d(N,M, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
//  fftw_execute(p);  repeat as needed 
*/
  return 0;
}
