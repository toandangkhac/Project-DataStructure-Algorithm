#pragma once
#include<iostream>
#include<string.h>
using namespace std;
 
struct Material{
    string MaVT;
    string TenVT;
    string DVTinh;
    float SLTon;
    Material(){
    	MaVT = "";
    	TenVT = "";
    	DVTinh = "";
    	SLTon = 0;
	}
};

struct MaterialNode{
    string key;
    Material data;
    MaterialNode *left;
    MaterialNode *right;
	bool check = false;	
};

class MaterialBST{
public:
	int soluong;
    MaterialNode *root;
    MaterialNode *rp;// con tro tro den vi tri muon xoa
    MaterialBST(){
    	root = NULL;
    	rp = NULL;
    	soluong = 0;
	}
    void Insert_Material(MaterialNode* &p, string Key, Material Data){
    	if(p == NULL){
    		p = new MaterialNode();
    		p->key = Key;
    		p->data = Data;
    		p->left = NULL;
    		p->right = NULL;
    		soluong++;
		}
		else{
			if(Key > p->key){
				Insert_Material(p->right, Key, Data);
			}
			if(Key < p->key){
				Insert_Material(p->left, Key, Data);
			}
		}
	}
	void Insert_Material(MaterialNode* &p, Material Data){
    	if(p == NULL){
    		p = new MaterialNode();
    		p->key = Data.MaVT;
    		p->data = Data;
    		p->left = NULL;
    		p->right = NULL;
    		soluong++;
		}
		else{
			if(Data.MaVT > p->key){
				Insert_Material(p->right, Data);
			}
			if(Data.MaVT < p->key){
				Insert_Material(p->left, Data);
			}
		}
	}
	void Insert_Material(MaterialNode* &p, string m_code, string m_name, string m_unit, float m_quantity){
    	if(p == NULL){
    		p = new MaterialNode();
    		p->key = m_code;
    		p->data.MaVT = m_code;
    		p->data.TenVT = m_name;
    		p->data.DVTinh = m_unit;
    		p->data.SLTon = m_quantity;
    		p->left = NULL;
    		p->right = NULL;
    		soluong++;
		}
		else{
			if(m_code > p->key){
				Insert_Material(p->right, m_code, m_name, m_unit, m_quantity);
			}
			if(m_code < p->key){
				Insert_Material(p->left, m_code, m_name, m_unit, m_quantity);
			}
		}
	}
	bool Empty(){
		if(root == NULL){
			return true;
		}
		return false;
	}
	MaterialNode* Search_Material(MaterialNode* &p,string Key)
	{
		MaterialNode* tam = p;
		while(tam!=NULL)
		{
			if(tam->key > Key)
			{
				tam = tam->left;
			}
			else if(tam->key < Key)
			{
				tam = tam->right;
			}
			else
			{
				return tam;
			}
		}
		return NULL;
	}
	void Remove_case3(MaterialNode* &r){
		if(r->left!=NULL){
			Remove_case3(r->left);
		}
		else{
			rp->key = r->key;
			rp->data = r->data;
			rp = r;
			r = rp->right;
		//	soluong--;
		}
		
	}
	void Delete_Material(MaterialNode* &p, string Key){// xoa theo khoa, khoa dang la mavattu nen ham nay la xoa theo ma
		if(p == NULL){
//			cout << "Khong tim thay"; ///////////////////// phai sua lai khi chuyen qua lam viec tren man hinh do hoa;
			
		}
		else{
			if(Key > p->key){
				Delete_Material(p->right, Key);
			}
			else if(Key < p->key){
				Delete_Material(p->left, Key);	
			}
			else{
				rp = p;
				if(rp->right == NULL){
					p = rp->left;
				}
				else if( rp->left == NULL){
					p = rp->right;
				}
				else{
					Remove_case3(rp->right);
				}
				delete rp;
				soluong--;
			}
		}
	}
	
	void Free(MaterialNode* &p){
		while(p!= NULL){
			if(p->left == NULL && p->right == NULL){
				rp = p;
				delete rp;
			}
			if(p->left!=NULL){
				Free(p->left);
			}
			if(p->right != NULL){
				Free(p->right);
			}
		}
		soluong = 0;
	}	
};	




