#pragma once
#include<iostream>
#include<string.h>
using namespace std;

struct DetailBill{
    string MAVT;
    float Soluong;
    float Dongia;
    float VAT;
};


struct DBNode{
    DetailBill data;
    DBNode *next;
    DBNode(){
        next = NULL;
    }
};


class DBList{
public:
    DBNode *First;
    int soluong;
public:
    DBList(){
    	First = NULL;
    	soluong = 0;
	}
	void Insert_Last_DBList(string m_code, float soluong, float dongia, float vat){
		if(First == NULL){
//			First = new DBNode;
//			First->data.MAVT = m_code;
//			First->data.Soluong = soluong;
//			First->data.Dongia = dongia;
//			First->data.VAT = vat;
			DBNode* q = new DBNode;
			q->data.MAVT = m_code;
			q->data.Soluong = soluong;
			q->data.Dongia = dongia;
			q->data.VAT = vat;	
			First = q;
		}
		else{
			DBNode* p = First;
			while(p->next != NULL){
				p = p->next;
			}
			DBNode* q = new DBNode;
			q->data.MAVT = m_code;
			q->data.Soluong = soluong;
			q->data.Dongia = dongia;
			q->data.VAT = vat;
			p->next =q;
		}
		this->soluong++;
	}
	void ClearList(){
		DBNode*p;
		while(First!= NULL){
			p = First;
			First = First->next;
			delete p;
		}
	}
	void Delete_First(){
		if(First == NULL){
			return;
		}
		DBNode* p;
		p = First;
		First = First->next;
		delete p;
		soluong--;
	}
	void Delete_DBNode(DBNode* p){
		if(p == First){
			Delete_First();
		}
		else{
			DBNode* q = First;
			while(q!= NULL){
				if(q->next == p){
					break;
				}
				q = q->next;
			}
			DBNode* temp = q->next;
			q->next = temp->next;
			delete temp;
			soluong--;
		}
		
	}
};
