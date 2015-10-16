#ifndef EVALUATEEXPRESSION_H
#define EVALUATEEXPRESSION_H

#include"define.h"
#include"SqStack.h"

#include<stdio.h>
#include<stdlib.h>

char Precede(char left, char right){
	//判断left运算符和right运算符之间的优先关系

	//运算符间的优先关系 只读
	char relation[7][7]={'>','>','<','<','<','>','>',
						 '>','>','<','<','<','>','>',
						 '>','>','>','>','<','>','>',
						 '>','>','>','>','<','>','>',
						 '<','<','<','<','<','=','0',
						 '>','>','>','>','0','>','>',
						 '<','<','<','<','<','0','='};
	switch(left){
		case '+':left=0;break;
		case '-':left=1;break;
		case '*':left=2;break;
		case '/':left=3;break;
		case '(':left=4;break;
		case ')':left=5;break;
		case '#':left=6;break;
	}
	switch(right){
		case '+':right=0;break;
		case '-':right=1;break;
		case '*':right=2;break;
		case '/':right=3;break;
		case '(':right=4;break;
		case ')':right=5;break;
		case '#':right=6;break;
	}
	return relation[left][right];
}//Precede

int Operate(int left, char ope, int right){
	//进行运算 如Operate(3,'+',4)的返回值为7
	switch(ope){
		case '+':return left+right;
		case '-':return left-right;
		case '*':return left*right;
		case '/':if(0==right) exit("ERROR"); return left/right;
	}
}//Operate

Status Check(const char *source){
	//检查source串的内容是否符合EvaluateExpression函数的要求
	//source串只能包含0-9 + - * / ( ) 字符 且括号要配对
	char *index=source;
	int bracket=0, len;
	len=strlen(source);
	while(len--){
		//判断是否有非法字符
		if(!isdigit(*index)){
			switch(*index){
				case '+':break;
				case '-':break;
				case '*':break;
				case '/':break;
				case '(':bracket++;break;	//bracket代表剩余需配对的左括号
				case ')':bracket--;break;
				default :return ERROR;
			}
		}//if
		//判断右括号是否比左括号多
		if(bracket<0) return ERROR;
		index++;
	}
	//判断所有括号是否配对完毕
	if(bracket!=0) return ERROR;
	return OK;
}

Status EvaluateExpression(char *expression, int *result){
	//计算expression表达式字符串的值 用#代表开始和结束
	//expression字符串末尾至少需要剩余一个char空间用来存放#

	if(ERROR==Check(expression)) return ERROR;

	char *index;
	index=expression+strlen(expression)+1;		//index指向e串的结束符的下一个位置
	*index='\0';					//s串结束符后移
	*--index='#';					//空出来的空间填#

	//创建运算符栈OPTR 操作数栈OPND
	//c不能使用模板 所以OPTR的数据类型是int 存取char类型运算符依赖于内置类型转换

	SqStack OPTR, OPND;
	InitStack_Sq(&OPTR);InitStack_Sq(&OPND);
	int PoundSign;
	Push_Sq(&OPTR, '#');				//OPTR栈起始符号为#

	//开始运算

	index=expression;
	GetTop_Sq(OPTR, &PoundSign);			//如果PoundSign为char类型的话就会出现不知道什么鬼的错误
	while('#'!=*index||'#'!=PoundSign){
		if(isdigit(*index)){
			int char2number=0;
			while(isdigit(*index)){
				char2number*=10;
				char2number+=*index-'0';
				index++;
			}
			Push_Sq(&OPND, char2number);
		}
		else{
		    //ope为OPTR栈顶操作符 temp无意义
		    char ope,temp;
		    GetTop_Sq(OPTR, &ope);
			switch(Precede(ope, *index)){
				//栈顶元素优先权低
				case '<':Push_Sq(&OPTR, *index);index++;break;
				//脱括号并接受下一个字符
				case '=':Pop_Sq(&OPTR, &temp);index++;break;
				//退栈并将运算结果入栈
				case '>':{
					char theta;
					int a, b;
					Pop_Sq(&OPTR, &theta);
					Pop_Sq(&OPND, &b);Pop_Sq(&OPND, &a);
					Push_Sq(&OPND, Operate(a, theta, b));
				}break;
			}//switch
		}//else
		GetTop_Sq(OPTR, &PoundSign);
	}//while
	GetTop_Sq(OPND, result);
	return OK;
}//EvaluateExpression

#endif
