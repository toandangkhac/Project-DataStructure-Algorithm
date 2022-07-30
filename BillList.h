#pragma once
#include<iostream>
#include<string.h>
#include "DetailBillList.h"
using namespace std;

struct Date{
    short day;
    short month;
    short year;
};

Date currentTime;

void CatchTime(){
	time_t currenttime = time(NULL);
	tm* now = localtime(&currenttime);
	currentTime.day = now->tm_mday;
	currentTime.month = now->tm_mon + 1;
	currentTime.year = now->tm_year + 1900;
}

struct Bill{
    string soHD;
    Date date;
    char loai;
    DBList dscthd;
};

class BillNode{
public:
    Bill data;
    BillNode* next;
public:
    BillNode(){
    	next = NULL;
	}
};

class BillList{
public:
    BillNode* First;
    int sl;
public:
    BillList(){
    	First = NULL;
    	sl = 0;
	}
	bool Empty(){
		if(First == NULL){
			return 1;
		}
		return 0;
	}
	void Insert_HD(string sohoadon, int ngay, int thang, int nam, char loai, DBList* dscthd){
		if(First == NULL){
			First = new BillNode;
			First->data.soHD = sohoadon;
			First->data.date.day = ngay;
			First->data.date.month = thang;
			First->data.date.year = nam;
			First->data.loai = loai;
			First->data.dscthd.First = dscthd->First;
			First->data.dscthd.soluong = dscthd->soluong;
		}
		else{
			BillNode* p = First;
			while(p->next!=NULL){
				p = p->next;
			}
			BillNode* q = new BillNode;
			q->data.soHD = sohoadon;
			q->data.date.day = ngay;
			q->data.date.month = thang;
			q->data.date.year = nam;
			q->data.loai = loai;
			q->data.dscthd.First = dscthd->First;
			q->data.dscthd.soluong = dscthd->soluong;
			p->next = q;
		}
		sl++;
	}
	
	
};
