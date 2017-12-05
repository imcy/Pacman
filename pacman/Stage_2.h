#pragma once
#include "GMap.h"
/*第二关地图设计*/
class Stage_2 :
	public GMap
{
public:
	Stage_2();
	~Stage_2();
private:
	bool static initData[MAPLENTH][MAPLENTH];	//地图数据
};

