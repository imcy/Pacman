#include "stdafx.h"
#include "Stage_2.h"


//Stage_2成员定义
#define A true
#define B false
bool Stage_2::initData[MAPLENTH][MAPLENTH] = {
	B, B, B, B, B, B, B, B, B, A, B, B, B, A, B, B, B, B, B, //0
	A, A, A, A, A, A, A, B, A, A, B, A, A, A, B, A, B, A, A, //1
	B, A, A, A, B, A, A, B, A, A, B, A, B, A, B, A, B, A, B, //2
	B, B, B, A, B, A, A, B, B, A, B, A, B, A, B, A, B, B, B, //3
	B, A, A, A, A, A, A, A, A, A, A, A, B, B, B, A, A, A, B, //4
	B, A, A, B, A, A, A, A, A, A, A, A, A, A, A, A, A, A, B, //5
	B, A, A, B, A, A, A, B, B, B, B, B, B, A, A, B, A, A, B, //6
	B, A, A, B, A, B, A, A, A, A, A, A, A, A, A, B, A, A, B, //7
	B, A, A, B, A, B, A, A, B, A, B, A, A, B, A, B, A, A, B, //8
	A, A, A, B, A, B, A, A, B, B, B, A, A, B, A, B, A, A, A, //9
	B, A, A, B, A, B, A, A, A, A, A, A, A, B, A, A, A, A, B, //10
	B, A, A, B, A, A, A, B, B, B, B, B, A, B, A, A, A, A, B, //11
	B, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, B, //12
	B, A, A, A, B, B, B, B, B, B, B, A, A, A, A, A, A, A, B, //13
	B, A, A, A, A, A, A, A, A, A, A, A, A, B, A, A, A, A, B, //14
	B, B, B, B, B, A, A, A, A, B, B, B, A, B, A, A, A, A, B, //15
	B, A, A, A, B, B, B, A, A, A, A, B, A, B, B, B, A, A, B, //16
	A, A, A, A, B, A, A, A, A, A, A, B, A, A, A, B, A, A, A, //17
	B, B, B, B, B, B, B, B, B, A, B, B, B, A, B, B, B, B, B, //18
};
#undef A
#undef B
Stage_2::Stage_2()
{
	color = RGB(240, 140, 140); 								// 墙的颜色
	for (int i = 0; i < MAPLENTH; i++) {
		for (int j = 0; j < MAPLENTH; j++) {
			this->mapData[i][j] = this->initData[i][j];
			this->peaMapData[i][j] = this->initData[i][j];
		}
	}
	//敌我双方出现位置没有豆子出现
	this->InitOP();
}

Stage_2::~Stage_2()
{
}
