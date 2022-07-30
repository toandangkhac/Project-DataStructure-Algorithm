#pragma once
#define STACKSIZE 50
#define QUEUESIZE 50
template<class T>
struct node{
	T* data;
	node* next;
};
template<class T>
class Stack{
	private:
		node<T>* sp;
	public:
		Stack(){
			sp = NULL;
		}
		bool isEmpty(){
			if(sp==NULL){
				 return true;
			}
			return false;
		}
		void push(T* p){
			node<T>* temp = new node<T>();
			temp->data = p;
			temp->next = sp;
			sp = temp;
		}
		int pop(T* &p){
			if(isEmpty()){
				return 0;
			}
			node<T>* temp = sp;
			sp = temp->next;
			p = temp->data;
			delete temp;
			return 1;
		}
};
template<class T>
class Queue{
	private:
		node<T>* front;
		node<T>* rear;
	public:
		Queue(){
			front = NULL;
			rear =NULL;
		}
		bool isEmpty(){
			if(front == NULL || rear == NULL){
				return true;
			}
			return false;
		}
		void push(T* p){
			node<T>* temp = new node<T>();
			temp->data = p;
			temp->next = NULL;
			if(front == NULL){
				front = temp;
			}
			else{
				rear->next = temp;
			}
			rear = temp;
		}
		int pop(T* &p){
			if(isEmpty()){
				return 0;
			}
			node<T>* temp;
			p = front->data;
			temp = front;
			front = temp->next;
			delete temp;
			return 1;
		}
		T* getFront(){
			return front->data;
		}
};
