#pragma once
#include<vector>
#include"node.h"
#define MAX_NUM 100000000


using namespace std;

typedef struct Expression {
	string expression;
	node  consequence;
}Expression;


class generate
{
private:
	Setting setting;
	vector<node*>  TreeList;       //用vector存放表达式指针的数组//或者用什么其它的链表之类的
	node* creExpression(node* Nptr, int &onum);                  //递归生成一棵表达式二叉树
	bool checkrepeat(node* Nptr, Expression &exp);                           //检查是否重复
	bool checkRepeatT(node* ptr, node* rootptr);                                 //检查树是否重复
	void addTree(node* rootptr);                            //把树放到vector中
	void addExpression(Expression expression);                 //把表达式放到vector
	Expression getExpression(node* rootptr);        //中序遍历得到表达式和值
	node getValue(node left, node right, int Operate);        //计算

public:
	generate();
	~generate();
	bool set(int ExpNumber, int operator_number, int Accuracy, bool fraction, bool decimal, int min, int max, int operator_mode);                         //设置参数结构体
	vector<Expression> ExpressionList;    //表达式数组
	void setRootnode(node* rootptr, Setting setting);                      //设置根结点参数
	void expression();                   //创建一系列表达式（一堆二叉树，并用vector存放）
	void str_cat(Expression &dis, Expression src1, Expression src2);  //表达式的链接
	Setting get_Setting();
};








