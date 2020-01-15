//本程序只供学习使用，未经作者许可，不得用于其它任何用途//

/******************说明********************
*作者：月祺
*版本：V 1.0
*用于多平台移植使用的OLED
*目前已支持STM  C51
*调用时请先调用OLED_Init(x,y); x y分别使能水平翻转与垂直翻转
*调用OLED_ShowStr前推荐使用sprintf转化为字符串
*时间：2020.1.14
*****************************************/

#ifndef __OLED_H
#define __OLED_H
#include "iic.h"

#define OLED_ADDRESS	0x78 //通过调整0R电阻,屏可以0x78和0x7A两个地址 -- 默认0x78

#define OLED_CMD 		0	//写命令
#define OLED_DATA 	1	//写数据

#define SIZE 				16
#define XLevelL			0x00
#define XLevelH			0x10
#define Max_Column	128
#define Max_Row			64
#define	Brightness	0xFF 
#define X_WIDTH 		128
#define Y_WIDTH 		64	    



//OLED控制用函数///////////////////////////////////////////
void OLED_WriteCmd(unsigned char I2C_Command);			// -- 写命令
void OLED_WriteDat(unsigned char I2C_Data);					// -- 写数据
void OLED_Init(unsigned char x,unsigned char y);		// -- OLED屏初始化
void OLED_SetPos(unsigned char x, unsigned char y);	// -- 设置起始点坐标
void OLED_Fill(unsigned char fill_Data);						// -- 全屏填充  0xff
void OLED_ON(void);																	// -- 唤醒
void OLED_OFF(void);																// -- 睡眠
void OLED_Refresh_Gram(void);												// -- 刷屏
/*-- 显示字符串(字体大小有6*8和8*16两种)****/
//只显示字符串不显示变量
/*-- 例如OLED_ShowStr(0,0,"abc",2);*/
void OLED_ShowStr(unsigned char x, unsigned char y, char ch[], unsigned char TextSize);		

/*-- 显示中文(中文需要先取模，然后放到codetab.h中*/
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);

/*-- 显示-- BMP图片*/
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);

#endif

