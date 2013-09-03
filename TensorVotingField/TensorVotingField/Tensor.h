#if !defined ( _TENSOR_H_ )
#define _TENSOR_H_

#include "Common.h"

/////////////////////////////////
// Default Tensor 

double	norm(Vector v);
void	setTensorArrayZero(TensorArray ta,int size);
TensorArray	createTensorArray(int size);
void	destroyTensorArray(TensorArray ta,int size);
Tensor	divide(Tensor t, double d);

#endif // _TENSOR_H_