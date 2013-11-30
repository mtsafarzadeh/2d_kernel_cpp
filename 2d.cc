#include <iostream>
#include <math.h>
#include <complex>
#include <fftw3.h> 
#include <stdlib.h>
#include <fstream>
using namespace std;

int main ()
{
  ofstream result,kernel,image;
  result.open("result.txt");
  kernel.open("kernel.txt");
  image.open("image.txt");
  fftw_plan p;
  
  // all the matrices X[][][0] is the real part and X[][][1] is the imaginary part 
  fftw_complex A[100][100]; //saves the kernel (here is a gaussian )
  fftw_complex B[100][100]; // image before convolution, here is  point source
  fftw_complex C[100][100];  // FFT of kernel
  fftw_complex D[100][100];  // FFT of image
  fftw_complex E[100][100];  // saves the multiplication of  C and D
  fftw_complex F[100][100];  // the IFFT of E  ( the final result of convolution)

  for (int row=0; row<100 ;row++) 
    for (int column=0;column<100;column++)
	{A[row][column][0]=exp(-1*( pow( pow(abs(row-50.),2.) + pow(abs(column-50.),2.) ,0.5 ) ) );A[row][column][1]=(0.0);
	};

for (int row=0; row<100 ;row++)
    for (int column=0;column<100;column++)
        {B[row][column][0]=0;B[row][column][1]=(0.0);
        };

  B[49][49][0]=10;
  for(int i=0; i<100; i++)    //This loops on the rows.
	{
		for(int j=0; j<100; j++) //This loops on the columns
		{
			kernel<< A[i][j][0]  <<'\t';
			image<< B[i][j][0]<<'\t';
		}
		kernel << endl;
		image << endl;
	}
  p=fftw_plan_dft_2d(100,100,&A[0][0],&C[0][0], FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(p); 
  fftw_destroy_plan(p);

  p=fftw_plan_dft_2d(100,100,&B[0][0],&D[0][0], FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(p); 
  fftw_destroy_plan(p);
cout<<"printing IFFT, D================="<<endl;
  for(int i=0; i<100; i++)    //This loops on the rows.
        {
                for(int j=0; j<100; j++) //This loops on the columns
                {
                        cout << D[i][j][0]  << "  ";
                }
                cout << endl;
        }


// MATRIX MULTIPLICATION ************//

  for(int i=0; i<100; i++)    //This loops on the rows.
        {
                for(int j=0; j<100; j++) //This loops on the columns
                {
                E[i][j][0]=0;
                for(int k=0;k<100;k++)
			{
			E[i][j][0]=E[i][j][0]+(C[i][k][0] * D[k][j][0] - C[i][k][1] * D[k][j][1]);
                	E[i][j][1]=E[i][j][1]+(C[i][k][0] * D[k][j][1] + C[i][k][1] * D[k][j][0]);
			}
		}

          
        }


p=fftw_plan_dft_2d(100,100,&E[0][0],&F[0][0], FFTW_BACKWARD, FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);

cout<<"printing IFFT, F================="<<endl;
  for(int i=0; i<100; i++)    //This loops on the rows.
        {
                for(int j=0; j<100; j++) //This loops on the columns
                {
                        //cout << F[i][j][0]  << "  ";
                        result << pow(pow(F[i][j][0],2)+pow(F[i][j][1],2),0.5)  <<'\t';
			            //result <<F[i][j][0]  <<'\t';
                }
                result << endl;
        }
  result.close();
  kernel.close();
  image.close();
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
