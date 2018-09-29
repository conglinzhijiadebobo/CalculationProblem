#pragma once



typedef struct {             //�����ṹ�壬��ĸĬ��Ϊ1��������        
	int numerator = 0;      //����
	int denominator = 1;    //��ĸ			
}Element;                   //������ṹ��

typedef struct {
	char question[40] = { 0 };
	Element answer;
}Equation;

typedef struct stack1 {      // ��ջ
	Element e[10];
	int top;
}NumberStack;

typedef struct stack2 {       //����ջ
	char op[10];
	int top;
}OpStack;

char CompareOp(char op1, char op2);   //���ȼ��ж�
Element GetNumberFromStr(char s[]);	 //�Ӻ����������ַ������еó���Ӧ��ֵ 
int GetGreatestCommonFactor(int a, int b); //�����������


Element f_AnAnswer(char s[40]); //����ó�����
Element AnAnswer(char s[40]); //����ó�����
Equation *OpenAndSave(char c[800], int n);  //���ļ�������Ŀ��������ṹ������,nΪ����

Element *ReadTheAnswer(char AnsFile[800], int n);//���ļ������𰸴�������ṹ������

void OutputFile(Equation *ep, char c[], int n);   //��Equation�ṹ�е�answer������ļ�
void OpenFileAndGiveTheAnswer(char *filename, int n);	//�����ļ�������Ŀ��


void CompareAnswerAndGiveTheGrade(char QFile[800], char AnsFile[800], int n); //��ȡ�ļ�������𰸣��ֱ�Ա�