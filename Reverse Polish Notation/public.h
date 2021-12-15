#include<stdio.h>
Template<typename E>  class Node {
	Node* next;
	E element;// ´æ´¢ÄÚÈÝ
	Node(E input) {
		element = input;
	}
};
//operand statck
Template<typename T> class Opnd { 
	Node* top;
	int size;
	Opnd() {
		size = 0;
		top = NULL;
	}
	void Push(T) {
		node = new Node(T);
	}
	void Pop() {

	}
};
Template<typename T> class optr {
	Node* top;
	void Push() {

	}
	void Pop() {

	}

};
