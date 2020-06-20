#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>

const int k = 2;                                                        // k,l: dimensions of the feature map
const int l = 1;
const int m = 9;                                                   // m: no. of data points
const int n = 8;                                                        // n: no. of attributes in the input set


// The following function is employed to calculate the coefficient when incrementing the weights of the map
float coef(int a, int b, int c, int d, int t)
{
	float n0, t0, tn, s0;
	n0 = 1.; t0 = 500000.; tn = 50000.; s0 = 1.;
	float S, S0;
	S = (a - c) * (a - c) + (b - d) * (b - d);
	S0 = s0 * exp((-1.0 * t / t0));
	if (S0 == 0 && S != 0) return 0;
	if (S0 == 0 && S == 0) return n0 * exp((-1.0 * t / tn));
	S0 *= S0;
	return exp((-1.0 * S / (2 * S0))) * n0 * exp((-1.0 * t / tn));
}

int main()
{
	//Getting the training data
	float Inp[m][n];
	float R[m][n];
	float temp;
	int temp1, temp2;
	srand(time(NULL));
	
	R[0][0] = 84.8;
	R[0][1] = 976.4;
	R[0][2] = 746.5;
	R[0][3] = 5;
	R[0][4] = 1;
	R[0][5] = 2;
	R[0][6] = 2;
	R[0][7] = 4.7;

	R[1][0] = 77;
	R[1][1] = 958.6;
	R[1][2] = 2003;
	R[1][3] = 7;
	R[1][4] = 1;
	R[1][5] = 4;
	R[1][6] = 15;
	R[1][7] = 7.6;

	R[2][0] = 43.7;
	R[2][1] = 378.4;
	R[2][2] = 1636.4;
	R[2][3] = 4;
	R[2][4] = 4;
	R[2][5] = 10;
	R[2][6] = 35;
	R[2][7] = 5.2;

	R[3][0] = 34.9;
	R[3][1] = 379.5;
	R[3][2] = 752.1;
	R[3][3] = 4;
	R[3][4] = 0;
	R[3][5] = 3;
	R[3][6] = 11;
	R[3][7] = 5.2;

	R[4][0] = 47.3;
	R[4][1] = 598.4;
	R[4][2] = 645.4;
	R[4][3] = 6;
	R[4][4] = 0;
	R[4][5] = 5;
	R[4][6] = 4;
	R[4][7] = 33.4;

	R[5][0] = 60.2;
	R[5][1] = 699.7;
	R[5][2] = 797.3;
	R[5][3] = 7;
	R[5][4] = 1;
	R[5][5] = 5;
	R[5][6] = 16;
	R[5][7] = 18.1;

	R[6][0] = 61;
	R[6][1] = 656.8;
	R[6][2] = 1907.5;
	R[6][3] = 4;
	R[6][4] = 1;
	R[6][5] = 9;
	R[6][6] = 4;
	R[6][7] = 3.5;

	R[7][0] = 32.5;
	R[7][1] = 384.5;
	R[7][2] = 1830.6;
	R[7][3] = 4;
	R[7][4] = 0;
	R[7][5] = 9;
	R[7][6] = 24;
	R[7][7] = 3.3;

	R[8][0] = 29.4;
	R[8][1] = 317.9;
	R[8][2] = 641.7;
	R[8][3] = 3;
	R[8][4] = 0;
	R[8][5] = 16;
	R[8][6] = 3;
	R[8][7] = 2.5;

	//Normalising data
	float x;
	for (int j = 0; j < n; j++)
	{
		x = 0;
		for (int i = 0; i < m; i++)
		{
			if (R[i][j] > x) x = R[i][j];
		}
		for (int i = 0; i < m; i++)
		{
			R[i][j] = (R[i][j] / x) * 100.;
		}

	}

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			Inp[i][j] = R[i][j];
		}
	}

	float o[500][2];
	int length = 0;
	for (int p = 0; p < 100; p++)
	{
		//randomising the order of the inputs in Inp[m][n] for increased effectiveness	
		for (int i = 0; i < 3 * m; i++)
		{
			temp1 = rand() % m;
			temp2 = rand() % m;
			for (int j = 0; j < n; j++)
			{
				temp = Inp[temp1][j];
				Inp[temp1][j] = Inp[temp2][j];
				Inp[temp2][j] = temp;
			}
		}

		// a[k][l][n]: Feature map with dimensions k,l and n no. of weights
		float a[k][l][n];

		// Assigning small random values to the map for initialisation
		for (int t1 = 0; t1 < k; t1++)
		{
			for (int t2 = 0; t2 < l; t2++)
			{
				for (int t3 = 0; t3 < n; t3++)
				{
					a[t1][t2][t3] = (rand() % 10) / 10.;
				}
			}
		}

		// k1,l1: coordinates of the winning neuron
		int k1, l1;
		float tempmin;
		float coeff;

		// SOM algorithm over all the training data given
		for (int t = 0; t < m * 200000; t++)
		{
			int k1 = 0, l1 = 0;
			temp = 0;
			float tempmin = 0;

			// Determination of the winning neuron		
			for (int i = 0; i < k; i++)
			{
				for (int j = 0; j < l; j++)
				{
					temp = 0;
					for (int n1 = 0; n1 < n; n1++)
					{
						temp += ((Inp[t % m][n1] - a[i][j][n1]) * (Inp[t % m][n1] - a[i][j][n1]));
					}
					if (i == 0 && j == 0) tempmin = temp;
					else if (temp < tempmin) { tempmin = temp; k1 = i; l1 = j; }
				}
			}

			// Incrementing weights of all the neurons
			for (int i = 0; i < k; i++)
			{
				for (int j = 0; j < l; j++)
				{
					coeff = coef(i, j, k1, l1, t);
					for (int n1 = 0; n1 < n; n1++)
					{
						a[i][j][n1] += coeff * (Inp[t % m][n1] - a[i][j][n1]);
					}

				}
			}
		}

		// Output recorded in output.dat in an array format with the attributes in each point on the map seperated by commas 

		int t3;
		/*for (int t1 = 0; t1 < k; t1++)
		{
			for (int t2 = 0; t2 < l; t2++)
			{
				for (t3 = 0; t3 < n; t3++)
				{
					printf("%.0f", a[t1][t2][t3]);
					//if(t3==n-1) fprintf(fp,"\n");
					//else fprintf(fp,"\t");
					if (t3 != n - 1) printf(",");
				}
				if (t2 == l - 1) printf("\n\n");
				else printf("\t");
			}
		}*/
		//printf("\n\n");

		float o1 = 0;
		float o2;
		int oc;
		for (int t = 0; t < m; t++)
		{
			k1 = 0; l1 = 0;
			temp = 0;
			tempmin = 0;

			for (int i = 0; i < k; i++)
			{
				for (int j = 0; j < l; j++)
				{
					temp = 0;
					for (int n1 = 0; n1 < n; n1++)
					{
						temp += ((R[t][n1] - a[i][j][n1]) * (R[t][n1] - a[i][j][n1]));
					}
					if (i == 0 && j == 0) tempmin = temp;
					else if (temp < tempmin) { tempmin = temp; k1 = i; l1 = j; }
				}
			}
			if (t == 0) oc = k1;
			//o2 = m - (t + 1);
			o2 = t;
			//printf("%d,%d  %f\n", k1, l1, o2);
			if (k1 != oc) o1 += pow(2, o2);

		}
		//printf("\n%f", o1);
		int sign=0;
		for (int i = 0; i < length; i++)
		{
			if (o[i][0] == o1) { o[i][1]++; sign = 1; }
		}
		if (sign == 0)
		{
			o[length][0] = o1;
			o[length][1] = 1;
			length++;
		}
	}
	for (int i = 0; i < length; i++)
	{
		int c;
		int q = 0;
		int r = 10;
		c = o[i][0];
		while (c != 0)
		{
			r = c % 2;
			c = c / 2;
			printf("%d ", r);
			q++;
		}
		while (q < m )
		{
			printf("0 ");
			q++;
		}
		printf("-> %.0f\n\n", o[i][1]);
	}
	return 0;

}