#include "GameController.h"

static const KEYCODE button_key_code[]=
{
	KEY_A,		//○
	KEY_B,		//×
	KEY_D,		//□
	KEY_C,		//△

	KEY_R1,		//R1
	KEY_R2,		//R2
	KEY_R3,		//R3

	KEY_L1,		//L1
	KEY_L2,		//L2
	KEY_L3,		//L3

	KEY_UP,		//↑
	KEY_DOWN,	//↓
	KEY_RIGHT,	//→
	KEY_LEFT,	//←
};

static const KEYCODE stick_key_code[][2]=
{
	{	KEY_AXISX,	KEY_AXISY },	//左スティック
	{	KEY_AXISX2, KEY_AXISY2 },	//右スティック
};

//押した瞬間かどうか
bool controller::GetTRG(button::button_type x, CONTROLLER_NUM num)
{
	return KEY(button_key_code[x], num) == 3;
}

bool controller::GetLeave(button::button_type x, CONTROLLER_NUM num)
{
	return KEY(button_key_code[x], num) == 2;
}

//押しているかどうか
bool controller::GetPush(button::button_type x, CONTROLLER_NUM num)
{
	return KEY(button_key_code[x], num) != 0;
}

//スティックの傾きの値を得る
Vector2 controller::GetStickValue(stick::stick_type x, CONTROLLER_NUM num)
{
	Vector2 ret(KEY(stick_key_code[x][0],num)*0.001f, KEY(stick_key_code[x][1],num)*-0.001f);
	
	//補正
	if (fabsf(ret.x)<0.3f)ret.x = 0;
	if (fabsf(ret.y)<0.3f)ret.y = 0;

	if (Vector2Length(ret) > 1)return Vector2Normalize(ret);

	return ret;
}


//指定したコントローラーを振動させる
void controller::SetVibration(RATIO power, int frame, CONTROLLER_NUM num)
{

}
