#include "oled.h"
#include "codetab.h"
//IIC总线向OLED写命令
void OLED_WriteCmd(unsigned char IIC_Command)
{
	IIC_Write_Data(OLED_ADDRESS,0x00,IIC_Command);
}

//IIC总线向OLED写数据
void OLED_WriteDat(unsigned char I2C_Data)
{
	IIC_Write_Data(OLED_ADDRESS,0x40,I2C_Data);
}

/*
**OLED初始化
**x：非0 水平翻转使能 
**y：非0 垂直翻转使能 
*/
void OLED_Init(unsigned char x,unsigned char y)
{
	IIC_Init();
	OLED_WriteCmd(0xAE); //---显示关闭
	OLED_WriteCmd(0x20); //---显示设置内存寻址模式
	OLED_WriteCmd(0x10); //---00，水平寻址模式；01，垂直寻址模式；10，页寻址模式（重置）；11，无效	WriteCmd(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
	OLED_WriteCmd(0xb0); //---Set Page Start Address for Page Addressing Mode,0-7
	if(y)OLED_WriteCmd(0xc0); //---设置COM输出扫描方向 		/*0xc8, 0xc0垂直翻转*/
	else OLED_WriteCmd(0xc8);
	OLED_WriteCmd(0x00); //---设置低列地址
	OLED_WriteCmd(0x10); //---设置高列地址
	OLED_WriteCmd(0x40); //---设置起始行地址
	OLED_WriteCmd(0x81); //---设置对比度控制寄存器
	OLED_WriteCmd(0xff); //---亮度调节 0x00~0xff
	
	if(x)OLED_WriteCmd(0xa0); //---设置段重新映射，0~127  	/*0xa0, 0xa1水平翻转*/
	else OLED_WriteCmd(0xa1);
	OLED_WriteCmd(0xa6); //---设置正常显示
	OLED_WriteCmd(0xa8); //---设置多路复用比率（1到64）
	OLED_WriteCmd(0x3F); //
	OLED_WriteCmd(0xa4); //---0xA4，输出跟随RAM内容；0xA5，输出忽略RAM内容
	OLED_WriteCmd(0xd3); //---设置显示偏移
	OLED_WriteCmd(0x00); //---不偏移
	OLED_WriteCmd(0xd5); //---设置显示时钟分频比/振荡器频率
	OLED_WriteCmd(0xf0); //---设置分割比率
	OLED_WriteCmd(0xd9); //---设置重装载时间
	OLED_WriteCmd(0x22); //
	OLED_WriteCmd(0xda); //---设置COM针硬件配置
	OLED_WriteCmd(0x12);
	OLED_WriteCmd(0xdb); //--设置VCOMH
	OLED_WriteCmd(0x20); //0x20,0.77xVcc
	OLED_WriteCmd(0x8d); //--set DC-DC enable
	OLED_WriteCmd(0x14); //
	OLED_WriteCmd(0xaf); //--turn on oled panel
	OLED_ON();			//OLED 启动必须有OLED_ON();
	OLED_Fill(0x00);

}
//--------------------------
// function : 画点 
// 	 x			: 点的横坐标
//   y			: 点的纵坐标
//--------------------------
void OLED_SetPos(unsigned char x, unsigned char y)
{
	OLED_WriteCmd(0xb0+y);
	OLED_WriteCmd(((x&0xf0)>>4)|0x10);
	OLED_WriteCmd((x&0x0f)|0x01);
}

//--------------------------
// function : 填充 
// fill_Data: 列填充值
//--------------------------
void OLED_Fill(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		OLED_WriteCmd(0xb0+m);		//page0-page1
		OLED_WriteCmd(0x00);		//low column start address
		OLED_WriteCmd(0x10);		//high column start address
		for(n=0;n<128;n++)
		{
			OLED_WriteDat(fill_Data);
		}
	}
}

//--------------------------------------------------------------
// Description    : 将OLED从休眠中唤醒
//--------------------------------------------------------------
void OLED_ON(void)
{
	OLED_WriteCmd(0X8D);  //设置电荷泵
	OLED_WriteCmd(0X14);  //开启电荷泵
	OLED_WriteCmd(0XAF);  //OLED唤醒
}

//--------------------------------------------------------------
// Description    : 让OLED休眠 -- 休眠模式下,OLED功耗不到10uA
//--------------------------------------------------------------
void OLED_OFF(void)
{
	OLED_WriteCmd(0X8D);  //设置电荷泵
	OLED_WriteCmd(0X10);  //关闭电荷泵
	OLED_WriteCmd(0XAE);  //OLED休眠
}

//--------------------------------------------------------------
// Description    : 显示codetab.h中的ASCII字符,有6*8和8*16可选择
// Parameters     : x,y -- 起始点坐标(x:0~127, y:0~7); ch[] -- 要显示的字符串; TextSize -- 字符大小(1:6*8 ; 2:8*16)
//--------------------------------------------------------------
void OLED_ShowStr(unsigned char x, unsigned char y, char ch[], unsigned char TextSize)
{
	unsigned char c = 0,i = 0,j = 0;
	switch(TextSize)
	{
		case 1:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 126)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<6;i++)
					OLED_WriteDat(F6x8[c][i]);
				x += 6;
				j++;
			}
		}break;
		case 2:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 120)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<8;i++)
					OLED_WriteDat(F8X16[c*16+i]);
				OLED_SetPos(x,y+1);
				for(i=0;i<8;i++)
					OLED_WriteDat(F8X16[c*16+i+8]);
				x += 8;
				j++;
			}
		}break;
	}
}

//--------------------------------------------------------------
// Description    : 显示codetab.h中的汉字,16*16点阵
// Parameters     : x,y -- 起始点坐标(x:0~127, y:0~7); N:汉字在codetab.h中的索引
//--------------------------------------------------------------
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N)
{
	unsigned char wm=0;
	unsigned int  adder=32*N;
	OLED_SetPos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WriteDat(F16x16[adder]);
		adder += 1;
	}
	OLED_SetPos(x,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WriteDat(F16x16[adder]);
		adder += 1;
	}
}


//--------------------------------------------------------------
// Description    : 显示BMP位图
// Parameters     : x0,y0 -- 起始点坐标(x0:0~127, y0:0~7); x1,y1 -- 起点对角线(结束点)的坐标(x1:1~128,y1:1~8)
//--------------------------------------------------------------
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[])
{
	unsigned int j=0;
	unsigned char x,y;

  if(y1%8==0)
		y = y1/8;
  else
		y = y1/8 + 1;
	for(y=y0;y<y1;y++)
	{
		OLED_SetPos(x0,y);
    for(x=x0;x<x1;x++)
		{
			OLED_WriteDat(BMP[j++]);
		}
	}
}

#ifndef C51
unsigned char OLED_GRAM[128][8];	 
void OLED_Refresh_Gram(void)
{
	unsigned char i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WriteCmd (0xb0+i);    //设置页地址（0~7）
		OLED_WriteCmd (0x00);      //设置显示位置—列低地址
		OLED_WriteCmd (0x10);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WriteCmd(OLED_GRAM[n][i]); 
	}   

}
#endif
