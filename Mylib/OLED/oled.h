//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;//

/******************˵��********************
*���ߣ�����
*�汾��V 1.0
*���ڶ�ƽ̨��ֲʹ�õ�OLED
*Ŀǰ��֧��STM  C51
*����ʱ���ȵ���OLED_Init(x,y); x y�ֱ�ʹ��ˮƽ��ת�봹ֱ��ת
*����OLED_ShowStrǰ�Ƽ�ʹ��sprintfת��Ϊ�ַ���
*ʱ�䣺2020.1.14
*****************************************/

#ifndef __OLED_H
#define __OLED_H
#include "iic.h"

#define OLED_ADDRESS	0x78 //ͨ������0R����,������0x78��0x7A������ַ -- Ĭ��0x78

#define OLED_CMD 		0	//д����
#define OLED_DATA 	1	//д����

#define SIZE 				16
#define XLevelL			0x00
#define XLevelH			0x10
#define Max_Column	128
#define Max_Row			64
#define	Brightness	0xFF 
#define X_WIDTH 		128
#define Y_WIDTH 		64	    



//OLED�����ú���///////////////////////////////////////////
void OLED_WriteCmd(unsigned char I2C_Command);			// -- д����
void OLED_WriteDat(unsigned char I2C_Data);					// -- д����
void OLED_Init(unsigned char x,unsigned char y);		// -- OLED����ʼ��
void OLED_SetPos(unsigned char x, unsigned char y);	// -- ������ʼ������
void OLED_Fill(unsigned char fill_Data);						// -- ȫ�����  0xff
void OLED_ON(void);																	// -- ����
void OLED_OFF(void);																// -- ˯��
void OLED_Refresh_Gram(void);												// -- ˢ��
/*-- ��ʾ�ַ���(�����С��6*8��8*16����)****/
//ֻ��ʾ�ַ�������ʾ����
/*-- ����OLED_ShowStr(0,0,"abc",2);*/
void OLED_ShowStr(unsigned char x, unsigned char y, char ch[], unsigned char TextSize);		

/*-- ��ʾ����(������Ҫ��ȡģ��Ȼ��ŵ�codetab.h��*/
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);

/*-- ��ʾ-- BMPͼƬ*/
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);

#endif

