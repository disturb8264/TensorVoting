#include <iostream>
#include <fstream>
#include "tensorvoting.h"

using namespace std;

int main()
{
	#if defined ( _MSC_VER )
	system("mode con:cols=160 ");	
	#endif
	
	int sigma = 3;

	tvf_ptr tvf = createTVF(sigma);
	TensorArray svf =getVotingField(tvf);

		/* test out vf */	
	cout << "=========bvf================" << endl;
	int w = getTVFWindowSize(tvf);
	for (int i=0;i<w;i++)
	{
		for (int j=0;j<w;j++)
		{
			cout.setf(ios::fixed,ios::floatfield);
			cout.precision(3);
			cout << svf[i*w+j][3] <<"\t";
		}
		cout << endl;
	}
	cout << "=========================" << endl;
	/* test out vf */

	/* output to txt file */
	/*
	ofstream file;
	file.open("d:\\tv.txt");
	file.precision(3);
	if (file.is_open())
	{
		int w =getTVFWindowSize(tvf);
		file << w << endl;
		for (int i=0;i<w;i++)
		{
			for (int j=0;j<w;j++)
			{
				file << svf[i*w+j][3] <<endl;
			}			
		}
	}
	file.close();
	*/
	/* output to txt file */

	return 0;

}