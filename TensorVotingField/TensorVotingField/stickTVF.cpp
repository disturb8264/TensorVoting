#include "stickTVF.h"

Matrix	getRotationMat(double theta)
{
	Matrix rot = new double[4];
	rot[0] = cos(theta);
	rot[1] = sin(theta);
	rot[2] = -sin(theta);
	rot[3] = cos(theta);
	return rot;
}

Matrix	getRotationMat(Vector uv)
{
	Matrix rot = new double[4];
	double l = norm(uv);
	rot[0] = uv[0]/l;
	rot[1] = uv[1]/l;
	rot[2] = -uv[1]/l;
	rot[3] = uv[0]/l;	
	rot = divide(rot,norm(uv));
	return rot;
}


Matrix generateRectMap(int wsHalf)
{
	int wsize = wsHalf*2+1;	

	Matrix rectMap = new double[wsize * wsize *2];	
	int pitch = 2*wsize;
	// X direction
	for (int y=0;y<wsize;y++)
	{
		int k = -wsHalf;
		for (int x=0;x<wsize;x++)
		{			
			rectMap[y*pitch+2*x] = k++;
		}
	}	
	// Y direction
	for (int x=0;x<wsize;x++)
	{
		int k = wsHalf;
		for (int y=0;y<wsize;y++)
		{			
			rectMap[y*pitch+2*x+1] = k--;
		}
	}
	return rectMap;
}


Matrix rotateRectMap(int wsHalf, Matrix rot)
{
	
	int wsize = wsHalf*2+1;
	Matrix rectMap = generateRectMap(wsHalf);
	Matrix rotMap = new double[wsize * wsize *2];

	for (int y=0;y<wsize;y++)
	{
		for (int x=0;x<wsize;x++)
		{
			int position = (y*wsize*2)+(x*2);
			rotMap[position+0] = rot[0]*rectMap[position+0] + rot[1]*rectMap[position+1];	// X
			rotMap[position+1] = rot[2]*rectMap[position+0] + rot[3]*rectMap[position+1]; // Y
		}
	}
	return rotMap;
}

Matrix generateThetaMap(Matrix rotMap, int wsHalf)
{ 
	int wsize = wsHalf*2+1;
	Matrix thetaMap = new double[wsize*wsize];
	for (int y=0;y<wsize;y++)
	{
		for (int x=0;x<wsize;x++)
		{
			int position = (y*wsize*2)+(x*2);
			thetaMap[y*wsize+x] = atan2(rotMap[position+1],rotMap[position]);
		}
	}
	return thetaMap;
}


double* generateRotationMatrix(double theta)
{		
	double rot[4];
	rot[0] = cos(theta);
	rot[1] = sin(theta);
	rot[2] = -sin(theta);
	rot[3] = cos(theta);
	return rot;
}

TensorArray generateStickTVF(tvf_ptr tvf, double theta )
{
	double sigma = tvf->getSigma();
	int w=tvf->getWindowSize();
	int wh = tvf->getHalfWindowSize();
	TensorArray svf = createTensorArray(tvf->getFullSize());	 

	Matrix mRotation = getRotationMat(theta);	
	Matrix rotMap = rotateRectMap(wh,mRotation);	
	Matrix thetaMap = generateThetaMap(rotMap,wh);

	generateDirectionMap(tvf,svf,thetaMap,theta);
	generateDKMap(tvf,svf,rotMap,thetaMap);
	return svf;
}

TensorArray generateStickTVF(tvf_ptr tvf, Vector uv)
{	
	double sigma = tvf->getSigma();
	int w=tvf->getWindowSize();
	int wh = tvf->getHalfWindowSize();
	double theta = atan2(uv[1],uv[0]);	
	TensorArray svf = createTensorArray(tvf->getFullSize());	

	Matrix mRotation = getRotationMat(uv);
	Matrix rotMap = rotateRectMap(wh,mRotation);	
	Matrix thetaMap = generateThetaMap(rotMap,wh);

	generateDirectionMap(tvf,svf,thetaMap,theta);
	generateDKMap(tvf,svf,rotMap,thetaMap);
	return svf;
}

void generateDirectionMap(const tvf_ptr &tvf, TensorArray svf, Matrix thetaMap, double bTheta)
{
	
	int w=tvf->getWindowSize();
	int wh = tvf->getHalfWindowSize();

	TensorArray T1 = createTensorArray(tvf->getFullSize());	 
	TensorArray T2 = createTensorArray(tvf->getFullSize());	 
	TensorArray T3 = createTensorArray(tvf->getFullSize());	 
	TensorArray T4 = createTensorArray(tvf->getFullSize());	 
	
	for (int i=0;i<w;i++)
	{
		for (int j=0;j<w;j++)
		{
			for (int k=0;k<4;k++)
			{
				T1[i*w+j][k] = -sin(2*thetaMap[i*w+j]+bTheta);
				T2[i*w+j][k] = cos(2*thetaMap[i*w+j]+bTheta);
				T3[i*w+j][k] = T1[i*w+j][k];
				T4[i*w+j][k] = T2[i*w+j][k];		
			}		
			T1[i*w+j][1] = 1;
			T1[i*w+j][3] = 1;	//	T1(:,:,2,1:2) = 1;			
			T2[i*w+j][0] = 1;
			T2[i*w+j][1] = 1;	//	T2(:,:,1:2,1) = 1;
			T3[i*w+j][2] = 1;
			T3[i*w+j][3] = 1;	//	T3(:,:,1:2,2) = 1;			
			T4[i*w+j][0] = 1;
			T4[i*w+j][2] = 1;	//	T4(:,:,1,1:2) = 1;	
			//  stickT = T1.*T2.*T3.*T4;
			for (int k=0;k<4;k++)
			{
				svf[i*w+j][k] = abs(T1[i*w+j][k] * T1[i*w+j][k] * T3[i*w+j][k] * T4[i*w+j][k]);
			}
		}
	}
}

void generateDKMap(const tvf_ptr &tvf, TensorArray svf, Matrix rotMap, Matrix thetaMap)
{	
	double sigma = tvf->getSigma();
	int w=tvf->getWindowSize();
	int wh = tvf->getHalfWindowSize();
	double c = (-16*(log(0.1)/log(2))*(sigma-1))/(pow(PI,2));
	double* DK = new double[tvf->getFullSize()];
	
	// thetaMap
	for (int i=0;i<w;i++)
	{
		for (int j=0;j<w;j++)
		{
			thetaMap[i*w+j] = abs(thetaMap[i*w+j]);			
			if (thetaMap[i*w+j]  > PI/2)
			{
				thetaMap[i*w+j] = PI - thetaMap[i*w+j];
			}
		    thetaMap[i*w+j] = 4*thetaMap[i*w+j];		
		}
	}
	
	for (int i=0;i<w;i++)
	{
		for (int j=0;j<w;j++)
		{
			int position = (i*w*2)+(j*2);
			double c = (-16*log(0.1)*(sigma-1))/pow(PI,2);
			double th = thetaMap[i*w+j];
			if (th>PI/2)
			{
				DK[i*w+j] = 0;
			}
			else
			{
				double length = sqrt(pow(rotMap[position],2)+pow(rotMap[position+1],2));	
				double arcLength = (length*th)/sin(th);
				if (th==0 || length==0)
					arcLength = length;
				
				double curv = (2*sin(th))/length;
				if (length==0)
					curv = 0;
									
				DK[i*w+j] = exp( -( pow(arcLength,2) + (c*pow(curv,2)) ) / (pow(sigma,2)) );
								
				if (_isnan(DK[i*w+j])!=0)
				{
					throw _NANCODE;
				}				
			}
			
			for (int k=0;k<4;k++)
			{
				svf[i*w+j][k] *= DK[i*w+j];
			}
		}
	}
}