
#pragma once
#define NUMBER 0
#define OPERATOR 1
#define UP 0                   //Ĭ��ֵ
#define DOWN 1                //Ĭ��ֵ
#define OPERATE 0             //Ĭ��ֵ
#include"setting.h"
class node
{
private:
	int operate;                             	//����������� 0��ʾ��������� 1��ʾ+ 2��ʾ- 4��ʾ* 8��ʾ/ 16��ʾ^
	bool type;                                  //1�ǲ����� 0�ǲ�����
												//int numtype;                                 //���ò���������,����Ϊ0��С��Ϊ1�� �����Ϊ2
	float up;                                  //����
	long long  down;                                 //��ĸ

public:
	node(bool Type, int operate, double up, long long down);
	node();
	~node();
	node* leftptr;                                       //��ָ��
	node* rightptr;                                      //��ָ��
	void setNode(bool type, Setting setting);                              //���ý������,�����ɽ������
	void setNode(bool Type, double Up, long long Down, int Operate);
	void setNodePow();                                               //���ó˷����
	void geneNode(Setting setting);                                      //���ɽ�����ͣ������ɽ������
	bool getType();                                    //��ȡ�������
	double getup();                                        //��ȡ����
	long long getdown();                                        //��ȡ��ĸ
	int getOperate();                                     //��ȡ������
	bool operator_is_div();                               //�ж��Ƿ�Ϊ����
	bool operator_is_pow();                               //�ж��Ƿ�Ϊ�˷�
	bool operator==(node &num2);                          //�ж϶����Ƿ����
	node operator+(node &num2);
	node operator-(node &num2);
	node operator*(node &num2);
	node operator/(node &num2);
	node power(node &right);
	bool judge_node();                                           //�жϽ���Ƿ�Ƿ� //Ҳ���Ƿ�ĸ
	std::string num2str(Setting setting);                                             //�������ת��Ϊchar������
	int judge_priority(node node2);                           //�ж����ȼ�
	std::string transform_Operate();                                  //������ת��
	void simplify();                                            //Լ��

};

