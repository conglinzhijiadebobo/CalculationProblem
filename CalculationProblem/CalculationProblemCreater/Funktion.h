#pragma once

struct Variable
{
	char *val;
	int left = 0;			//1�������������������
	int ator = 0;		//1������Ϊ����
};

char OperationalCreater();				//	��������ɺ���
void NumCreater(int r, Variable m_VarStruct, int x);					// �������ɺ�����rΪ��Χ������xΪ�ṹ��������
void Creater(int r);