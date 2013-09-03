#include "Common.h"
#include "tvf.h"
#include "stickTVF.h"


TVF::TVF(double sigma, int nSvf):_sigma(sigma), _nSvf(nSvf)
{
	if (sigma > SIGMA_MAX || sigma < SIGMA_MIN)
	{
		throw E_SIGMA_OUT_OF_RANGE;
	}
	_wSize = calcWindowSize(_sigma);			// window width size
	_wsHalf = (_wSize-1)/2;						// half window width size
	_vfSize = _wSize * _wSize;					// width * width
	_vf = createTensorArray(_vfSize);			// allocate tensor array heap
	initVotingField();									// create ball voting field
}	

TVF::~TVF()
{
	destroyTensorArray(_vf,_vfSize);			// free heap
}

int TVF::calcWindowSize(double sigma)
{
	int ws = (int)ceil(sqrt( -log(0.01)*pow(sigma,2) )*2);
	return (int)floor(ws/2)*2+1;
}

void TVF::initVotingField()
{
	// cumulative stick voting field.
	for (int i=0;i<_nSvf;i++)
	{
		double theta = (((double)i)/_nSvf-1/_nSvf)*PI*2;	
		TensorArray svf = generateStickTVF(this,theta);		
		for (int h=0;h<_wSize;h++)
		{
			for (int w=0;w<_wSize;w++)
			{
				_vf[h*_wSize+w][0] += svf[h*_wSize+w][0];
				_vf[h*_wSize+w][1] += svf[h*_wSize+w][1];
				_vf[h*_wSize+w][2] += svf[h*_wSize+w][2];
				_vf[h*_wSize+w][3] += svf[h*_wSize+w][3];
			}
		}
		destroyTensorArray(svf,_vfSize);
	}

	for (int h=0;h<_wSize;h++)	
	{
		for (int w=0;w<_wSize;w++)
		{
			_vf[h*_wSize+w][0] /= _nSvf;
			_vf[h*_wSize+w][1] /= _nSvf;
			_vf[h*_wSize+w][2] /= _nSvf;
			_vf[h*_wSize+w][3] /= _nSvf;
		}
	}
}

int TVF::getWindowSize()
{
	return _wSize;
}
int TVF::getHalfWindowSize()
{
	return _wsHalf;
}

// wsize*wsize
int TVF::getFullSize()
{
	return _vfSize;
}

double TVF::getSigma()
{
	return _sigma;
}
TensorArray TVF::getVF()
{
	return _vf;
}


/////////////////////////////////////////
// end of class TVF

