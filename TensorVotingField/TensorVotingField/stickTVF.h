#if !defined ( _STICKTVF_H_ )
#define _STICKTVF_H_

#include <math.h>
#include "tensorvoting.h"
#include "tvf.h"
#include "Tensor.h"


/* 배포시 삭제할 것 */
#include <iostream>
using namespace std;

// Math Operation
Matrix	getRotationMat(double theta);
Matrix	getRotationMat(Vector uv);
Matrix	generateRectMap(int wsHalf);
Matrix	rotateRectMap(int wsHalf, Matrix rot);
Matrix	generateThetaMap(Matrix rotMap, int wsHalf);

// Generate TV Operation
double* generateRotationMatrix(double theta);
TensorArray generateStickTVF(tvf_ptr tvf, double theta);
TensorArray generateStickTVF(tvf_ptr tvf, Vector uv);
void generateDirectionMap(const tvf_ptr &tvf, TensorArray svf, Matrix thetaMap, double bTheta);
void generateDKMap(const tvf_ptr &tvf, TensorArray svf, Matrix rotMap, Matrix thetaMap);

#endif	// !_STICKTVF_H_