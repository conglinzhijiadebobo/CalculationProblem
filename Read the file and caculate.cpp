# include <stdio.h>
# include <stdlib.h>

typedef struct{             //�����ṹ�壬��ĸĬ��Ϊ1��������        
	int numerator = 0;      //����
	int denominator = 1;    //��ĸ			
}Element;                   //������ṹ��

FILE *questions = NULL;
questions = fopen( "Exercises.txt", "r" );

char questions_list[ ][30]
for(int i = 0;i < 188 ; i++){  //xiu
	char buff[30]; 
	fgets(buff, 40, (FILE*)questions);
	questions_list[i] = buff;      //���ܻ��ͷ� 
}

	
	

Element GetNumberFromStr (char a[5]){  //�Ӻ����������ַ������еó���Ӧ��ֵ 
	int flag = 0;
	int j = 0;
	int k = 0;
	char buff1[5];    //ʢ�ŷ��ӵ��ַ���
	char buff2[5];    //ʢ�ŷ�ĸ���ַ���
	Element TheNumber; 
	for(int i = 0;i < 5;i++){
		buff1[j] = a[i];
		j++;
		if (a[i] == '/') {
			flag = 1;continue;
		}
		if(flag == 1){
			buff2[k] = a[i];
			k++;
		}
	}
	switch(flag){
		case 0:TheNumber.numerator = atoi(a);break;
		case 1:{
		TheNumber.numerator = atoi(buff1);
        TheNumber.denominator = atoi(buff2);break;		
		}
		default: return ERROR;
	}
	return TheNumber;
}


int GetGreatestCommonFactor(int a, int b){  //�����������
	int temp = 0;
	while(a!=0){
        temp = b % a; 
		b = a;  
		a = temp;
	}                                     
	return b;
}


Element Add(Element e1,Element e2){   //�ӷ�
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

Element minus(Element e1,Element e2){ //����,ǰһ���Ǳ���������һ���Ǽ���
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

Element Multiply(Element e1,Element e2){
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

Element Divide(Element e1,Element e2){ //������ǰһ���Ǳ���������һ���ǳ���
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


Element AnAnswer(char s[30]){   //�ó�һ����Ŀ�Ĵ�
	Element e[4];   //�ṹ����������޷�����
	char buff[5];
	int OperatorCharacters[7];
	int flag = 0;
	int j = 0;
	int k = 0; 
	int l = 0;
	for(int i = 2; s[i] != '=';i++){
		if (s[i] == '('){
			OperatorCharacters[l] = 0;
			l++;
		}
		else if (s[i] == ')'){
			OperatorCharacters[l] = 1;
			l++;
		}    
		else if (s[i] >= 49 and s[i] <= 57 or s[i] == '/'){ //һ����λ�����ַ����飩��ʼ �������buff 
			 flag = 1;
			 buff[j] = s[i];
			 j++;  
		}
		else if(flag == 1 and (s[i] < 49 or s[i] > 57)){ //һ�� ��λ�����ַ����飩���� buff�ַ���ͨ��GetNumberFromStr()�ó���,����e[]�У���buff��� 
			flag = 0;
			j = 0;
			e[k] = GetNumberFromStr(buff);
			k++; 
		}
		else if(s[i] == '+'){
			OperatorCharacters[l] = 2;
			l++;
		}
		else if(s[i] == '-'){
			OperatorCharacters[l] = 3;
			l++;
	    }
	    else if(s[i] == '��'){
			OperatorCharacters[l] = 4;
			l++;
	   }
	    else if(s[i] == '��'){
			OperatorCharacters[l] = 5;
			l++;
	   }
	}  //�ó���e[0]��e[1]��e[2]��e[3] �Լ�������OperatorCharacters[] ���������㷨
	
}




int *TheAnswers(char a[][30], int n) {   //ͨ���ַ����������ó������� 
	int i = 0;
	for(i; i <n; i++){
		
	}
}
//fclose(questions);
