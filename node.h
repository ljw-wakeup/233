
#pragma once
#define NUMBER 0
#define OPERATOR 1
#define UP 0                   //默认值
#define DOWN 1                //默认值
#define OPERATE 0             //默认值
#include"setting.h"
class node
{
private:
	int operate;                             	//运算符的类型 0表示不是运算符 1表示+ 2表示- 4表示* 8表示/ 16表示^
	bool type;                                  //1是操作符 0是操作数
												//int numtype;                                 //设置操作数类型,整数为0，小数为1， 真分数为2
	float up;                                  //分子
	long long  down;                                 //分母

public:
	node(bool Type, int operate, double up, long long down);
	node();
	~node();
	node* leftptr;                                       //左指针
	node* rightptr;                                      //右指针
	void setNode(bool type, Setting setting);                              //设置结点类型,并生成结点数据
	void setNode(bool Type, double Up, long long Down, int Operate);
	void setNodePow();                                               //设置乘方结点
	void geneNode(Setting setting);                                      //生成结点类型，并生成结点数据
	bool getType();                                    //获取结点类型
	double getup();                                        //获取分子
	long long getdown();                                        //获取分母
	int getOperate();                                     //获取操作符
	bool operator_is_div();                               //判断是否为除法
	bool operator_is_pow();                               //判断是否为乘方
	bool operator==(node &num2);                          //判断对象是否相等
	node operator+(node &num2);
	node operator-(node &num2);
	node operator*(node &num2);
	node operator/(node &num2);
	node power(node &right);
	bool judge_node();                                           //判断结点是否非法 //也就是分母
	std::string num2str(Setting setting);                                             //将真分数转化为char型数组
	int judge_priority(node node2);                           //判断优先级
	std::string transform_Operate();                                  //操作符转换
	void simplify();                                            //约分

};

