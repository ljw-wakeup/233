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
	int expnumber;        //���ɱ��ʽ�ĸ���
	int operator_account;   //����������
	int operation;                //��������Ӧ����ֵ
	bool is_proper_fraction;   //�Ƿ�֧�����������
	bool is_decimal;           //�Ƿ�֧��С������
	int accuracy;               //����
	int range[2];              //��Χ
	struct Operate {               //������ѡ��//����÷���
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
	std::string load(double number);                                       //��int ��ת����char*����
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




