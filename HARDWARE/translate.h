#ifndef	_translate_H
#define	_translate_H
/****************************************************************************
* Function Name :   translate.h
* Description   :   5Ƶ���������Ʋ�����ȫ�������ϴ�����
* Input         ��
* Output        ��
*****************************************************************************/
#include   "public.h"

void transdata(uint8_t row,uint8_t col);
void transdata_point(uint8_t p);
void transdata_reverse(uint8_t row,uint8_t col);
void transdata_t(uint8_t row,uint8_t col);
void transdata_point_t(uint8_t p,uint8_t row,uint8_t col);

#endif
