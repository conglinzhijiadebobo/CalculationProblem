#pragma once
typedef int BOOL;
struct Variable
{
	char *val;
	int left = 0;			//1�������������������
	int right = 0;
	int ator = 0;		//1������Ϊ����
	int size = 0;
};

struct VarSq
{
	char *elem;
	int front;
	int rear;
	int maxSize;
};

//���в���
//int InitStack_Sq(VarSq &S, int size, int inc);

char OperationalCreater();				//	��������ɺ���
void NumCreater(int r, struct Variable m_VarStruct[], int x);	// �������ɺ�����rΪ��Χ������xΪ�ṹ��������
int Creater(int r);
BOOL BracketCreater(char *,int,int);		//��������,����ֵ0�޷���������
char *CalProblem(int num);