仍然是按照教程做的一个有三关的吃豆子游戏，这个游戏比较简单创建的是win32应用程序，调用了GDI绘图库。玩家吃完地图内全部豆子则胜利，地图内安放4个干扰小人，被干扰小人吃掉则游戏结束。
### 游戏结果：
关卡1：<br>
![这里写图片描述](http://img.blog.csdn.net/20171206104803772?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvdTAxMzk0ODAxMA==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)<br>
关卡2：<br>
![这里写图片描述](http://img.blog.csdn.net/20171206104930596?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvdTAxMzk0ODAxMA==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)<br>
关卡3：<br>
![这里写图片描述](http://img.blog.csdn.net/20171206104944277?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvdTAxMzk0ODAxMA==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)
### 框架结构
![这里写图片描述](http://img.blog.csdn.net/20171206104400941?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvdTAxMzk0ODAxMA==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)<br>
>pacman:游戏主函数，控制主循环
>GMap:地图类用于创建三关的地图
>Stage_1、Stage_2、Stage3:继承自GMap，用于绘制三关的地图
>GObject:所有可移动物体父类

### GMap类
预定义地图的大小
```cpp
#define MAPLENTH 19	//逻辑地图大小
#define P_ROW 10	//我方的位置坐标
#define P_ARRAY 9	//我方的位置坐标
#define E_ROW 8		//敌方的位置坐标
#define E_ARRAY	9	//敌方的位置坐标
```
**类成员变量**
保存障碍物尺寸和豆子半径还有墙面颜色和障碍物和豆子的点阵地图
```cpp
static int LD;	//障碍物尺寸
static int PD;	//豆子半径
void InitOP();	//敌我双方出现位置没有豆子出现
bool mapData[MAPLENTH][MAPLENTH];	//障碍物逻辑地图点阵
bool peaMapData[MAPLENTH][MAPLENTH];	//豆子逻辑地图点阵
COLORREF color;	//地图中墙的颜色
```
**成员函数**
主要是三个成员函数，绘制墙面和绘制豆子，以及保存敌我双方无豆子出现
```cpp
void DrawMap(HDC &memDC);		//绘制地图
void DrawPeas(HDC &hdc);	//绘制豆子
void InitOP()	//敌我双方出现位置有没有豆子出现，初始化地图使用
{
	peaMapData[E_ROW][E_ARRAY] = false;	//敌方位置没有豆子出现
	peaMapData[P_ROW][P_ARRAY] = false;		//玩家位置没有豆子出现
}
```
>DrawPeas:遍历peaMapData调用Ellipse画圆形豆子
>DrawMap:遍历mapData调用FillRect画墙壁

### Stage_1、Stage_2、Stage3类
各自维护一个数组initData,在构造函数中用initData数组初始化豆子地图和墙面地图
```cpp
bool static initData[MAPLENTH][MAPLENTH];	//地图数据
Stage_1::Stage_1()
{
	color = RGB(140, 240, 240);								// 墙的颜色
	for (int i = 0; i < MAPLENTH; i++) {
		for (int j = 0; j < MAPLENTH; j++) {
			this->mapData[i][j] = this->initData[i][j];
			this->peaMapData[i][j] = this->initData[i][j];
		}
	}
	//敌我双方出现位置没有豆子出现
	this->InitOP();
}
```
### GObject类
预定义玩家敌人速度，移动小人的警戒范围等,枚举上下左右和游戏结束
```cpp
#define PLAYERSPEED 6	//玩家速度
#define ENERMYSPEED 4	//敌人速度
#define LEGCOUNTS	5	//敌人数量
#define DISTANCE	10	//图形范围
#define BLUE_ALERT	8	//蓝色警戒范围
#define D_OFFSET	2	//绘图误差
#define RD (DISTANCE+D_OFFSET)	//绘图范围
enum TWARDS {	//方向枚举
	UP,
	DOWN,
	LEFT,
	RIGHT,
	OVER,	//游戏结束
};
```
**成员变量：**
>当前移动物体的中心坐标
>逻辑坐标（地图数组中的下标），
>当前物体朝向
>绘制用的帧数
>移动指令（上下左右结束）
>
```cpp
int m_nX;							//实际横坐标
int m_nY;							//实际纵坐标
TWARDS m_cmd; 						// 指令缓存
POINT m_ptCenter; 					// 中心坐标
int m_nRow; 							// 逻辑横坐标
int m_nArray; 						// 逻辑纵坐标
int m_nSpeed; 						// 速度
TWARDS m_dir; 						// 朝向
int m_nFrame; 						// 祯数
```
**成员函数：**
```cpp
bool Achive();						// 判断物体是否到达逻辑坐标位置
bool Collision();						// 逻辑碰撞检测,将物体摆放到合理的位置
int PtTransform(int k); 				// 将实际坐标转换为逻辑坐标
virtual void AchiveCtrl();			// 到达逻辑点后更新m_nRow和m_nArray
void SetPosition(int Row, int Array);	// 设置位置
void DrawBlank(HDC &hdc); 			//吃掉豆子，画一个空白矩形框
void virtual Draw(HDC &hdc) = 0;		// 绘制对象
void virtual action() = 0;			// 数据变更的表现
int GetRow();		//返回横坐标m_nRow
int GetArray();		//返回纵坐标m_nArray
```
### PacManPlayer类
定义于GObject.h头文件中，是玩家类，继承自GObject类
**成员函数**
>构造函数设置玩家速度和位置
>action函数用于碰撞检测，判断下一次的方向
>IsWin遍历豆子数组，如果还存在豆子，则游戏未结束
>AchiveCtrl()重载GObject的数据更新函数，用于吃掉豆子后更新豆子数组
>draw()根据五帧画不同张嘴程度的玩家

```cpp
virtual void AchiveCtrl();			// 到达逻辑点后更新数据
POINT GetPos();
bool IsOver()	//游戏是否结束
{
	return m_dir == OVER;							// 判断游戏是否结束
}
bool IsWin();		//玩家是否赢得比赛
void Draw(HDC &hdc);						// 负责绘制自己
void SetTwCommand(TWARDS command);			// 设置玩家下一步指令
PacManPlayer(int x, int y) : GObject(x, y)		// 构造函数，产生新对象时调用
{
	this->m_nSpeed = PLAYERSPEED;			// 设置玩家速度
	m_cmd = m_dir = LEFT;					// 设置
}
void action();							// 玩家的动作函数
void SetOver();							// 设置游戏结束函数
```
### EnermyPlayer类
定义于GObject.h头文件中，是敌人类，继承自GObject类
**成员函数**
>action()函数根据碰撞检测，自动决定敌人的下一个运动方向
>Catch()敌人与玩家距离小于一个阈值时，抓到玩家，玩家结束游戏
>MakeDecision()一直向玩家方向移动
> Draw()根据颜色画一个奇奇怪怪形状的敌人

```cpp
void Catch();	//是否抓住玩家
{
	int DX = m_ptCenter.x - player->GetPos().x;
	int DY = m_ptCenter.y - player->GetPos().y;
	if ((-RD < DX && DX < RD) && (-RD < DY && DY < RD)) {
		player->SetOver();
	}
}
void virtual MakeDecision(bool b) = 0;	//AI实现，确定方向
void virtual  Draw(HDC &hdc);				// 负责绘制自己
EnermyPlayer(int x, int y) : GObject(x, y)		// 构造函数
{
	this->m_nSpeed = ENERMYSPEED;			// 设置速度
	m_dir = LEFT;							// 设置朝向
	m_cmd = UP;							// 设置移动方向
}
void virtual action()					// 负责行为
{
	bool b = Collision();											// 判断是否发生碰撞
	MakeDecision(b);												// 设定方向
	Catch();														// 开始抓捕
}
```
**成员变量**
>维护自己的颜色，以及一个玩家类的智能指针

```cpp
COLORREF color;
static std::shared_ptr<PacManPlayer> player;
```
### RedOne、BlueOne、YellowOne类
定义于GObject.h头文件中，是三个具体的敌人类
>RedOne继承自EnermyPlayer
>BlueOne、YellowOne继承自RedOne

### pacman主函数
预定义游戏窗口大小和关卡及游戏窗口句柄
```cpp
#define WLENTH 700	//高
#define WHIGHT 740	//宽
#define STAGE_COUNT 3	//一共3关
static HWND g_hwnd;	//游戏窗口句柄
```
wWinMain函数中主循环
>初始化关卡
>初始化四个敌人对象
>初始化玩家对象
>初始化敌人对象中的玩家指针（用于获取玩家位置信息）
```cpp
// 当前的关卡
int s_n = 0; // [0, 1, 2]
// 地图
GMap *MapArray[STAGE_COUNT] = { new Stage_1(), new Stage_2(), new Stage_3() };
// 玩家对象
auto g_me = std::make_shared<PacManPlayer>(P_ROW, P_ARRAY);
// 设定四个敌人对象
auto e1 = std::make_shared<RedOne>(E_ROW, E_ARRAY);			// 红色敌军对象
auto e2 = std::make_shared<RedOne>(E_ROW, E_ARRAY);			// 红色敌军对象
auto e3 = std::make_shared<BlueOne>(E_ROW, E_ARRAY);			// 蓝色敌军对象
auto e4 = std::make_shared<YellowOne>(E_ROW, E_ARRAY);			// 黄色敌军对象
// 关卡
GObject::pStage = MapArray[s_n]; 								// 初始化为第一关地图
EnermyPlayer::player = g_me;									// 用一个指针指向玩家对象
```
主游戏循环,关卡小于3并且游戏player还没被抓时循环
```cpp
while (!g_me->IsOver() && s_n < STAGE_COUNT) {
	if (g_me->IsWin()) {
		//当前关卡胜利了
		s_n++;
		if (s_n < 3) {
			//进入下一关卡
			GObject::pStage = MapArray[s_n];	
			GObject::pStage->DrawMap(hdc);					// 画地图
			continue; 									// 继续进行循环
		}else{
			//游戏结束跳出循环
			break;
		}
	}
	MapArray[s_n]->DrawPeas(hdc);					// 画豆子
	MapArray[s_n]->DrawMap(hdc);					// 画地图
	//设置四个敌军的主体
	e1->action();								// 敌军一的行为函数
	e1->DrawBlank(hdc);						// 画敌军一的空白
	e1->Draw(hdc);							// 画敌军一的主体部分
	//设置玩家，响应按键消息
	// 画自己
	g_me->DrawBlank(hdc);
	g_me->Draw(hdc);
	// 自己向前移动
	g_me->action();
    // 获取按键 : 控制自己的方向
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {	// 检测到下方向键按下
		g_me->SetTwCommand(DOWN);				// 设置下一步的移动方向为向下
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {	// 检测到左方向键按下
		g_me->SetTwCommand(LEFT); 				// 设置下一步的移动方向为向左
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {	// 检测到右方向键按下
		g_me->SetTwCommand(RIGHT); 			// 设置下一步的移动方向为向右
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000) {		// 检测到上方向键按下
		g_me->SetTwCommand(UP); 				// 设置下一步的移动方向为向上
	}
}
```
