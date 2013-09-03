#include "Tensor.h"

double	norm(Vector v)
{
	return sqrt(pow( abs(v[0])+abs(v[1]) , 2 ));	
}

void	setTensorArrayZero(TensorArray ta,int size)
{
	for (int i=0;i<size;i++)
	{
		for (int j=0;j<4;j++) 
		{
			ta[i][j] = 0;
		}
	}
}

TensorArray	createTensorArray(int size)
{
	TensorArray _ta = new Tensor[size];
	for (int i=0;i<size;i++)
	{
		_ta[i] = new double[4];
	}
	setTensorArrayZero(_ta,size);
	return _ta;
}

void	destroyTensorArray(TensorArray ta,int size)
{
	for (int i=0;i<size;i++)
	{
		delete  [] ta[i];
	}
	delete [] ta;
	ta = NULL;
}


Matrix	divide(Matrix t, double d)
{	
	for (int i=0;i<4;i++)
		t[i] = t[i]/d;
	return t;
}
