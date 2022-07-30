#pragma once
#include<iostream>
#include<string.h>
#include "BillList.h"
using namespace std;

const int MAX_NUMBER_EMPLOYEE =  500;
 
struct Employee{
    string id;
    string HO;
    string TEN;
    bool PHAI; 
    BillList* HoaDon;
    Employee(){
    	id = "";
    	HO = "";
    	TEN = "";
    	PHAI = 0;
    	HoaDon = new BillList;
	}
	void InsertBill(string sohoadon, int ngay, int thang, int nam, char loai, DBList* dscthd){
		HoaDon->Insert_HD(sohoadon, ngay, thang, nam, loai, dscthd);
	}
};

class ListEmployee{
public:
	    int sl;
	    Employee *nhanVien[MAX_NUMBER_EMPLOYEE];
	
    	ListEmployee(){
    		sl =0;
    		for(int i = 0; i < MAX_NUMBER_EMPLOYEE; i++){
    			nhanVien[i]= NULL;
			}
		}
		void Insert_Staff(string ho, string ten, string id, bool phai){
			nhanVien[sl] = new Employee;
			nhanVien[sl]->id = id;
			nhanVien[sl]->HO = ho;
			nhanVien[sl]->TEN = ten;
			nhanVien[sl]->PHAI = phai;
			sl++;
		}
		void Insert_Staff(Employee a){
			nhanVien[sl] = new Employee;
			nhanVien[sl]->id = a.id;
			nhanVien[sl]->HO = a.HO;
			nhanVien[sl]->TEN = a.TEN;
			nhanVien[sl]->PHAI = a.PHAI;
			sl++;
		}
		int Search_MaNV(Employee *nhanVien[],string ma)
		{
			for(int i = 0 ; i < sl ;i++)
			{
				if(nhanVien[i]->id == ma)
				{
					return i;
				}
			}
			return -1;
		}
		void Delete_Staff(Employee *nhanVien[],string ma)
		{
			int t = Search_MaNV(nhanVien,ma);
			if(t < 0 || t >= sl || sl==0)
			return;
			for(int i = t  ; i < sl - 1;i++)
			{
				nhanVien[i] = nhanVien[i+1];
			(nhanVien[i]->PHAI) = (nhanVien[i+1]->PHAI);
			}
			Employee * temp = nhanVien[sl--];
			nhanVien[sl] = NULL;
			delete temp;
		}
		void Free(){
			for(int i = 0; i < sl; i++){
				delete nhanVien[i];
			}
			sl = 0;
		}
    
};
