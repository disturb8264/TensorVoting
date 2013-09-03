#if !defined ( _TENSORVOTING_H_ )
#define _TENSORVOTING_H_

#include "Common.h"


class TVF;
typedef TVF* tvf_ptr;


/// @brief		텐서보팅필드 객체를 생성 (모듈 사용 최초에 실행)
/// @param		simga			[in] 보팅필드의 크기와 강도를 결정하는 값.
/// @return		Reentrant를 위한 텐서보팅필드 객체를 반환
tvf_ptr createTVF(double sigma);

/// @brief		텐서보팅필드 객체를 해제 (모듈 사용 마지막에 실행)
/// @param		tvf_ptr		[in] createTVF()로 생성한 객체.
/// @return		void
void	destroyTVF(tvf_ptr tvf);

/// @brief		생성된 텐서보팅필드의 너비 길이를 반환
/// @param		tvf			[in] 너비 길이를 가져올 텐서보팅필드 객체.
/// @return		텐서보팅필드의 width를 반환
int		getTVFWindowSize(tvf_ptr tvf);

/// @brief		생성된 텐서보팅필드의 총 크기(windowSize^2)를 반환
/// @param		tvf			[in] 총 크기를 가져올 텐서보팅필드 객체.
/// @return		텐서보팅필드의 full size를 반환
int		getTVFFullSize(tvf_ptr tvf);

/// @brief		생성된 텐서보팅필드 데이터(double **)를 반환
/// @param		tvf			[in] 텐서보팅필드 데이터를 가져올 텐서보팅필드 객체.
/// @return		텐서보팅필데이터 주소를 반환
TensorArray getVotingField(tvf_ptr tvf);

/// @brief		해당 위치의 텐서(double*)를 반환
/// @param		tvf			[in] 텐서를 가져올 텐서보팅필드 객체.
/// @param		w			[in] x축 위치
/// @param		h			[in] y축 위치
/// @return		텐서주소를 반환
Tensor	getTensorElements(tvf_ptr tvf, int w, int h);

/// @brief		해당 위치의 텐서(double*)를 주어진 배열(t[])에 저장
/// @param		tvf			[in] 텐서를 가져올 텐서보팅필드 객체.
/// @param		t[]			[out] 텐서를 저장할 배열주소
/// @param		w			[in] x축 위치
/// @param		h			[in] y축 위치
/// @return		N/A
void	getTensorElements(tvf_ptr tvf, double t[], int w, int h);

/// @brief		주어진 텐서에서 고유값, 고유 백터를 추출
/// @param		t			[in] 고유값을 추출할 텐서.
/// @param		e1			[out] 1번째 고유벡터.
/// @param		e2			[out] 2번째 고유벡터
/// @param		l1			[out] 1번째 고유값.
/// @return		l2			[out] 2번째 고유값.
/// @return		N/A
void	convertTensorToEigen(Tensor t, Vector e1, Vector e2, double &l1, double &l2);

/// @brief		주어진 이진 영상을 이용해 텐서영상을 생성하고 초기화 한다.
/// @param		bImage			[in] 텐서 영상을 만들기 위한 이진 영상.
/// @param		imageSize		[in] 영상의 크기. width * height
/// @return		2차원 텐서영상을 반환
TensorArray initTensorImage(unsigned char *bImage, int imageSize);



#endif	// !_TENSORVOTING_H_