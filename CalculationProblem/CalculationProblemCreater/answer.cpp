#include "pch.h"
#include "answer.h"


//����ջ�ĳ�ʼ������
void InitNumberStack(NumberStack *numberstack) {
	numberstack->top = -1;
}

void InitOpStack(OpStack *opstack) {
	opstack->top = -1;
}


//����ջ��PUSH����
int PushNumberStack(NumberStack *numberstack, Element e) {
	if (numberstack->top == 99) {
		printf("���ֳ���\n");
		return -1;
	}
	numberstack->top++;
	numberstack->e[numberstack->top] = e;
	return 0;
}

int PushOpStack(OpStack *opstack, char c) {
	if (opstack->top == 99) {
		printf("���ų���\n");
		return -1;
	}
	opstack->top++;
	opstack->op[opstack->top] = c;
	return 0;
}


//����ջ��POP����
Element PopNumberStack(NumberStack *numberstack) {
	Element e;
	e = numberstack->e[numberstack->top];
	numberstack->top--;
	return e;
}

char PopOpstack(OpStack *opstack) {
	char c;
	c = opstack->op[opstack->top];
	opstack->top--;
	return c;
}


int JudgeOp(char c) {                //�ж��Ƿ�Ϊ�����
	if (c == '+' || c == '-' || c == -62 || c == '*' || c == '(' || c == ')' || c == '=' || c == '\n') {    //-62
		return 1;
	}
	else return 0;
}

char CompareOp(char op1, char op2) {    //���ȼ��ж�
	char c;
	switch (op2) {
	case '+':
	case '-': {
		if (op1 == '(' || op1 == '=') c = '<';
		else c = '>';
		break;
	}
	case '*':
	case -62: {
		if (op1 == '*' || op1 == -62 || op1 == ')') c = '>';
		else c = '<';
		break;
	}
	case '(': {
		if (op1 == ')') {
			printf("��������\n");
			return -1;
		}
		else c = '<';
		break;
	}
	case ')': {
		switch (op1) {
		case '(': {
			c = '=';
			break;
		}
		case '=': {
			printf("��������\n");
			return -1;
		}
		default:c = '>';
		}
		break;
	}
	case '=': {
		switch (op1) {
		case '=': {
			c = '=';
			break;
		}
		case '(': {
			printf("��������\n");
			return -1;
		}
		default: c = '>';
		}
	}
	}
	return c;
}




Element GetNumberFromStr(char s[]) {  //�Ӻ����������ַ������еó���Ӧ��ֵ 
	int flag = 0;
	int j = 0;
	int k = 0;
	char buff1[10];    //ʢ�ŷ��ӵ��ַ���
	char buff2[10];    //ʢ�ŷ�ĸ���ַ���
	Element TheNumber;
	for (int i = 0; s[i] != '\0'; i++) {
		buff1[j] = s[i];
		j++;
		if (s[i] == '/') {
			buff1[j] = '\0';
			flag = 1; continue;
		}
		if (flag == 1) {
			buff2[k] = s[i];
			k++;
		}
	}
	buff2[k] = '\0';
	switch (flag) {
	case 0:TheNumber.numerator = atoi(s); break;
	case 1: {
		TheNumber.numerator = atoi(buff1);
		TheNumber.denominator = atoi(buff2);
	}
	}
	return TheNumber;
}


int GetGreatestCommonFactor(int a, int b) {  //�����������
	int temp = 0;
	while (a != 0) {
		temp = b % a;
		b = a;
		a = temp;
	}
	return b;
}

//���㲿��
Element Add(Element e1, Element e2) {   //�ӷ�
	Element e3;
	int n = 0;
	int d = 0;
	n = e1.numerator * e2.denominator + e2.numerator * e1.denominator;
	d = e2.denominator * e1.denominator;
	int C = GetGreatestCommonFactor(n, d);   //������Ӻͷ�ĸ���������
	e3.numerator = n / C;
	e3.denominator = d / C;
	return e3;
}

Element minus(Element e1, Element e2) { //����,ǰһ���Ǳ���������һ���Ǽ���
	Element e3;
	int n = 0;
	int d = 0;
	n = e1.numerator * e2.denominator - e2.numerator * e1.denominator;
	d = e2.denominator * e1.denominator;
	int C = GetGreatestCommonFactor(n, d);
	e3.numerator = n / C;
	e3.denominator = d / C;
	return e3;
}

Element Multiply(Element e1, Element e2) {
	Element e3;
	int n = 0;
	int d = 0;
	n = e1.numerator * e2.numerator;
	d = e2.denominator * e1.denominator;
	int C = GetGreatestCommonFactor(n, d);   //������Ӻͷ�ĸ���������
	e3.numerator = n / C;
	e3.denominator = d / C;
	return e3;
}

Element Divide(Element e1, Element e2) { //������ǰһ���Ǳ���������һ���ǳ���
	Element e3;
	int n = 0;
	int d = 0;
	n = e1.numerator * e2.denominator;
	d = e1.denominator * e2.numerator;
	int C = GetGreatestCommonFactor(n, d);
	e3.numerator = n / C;
	e3.denominator = d / C;
	return e3;
}


Element CaculateOneOp(Element e1, char op, Element e2) {
	Element result;
	extern int ZEROTag;
	switch (op) {
	case '+': {
		result = Add(e1, e2);
		break;
	}
	case '-': {
		result = minus(e1, e2);
		break;
	}
	case '*': {
		result = Multiply(e1, e2);
		break;
	}
	case -62: {
		if (e2.numerator == 0)
		{
			//printf("���ܳ���0\n");
			ZEROTag = 1;
		}
		else result = Divide(e1, e2);
	}
	}
	return result;
}


Element AnAnswer(char s[40]) {     //����ó�����
	NumberStack numberstack;
	OpStack opstack;
	Element num1, num2, result, num;
	char c, sign;
	char *str = NULL;
	int count = 0;

	InitNumberStack(&numberstack);
	InitOpStack(&opstack);

	PushOpStack(&opstack, '=');
	int j = 0;
	while (s[j] != '\t') j++;
	int i = j;
	j = 0;
	c = s[i];
	while ((c != '=') || opstack.op[opstack.top] != '=') {
		if (JudgeOp(c) == 0) {
			str = (char*)malloc(sizeof(char) * 12);
			do {
				*str = c;
				str++;
				count++;
				i++;
				c = s[i];
			} while (JudgeOp(c) == 0);
			*str = '\0';
			str = str - count;
			num = GetNumberFromStr(str);
			PushNumberStack(&numberstack, num);
			str = NULL;
			count = 0;
		}
		else {    //wei 
			switch (CompareOp(opstack.op[opstack.top], c)) {
			case '<': {
				PushOpStack(&opstack, c);
				i++;
				c = s[i];
				break;
			}
			case '=': {
				sign = PopOpstack(&opstack);
				i++;
				c = s[i];
				break;
			}
			case '>': {
				sign = PopOpstack(&opstack);
				num2 = PopNumberStack(&numberstack);
				num1 = PopNumberStack(&numberstack);
				result = CaculateOneOp(num1, sign, num2);
				PushNumberStack(&numberstack, result);
				break;
			}

			}
		}
	}
	result = numberstack.e[numberstack.top];
	return result;
}

Element f_AnAnswer(char s[40]) {     //����ó�����
	NumberStack numberstack;
	OpStack opstack;
	Element num1, num2, result, num;
	char c, sign;
	char *str = NULL;
	int count = 0;

	InitNumberStack(&numberstack);
	InitOpStack(&opstack);

	PushOpStack(&opstack, '=');
	int j = 0;
	//while (s[j] != '\t') j++;
	int i = j;
	j = 0;
	c = s[i];
	while ((c != '=') || opstack.op[opstack.top] != '=') {
		if (JudgeOp(c) == 0) {
			str = (char*)malloc(sizeof(char) * 12);
			do {
				*str = c;
				str++;
				count++;
				i++;
				c = s[i];
			} while (JudgeOp(c) == 0);
			*str = '\0';
			str = str - count;
			num = GetNumberFromStr(str);
			PushNumberStack(&numberstack, num);
			str = NULL;
			count = 0;
		}
		else {    //wei 
			switch (CompareOp(opstack.op[opstack.top], c)) {
			case '<': {
				PushOpStack(&opstack, c);
				i++;
				c = s[i];
				break;
			}
			case '=': {
				sign = PopOpstack(&opstack);
				i++;
				c = s[i];
				break;
			}
			case '>': {
				sign = PopOpstack(&opstack);
				num2 = PopNumberStack(&numberstack);
				num1 = PopNumberStack(&numberstack);
				result = CaculateOneOp(num1, sign, num2);
				PushNumberStack(&numberstack, result);
				break;
			}

			}
		}
	}
	result = numberstack.e[numberstack.top];
	return result;
}




Equation *OpenAndSave(char c[800], int n) {    //���ļ�������Ŀ��������ṹ������,nΪ����
	FILE *fp;
	Equation *qu;
	char buff[50];
	int len;
	int count = 0;
	qu = (Equation*)malloc(sizeof(Equation) * n);
	if ((fp = fopen(c, "r")) == NULL) {
		printf("The file doesn't exist!\n");
		exit(0);
	}
	int j = 0;
	while (fgets(buff, 100, fp) != NULL) {
		len = strlen(buff);
		buff[len - 1] = '\0';            //ȥ�����з�
		strcpy(qu->question, buff);
		qu++;
		count++;
	}
	fclose(fp);
	qu = qu - count;
	return qu;
}

Element *ReadTheAnswer(char AnsFile[800], int n) { //���ļ������𰸴�������ṹ������
	FILE *fp;
	int time = 0;
	Element *ans;
	ans = (Element*)malloc(sizeof(Element)*n*3);
	int len;
	int count = 0;
	char buff[2000] = { 0 };	                             //��ŵ������ַ���
	char buff1[10] = { 0 };
	char buff2[10] = { 0 };                              //�ֱ��ŷ��ӷ�ĸ
	if ((fp = fopen(AnsFile, "r")) == NULL) {
		printf("The file doesn't exist!\n");
		exit(0);
	}
	while (fgets(buff, 500, fp) != NULL) {
		len = strlen(buff);
		if (len == 0) continue;
		buff[len - 1] = '\0';                     //ȥ�����з�
		int i = 0;
		int j = 0;
		int k = 0;
		while (buff[i] != '=') i++;               //ȷ����λ��,ѭ������
		if ((strlen(buff) - 1) == i)
		{
			ans->numerator = -1;
			ans->denominator = 1;
			ans++;
			count++;
			continue;
		}
		i++;
		for (i; buff[i] != '/' and buff[i] != '\0'; i++) {
			buff1[j] = buff[i];                     //************
			j++;
		}
		int temp = sizeof(buff1);
		buff1[j] = '\0';
		i++;            		//**********���ܳ���� 
		for (i; buff[i] != '\0'; i++) {
			buff2[k] = buff[i];
			k++;
		}
		buff2[k] = '\0';
		ans->numerator = atoi(buff1);
		ans->denominator = atoi(buff2);
		if (ans->denominator == 0) {
			ans->denominator = 1;
		}
		memset(buff1, 0, 10);
		memset(buff2, 0, 10);
		memset(buff, 0, 2000);
		ans++;
		count++;
	}
	ans = ans - count;
	fclose(fp);
	return ans;
}

char *OutputElement(Element e) {               //����תΪ�ַ���
	char *str;
	char buff1[30];
	char buff2[30];
	char temp[30];
	int daifenshu = 0;
	char c[3] = { '/', ' ' };
	if (e.numerator > e.denominator&&e.denominator!=1)
	{
		daifenshu = e.numerator / e.denominator;
		e.numerator = e.numerator-daifenshu * e.denominator ;
		if (e.numerator == 0)
		{
			e.numerator = daifenshu;
			e.denominator = 1;
		}
		_itoa(daifenshu,buff1, 10);
		strcat_s(buff1, strlen(buff1) + 2, "^");
		_itoa(e.numerator, temp, 10);
		strcat_s(buff1, strlen(buff1) + 1 + strlen(temp), temp);
	}
	else _itoa(e.numerator, buff1, 10);
	_itoa(e.denominator, buff2, 10);
	str = (char*)malloc(sizeof(char) * 14);
	strcpy(str, buff1);
	if (e.denominator != 1) {
		strcat(str, c);
		strcat(str, buff2);
	}
	return str;
}

void SaveAnswers(Equation *ep, int n) {    //������𰸲����浽Equation�ṹ��answer��,nΪ����
	int count = 0;
	int i = 0;
	for (i; i < n; i++) {
		ep->answer = AnAnswer(ep->question);
		ep++;
		count++;
	}
	ep = ep - count;
}

void OutputFile(Equation *ep, char c[800], int n) {   //��Equation�ṹ�е�answer������ļ�
	FILE * fp;
	int i = 1;
	int count = 0;
	if ((fp = fopen(c, "w")) == NULL) {
		printf("Can not open this file!\n");
		exit(0);
	}
	for (i; i <= n; i++) {
		char buff[10];
		char buff1[4] = { '.','\t' };
		_itoa(i, buff, 10);
		strcat(buff, buff1);
		fputs(buff, fp);
		fputs(OutputElement(ep->answer), fp);
		fputs("\n", fp);
		ep++;
		count++;
	}
	ep = ep - count;
	fclose(fp);

}

void OpenFileAndGiveTheAnswer(char *filename, int n) {  //�����ļ�������Ŀ��
	Equation* ep;
	char aFile[] = "Answers.txt";
	ep = (Equation*)malloc(sizeof(Equation) * n);
	ep = OpenAndSave(filename, n);
	SaveAnswers(ep, n);
	OutputFile(ep, aFile, n);
	//ep = NULL;
	free(ep);
}


void CompareAnswerAndGiveTheGrade(char QFile[800], char AnsFile[800], int n) {  //��ȡ�ļ�������𰸣��ֱ�Ա�
	Element *ansp;
	int count = 0;
	extern int EMPTY;
	ansp = (Element*)malloc(sizeof(Element) * n);
	ansp = ReadTheAnswer(AnsFile, n);

	Equation *ep;
	ep = (Equation*)malloc(sizeof(Equation) * n);
	ep = OpenAndSave(QFile, n);
	SaveAnswers(ep, n);

	int corrects = 0;
	int wrongs = 0;
	int *correctnumber;
	int *wrongnumber;
	correctnumber = (int*)calloc(n, sizeof(int));
	wrongnumber = (int*)calloc(n, sizeof(int));
	memset(correctnumber, 0, n);
	memset(wrongnumber, 0, n);

	int j = 0;
	int k = 0;
	for (int i = 1; i <= n; i++) {
		if ((ansp->numerator == ep->answer.numerator) and (ansp->denominator == ep->answer.denominator)) {   //����������
			corrects++;                         //��ȷ������һ
			correctnumber[j] = i;                 //��ȷ��Ŵ�������
			j++;
		}
		else {
			wrongs++;                           //����������һ
			wrongnumber[k] = i;                   //������Ŵ�������
			k++;
		}
		ansp++;
		ep++;
		count++;
	}
	ansp = ansp - count;
	ep = ep - count;
	//	free(ansp);
	//	free(ep);

	FILE * fp;
	if ((fp = fopen("Grade.txt", "w")) == NULL) {
		printf("Can not open this file!\n");
		exit(0);
	}
	char *correctline;                               //�����Ҫ����
	char *wrongline;
	correctline = (char*)calloc(2 * n*(log10(n) + 1), sizeof(char));
	wrongline = (char*)calloc(2*n*(log10(n) + 1), sizeof(char));

	char left[3] = { '(' , ' ' };
	char right[3] = { ' ', ')' };
	char mid[3] = { ',' , ' ' };
	char buff[30] = { 0 };										//buff��洢�������
	strcpy(buff, "Correct:");
	strcpy(correctline, buff);
	strcpy(buff, "Wrong:");
	strcat(wrongline, buff);
	//��һ����β
	_itoa(corrects, buff, 10);
	strcat(correctline, buff);
	strcat(correctline, left);
	for (int j = 0; j < corrects; j++) {
		_itoa(correctnumber[j], buff, 10);
		strcat(correctline, buff);
		strcat(correctline, mid);
	}
	strcat(correctline, right);
	//��һ����β�������ڶ��п�ʼ��β
	_itoa(wrongs, buff, 10);
	strcat(wrongline, buff);
	strcat(wrongline, left);
	j = 0;
	for (j; j < wrongs; j++) {
		_itoa(wrongnumber[j], buff, 10);
		strcat(wrongline, buff);
		strcat(wrongline, mid);
	}
	strcat(wrongline, right);
	
	fputs(correctline, fp);
	fputs("\n", fp);
	fputs(wrongline, fp);
	fputs("\n", fp);
	fclose(fp);
}




