# include <stdio.h>
# include <stdlib.h>
# include <string.h>



typedef struct{             //�����ṹ�壬��ĸĬ��Ϊ1��������        
	int numerator = 0;      //����
	int denominator = 1;    //��ĸ			
}Element;                   //������ṹ��

typedef struct{
	char question[30];
	Element answer;
}Equation;

typedef struct stack1{      // ��ջ
	Element e[100];
	int top;
}NumberStack;

typedef struct stack2{       //����ջ
	char op[100];
	int top;
}OpStack;


//����ջ�ĳ�ʼ������
void InitNumberStack(NumberStack *numberstack){
	numberstack->top = -1;
}

void InitOpStack(OpStack *opstack){
	opstack->top = -1;
}


//����ջ��PUSH����
int PushNumberStack(NumberStack *numberstack, Element e){
	if(numberstack->top == 99 ){
		printf("���ֳ���\n");
		return -1;
	}
	numberstack->top++;
	numberstack->e[numberstack->top] = e;
	return 0;
}

int PushOpStack(OpStack *opstack, char c){
	if(opstack->top == 99){
		printf("���ų���\n");
		return -1;
	}
	opstack->top++;
	opstack->op[opstack->top] = c;
	return 0;
}


//����ջ��POP����
Element PopNumberStack(NumberStack *numberstack){
	Element e;
	e =  numberstack->e[numberstack->top];
	numberstack->top--;
	return e;
}

char PopOpstack(OpStack *opstack){
	char c;
	c = opstack->op[opstack->top];
	opstack->top--;
	return c;
}


int JudgeOp(char c){                //�ж��Ƿ�Ϊ�����
	if (c == '+'||c == '-'||c == -62||c == '*'|| c == '('||c == ')'||c == '='||c == '\n'){    //-62
		return 1;
	} 
	else return 0;
}

char CompareOp(char op1,char op2){    //���ȼ��ж�
	char c;
	switch(op2){
		case '+':
		case '-':{
			if(op1 == '('||op1 == '=') c = '<';
			else c = '>';
			break;
		}
		case '*':
		case -62:{
			if(op1 == '*'||op1 == -62||op1 == ')') c = '>';
			else c = '<';
            break;			
		}
		case '(':{
			if(op1 == ')'){
				printf("��������\n");
				return -1;
			}
			else c = '<';
            break;			
		}
		case ')':{
			switch(op1){
				case '(':{
					c = '=';
					break;
				}
				case '=':{
					printf("��������\n");
					return -1; 
				}
                default:c = '>';				
			}
			break;
		}
		case '=':{
			switch(op1){
				case '=':{
					c = '=';
					break;
				}
		    	case '(':{
				printf("��������\n");
				return -1;
			    }
			default: c = '>';
	    	}
	    }
    }
	return c;
}




Element GetNumberFromStr (char s[]){  //�Ӻ����������ַ������еó���Ӧ��ֵ 
	int flag = 0;
	int j = 0;
	int k = 0;
	char buff1[5];    //ʢ�ŷ��ӵ��ַ���
	char buff2[5];    //ʢ�ŷ�ĸ���ַ���
	Element TheNumber; 
	for(int i = 0;s[i] != '\0';i++){
		buff1[j] = s[i];
		j++;
		if (s[i] == '/') {
			buff1[j] = '\0';
			flag = 1;continue;
		}
		if(flag == 1){
			buff2[k] = s[i];
			k++;
		}	
	}
	buff2[k] = '\0';
	switch(flag){
		case 0:TheNumber.numerator = atoi(s);break;
		case 1:{
		TheNumber.numerator = atoi(buff1);
        TheNumber.denominator = atoi(buff2);		
		}
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

//���㲿��
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


Element CaculateOneOp(Element e1, char op, Element e2){
	Element result;
	switch(op){
		case '+':{
			result = Add(e1, e2);
			break;
		}
		case '-':{
			result = minus(e1, e2);
			break;
		}
        case '*':{
			result = Multiply(e1, e2);
			break;
		}		
		case -62:{
			if(e2.numerator == 0) printf("���ܳ���0\n");
			else result = Divide(e1, e2);
		}
	}
	return result;
}


Element AnAnswer(char s[]){
	NumberStack numberstack;
	OpStack opstack;
	Element num1,num2,result,num;
	char c,sign;
	char *str = NULL;
	int count = 0;
	
	InitNumberStack(&numberstack);
	InitOpStack(&opstack);
	
	PushOpStack(&opstack, '=');
	int j = 0;
	while(s[j] != '\t') j++;
	int i = j; 
	j = 0; 
	c = s[i];
	while((c != '=')||opstack.op[opstack.top] != '='){
		if(JudgeOp(c) == 0){
			str = (char*)malloc(sizeof(char)*11);
			do{
				*str = c;
				str++;
				count++;
				i++;
				c = s[i];
			}while(JudgeOp(c) == 0); 
			*str = '\0';
			str = str - count;
			num = GetNumberFromStr(str);
			PushNumberStack(&numberstack, num);
			str = NULL;
			count = 0;
		}
		else{    //wei 
			switch(CompareOp(opstack.op[opstack.top], c)){
				case '<':{
					PushOpStack(&opstack, c);
					i++;
					c = s[i];
					break;
				}
				case '=':{
					sign = PopOpstack(&opstack);
					i++;
					c = s[i];
					break;
				}
                case '>':{
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




Equation *OpenAndSave(char c[], int n){    //���ļ�������Ŀ��������ṹ������,nΪ����
	FILE *fp;
	Equation *qu;
	char buff[30];
	int len;
	int count;
	qu = (Equation*)malloc(sizeof(Equation) * n);
	if ((fp = fopen(c,"r")) == NULL){
		printf("The file doesn't exist!\n");
		exit(0);
	}
	while(fgets(buff,31,fp) != NULL){
	    len = strlen(buff); 
		buff[len-1] = '\0';            //ȥ�����з�
		strcpy(qu->question , buff);     
        qu++;
        count++;		
	}
	fclose(fp);
	qu = qu - count;
	return qu;
}              

char *OutputElement(Element e){         //����תΪ�ַ���
	char *str;
	char buff1[5];
	char buff2[5];
	char c[2] = {'/', ' '};
	itoa(e.numerator , buff1 , 10);
	itoa(e.denominator , buff2 , 10);
	str = (char*)malloc(sizeof(char)*11);
	strcpy(str , buff1);
	if(e.denominator != 1){
		strcat(str , c);
		strcat(str , buff2);
	}
	return str;
}

void OutputAnswers(Equation *ep, int n) {    //������𰸲����,nΪ����
	int count;
	int i = 0; 
	for(i ; i < n; i++){
		ep->answer = AnAnswer(ep->question);
		ep++;
		count++;
	}
	ep = ep - count;
	int j = 0;
	for(j ;j < n;j++){
		char *str;
		str = (char*)malloc(sizeof(char) * 11);
		str = OutputElement(ep->answer);
		printf("%s\n",str);
		ep++;
	}
}







int main(){
	char a[5] = {'1','2','3','4','5'};
	char b = -62;
	
	char s[30] = {'2','	','2','2','*','1','9','+','2','7','/','4','8','='};
	Element e1,e2;
	Equation *equationpoint;
	equationpoint = (Equation*)malloc(sizeof(Equation)*5); 
	equationpoint = OpenAndSave("e:\Question.txt",5);
	e1 = AnAnswer(s);
	//printf("%d/%d",e1.numerator,e1.denominator);
	OutputAnswers(equationpoint,4);
	//printf("%s",OutputElement(e1));
	/*for(int i = 0;i < 5;i++){
		printf("%s\n",equationpoint->question);
		equationpoint++;
	}*/
	
}
