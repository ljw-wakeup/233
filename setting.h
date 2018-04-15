#pragma once
#include<string>
#include"stdafx.h";
using namespace std;

#define ADD 1
#define SUB 2
#define MUL 4
#define DIV 8
#define POW 16

#define EXPNUMBER 1000
#define OPERATOR_NUMBER 1000
#define ACCURACY 1
#define OPERATOR_MODE  2
#define MAX  1000
#define MIN 0

class Setting :exception
{
private:
	int expnumber;        //生成表达式的个数
	int operator_account;   //操作符数量
	int operation;                //操作符对应函数值
	bool is_proper_fraction;   //是否支持真分数运算
	bool is_decimal;           //是否支持小数运算
	int accuracy;               //精度
	int range[2];              //范围
	struct Operate {               //操作符选择//这个好烦啊
		bool add;
		bool sub;
		bool mul;
		bool div;
		bool pow;
	};
	Operate operate;
public:
	int funcOperate();
	int numbertype();
	std::string load(double number);                                       //将int 型转换成char*数组
	Setting(int ExpNumber, int operator_number, int Accuracy, bool fraction, bool decimal, int min, int max, bool Add, bool Sub, bool Mul, bool Div, bool Pow);
	int getRange_min();
	int getRange_max();
	int getAccuracy();
	int getOperator_account();
	bool getIs_proper_fraction();
	bool getIs_decimal();
	int getExpnumber();
	void init(int ExpNumber, int operator_number, int Accuracy, bool fraction, bool decimal, int min, int max, int operator_mode);
	Setting();
	void setOperate_pow(bool value);
	void setRange(int min, int max);
};




