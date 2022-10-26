#include <cmath>
#include <iostream>
#include <iomanip>



double AttackerSuccessProbability(double q, int z)
{
	double p = 1.0 - q;
	double lambda = z * (q / p);
	double sum = 1.0;
	for (int k = 0; k <= z; k++)
	{
		double poisson = exp(-lambda);
		for (int i = 1; i <= k; i++)
			poisson *= lambda / i;
		sum -= poisson * (1 - pow(q / p, z - k));
	}
	return sum;
}

int main()
{
	using namespace std;
	double q = 0.1;

	cout << fixed << setprecision(8);
	cout << "q=" << q << endl;  
	for (int z = 0; z <= 10; ++z)
	{
		cout << "z="<< z << "\t" << "P=" << AttackerSuccessProbability(q, z) << endl;;
	}


	q = 0.3;
	cout << "q=" << q << endl;  
	for (int z = 0; z <= 50; z+=5)
	{
		cout << "z="<< z << "\t" << "P=" << AttackerSuccessProbability(q, z) << endl;;
	}
	return 1;
}
