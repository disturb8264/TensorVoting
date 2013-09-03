#if !defined ( _TVF_H_ )
#define	_TVF_H_

#include "Common.h"
#include "Tensor.h"

///////////////////////////////////////
// class TVF
class TVF{
private:
	// array
	TensorArray	_vf;			// 보팅 필드 데이타

	// variable
	double		_sigma;			// 보팅필드의 크기와 강도가 정해진다.
	int			_wSize;			// sigma를 이용해 얻은 보팅 필드의 너비 길이.
	int			_wsHalf;		// 너비의 반절 길이
	int			_vfSize;		// sigma를 이용해 얻은 보팅 필드의 총 크기. (wSize * wSize)
	int			_nSvf;		// ball voting field 생성시 사용할 stick voting field의 개수
protected:
	// functions
	int calcWindowSize(double sigma);
	void initVotingField();			// 스틱 보팅 필드를 회전/누적시켜 볼보팅 필드를 계산.

public:
	// constructors
	TVF(double sigma=18.0, int nSvf=32);
	~TVF();

	///////////////////////////
	// functions
	int getWindowSize();			// 새로운 보팅 필드를 만들기 위한 크기를 얻는 함수
	int getHalfWindowSize();
	int getFullSize();				// 보팅필드 배열의 총 크기 (너비*너비*차원수^2)
	double getSigma();
	TensorArray getVF();
	///////////////////////////
	// operator
	Tensor operator [](int idx) const 
	{
		return _vf[idx];
	}	
};

#endif	// !_TVF_H_