#include"stdafx.h"
#include "node.h"
#include <math.h>
#include<stdlib.h>
#include<time.h>

using namespace std;

node::node()
{
	type = NUMBER;
	operate = OPERATE;
	up = UP;
	down = DOWN;
}
node::node(bool Type, int Operate, double Up, long long Down)
{
	type = Type;
	operate = Operate;
	up = Up;
	down = Down;
}

node::~node()
{
}
void node::geneNode(Setting setting) {
	srand((unsigned)time(NULL));
	type = rand() % 2;
	if (type == OPERATOR) {
		int op = setting.funcOperate();
		int op1;
		do {
			op1 = (int)pow(2, rand() % 5);
		} while (!(op & op1));
		operate = op1;
		up = UP;
		down = DOWN;
	}
	else if (type == NUMBER) {
		operate = OPERATE;
		int num = setting.numbertype();
		switch (num) {
		case 0:
		{
			up = setting.getRange_min() + rand() % (setting.getRange_max() - setting.getRange_min() + 1);
			down = 1;
			break;
		}
		//真分数
		case 1:
		{
			up = setting.getRange_min() + rand() % ((setting.getRange_max() - setting.getRange_min() + 1));
			down = setting.getRange_min() + rand() % (setting.getRange_max() - setting.getRange_min() + 1);
			break;
		}
		case 2:
		{
			up = setting.getRange_min() + (double)(rand() % ((setting.getRange_max() - setting.getRange_min())*setting.getAccuracy() + 1)) / (double)setting.getAccuracy();
			down = 1;
			break;
		}
		}

	}
}
void node::setNodePow()
{
	srand((unsigned)time(NULL));
	type = NUMBER;
	operate = OPERATE;
	up = rand() % 2 + 2;
	down = DOWN;
}


void node::setNode(bool type1, Setting setting) {
	srand((unsigned)time(NULL));
	if (type1 == OPERATOR) {
		type = OPERATOR;
		int op = setting.funcOperate();
		int op1;
		do {
			op1 = (int)pow(2, rand() % 5);
		} while (!(op1 & op));
		operate = op1;
		up = UP;
		down = DOWN;
	}
	else if (type1 == NUMBER) {
		type = NUMBER;
		operate = OPERATE;
		int num = setting.numbertype();
		switch (num) {
		case 0:
		{
			up = setting.getRange_min() + rand() % (setting.getRange_max() - setting.getRange_min() + 1);
			down = 1;
		}
		//真分数
		case 1:
		{
			up = setting.getRange_min() + rand() % ((setting.getRange_max() - setting.getRange_min() + 1));
			down = setting.getRange_min() + rand() % ((setting.getRange_max() - setting.getRange_min() + 1));
		}
		case 2:
		{
			up = setting.getRange_min() + (rand() % ((setting.getRange_max() - setting.getRange_min())*setting.getAccuracy() + 1) / setting.getAccuracy());
			down = 1;
		}
		}
	}
}
void node::setNode(bool Type, double Up, long long Down, int Operate)
{
	type = Type;
	operate = Operate;
	up = Up;
	down = Down;
}


//获取结点类型 操作数为0， 操作符为1
bool node::getType() {
	return type;
}


//判断分母是否合法
bool node::judge_node()
{
	return (bool)down;
}

//操作符是否是除法
bool node::operator_is_div() {
	if (operate == 8) return true;
	return false;
}
bool node::operator_is_pow() {
	if (operate == 16) return true;
	return false;
}



//计算优先级
int node::judge_priority(node node2)
{
	if ((operate<4 && node2.operate >= 4) || (operate<16 && node2.operate == 16))
		return -1;
	else if ((node2.operate<4 && operate >= 4) || (node2.operate<16 && operate == 16)) {
		return 1;
	}
	return 0;
}

//将操作符返回成字符
string node::transform_Operate() {
	switch (getOperate()) {
	case 1:
		return "+";
	case 2:
		return "-";
	case 4:
		return "*";
	case 8:
		return "/";
	case 16:
		return "^";
	default:
		return 0;
	}
	return 0;
}

//获取操作符
int node::getOperate()
{
	return operate;
}


//int node::getNumtype()
//{
//	return numtype;
//}

long long node::getdown()
{
	return down;
}

double node::getup()
{
	return up;
}



//操作符重载
bool node::operator==(node &num2) {
	if (fabs(up - num2.up) <1e-5 && down == num2.down && type == num2.type && operate == num2.operate)
		return true;
	return false;
}


node node::operator+(node & num2)
{
	node num3;
	num3.type = NUMBER;
	num3.operate = ADD;
	//num3.numtype = numtype;
	num3.down = down * num2.down;
	num3.up = num2.down*up + num2.up*down;
	return num3;
}

node node::operator-(node & num2)
{
	node num3;
	num3.type = NUMBER;
	num3.operate = SUB;
	//num3.numtype = numtype;
	num3.down = down * num2.down;
	num3.up = num2.down*up - num2.up*down;
	return num3;
}

node node::operator*(node & num2)
{
	node num3;
	num3.type = NUMBER;
	num3.operate = MUL;
	//num3.numtype = numtype;
	num3.down = down * num2.down;
	num3.up = up * num2.up;
	return num3;
}

node node::operator/(node & num2)
{
	node num3;
	num3.type = NUMBER;
	num3.operate = DIV;
	//num3.numtype = numtype;
	num3.down = down * num2.up;
	num3.up = num2.down*up;
	return num3;
}

node node::power(node &right)
{
	node num3;
	num3.type = NUMBER;
	num3.operate = POW;
	//num3.numtype = right.getNumtype();
	num3.up = pow(up, right.up);
	if (right.down != 1) {
		num3.down = 0;
	}
	else {
		num3.down = pow(down, right.up);
	}
	return num3;
}

string node::num2str(Setting setting)
{

	string upc;
	upc = setting.load(up);
	if (upc == "wrong") {
		down = 0;
		return "wrong";
	}
	if (down == 1) {
		return upc;
	}
	else {
		string downc;
		downc = setting.load(down);
		if (downc == "wrong") {
			down = 0;
			return "wrong";
		}
		string express = upc + "//" + downc;
		return express;
	}

}

void node::simplify()
{
	if (down != 1 && up >= 0 && down) {
		long long  tem_up = up, tem_down = down;
		while (tem_up*tem_down) {
			if (tem_up >= tem_down)
				tem_up %= tem_down;
			else
				tem_down %= tem_up;
		}
		long long  GCD = abs(tem_up - tem_down);
		up /= GCD;
		down /= GCD;
	}
}



