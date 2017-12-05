#pragma once
#include "GMap.h"
/*第一关地图设计*/
class Stage_1 :
	public GMap
{
public:
	Stage_1();
	~Stage_1();
private:
	bool static initData[MAPLENTH][MAPLENTH];	//地图数据
};

