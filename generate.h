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
	vector<node*>  TreeList;       //��vector��ű��ʽָ�������//������ʲô����������֮���
	node* creExpression(node* Nptr, int &onum);                  //�ݹ�����һ�ñ��ʽ������
	bool checkrepeat(node* Nptr, Expression &exp);                           //����Ƿ��ظ�
	bool checkRepeatT(node* ptr, node* rootptr);                                 //������Ƿ��ظ�
	void addTree(node* rootptr);                            //�����ŵ�vector��
	void addExpression(Expression expression);                 //�ѱ��ʽ�ŵ�vector
	Expression getExpression(node* rootptr);        //��������õ����ʽ��ֵ
	node getValue(node left, node right, int Operate);        //����

public:
	generate();
	~generate();
	bool set(int ExpNumber, int operator_number, int Accuracy, bool fraction, bool decimal, int min, int max, int operator_mode);                         //���ò����ṹ��
	vector<Expression> ExpressionList;    //���ʽ����
	void setRootnode(node* rootptr, Setting setting);                      //���ø�������
	void expression();                   //����һϵ�б��ʽ��һ�Ѷ�����������vector��ţ�
	void str_cat(Expression &dis, Expression src1, Expression src2);  //���ʽ������
	Setting get_Setting();
};








