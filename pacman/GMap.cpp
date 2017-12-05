#include "stdafx.h"
#include "GMap.h"

int GMap::LD = 36;	//墙宽度
int GMap::PD = 3;	//豆子半径


void GMap::InitOP()
{
	peaMapData[E_ROW][E_ARRAY] = false;	//敌方位置没有豆子出现
	peaMapData[P_ROW][P_ARRAY] = false;		//玩家位置没有豆子出现
}

GMap::~GMap()
{
}
/*根据mapdata存储的墙体数据，遍历数组，发现是墙壁时绘制一个矩形模拟墙体*/
void GMap::DrawMap(HDC &memDC)
{
	HBRUSH hBrush = CreateSolidBrush(color);
	for (int i = 0; i < MAPLENTH; i++) {
		for (int j = 0; j < MAPLENTH; j++) {
			//绘制墙壁
			if (!mapData[i][j]) {
				RECT rect;
				rect.left = j * LD;
				rect.top = i * LD;
				rect.right = (j + 1) * LD;
				rect.bottom = (i + 1) * LD;
				FillRect(memDC, &rect, hBrush);	// 填充矩型区域，模拟墙体
			}
		}
	}
	DeleteObject(hBrush);							// 删除画刷对象
}

void GMap::DrawPeas(HDC & hdc)	// 画豆子函数
{
	for (int i = 0; i < MAPLENTH; i++) {				// 遍历整个数组
		for (int j = 0; j < MAPLENTH; j++) {
			if (peaMapData[i][j]) {					// 如果该处有豆子

				Ellipse(hdc, (LD / 2 - PD) + j * LD,	// 画圆：模拟豆子
					(LD / 2 - PD) + i * LD,
					(LD / 2 + PD) + j * LD,
					(LD / 2 + PD) + i * LD);
			}
		}
	}
	// 如果按下B，直接过关
	if (GetAsyncKeyState('B') & 0x8000) {
		MessageBoxA(NULL, "无意中您发现了秘笈", "", MB_OK);
		for (int i = 0; i < MAPLENTH; i++) {
			for (int j = 0; j < MAPLENTH; j++) {
				peaMapData[i][j] = false;
			}
		}
	}
}
