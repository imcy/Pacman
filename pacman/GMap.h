#pragma once
#include <list>
#define MAPLENTH 19	//逻辑地图大小
#define P_ROW 10	//我方的位置坐标
#define P_ARRAY 9	//我方的位置坐标
#define E_ROW 8		//敌方的位置坐标
#define E_ARRAY	9	//敌方的位置坐标

class GMap
{
protected:
	static int LD;	//障碍物尺寸
	static int PD;	//豆子半径
	void InitOP();	//敌我双方出现位置没有豆子出现
	bool mapData[MAPLENTH][MAPLENTH];	//障碍物逻辑地图点阵
	bool peaMapData[MAPLENTH][MAPLENTH];	//豆子逻辑地图点阵
	COLORREF color;	//地图中墙的颜色
public:
	GMap()
	{

	}
	virtual ~GMap();
	void DrawMap(HDC &memDC);		//绘制地图
	void DrawPeas(HDC &hdc);	//绘制豆子
	friend class GObject;	//允许物体类使用直线的起点和终点信息做碰撞检测
	friend class PacMan;	//允许大嘴访问豆子地图
};

