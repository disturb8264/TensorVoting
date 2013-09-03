#if !defined ( _COMMON_H_ )
#define _COMMON_H_

#include <stddef.h>
#include <math.h>

//////////////////////////////////////////////////////
// define
typedef		double*				Tensor;
typedef		double**			TensorArray;
typedef		double**			Tarray;
typedef		double*				Matrix;

//////////////////////////////////////////////////////
// CONSTANT
#define		PI						3.14159265358979f 
#define		SIGMA_MAX		999
#define		SIGMA_MIN			0

//////////////////////////////////////////////////////
// EXCEPTION CODE
#define		E_SIGMA_OUT_OF_RANGE			-0x001
#define		E_VECTOR_OUT_OF_RANGE		-0x001

class Vector{
public:
	double v[2];
	Vector(double x=0,double y=0)
	{	
		v[0] = x;v[1] = y;	
	}

	double& operator [](int idx)
	{
		if (idx>=0 && idx<=2)
			return v[idx];
		else 
			throw E_VECTOR_OUT_OF_RANGE;
	}
};


#endif // !_COMMON_H_
