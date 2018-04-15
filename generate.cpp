#include"stdafx.h"
#include "generate.h"
#include<iostream>
#include<fstream>

#define OPERATOR 1
#define NUMBER 0

using namespace std;

generate::generate()
{
}


generate::~generate()
{
}

node* generate::creExpression(node* Nptr, int & onum) {

	int min = 0;
	int max = 0;
	if (!Nptr)  return NULL;
	//����
	Nptr->leftptr = new node;
	if ((*Nptr).operator_is_pow()) {
		setting.setOperate_pow(false);
		min = setting.getRange_min();
		max = setting.getRange_max();
		setting.setRange(setting.getRange_min(), setting.getRange_min()+10);
	}
	//��������Ŀ��δ��������
	if (onum <= setting.getOperator_account()) {
		Nptr->leftptr->geneNode(setting);                        //������������
																 //����������Ϊ������
		if (Nptr->leftptr->getType() == 1) {
			onum++;                                               //��������Ŀ��һ
			creExpression(Nptr->leftptr, onum);                      //�ݹ�����������
		}
	}
	//�������Ѵ�����
	else {
		Nptr->leftptr->setNode(NUMBER, setting);
	}

	//�ҽ��
	Nptr->rightptr = new node();
	//����������ǳ˷�
	if ((*Nptr).operator_is_pow()) {
		Nptr->rightptr->setNodePow();
	}
	//��������Ŀδ������
	else if (onum <= setting.getOperator_account()) {
		Nptr->rightptr->geneNode(setting);                        //�����ҽ������
																  //����������Ϊ������
		if (Nptr->rightptr->getType() == 1) {
			onum++;                                               //��������Ŀ��һ
			creExpression(Nptr->rightptr, onum);                      //�ݹ�����������
		}
	}
	//��������Ŀ�ﵽ����
	else {
		Nptr->rightptr->setNode(NUMBER, setting);
	}
	if ((*Nptr).operator_is_pow()) {
		setting.setOperate_pow(true);
		setting.setRange(min, max);
	}
	return Nptr;

}


void generate::addTree(node* rootptr) {
	TreeList.push_back(rootptr);
}

void generate::addExpression(Expression express)
{
	ExpressionList.push_back(express);
}


Expression generate::getExpression(node* rootptr) {

	if (!rootptr) {
		node num3;
		Expression Express;
		Express.consequence = num3;
		Express.expression = {};
		return Express;
	}//��Ȼ����������������ڵ�
	if (!rootptr->getType()) {
		Expression Express;
		Express.consequence = *rootptr;
		Express.expression = Express.consequence.num2str(setting);
		return Express;
	}
	Expression Express;
	Express.consequence = (*rootptr);

	Expression left = getExpression(rootptr->leftptr);
	if (left.consequence.getup() > MAX_NUM || left.consequence.getdown() > MAX_NUM) {
		left.consequence.setNode(NUMBER, UP, 0, OPERATE);
	}
	Expression right = getExpression(rootptr->rightptr);
	if (right.consequence.getup() > MAX_NUM || right.consequence.getdown() > MAX_NUM) {
		right.consequence.setNode(NUMBER, UP, 0, OPERATE);
	}
	//����������ַǷ�
	if (!left.consequence.judge_node()) {
		return left;
	}
	if (!right.consequence.judge_node()) {
		return right;
	}
	if ((*rootptr).operator_is_div() && right.consequence.getup()) {//����
		if (!setting.getIs_decimal() && !setting.getIs_proper_fraction()) {//��֧������
			if (left.consequence.getup() / right.consequence.getup() != (long long)(left.consequence.getup() / right.consequence.getup())) {//������
				long long makeup = ((long long)left.consequence.getup()) % ((long long)right.consequence.getup());
				makeup = (long long)right.consequence.getup() - makeup;
				node* new_operate = new node;
				node* new_number = new node;
				(*new_operate).setNode(OPERATOR, setting);
				(*new_number).setNode(NUMBER, setting);
				(*new_operate).setNode(OPERATOR, UP, DOWN, ADD);
				(*new_number).setNode(NUMBER, makeup, DOWN, NUMBER);
				(*new_operate).rightptr = new_number;
				(*new_operate).leftptr = rootptr->leftptr;
				rootptr->leftptr = new_operate;


				string c_num = setting.load(makeup);
				if (c_num == "wrong") {
					Express.consequence.setNode(NUMBER, UP, 0, OPERATE);
					return Express;
				}
				left.expression = left.expression + new_operate->transform_Operate() + c_num;
				left.consequence.setNode(NUMBER, left.consequence.getup() + makeup, DOWN, ADD);

			}
		}

	}


	Express.consequence = getValue(left.consequence, right.consequence, rootptr->getOperate());
	if (Express.consequence.getup() < 0) {
		Express.consequence.setNode(NUMBER, -Express.consequence.getup(), Express.consequence.getdown(), Express.consequence.getOperate());
		node* tem;
		tem = rootptr->leftptr;
		rootptr->leftptr = rootptr->rightptr;
		rootptr->rightptr = tem;
		str_cat(Express, right, left);
	}
	else {
		str_cat(Express, left, right);
	}

	if (setting.numbertype() == 2) {
		double tem = Express.consequence.getup();
		tem /= Express.consequence.getdown();
		Express.consequence.setNode(NUMBER, tem, DOWN, Express.consequence.getOperate());
	}
	else {
		Express.consequence.simplify();
	}


	return Express;
}
int sd = 0;
void generate::expression()
{
	fstream fileExp;
	fileExp.open("expression", ios::out);
	fstream fileConsequence;
	fileConsequence.open("consequence", ios::out);
	int i;
	for (i = 0; i < setting.getExpnumber(); i++) {
		node* rootptr = new node();
		setRootnode(rootptr, setting);
		int a = 0;
		rootptr = creExpression(rootptr, a);
		Expression exp;

		exp = getExpression(rootptr);

		if (!exp.consequence.judge_node()) {
			i--;
		}
		else if (checkrepeat(rootptr, exp) == 0) {
			addTree(rootptr);
			addExpression(exp);
		}
		sd++;
	}
	for (Expression a : ExpressionList) {
		fileExp << a.expression << endl;
		fileConsequence << a.consequence.num2str(setting) << endl;
	}

	fileExp.close();
	fileConsequence.close();
}

void generate::setRootnode(node* rootptr, Setting setting) {
	rootptr->setNode(OPERATOR, setting);
}

bool generate::checkrepeat(node* rootptr, Expression &exp) {
	for (Expression exp1 : ExpressionList) {
		if (exp1.consequence == exp.consequence)
			return true;
	}
	for (node* ptr : TreeList) {
		if (checkRepeatT(ptr, rootptr)) return true;
	}
	return false;
}

bool generate::checkRepeatT(node* ptr, node* rootptr) {
	//������������
	if (ptr == NULL && rootptr == NULL) return true;
	if (ptr == NULL || rootptr == NULL) return false;
	if (*ptr == *rootptr) {
		return checkRepeatT(ptr->leftptr, rootptr->leftptr) && checkRepeatT(ptr->rightptr, rootptr->rightptr) || checkRepeatT(ptr->leftptr, rootptr->rightptr) && checkRepeatT(ptr->rightptr, rootptr->leftptr);
	}
	else return false;
}


bool generate::set(int ExpNumber, int operator_number, int Accuracy, bool fraction, bool decimal, int min, int max, int operator_mode) {

	fstream setfile;
	setfile.open("setting", ios::out);
	//���ʽ����
	setfile << "ExpNumber:" << endl;
	if (ExpNumber > MAX || ExpNumber < 0) {
		ExpNumber = EXPNUMBER;
		setfile << "false" << endl;
	}
	else  setfile << "true" << endl;
	setfile << ExpNumber << endl;

	//����������
	setfile << "operator_number:" << endl;
	if (operator_number > OPERATOR_NUMBER || operator_number < 0) {
		operator_number = OPERATOR_NUMBER;
		setfile << "false" << endl;
	}
	else setfile << "true" << endl;
	setfile << operator_number << endl;

	//С��λ��
	setfile << "Accuracy:" << endl;
	if (Accuracy < 0 || Accuracy >3) {
		setfile << "false" << endl;
		Accuracy = ACCURACY;
		setfile << Accuracy << endl;
	}
	else {
		setfile << "true" << endl;
		setfile << Accuracy << endl;
		Accuracy = (int)pow(10, Accuracy);

	}
	//������С��������
	if (fraction && decimal) {
		setfile << "fration:" << endl;
		setfile << "false" << endl;
		fraction = false;
		setfile << "no" << endl;
		setfile << "decimal:" << endl;
		setfile << "false" << endl;
		decimal = false;
		setfile << "no" << endl;
	}

	//����
	else {
		setfile << "fraction:" << endl;
		setfile << "true" << endl;
		if (fraction) setfile << "yes" << endl;
		else setfile << "no" << endl;

		//С��
		setfile << "decimal:" << endl;
		setfile << "true" << endl;
		if (decimal) setfile << "yes" << endl;
		else setfile << "no" << endl;
	}
	//��С��Χ��
	setfile << "minnum:" << endl;
	if (min > max || min>MAX || min<0) {
		min = MIN;
		setfile << "false" << endl;
	}
	else setfile << "true" << endl;
	setfile << min << endl;

	//��Χ�����
	setfile << "maxnum:" << endl;
	if (max > MAX || max <= 0) {
		max = MAX;
		setfile << "false" << endl;
	}
	else setfile << "true" << endl;
	setfile << max << endl;

	setfile << "operator_mode:" << endl;
	//�������ʽ
	if (operator_mode < 0 || operator_mode >4) {
		operator_mode = OPERATOR_MODE;
		setfile << "flase" << endl;
		setfile << "+-*" << endl;
	}
	else {
		setfile << "true" << endl;
		switch (operator_mode) {
		case 0: setfile << "+" << endl;
			break;
		case 1: setfile << "+-" << endl;
			break;
		case 2:setfile << "+-*" << endl;
			break;
		case 3:setfile << "+-*/" << endl;
			break;
		case 4:setfile << "+-*/^" << endl;
			break;
		default:
			break;
		}
	}
	setfile << operator_mode << endl;
	setfile.close();
	setting.init(ExpNumber, operator_number, Accuracy, fraction, decimal, min, max, operator_mode);
	return true;
}






void generate::str_cat(Expression &Express, Expression left, Expression right)
{
	int size = left.expression.size() + right.expression.size();
	int judge_left = left.consequence.judge_priority(Express.consequence), judge_right = right.consequence.judge_priority(Express.consequence);

	if (judge_left < 0 && left.consequence.getOperate()) {
		size += 2;
	}
	if (judge_right != 1 && right.consequence.getOperate()) {
		size += 2;
	}

	if (judge_left < 0 && left.consequence.getOperate()) {
		Express.expression += "(";
	}
	Express.expression += left.expression;
	if (judge_left < 0 && left.consequence.getOperate()) {
		Express.expression += ")";
	}
	Express.expression += Express.consequence.transform_Operate();
	if (judge_right != 1 && right.consequence.getOperate()) {
		Express.expression += "(";
	}
	Express.expression += right.expression;
	if (judge_right != 1 && right.consequence.getOperate()) {
		Express.expression += ")";
	}
}

Setting generate::get_Setting()
{
	return setting;
}


node generate::getValue(node leftValue, node rightValue, int Operate) {//����
	switch (Operate) {
	case 1:
		return leftValue + rightValue;
	case 2:
		return leftValue - rightValue;
	case 4:
		return leftValue * rightValue;
	case 8:
		return leftValue / rightValue;
	case 16:
		return leftValue.power(rightValue);
	}
}


