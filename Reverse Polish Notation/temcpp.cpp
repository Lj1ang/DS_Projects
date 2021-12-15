#include<iostream>
#include<string>
#include"header_for_test.h"
using namespace std;

Template<typename E>  class Node {
public:	
	Node* next;
	E element;// 存储内容

	Node(E input) {
		element = input;
		next = NULL;
	}
	Node(E input,Node* top) {
		element = input;
		next = top;
	}
};

Template<typename T> class Op {
public:
	Node<T>* top;
	size_t size;

	Op() {
		size = 0;
		top = NULL;
	}
	void Push(T ele) {
		top = new Node<T>(ele,top);//new returns node ptr
		size++;
	}

	T Pop() {
		if (top != NULL) {
			T it = top->element;
			Node<T>* Temptr = top->next;
			delete top;
			top = Temptr;
			size--;
			return it;	
		}
		return NULL;
	}
};
Template<typename T>class Expression {
public:
	Op<T>* opnd;
	Op<string>* optr;
	string infix_exp;
	string postfix_exp;
	string num_string;

	Expression(string input ) {
		infix_exp = input;
		opnd = new Op<T>();
		optr = new Op<string>();
		postfix_exp = "";
		num_string = "0123456789";
	}
	int Priority(string Operator){
		//.compare:return zero if equivalent
		//) have no priority
		if (!Operator.compare("+")|| !Operator.compare("-")) return 1;
		if (!Operator.compare("*") || !Operator.compare("/")) return 2;
		//if (!Operator.compare("(")) return 3;
		if (!Operator.compare("#")) return 3;//  # means single -
		return 0;
	}
	void AddToPostfixStringAndPrint(string input) {//input =op->pop()
		input += " ";
		postfix_exp += input;
		cout << input;
		
	}
	void PrintPostfixExp(){
		string Temp_num_string="";
		string sub_string = "";
		for (size_t i = 0; i < infix_exp.length(); i++) {
			//get num string
				//make the substring
			sub_string = "";
			sub_string = infix_exp.substr(i, 1);
			//cout << sub_string;//不能访问
			if (num_string.find(sub_string) == string::npos) { //is an operator
				AddToPostfixStringAndPrint(Temp_num_string);
				//cout << Temp_num_string << " ";
				Temp_num_string = "";
				if (optr->top == NULL||
					!sub_string.compare("(")||
					Priority(optr->top->element) < Priority(sub_string))//栈顶运算符优先级比当前运算符级别低则进栈)//null?
																		//( 优先级最高，故直接入栈
					optr->Push(sub_string);								//)不会是NULL， 也不会比栈顶元素优先级高
				else if(!sub_string.compare(")")){//如果是）,相等返回0，！0进入
					while (true) {
						if (optr->top->element.compare("(")) //是（ 返回0，!0进入
							AddToPostfixStringAndPrint(optr->Pop());
							//cout << optr->Pop();
						else{
							optr->Pop();//不需要加入postfix_exp
							break;
						}
							
					}
				}
				else
				{//optr栈顶出栈
					AddToPostfixStringAndPrint(optr->Pop());
					//cout << optr->Pop() << " ";
					i--;//再次对扫描到的optr进行判断
				}
			}
			else {//is an operand
				Temp_num_string += sub_string;
				//cout << sub_string << " ";
			}
		}
		//对剩余Temp_num_string进行输出
		AddToPostfixStringAndPrint(Temp_num_string);
		//cout << Temp_num_string << " ";
		//对optr剩余运算符出栈
		size_t length = optr->size;
		for (size_t i = 0; i < length; i++) {
			AddToPostfixStringAndPrint(optr->Pop());
			//cout<<optr->Pop()<<" ";
		}
	}
	int OptrToCal(string optr, string right_opnd, string left_opnd) {//传入操作符和操作数,先pop的ele在操作符右边
		//.compare:return zero if equivalent
		if (!optr.compare("+")) return stoi(left_opnd) + stoi(right_opnd);
		if (!optr.compare("-")) return stoi(left_opnd) - stoi(right_opnd);
		if (!optr.compare("*")) return stoi(left_opnd) * stoi(right_opnd);
		if (!optr.compare("/")) return stoi(left_opnd) / stoi(right_opnd);
		return NULL;
	}
	int CalPostfixExp() {
		string sub_string="";
		string Temp_num_string="";
		for (size_t i = 0; i <= postfix_exp.length(); i++) {
			//get the substring of a char at the index of i
			sub_string = postfix_exp.substr(i, 1);
			if (sub_string.compare(" ")) {//!0 if is not " " 
				if (num_string.find(sub_string) == string::npos) { //is an operator
					//opnd->Push(Temp_num_string);//operand 入栈
					
					string right_opnd = opnd->Pop();
					string left_opnd = opnd->Pop();
					int optr_to_cal = OptrToCal(sub_string, right_opnd,left_opnd);
					opnd->Push(to_string(optr_to_cal));
				}
				else
					Temp_num_string += sub_string;//加入到数字string
			}
			else if(Temp_num_string.compare("")) {
				opnd->Push(Temp_num_string);
				Temp_num_string = "";
				
			}
		}
		return stod(opnd->Pop());
	}
};


int main() {
	string myInput = "";
	cin >> myInput;
	Expression<string>* myExpression = new Expression<string>(myInput);
	myExpression->PrintPostfixExp();
	cout << "\n" << myExpression->CalPostfixExp();
	return 0;
}