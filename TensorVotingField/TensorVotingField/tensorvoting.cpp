#include "tensorvoting.h"
#include "Common.h"
#include <iostream>
#include "tvf.h"
#include "stickTVF.h"
using namespace std;

////////////////////////////////////////
// library function
tvf_ptr createTVF(double sigma)
{
	return new TVF(sigma);
}

void	destroyTVF(tvf_ptr tvf)
{
	if (tvf != NULL)
	{
		delete tvf;
		tvf =NULL;
	}
}

int		getTVFWindowSize(tvf_ptr tvf)
{
	return tvf->getWindowSize();
}

int		getTVFFullSize(tvf_ptr tvf)
{
	return tvf->getFullSize();
}

TensorArray getVotingField(tvf_ptr tvf)
{
	return tvf->getVF();
}

Tensor	getTensorElements(tvf_ptr tvf, int w, int h)
{
	return (*tvf)[4*w*h];
}

void	getTensorElements(tvf_ptr tvf, double t[], int w, int h)
{	
	t =(*tvf)[4*w*h];	
}


void	convertTensorToEigen(Tensor t, Vector e1, Vector e2, double &l1, double &l2)
{
	double tr = (t[0]+t[3])/2;
	double ab = sqrt( pow(t[0]-tr,2)+pow(t[1],2) );
	l1 = ab + tr;
	l2 = -ab +tr;
	double theta = atan2(ab-(t[0]-tr),t[2]);
	e1[0] = cos(theta);
	e1[1] = sin(theta);
	e2[0] = -sin(theta);
	e2[1] = cos(theta);
}

// init binary image to tensor image
TensorArray initTensorImage(unsigned char *bImage, int imageSize)
{
	TensorArray ta = createTensorArray(imageSize);
	for (int i=0;i<imageSize;i++)
	{
		if (bImage[i] > 0)
		{
			ta[i][0] = 1;
			ta[i][1] = 0;
			ta[i][2] = 0;
			ta[i][3] = 1;
		}
	}
	return ta;
}