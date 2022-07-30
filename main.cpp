#include <graphics.h> 
#include<iostream>
#include "GraphicsUserInterface.h"
#include "BillList.h"
#include "DetailBillList.h"
#include "EmployeeList.h"
#include "MaterialBST.h"
#include "CTDL.h"
#include<stdlib.h>
#include<stdio.h>
#include<fstream>
using namespace std;
const int MAX_STAFF=500;
const int MAX = 50;
class QuitButton{
	public:
		Button<QuitButton> quitButton;
	public: 
		QuitButton(){
			quitButton = Button<QuitButton>(1800, tab_height/2+2, 150, 34, tab_basic_color, RED, "THOAT", &QuitButton::Quit);
		}  
		
		void Quit(){
			
			isActive = false;
		}
		
};
MaterialNode* mNodeToSelect;
Employee* employeeToSelect;
class MaterialTab: public Tab{ 
	private: 
		enum MATERIAL_TAB_STATE{ADD,EDIT,PRINT,EMPTY,SEARCH};//  Trang thai cua so lam viec
		MATERIAL_TAB_STATE state;// bien luu trang thai dang lam viec
		InputField* fieldPointer;// con tro doi tuong co vai tro ve ra khung de nhap du lieu
		Button<MaterialTab> addButton, searchButton;//,editButton, printButton;// cac nut chuc nang;//,searchButton;
		InputField info[4];// name, unit, quantity, material code
		InputField text;
		Button<MaterialTab> save, close; // nut chuc nang
		// Cua so edit
		Button<MaterialTab> deleteButton, saveChange,search,findCode;
		Button<MaterialTab> nextPage, previousPage;
		int stt;// so thu tu de in danh sach
		MaterialNode* currentNode;
		MaterialNode* nodeNeedEdit;
		int pageNumber;
		bool isok0 = true;//kiem tra xem du lieu nhap co rong hay khong 
		bool isok = true;//kiem tra ma vat tu co trung khong
		bool initedit = false;
		int currentPageNumber;
		int cnt,dem;// bien vi tri cua mang con tro par
		MaterialNode *DanhsachVatTu[MAX];// khai bao mang con tro vat tu
		char *search_code= new char[11];
		
		InputField code;// ve ra khung de nhap  
		char *m_code = new char[11];	
		char *m_name = new char[41];  
		char *m_unit = new char[21];
		
		char *m_quantity = new char[11];
		char *codematerial = new char[11];
	public:
		//DATA
		MaterialBST* CayVatTu; 
		void Previous(){
			if(currentPageNumber > 1){
				currentPageNumber--;
			}	
		}
		void Next(){
			if(currentPageNumber < pageNumber){
				currentPageNumber++;
			}
		}
		void Reset(){ // lam trong toan bo
			fieldPointer = NULL;
			info[0].BlankField(); 
			info[1].BlankField();
			info[2].BlankField();
			info[3].BlankField();  
			code.BlankField(); 
		} 
		void Select(){
			mNodeToSelect = currentNode;
		}
		void InitAddMaterial(){
			Reset(); 
			state = ADD; 
			//fieldPointer = &info[0]; 
		}  
		void InitPrint(){
			Reset();
			state = PRINT;
		} 
		void InitSearch()
		{
			Reset();
			state = SEARCH;
		}
		void InitEdit(){
			Reset();
			state = EDIT;
			fieldPointer= &info[0];
		}
		void AddMaterialAction(){
			DrawInputWindow("Nhap thong tin vat tu");
			info[0].Action(fieldPointer);
			
			if(!info[0].CheckString()){
				isok0 = false;
			}
			info[1].Action(fieldPointer);
			if(!info[1].CheckString()){
				isok0 =false;
			}
			info[2].Action(fieldPointer);
			if(!info[2].CheckString())
			{
				isok0 = false;
			}
			info[3].Action(fieldPointer);
			if(!info[3].CheckString())
			{
				isok0 = false;
			}
			MaterialNode* ad = CayVatTu->Search_Material(CayVatTu->root,toString(m_code));
			if(ad!=NULL)
			{
				info[3].Announcement("Da ton tai vat tu!!",false);
				isok = false;
			}
			else
				isok = true;
			save.Action(this);
			close.Action(this);
		}
		void DisplayMaterialTheoName(MaterialNode* a, int x1, int x2, int x3, int x4, int x5, int y)
		{
			int leTrai  = 200;
			int lePhai = 1720;
			int leTren = 110;
			int height = 32;
			Button<MaterialTab> edit(1640,y + 15, textwidth("edit"), textheight("edit"), WHITE, addbutton_oncolor, "edit", &MaterialTab::Edit, BLACK);
			
			setcolor(BLACK);
			setbkcolor(smallwindow_bg_color);
			outtextxy(x1,y,(char*)toString(++stt).c_str());
			outtextxy(x2,y,(char*)toString(a->data.MaVT).c_str());
			outtextxy(x3,y,(char*)toString(a->data.TenVT).c_str());
			outtextxy(x4,y,(char*)toString(a->data.DVTinh).c_str());
			outtextxy(x5,y,(char*)toString(a->data.SLTon).c_str());
			currentNode = a;
			edit.Action(this);
		}
		void DisplayListMaterial(MaterialNode *DanhSachVatTu[])
		{
			int leTrai  = 200;
			int lePhai = 1720;
			int leTren = 110;
			int height = 32;
			if(search_code[0]=='\0')
			{
					for(int i = 0 ; i < cnt; i++)
						{
							if((stt >= 0 + (currentPageNumber-1)*25&& stt <= 24 +(currentPageNumber-1)*25))//&&(p->key==toString(search_code)))
								{
											DisplayMaterial(DanhsachVatTu[i], leTrai + 45, leTrai + 25 + 100, leTrai + 25 + 300, leTrai + 110 + 900 - textwidth((char*)toString(DanhsachVatTu[i]->data.DVTinh).c_str())/2, leTrai + 130 + 1100 - textwidth((char*)
									toString(DanhsachVatTu[i]->data.SLTon).c_str())/2, leTren + 34 + height/2 + (stt%25)*height);
								}
							else{
									stt++;
								}
					}
			}
			else
			{
				for(int i = 0 ; i < cnt; i++)
				{
					if(search_code==DanhsachVatTu[i]->data.MaVT)
					{
							DisplayMaterial(DanhsachVatTu[i], leTrai + 45, leTrai + 25 + 100, leTrai + 25 + 300, leTrai + 110 + 900 - textwidth((char*)toString(DanhsachVatTu[i]->data.DVTinh).c_str())/2, leTrai + 130 + 1100 - textwidth((char*)
									toString(DanhsachVatTu[i]->data.SLTon).c_str())/2, leTren + 34 + height/2 + (stt%25)*height);
					}
				}
			}
		}
			void DisplayListMaterialToSelect(MaterialNode *DanhSachVatTu[])
		{
			int leTrai  = 200;
			int lePhai = 1720;
			int leTren = 110;
			int height = 32;
			if(search_code[0]=='\0')
			{
					for(int i = 0 ; i < cnt; i++)
						{
							if((stt >= 0 + (currentPageNumber-1)*25&& stt <= 24 +(currentPageNumber-1)*25))//&&(p->key==toString(search_code)))
								{
											DisplayMaterialToSelect(DanhsachVatTu[i], leTrai + 45, leTrai + 25 + 100, leTrai + 25 + 300, leTrai + 110 + 900 - textwidth((char*)toString(DanhsachVatTu[i]->data.DVTinh).c_str())/2, leTrai + 130 + 1100 - textwidth((char*)
									toString(DanhsachVatTu[i]->data.SLTon).c_str())/2, leTren + 34 + height/2 + (stt%25)*height);
								}
							else{
									stt++;
								}
					}
			}
			else
			{
				for(int i = 0 ; i < cnt; i++)
				{
					if(search_code==DanhsachVatTu[i]->data.MaVT)
					{
							DisplayMaterial(DanhsachVatTu[i], leTrai + 45, leTrai + 25 + 100, leTrai + 25 + 300, leTrai + 110 + 900 - textwidth((char*)toString(DanhsachVatTu[i]->data.DVTinh).c_str())/2, leTrai + 130 + 1100 - textwidth((char*)
									toString(DanhsachVatTu[i]->data.SLTon).c_str())/2, leTren + 34 + height/2 + (stt%25)*height);
					}
				}
			}
		}
		void DisplayMaterialToSelect(MaterialNode* a, int x1, int x2, int x3, int x4, int x5, int y)
		{
			int leTrai  = 200;
			int lePhai = 1720;
			int leTren = 110;
			int height = 32;
			Button<MaterialTab> select(1640,y + 15, textwidth("chon"), textheight("chon"), WHITE, addbutton_oncolor, "chon", &MaterialTab::Select, BLACK);
			
			setcolor(BLACK);
			setbkcolor(smallwindow_bg_color);
			outtextxy(x1, y, (char*)toString(++stt).c_str());
			outtextxy(x2, y, (char*)toString(a->data.MaVT).c_str());
			outtextxy(x3, y, (char*)toString(a->data.TenVT).c_str());
			outtextxy(x4, y, (char*)toString(a->data.DVTinh).c_str());
			outtextxy(x5, y, (char*)toString(a->data.SLTon).c_str());
			currentNode = a;
			select.Action(this);
		}
		void PrintAction(){
			int leTrai  = 200;
			int lePhai = 1720;
			int leTren = 110;
			int height = 32;
			
			// ve Background
			setfillstyle(SOLID_FILL, smallwindow_bg_color);
			bar(leTrai, leTren, lePhai, leTren + 34 + height/2 + height*25);
			// title
			setfillstyle(SOLID_FILL, title_bg_color);
			bar(leTrai, leTren, lePhai, leTren + 34);
			setbkcolor(title_bg_color);
			setcolor(BLACK);
			outtextxy(leTrai + 35, leTren + 5 , "STT");
			outtextxy(leTrai + 95 + 100, leTren + 5 , "ID");
			outtextxy(leTrai + 195 + 300, leTren + 5 , "NAME OF MATERIAL");
			outtextxy(leTrai + 85 + 900, leTren + 5 , "UNIT");
			outtextxy(leTrai + 80 + 1100, leTren + 5 , "QUANTITY");
			outtextxy(leTrai + 50 + 1350, leTren + 5, "OPTION");
			outtextxy(screenWidth/2 - textwidth((char*)("PAGE " + toString(currentPageNumber)+"/"+toString(pageNumber)).c_str())/2, leTren + 34 + height/2 + height*25 +30, (char*)("PAGE " + toString(currentPageNumber)+"/"+toString(pageNumber)).c_str() );
			
			//ve khung
			setcolor(bg_border_color);
			line(leTrai, leTren, lePhai, leTren); 
			line(leTrai, leTren + 34, lePhai, leTren + 34);
			line(leTrai, leTren + 34 + height/2 + height * 25, lePhai, leTren+34 + height/2 +height*25);
			line(leTrai, leTren, leTrai, leTren + 34 + height/2 + height*25);
			line(leTrai + 25 + 90, leTren, leTrai + 25 + 90, leTren + 34 + height/2 + height*25);
			line(leTrai + 25 +290, leTren, leTrai + 25 + 290, leTren + 34 + height/2 + height*25);
			line(leTrai + 25 + 890, leTren, leTrai + 25 + 890, leTren + 34 + height/2 + height*25);
			line(leTrai + 25 + 1090, leTren, leTrai + 25 + 1090, leTren + 34 + height/2 + height*25);
			line(leTrai + 25 + 1340, leTren, leTrai + 25 + 1340, leTren + 34 + height/2 + height*25);
			line(lePhai, leTren, lePhai, leTren + 34 + height/2 + height*25);
			
			/// in noi dung
			
			
			//DisplayByInorder(CayVatTu->root);
			gan(CayVatTu->root);
			Sort_DanhSachVatTu(DanhsachVatTu,0,dem-1);
			DisplayListMaterial(DanhsachVatTu);
			cnt=0;// phai xet lai khong cnt se tang vo cung lon
			for(int i = 1; i <= stt; i++){
				int mod;
				if(i <= 25){
					mod = i;
				}
				
				else{
					mod = i % 25 +1;
				}
				line(leTrai, leTren + 34 + height/2 + mod*height, lePhai, leTren + 34 + height/2 + mod*height);
			}
			previousPage=Button<MaterialTab>(screenWidth/2 - 100 - textwidth("<<"), leTren + 34 + height/2 + height*25 +40, textwidth("<<"),textheight("<<"),tab_basic_color, tab_on_color, "<<", &MaterialTab::Previous);
			nextPage=Button<MaterialTab>(screenWidth/2 + 100+ textwidth(">>"), leTren + 34 + height/2 + height*25 +40,textwidth(">>"),textheight(">>"), tab_basic_color, tab_on_color, ">>", &MaterialTab::Next);
			nextPage.Action(this);
			previousPage.Action(this);
			stt = 0;
		}
		
		void DisplayMaterial(MaterialNode* a, int x1, int x2, int x3, int x4, int x5, int y)
		{
			int leTrai  = 200;
			int lePhai = 1720;
			int leTren = 110;
			int height = 32;
			Button<MaterialTab> edit(1640,y + 15, textwidth("edit"), textheight("edit"), WHITE, addbutton_oncolor, "edit", &MaterialTab::Edit, BLACK);
			
			setcolor(BLACK);
			setbkcolor(smallwindow_bg_color);
			outtextxy(x1, y, (char*)toString(++stt).c_str());
			outtextxy(x2, y, (char*)toString(a->data.MaVT).c_str());
			outtextxy(x3, y, (char*)toString(a->data.TenVT).c_str());
			outtextxy(x4, y, (char*)toString(a->data.DVTinh).c_str());
			outtextxy(x5, y, (char*)toString(a->data.SLTon).c_str());
			currentNode = a;
			edit.Action(this);
		}
		void DisplayByInorder(MaterialNode* p){
			int leTrai  = 200;
			int lePhai = 1720;
			int leTren = 110;
			int height = 32;
			if(search_code[0]=='\0')
			{
					if(p!=NULL){
					DisplayByInorder(p->left);
					if((stt >= 0 + (currentPageNumber-1)*25&& stt <= 24 +(currentPageNumber-1)*25))//&&(p->key==toString(search_code)))
					{
							DisplayMaterial(p, leTrai + 45, leTrai + 25 + 100, leTrai + 25 + 300, leTrai + 110 + 900 - textwidth((char*)toString(p->data.DVTinh).c_str())/2, leTrai + 130 + 1100 - textwidth((char*)
						toString(p->data.SLTon).c_str())/2, leTren + 34 + height/2 + (stt%25)*height);
					}
					else{
						stt++;
					}
					DisplayByInorder(p->right);
				}
			}
			else{// tim search_code tai day
				if(p!=NULL){
					DisplayByInorder(p->left);
					//(stt >= 0 + (currentPageNumber-1)*25&& stt <= 24 +(currentPageNumber-1)*25)
					if(p->key==toString(search_code))
					{
							DisplayMaterial(p, leTrai + 45, leTrai + 25 + 100, leTrai + 25 + 300, leTrai + 110 + 900 - textwidth((char*)toString(p->data.DVTinh).c_str())/2, leTrai + 130 + 1100 - textwidth((char*)
						toString(p->data.SLTon).c_str())/2, leTren + 34 + height/2 + (stt%25)*height);
					}
					else{
						code.Announcement("khong tim thay", false);
					}
//					else{
//						stt++;
//					}
					DisplayByInorder(p->right);
				}
			}
		}
		void Edit(){
			
			if(currentNode->check)
			{
					if( MessageBox(NULL,"Da ton tai vat tu nay trong don","THONG BAO",MB_ICONWARNING|MB_OKCANCEL) == IDOK)
					{
						return;
					}
					else{
						return;
					}
			}
			else
			{
				nodeNeedEdit = currentNode;
				InitEdit();
			}
			
			//EditDirect();
		}
		void EditDirect(){
			DrawInputWindow("Sua doi thong tin vat tu");
			if(!initedit)
			{
					info[0].CustomInit((char*)toString(nodeNeedEdit->data.TenVT).c_str());
					info[1].CustomInit((char*)toString(nodeNeedEdit->data.DVTinh).c_str());
					initedit = true;
			}
			info[0].Action(fieldPointer); 
			if(!info[0].CheckString())
			{
				isok0 = false;
			}
			info[1].Action(fieldPointer);
			if(!info[1].CheckString())
			{
				isok0 = false;
			}
			saveChange=Button<MaterialTab>(screenWidth/2,520,680,40,tab_on_color,tab_basic_color,"Luu thay doi",&MaterialTab::SaveEdit);
			deleteButton=Button<MaterialTab>(screenWidth/2,420,680,40,tab_on_color,tab_basic_color,"Xoa vat tu",&MaterialTab::Delete);
			saveChange.Action(this);
			deleteButton.Action(this);
			close.Action(this);
		}
		void SaveEdit(){
			if(info[0].CheckString()&&info[1].CheckString())
			{
				if( MessageBox(NULL,"Du Lieu Vua Nhap Ban Co Muon Luu Khong ??? ","THONG BAO",MB_ICONWARNING|MB_OKCANCEL) == IDOK)
				{
					nodeNeedEdit->data.TenVT = toString(m_name);
					nodeNeedEdit->data.DVTinh = toString(m_unit);
					initedit = false;
					state =EMPTY;
				}
			}
		}
		void CheckSearch()
		{
			//DrawInputWindow("Nhap vao ma vat tu");
			code.Action(fieldPointer);// nhap ma tim kiem lam nhu nay se tim ngay luon khong can phai nhan nut
			fieldPointer = &code;
			
		}
		void CheckMaterial()// ham nay khong co su dung chi viet roi de day th�i
		{
			MaterialNode* tamthoi;
			tamthoi = CayVatTu->Search_Material(CayVatTu->root,toString(search_code));
			if(tamthoi!=NULL)
			DisplayByInorder(CayVatTu->root);
			else
			code.Announcement("KHONG TIM THAY", false);
		}
		void Save(){
//			bool isok =true;
			if(info[0].CheckString()&&info[1].CheckString()&&info[2].CheckString()&&info[3].CheckString()&&isok==true)
			{
				if(MessageBox(NULL,"  Du Lieu Vua Nhap ban co muon luu khong ?","THONG BAO",MB_ICONWARNING|MB_OKCANCEL) == IDOK)
					{
						dem++;
						CayVatTu->Insert_Material(CayVatTu->root, chartostring(m_code), chartostring(m_name), chartostring(m_unit), atof(m_quantity));
						Reset();
						state = EMPTY;
					}
			}
			else
				return;
			pageNumber = CayVatTu->soluong/25 + 1;
	}
		void gan(MaterialNode* p)
			{
				if(p == NULL)
				return;
				else
				{
					DanhsachVatTu[cnt++]= p;
					gan(p->left);
					gan(p->right);
				}
			}
	void Sort_DanhSachVatTu(MaterialNode *DanhSachVatTu[], int left , int right)
	{
		if(left > right) return;
		if(left <= right)
		{
			string name;
			name = DanhSachVatTu[(left + right)/2]->data.TenVT;
			int i = left;
			int j = right;
			while(i <=j)
			{
				while(DanhSachVatTu[i]->data.TenVT <name )
				{
					i++;
				}
				while(DanhSachVatTu[j]->data.TenVT > name)
				{
					j--;
				}
				if(i <= j)
				{
					swap(DanhSachVatTu[i],DanhSachVatTu[j]);
					i++;
					j--;
				}
			}
			if(left < j)
			Sort_DanhSachVatTu(DanhSachVatTu,left,j);
			if(right >i)
			Sort_DanhSachVatTu(DanhSachVatTu,i,right);
		}
	}	
		void Delete(){
			if(MessageBox(NULL,"Ban co muon xoa vat tu nay khong ?","THONG BAO",MB_ICONWARNING|MB_OKCANCEL) == IDOK)
			{
				initedit = false;
				CayVatTu->Delete_Material(CayVatTu->root, nodeNeedEdit->key);
				state = EMPTY;
			}
			InitPrint();
		}
		void Close(){
			initedit = false;
			state = EMPTY;
		}
	public:
		void SaveData(){
			ofstream data;
			MaterialNode* p;
			data.open("vattu.txt",ios::trunc|ios::out);
			Queue<MaterialNode> queue;
			if(CayVatTu->root != NULL){
				queue.push(CayVatTu->root);
			}
			while(!queue.isEmpty()){
				queue.pop(p);
				data << p->data.TenVT << endl;
				data << p->data.MaVT << endl;
				data << p->data.DVTinh << endl;
				data << p->data.SLTon << endl;
				if(p->left != NULL){
					queue.push(p->left);
				}
				if(p->right != NULL){
					queue.push(p->right);
				}
			}
			data.close();
		}
		void ReadData(){
			fstream data;
			data.open("vattu.txt", ios::in);
			Material m;
			string temp; 
			while(1){
				
				getline(data, m.TenVT);
				if(m.TenVT == ""){
					break;
				}
				getline(data,m.MaVT);
				getline(data,m.DVTinh);
				data>>m.SLTon;
				getline(data, temp);
				dem++;
				CayVatTu->Insert_Material(CayVatTu->root, m);
			}
			pageNumber = CayVatTu->soluong/25 +1;
			data.close();
		}
	protected: 
		void DrawUI(){
			Tab::DrawUI(); 
		}		
	public:
		MaterialTab(){};		
		MaterialTab(int x, int y, int w, int h, int basiccolor, int oncolor, const char*Text): Tab(x, y, w, h, basiccolor, oncolor, Text){
			state = EMPTY;
			CayVatTu = new MaterialBST();
			CayVatTu->root = NULL;
			stt = 0;
			pageNumber = 1;
			currentPageNumber = 1;
			fieldPointer = NULL;
			dem = 0;
			cnt = 0;// vi tri cua par khi dang rong
			currentNode = NULL;
			MaterialNode *DanhsachVatTu[MAX] = {NULL};
			nodeNeedEdit = NULL;
			addButton = Button<MaterialTab>(195, 62, 160, 30, addbutton_basic_color, addbutton_oncolor , "Them vat tu", &MaterialTab::InitAddMaterial);
			searchButton = Button<MaterialTab>(355,62,160,30,addbutton_basic_color, addbutton_oncolor,"Tim vat Tu", &MaterialTab::InitSearch);	
			info[0] = InputField(screenWidth/2, 250, 40, 30, fieldborder_basic_color, fieldborder_on_color, "Ten vat tu: ", m_name);
			info[1] = InputField(screenWidth/2 , 340, 40, 30, fieldborder_basic_color, fieldborder_on_color, "Don vi tinh: ", m_unit);
			info[2] = InputField(screenWidth/2 - 180, 430, 10, 30, fieldborder_basic_color, fieldborder_on_color, "So luong ton: ", m_quantity);
			info[3] = InputField(screenWidth/2 + 120, 430, 10, 30, fieldborder_basic_color, fieldborder_on_color, "Ma vat tu: ", m_code);
			save =Button<MaterialTab>(screenWidth/2,520,680,40,tab_on_color,tab_basic_color,"Them vat tu",&MaterialTab::Save);
			close=Button<MaterialTab>(screenWidth/2 + 310,200,30,30,close_basic_color,close_basic_color,"X",&MaterialTab::Close);
			code = InputField(700,62,11,30,fieldborder_basic_color, fieldborder_on_color,"Tim Kiem : ",search_code);
		}
		///////////////////////// thu hoi vung nho cua cac nut tren cay nhi phan tim kiem
		~MaterialTab(){
			 CayVatTu->Free(CayVatTu->root);
		}
		void Action(){   
			addButton.Action(this);
			searchButton.Action(this);
			PrintAction();// de luon in ra danh sach
			switch(state){
				case ADD:
					AddMaterialAction();
					break;
				case EDIT:
					EditDirect();
					break;
					
				case SEARCH:
					CheckSearch();
					break;
				case PRINT:
					
					break;
			}
			// nhap du lieu
			int c=GetInput(); 
			int index=fieldPointer-info;
			if(fieldPointer!=NULL) {
				if(c==-1) fieldPointer->DeleteChar();
				else if(c==1||c==2){
					if(state==ADD){
						if(c==1) --index;
						else ++index;
						index=max(0,index);
						index=min(index,3);
						fieldPointer=&info[index];
					} 
				}
				else if(c!=0)
				{
					if(index == 0)
					{
						if( (c >= 65 && c<=90 )||(c >= 97 &&c<=122) || c==32)
						{
							fieldPointer->AddChar((char)c);
						}
						fieldPointer->DuaVeDangThuong(m_name);
					}
					else if(index==1)
					{
						if( (c >= 65 && c<=90 )||(c >= 97 &&c<=122)|| c==32)
						{
							fieldPointer->AddChar((char)c);
							fieldPointer->DuaVeDangThuong(m_unit);
						}
					}
					else if(index==2)
					{
						if(c<=57 && c>=48)
						{
							fieldPointer->AddChar((char)c);
						}
					}
					else if(index==3)
					{
						if((c >= 97 &&c<=122))
						{
							c-=32;
							fieldPointer->AddChar((char)c);
						}
						else if(c<=57 && c>=48)
						{
							fieldPointer->AddChar((char)c);
						}
					}
					else{
						if((c >= 97 &&c<=122))
						{
							c-=32;
							fieldPointer->AddChar((char)c);
						}
						else if(c<=57 && c>=48)
						{
							fieldPointer->AddChar((char)c);
						}
					}
				}	
			}
		}		
		void PrintActionToSelect(){
			int leTrai  = 200;
			int lePhai = 1720;
			int leTren = 110;
			int height = 32;
			// ve Background
			setfillstyle(SOLID_FILL, smallwindow_bg_color);
			bar(leTrai, leTren, lePhai, leTren + 34 + height/2 + height*25);
			// title
			setfillstyle(SOLID_FILL, title_bg_color);
			bar(leTrai, leTren, lePhai, leTren + 34);
			setbkcolor(title_bg_color);
			setcolor(BLACK);
			outtextxy(leTrai + 35, leTren + 5 , "STT");
			outtextxy(leTrai + 95 + 100, leTren + 5 , "ID");
			outtextxy(leTrai + 195 + 300, leTren + 5 , "NAME OF MATERIAL");
			outtextxy(leTrai + 85 + 900, leTren + 5 , "UNIT");
			outtextxy(leTrai + 80 + 1100, leTren + 5 , "QUANTITY");
			outtextxy(leTrai + 50 + 1350, leTren + 5, "OPTION");
			outtextxy(screenWidth/2 - textwidth((char*)("PAGE " + toString(currentPageNumber)+"/"+toString(pageNumber)).c_str())/2, leTren + 34 + height/2 + height*25 +30, (char*)("PAGE " + toString(currentPageNumber)+"/"+toString(pageNumber)).c_str() );
			//ve khung
			setcolor(bg_border_color);
			line(leTrai, leTren, lePhai, leTren); 
			line(leTrai, leTren + 34, lePhai, leTren + 34);
			line(leTrai, leTren + 34 + height/2 + height * 25, lePhai, leTren+34 + height/2 +height*25);
			line(leTrai, leTren, leTrai, leTren + 34 + height/2 + height*25);
			line(leTrai + 25 + 90, leTren, leTrai + 25 + 90, leTren + 34 + height/2 + height*25);
			line(leTrai + 25 +290, leTren, leTrai + 25 + 290, leTren + 34 + height/2 + height*25);
			line(leTrai + 25 + 890, leTren, leTrai + 25 + 890, leTren + 34 + height/2 + height*25);
			line(leTrai + 25 + 1090, leTren, leTrai + 25 + 1090, leTren + 34 + height/2 + height*25);
			line(leTrai + 25 + 1340, leTren, leTrai + 25 + 1340, leTren + 34 + height/2 + height*25);
			line(lePhai, leTren, lePhai, leTren + 34 + height/2 + height*25);
			/// in noi dung	
			//DisplayByInorder(CayVatTu->root);
			gan(CayVatTu->root);
			Sort_DanhSachVatTu(DanhsachVatTu,0,dem-1);
			DisplayListMaterialToSelect(DanhsachVatTu);
			cnt=0;// phai xet lai khong cnt se tang vo cung lon
			for(int i = 1; i <= 25; i++){
				line(leTrai, leTren + 34 + height/2 + i*height, lePhai, leTren + 34 + height/2 + i*height);
			}
			previousPage=Button<MaterialTab>(screenWidth/2 - 100 - textwidth("<<"), leTren + 34 + height/2 + height*25 +40, textwidth("<<"),textheight("<<"),tab_basic_color, tab_on_color, "<<", &MaterialTab::Previous);
			nextPage=Button<MaterialTab>(screenWidth/2 + 100+ textwidth(">>"), leTren + 34 + height/2 + height*25 +40,textwidth(">>"),textheight(">>"), tab_basic_color, tab_on_color, ">>", &MaterialTab::Next);
			nextPage.Action(this);
			previousPage.Action(this);
			stt = 0;
		}
};
class StaffTab: public Tab{ 
	private: 
		enum STAFF_TAB_STATE{ADD,EDIT,PRINT,EMPTY,SEARCH};//  Trang thai cua so lam viec
		STAFF_TAB_STATE state;// bien luu trang thai dang lam viec
		InputField* fieldPointer;// con tro doi tuong co vai tro ve ra khung de nhap du lieu
		Button<StaffTab> addButton;// cac nut chuc nang
		InputField info[3];// HO, TEN, MA 
		InputField code;
		char *search_code = new char[10];
		Button<StaffTab> nam, nu;
		Button<StaffTab> save, close; // nut chuc nang
		Button<StaffTab>saveChange,deleteButton,searchButton;
		char *HO= new char[40];	
		char *TEN=new char[10];  
		char *id= new char[10];
		bool sex;
		int pageNumber, currentPageNumber;
		int stt;
		int dem;
		bool isok0 = true;//kiem tra du lieu nhap co rong hay khong
		bool isok = true;//kiem tra xem co trung ma nhan vien hay khong
		bool initedit = false;// bien kiem tra de gan du lieu khi sua
		Employee *current,*nodeEdit;
		Button<StaffTab> previousPage, nextPage;
	public:
		//DATA
		ListEmployee dsNhanVien;
		void Reset(){ 
			fieldPointer = &info[0];
			info[0].BlankField();
			info[1].BlankField();
			info[2].BlankField();
			sex = 0;
		}
		void InitAddStaff(){
			Reset(); 
			state = ADD; 
			fieldPointer = &info[0]; 
		}  
		void InitPrint(){
			Reset();
			state = PRINT;			
		} 
		void InitEdit(){
			Reset();
			state = EDIT;
			fieldPointer=&info[0];
		}
		
		void InitSearch()
		{
			Reset();
			state = SEARCH;
		}
		void SearchNhanVien()
		{
			code.Action(fieldPointer);
			fieldPointer = &code;
		}
		void Select(){
			employeeToSelect = current;
		}
		void DisplayNu(){
			sex = 1;
		}
		void DisplayNam(){
			sex = 0;
		}
		void Previous(){
			if(currentPageNumber > 1){
				currentPageNumber--;
			}
		}
		void Next(){
			if(currentPageNumber < pageNumber){
				currentPageNumber++;
			}
		}
		void DisplayStaff(Employee* a, int x1, int x2, int x3, int x4, int x5, int y){
			int leTrai  = 200;
			int lePhai = 1720;
			int leTren = 110;
			int height = 32;
			Button<StaffTab> edit(1640,y + 15, textwidth("edit"), textheight("edit"), WHITE, addbutton_oncolor, "edit", &StaffTab::Edit, BLACK);
			  
			setcolor(BLACK);
			setbkcolor(smallwindow_bg_color);
			outtextxy(x1, y, (char*)toString(++stt).c_str());
			outtextxy(x2, y, (char*)toString(a->id).c_str());
			outtextxy(x3, y, (char*)toString(a->HO).c_str());
			outtextxy(x4, y, (char*)toString(a->TEN).c_str());
			if(a->PHAI ==0){
				outtextxy(x5, y, "NAM");
			} 
			else{
				outtextxy(x5, y, "NU");
			}
			current = a;
			edit.Action(this);
		}
		void DisplayStaffToSelect(Employee* a, int x1, int x2, int x3, int x4, int x5, int y){
			int leTrai  = 200;
			int lePhai = 1720;
			int leTren = 110;
			int height = 32;
			Button<StaffTab> select(1640,y + 15, textwidth("chon"), textheight("chon"), WHITE, addbutton_oncolor, "chon", &StaffTab::Select, BLACK);
			  
			setcolor(BLACK);
			setbkcolor(smallwindow_bg_color);
			outtextxy(x1, y, (char*)toString(++stt).c_str());
			outtextxy(x2, y, (char*)toString(a->id).c_str());
			outtextxy(x3, y, (char*)toString(a->HO).c_str());
			outtextxy(x4, y, (char*)toString(a->TEN).c_str());
			if(a->PHAI ==0){
				outtextxy(x5, y, "NAM");
			} 
			else{
				outtextxy(x5, y, "NU");
			}
			current = a;
			select.Action(this);
		}
			void AddStaffAction(){
				DrawInputWindow("Nhap thong tin nhan vien");
				info[0].Action(fieldPointer);
				if(!info[0].CheckString())
				{
					isok0 = false;
				}
				info[1].Action(fieldPointer);
				if(!info[1].CheckString())
				{
					isok0 = false;
				}
				info[2].Action(fieldPointer);
				if(!info[2].CheckString())
				{
					isok0 = false;
				}
				int bienktr = dsNhanVien.Search_MaNV(dsNhanVien.nhanVien,toString(id));
				if(bienktr!=-1)
				{
					info[2].Announcement("Da ton tai ma nhan vien!!!",false);
					isok = false;
				}
				else 
					isok = true;
				settextstyle(10, HORIZ_DIR, 2);
				setcolor(BLACK);
				outtextxy(screenWidth/2 -20, 420, "Gioi tinh: ");
				if(sex == 0){
					nam.Action(this);
				}
				else{
					nu.Action(this);	
				}
				save.Action(this);
				close.Action(this);
			}
		void Sort_DanhSachNhanVien(Employee *DSNhanVien[], int left , int right)
		{
			if(left > right) return;
			if(left <= right)
			{
				string name;
				name = DSNhanVien[(left + right)/2]->TEN;
				int i = left;
				int j = right;
				while(i <=j)
				{
					while(DSNhanVien[i]->TEN <name )
					{
						i++;
					}
					while(DSNhanVien[j]->TEN > name)
					{
						j--;
					}
					if(i <= j)
					{
						swap(DSNhanVien[i],DSNhanVien[j]);
						i++;
						j--;
					}
				}
				if(left < j)
				Sort_DanhSachNhanVien(DSNhanVien,left,j);
				if(right >i)
				Sort_DanhSachNhanVien(DSNhanVien,i,right);
			}
	}
		void PrintAction(){
			int leTrai  = 200;
			int lePhai = 1720;
			int leTren = 110;
			int height = 32;			
			// ve Background
			setfillstyle(SOLID_FILL, smallwindow_bg_color);
			bar(leTrai, leTren, lePhai, leTren + 34 + height/2 + height*25);
			// title
			setfillstyle(SOLID_FILL, title_bg_color);
			bar(leTrai, leTren, lePhai, leTren + 34);
			setbkcolor(title_bg_color);
			setcolor(BLACK);
			outtextxy(leTrai + 35, leTren + 5 , "STT");
			outtextxy(leTrai + 95 + 100, leTren + 5 , "ID");
			outtextxy(leTrai + 195 + 350, leTren + 5 , "LASTNAME");
			outtextxy(leTrai + 55 + 900, leTren + 5 , "FISRTNAME");
			outtextxy(leTrai + 80 + 1130, leTren + 5 , "SEX");
			outtextxy(leTrai + 50 + 1350, leTren + 5, "OPTION");
			outtextxy(screenWidth/2 - textwidth((char*)("PAGE " + toString(currentPageNumber)+"/"+toString(pageNumber)).c_str())/2, leTren + 34 + height/2 + height*25 +30, (char*)("PAGE " + toString(currentPageNumber)+"/"+toString(pageNumber)).c_str() );			
			//ve khung
			setcolor(bg_border_color);
			line(leTrai, leTren, lePhai, leTren);
			line(leTrai, leTren + 34, lePhai, leTren + 34);
			line(leTrai, leTren + 34 + height/2 + height * 25, lePhai, leTren+34 + height/2 +height*25);
			line(leTrai, leTren, leTrai, leTren + 34 + height/2 + height*25);
			line(leTrai + 25 + 90, leTren, leTrai + 25 + 90, leTren + 34 + height/2 + height*25);
			line(leTrai + 25 +290, leTren, leTrai + 25 + 290, leTren + 34 + height/2 + height*25);
			line(leTrai + 25 + 890, leTren, leTrai + 25 + 890, leTren + 34 + height/2 + height*25);
			line(leTrai + 25 + 1090, leTren, leTrai + 25 + 1090, leTren + 34 + height/2 + height*25);
			line(leTrai + 25 + 1340, leTren, leTrai + 25 + 1340, leTren + 34 + height/2 + height*25);
			line(lePhai, leTren, lePhai, leTren + 34 + height/2 + height*25);
			if(search_code[0]=='\0')
			{
				stt = 0 + (currentPageNumber-1)*25;
				for(int i = 0; i < dsNhanVien.sl; i++){
					if(i >= 0 + (currentPageNumber-1)*25 && i < currentPageNumber*25){
					DisplayStaff(dsNhanVien.nhanVien[i], leTrai + 45, leTrai + 25 + 100, leTrai + 25 + 300, leTrai + 90 + 900, leTrai + 80 + 1130, leTren + 34 + height/2 + (stt%25)*height);
					}
				}
			}
			else{
				for(int i = 0 ; i < dsNhanVien.sl;i++)
				{
					if(dsNhanVien.nhanVien[i]->id == search_code)
					{
						DisplayStaff(dsNhanVien.nhanVien[i], leTrai + 45, leTrai + 25 + 100, leTrai + 25 + 300, leTrai + 90 + 900, leTrai + 80 + 1130, leTren + 34 + height/2 + (stt%25)*height);
					 } 
				 } 
			} 
			for(int i = 1; i <= 24; i++){
				setcolor(BLACK);
				line(leTrai, leTren + 34 + height/2 + i*height, lePhai, leTren + 34 + height/2 + i*height);
			}
			previousPage=Button<StaffTab>(screenWidth/2 - 100 - textwidth("<<"), leTren + 34 + height/2 + height*25 +40, textwidth("<<"),textheight("<<"),tab_basic_color, tab_on_color, "<<", &StaffTab::Previous);
			nextPage=Button<StaffTab>(screenWidth/2 + 100+ textwidth(">>"), leTren + 34 + height/2 + height*25 +40,textwidth(">>"),textheight(">>"), tab_basic_color, tab_on_color, ">>", &StaffTab::Next);
			nextPage.Action(this);
			previousPage.Action(this);
			stt = 0;
		}
		void PrintActionToSelect(){
			int leTrai  = 200;
			int lePhai = 1720;
			int leTren = 110;
			int height = 32;			
			// ve Background
			setfillstyle(SOLID_FILL, smallwindow_bg_color);
			bar(leTrai, leTren, lePhai, leTren + 34 + height/2 + height*25);
			// title
			setfillstyle(SOLID_FILL, title_bg_color);
			bar(leTrai, leTren, lePhai, leTren + 34);
			setbkcolor(title_bg_color);
			setcolor(BLACK);
			outtextxy(leTrai + 35, leTren + 5 , "STT");
			outtextxy(leTrai + 95 + 100, leTren + 5 , "ID");
			outtextxy(leTrai + 195 + 350, leTren + 5 , "LASTNAME");
			outtextxy(leTrai + 55 + 900, leTren + 5 , "FISRTNAME");
			outtextxy(leTrai + 80 + 1130, leTren + 5 , "SEX");
			outtextxy(leTrai + 50 + 1350, leTren + 5, "OPTION");
			outtextxy(screenWidth/2 - textwidth((char*)("PAGE " + toString(currentPageNumber)+"/"+toString(pageNumber)).c_str())/2, leTren + 34 + height/2 + height*25 +30, (char*)("PAGE " + toString(currentPageNumber)+"/"+toString(pageNumber)).c_str() );			
			//ve khung
			setcolor(bg_border_color);
			line(leTrai, leTren, lePhai, leTren);
			line(leTrai, leTren + 34, lePhai, leTren + 34);
			line(leTrai, leTren + 34 + height/2 + height * 25, lePhai, leTren+34 + height/2 +height*25);
			line(leTrai, leTren, leTrai, leTren + 34 + height/2 + height*25);
			line(leTrai + 25 + 90, leTren, leTrai + 25 + 90, leTren + 34 + height/2 + height*25);
			line(leTrai + 25 +290, leTren, leTrai + 25 + 290, leTren + 34 + height/2 + height*25);
			line(leTrai + 25 + 890, leTren, leTrai + 25 + 890, leTren + 34 + height/2 + height*25);
			line(leTrai + 25 + 1090, leTren, leTrai + 25 + 1090, leTren + 34 + height/2 + height*25);
			line(leTrai + 25 + 1340, leTren, leTrai + 25 + 1340, leTren + 34 + height/2 + height*25);
			line(lePhai, leTren, lePhai, leTren + 34 + height/2 + height*25);			
			/// in noi dung
			stt = 0 + (currentPageNumber-1)*25;
			for(int i = 0; i < dsNhanVien.sl; i++){
				if(i >= 0 + (currentPageNumber-1)*25 && i < currentPageNumber*25){
					DisplayStaffToSelect(dsNhanVien.nhanVien[i], leTrai + 45, leTrai + 25 + 100, leTrai + 25 + 300, leTrai + 90 + 900, leTrai + 80 + 1130, leTren + 34 + height/2 + (stt%25)*height);
				}
			}
			for(int i = 1; i <= 24; i++){
				setcolor(BLACK);
				line(leTrai, leTren + 34 + height/2 + i*height, lePhai, leTren + 34 + height/2 + i*height);
			}
			previousPage=Button<StaffTab>(screenWidth/2 - 100 - textwidth("<<"), leTren + 34 + height/2 + height*25 +40, textwidth("<<"),textheight("<<"),tab_basic_color, tab_on_color, "<<", &StaffTab::Previous);
			nextPage=Button<StaffTab>(screenWidth/2 + 100+ textwidth(">>"), leTren + 34 + height/2 + height*25 +40,textwidth(">>"),textheight(">>"), tab_basic_color, tab_on_color, ">>", &StaffTab::Next);
			nextPage.Action(this);
			previousPage.Action(this);
			stt = 0;	
		}
		void Edit(){
			if(current->HoaDon->First==NULL){
				nodeEdit = current;
				InitEdit();
			}
			else{
					if( MessageBox(NULL,"Da ton tai vat tu nay trong don","THONG BAO",MB_ICONWARNING|MB_OKCANCEL) == IDOK)
					{
						return;
					}
					else{
						return;
					}
			}	
		}	
		void EditDirect()
		{
			DrawInputWindow("Sua thong tin nhan vien");
			if(!initedit)
			{
				info[0].CustomInit((char*)toString(nodeEdit->HO).c_str());
				info[1].CustomInit((char*)toString(nodeEdit->TEN).c_str());
				initedit = true;//
			}
			info[0].Action(fieldPointer);
			if(!info[0].CheckString())
			{
				isok0 =false;
			}
			info[1].Action(fieldPointer);
			if(!info[1].CheckString())
			{
				isok0=false;
			}
			outtextxy(screenWidth/2 -20, 420, "Gioi tinh: ");
			if(sex == 0){
				nam.Action(this);
			}
			else{
				nu.Action(this);	
			}
			saveChange.Action(this);
			deleteButton.Action(this);
			close.Action(this);	
		}
		void SaveEditStaff()
		{
			if(info[0].CheckString()&&info[1].CheckString())
			{
				if( MessageBox(NULL,"Du Lieu Vua Nhap Ban Co Muon Luu Khong ??? ","THONG BAO",MB_ICONWARNING|MB_OKCANCEL) == IDOK)
				{
					nodeEdit->HO = toString(HO);
					nodeEdit->TEN = toString(TEN);
					nodeEdit->PHAI = sex;
					initedit = false;
					state =EMPTY;
				}
			}
		}
		void DeleteStaff()
		{
				initedit = false;
				dsNhanVien.Delete_Staff(dsNhanVien.nhanVien,nodeEdit->id);// neu using current se chi co the xoa cuoi
		}
		void Save(){
			if(info[0].CheckString()&&info[1].CheckString()&&info[2].CheckString()&&isok==true)
			{
				if(MessageBox(NULL,"  Du Lieu Vua Nhap ban co muon luu khong ?","THONG BAO",MB_ICONWARNING|MB_OKCANCEL) == IDOK)
					{
						dsNhanVien.Insert_Staff(toString(HO),toString(TEN),toString(id), sex);
						dem++;
						Sort_DanhSachNhanVien(dsNhanVien.nhanVien,0,dem-1);
						Reset();
						state = EMPTY;
					}
			}	
			else
				return;		
			pageNumber = dsNhanVien.sl /25 + 1;
		}
		void Close(){
			initedit = false;
			state = EMPTY;
			Reset();
		}	
	protected: 
		void DrawUI(){
			Tab::DrawUI();
		}		
	public:
		StaffTab(){};		
		StaffTab(int x, int y, int w, int h, int basiccolor, int oncolor, const char*Text): Tab(x, y, w, h, basiccolor, oncolor, Text){
			state = EMPTY;
			
			fieldPointer = NULL;
			addButton = Button<StaffTab>(195, 62, 160, 30, addbutton_basic_color, addbutton_oncolor , "Them nhan vien", &StaffTab::InitAddStaff, WHITE);
			info[0] = InputField(screenWidth/2, 250, 40, 30, fieldborder_basic_color, fieldborder_on_color, "Ho nhan vien: ", HO);
			info[1] = InputField(screenWidth/2- 120, 340, 20, 30, fieldborder_basic_color, fieldborder_on_color, "Ten nhan vien: ", TEN);
			info[2] = InputField(screenWidth/2 - 180, 430, 10, 30, fieldborder_basic_color, fieldborder_on_color, "Ma nhan vien: ", id);
			nam = Button<StaffTab>(screenWidth/2 +150, 430, 100, 30, 3, 11, "Nam", &StaffTab::DisplayNu, BLACK);
			nu = Button<StaffTab>(screenWidth/2 + 150, 430, 100, 30, 13, 11, "Nu", &StaffTab::DisplayNam, BLACK);
			sex = 0;
			save =Button<StaffTab>(screenWidth/2,520,680,40,tab_on_color,tab_basic_color,"Them nhan vien",&StaffTab::Save);
			close=Button<StaffTab>(screenWidth/2 + 450,200,30,30,close_basic_color,close_basic_color,"X",&StaffTab::Close);
			saveChange=Button<StaffTab>(screenWidth/2,520,680,40,tab_on_color,tab_basic_color,"Luu thay doi",&StaffTab::SaveEditStaff);
			deleteButton=Button<StaffTab>(screenWidth/2,470,680,40,tab_on_color,tab_basic_color,"Xoa nhan vien",&StaffTab::DeleteStaff);
			code = InputField(700,62,11,30,fieldborder_basic_color, fieldborder_on_color,"Tim Kiem : ",search_code);
			searchButton = Button<StaffTab>(370,62,160,30,addbutton_basic_color, addbutton_oncolor,"Tim nhan vien", &StaffTab::InitSearch);
			pageNumber = 1;
			currentPageNumber = 1;
			stt = 0;
			dem = 0;
		}
		///////////////////////// thu hoi vung nho cua cac nut tren cay nhi phan tim kiem
		~StaffTab(){
			dsNhanVien.Free();
		}
		void Action(){   
			addButton.Action(this);
			searchButton.Action(this);
			PrintAction();
			switch(state){
				case ADD:
					AddStaffAction();
					break;
				case EDIT:
					EditDirect();
					break;
				case PRINT:
					
					break;
				case SEARCH:
					SearchNhanVien();
					break;
			}			 
			// nhap du lieu
			int c=GetInput(); 
			int index=fieldPointer-info;
			if(fieldPointer!=NULL) {
				if(c==-1) fieldPointer->DeleteChar();
				else if(c==1||c==2){
					if(state==ADD){
						//int index=fieldPointer-info;
						if(c==1) --index;
						else ++index;
						index=max(0,index);
						//index=min(index,3);
						index=min(index,2);
						fieldPointer=&info[index];
					} 
					if(state==EDIT){
					}
				}
				else if(c!=0)
				{
					
					if(index==0||index==1)
					{
						if( (c >= 65 && c<=90 )||(c >= 97 &&c<=122) || c==32)
						{
							fieldPointer->AddChar((char)c);
						}
						fieldPointer->DuaVeDangThuong(HO);
						fieldPointer->DuaVeDangThuong(TEN);
					}
					else if(index==2)
						{
							if(c >= 97 &&c<=122)
							{
								c-=32;
								fieldPointer->AddChar((char)c);
							}
							else if((c<=57 && c>=48)||(c >= 65 && c<=90 ))
							{
								fieldPointer->AddChar((char)c);
							}
						}
					else{
						if((c >= 97 &&c<=122))
						{
							c-=32;
							fieldPointer->AddChar((char)c);
						}
						else if(c<=57 && c>=48)
						{
							fieldPointer->AddChar((char)c);
						}
						//fieldPointer->AddChar((char)c);// dieu kien chu khong se khong nhap duoc search code
					}					
				}
			}	
		}
		void ReadData(){
			// ifstream data;
			// data.open("nhanvien.txt", ios::in);
			// Employee a;
			// string temp;
			// while(1){
			// 	getline(data, a.HO);
			// 	if(a.HO == ""){
			// 		break;
			// 	}
			// 	getline(data, a.TEN);
			// 	getline(data, a.id);
			// 	data >> a.PHAI;
			// 	getline(data, temp);
			// 	dsNhanVien.Insert_Staff(a);
			// 	pageNumber= dsNhanVien.sl/25 + 1;
			// }
			// data.close();
		}
		void WriteData(){
			// ofstream data;
			// data.open("nhanvien.txt", ios::out| ios::trunc);
			// for(int i = 0; i< dsNhanVien.sl; i++){
			// 	data<< dsNhanVien.nhanVien[i]->HO << endl;
			// 	data << dsNhanVien.nhanVien[i]->TEN << endl;
			// 	data<< dsNhanVien.nhanVien[i]->id << endl;
			// 	data << dsNhanVien.nhanVien[i]->PHAI << endl;
			// }
			// data.close();
		}
		Employee* Search_NV_ToAddBill(string id){
			for(int i = 0; i < dsNhanVien.sl; i++){
				if(dsNhanVien.nhanVien[i]->id == id){
					return dsNhanVien.nhanVien[i];
				}
			}
		}		
};
class BillTab: public Tab{
	private:
		enum BILL_TAB_STATE{ADD, EDIT, PRINT,EMPTY, SELECT_EMPLOYEE, SELECT_MATERIAL};//  Trang thai cua so lam viec
		BILL_TAB_STATE state;// bien luu trang thai dang lam viec
		InputField* fieldPointer;// con tro doi tuong co vai tro ve ra khung de nhap du lieu
		Button<BillTab> addButton, printButton;
		InputField info[11]; // so hoa don, ma nhan vien, ten nhan vien, ngay, thang, nam, ma vat tu, ten vat tu, so luong, don gia, vat
		InputField contentedit[4];//ma vat tu,so luong , don gia,vat
		char *soHD= new char[20];// ->info[0]
		char *maNV= new char[10];// info[1]
		char *tenNV = new char[50];// chuc nangw moi de thuan tien cho nguoi dung   info[2]
		char *day = new char[2]; // info[3]
		char *month = new char[2]; // info[4]
		char *year = new char [4]; // info[5]
		char loaiHD;
		char *m_code = new char[10]; // info[6]
		char *m_name = new char[40]; // info[7]
		char *m_quantity = new char[10]; // info[8]
		char *m_price = new char[10]; // info[9]
		char *VAT = new char[3]; // info[10]
		Button<BillTab> NButton, XButton, AddDetailBill, Payment;
		DBList* dscthd = new DBList;///////////////---------	---------------------------------------------------
		DBNode* duyetCTHD;// con tro duyet danh sach chi tiet hoa don--------------------------------------------------------
		int pageNumberCTHD, currentPageNumberCTHD;
		bool isok0 = true;// quan li edit khong duoc trong
		bool isok = true;// quan li nhap them hoa don
		bool initedit= false;
		Button<BillTab> previousPageCTHD, nextPageCTHD;
		Button<BillTab>close,savechange;
		Button<BillTab> selectNV, selectVT;
		MaterialTab* vattu;////////////----------------------------------------------------
		StaffTab* nhanvien;/////--------------------------------------------------------------------------
		Employee* nvLapHD;
		DBNode* nodeNeedEdit;
		DBNode* currentNodeCTHD;
		long long total;
		int currentPageNumber;
		int pageNumber;
		int stt;
	protected:
		void DrawUI(){
			Tab::DrawUI();
		}
		void ResetCTHD(){
			fieldPointer = &info[6];
			info[6].BlankField();
			info[7].BlankField();
			info[8].BlankField();
			info[9].BlankField();
			info[10].BlankField();
		}
		void ResetHD(){
			fieldPointer = &info[0];
			info[0].BlankField();
			info[1].BlankField();
			info[2].BlankField();
			info[6].BlankField();
			info[7].BlankField();
			info[8].BlankField();
			info[9].BlankField();
			info[10].BlankField();
		}
		void InitAddBill(){
			state = ADD;
		}
		void InitPrintBill(){
			state = PRINT;
		}
		void InitEdit()
		{
			nodeNeedEdit = currentNodeCTHD;
			state = EDIT;
			//ResetCTHD();
		}
		void checkVatTuCoTrongCTHD(){
			for(int i = 0; i < nhanvien->dsNhanVien.sl; i++){
				BillNode*temp = nhanvien->dsNhanVien.nhanVien[i]->HoaDon->First;
				while(temp!=NULL){
					DBNode*tmpDBNode =temp->data.dscthd.First;
					while(tmpDBNode !=NULL){
						MaterialNode* tempVT = vattu->CayVatTu->Search_Material(vattu->CayVatTu->root,tmpDBNode->data.MAVT);
						tempVT->check = true;
						tmpDBNode = tmpDBNode->next;
					}
					temp = temp->next;
				}
			}
		}		
		void SetHoaDonNhap(){
			loaiHD = 'N';
		}
		void SetHoaDonXuat(){ 
			loaiHD = 'X';
		}
		void PreviousPageCTHD(){
			if(currentPageNumberCTHD > 1){
				currentPageNumberCTHD--;
			}
		}
		void NextPageCTHD(){
			if(currentPageNumberCTHD < pageNumberCTHD){
				currentPageNumberCTHD++;
			}
		}	
		void ThemChiTietHoaDon(){
			if(info[0].CheckString()&&info[1].CheckString()&&info[2].CheckString()&&info[3].CheckString()&&info[4].CheckString()&&info[5].CheckString()&&info[5].CheckString()&&info[7].CheckString()&&info[8].CheckString()&&info[9].CheckString()&&info[10].CheckString())
			{
				dscthd->Insert_Last_DBList(toString(m_code), toFloat(m_quantity), toFloat(m_price), toFloat(VAT));
				
				MaterialNode* temp  = vattu->CayVatTu->Search_Material(vattu->CayVatTu->root, toString(m_code));
				
				if(loaiHD == 'N'){
					temp->data.SLTon+= toFloat(m_quantity);
				}
				else{
					temp->data.SLTon-= toFloat(m_quantity);
				}
				pageNumberCTHD = dscthd->soluong/16+1;
				DBNode* last = dscthd->First;
				while(last->next!=NULL){
					last = last->next;
				}
				total = total + last->data.Dongia* last->data.Soluong*(100 + last->data.VAT)/100;
				ResetCTHD();
			}

		}
		void ThanhToanHoaDon(){
			if(dscthd->First == NULL){
				return;
			}
			nvLapHD = nhanvien->Search_NV_ToAddBill(toString(maNV));
			checkVatTuCoTrongCTHD();
			outtextxy(1800,980, (char*)nvLapHD->HO.c_str());
			
			nvLapHD->InsertBill(toString(soHD), toFloat(day), toFloat(month), toFloat(year), loaiHD, dscthd);
			nvLapHD =NULL;
			dscthd = new DBList; 
			/*
				khi thanh toan hoa don
				nhung thong tin can thiet
					so hoa don
					ma nhan vien
					ngay lap
					loai hoa don
					danh sach chi tiet hoa don(da co san)
					
			*/
			ResetHD();
		}
		void xoaChiTietHoaDon(){
			MaterialNode* temp  = vattu->CayVatTu->Search_Material(vattu->CayVatTu->root, currentNodeCTHD->data.MAVT);
			if(loaiHD == 'N'){
				temp->data.SLTon-= toFloat(currentNodeCTHD->data.Soluong);
			}
			else{
				temp->data.SLTon+= toFloat(currentNodeCTHD->data.Soluong);
			}
			dscthd->Delete_DBNode(currentNodeCTHD);
			pageNumberCTHD = dscthd->soluong/16 +1;
			
		}
		void chonNhanVien(){
			state = SELECT_EMPLOYEE;
		}
		void chonVatTu(){
			state = SELECT_MATERIAL;			
		}
		void Watch(){			
		}
		void DisplayListBill()
		{
			int leTrai  = 200;
			int lePhai = 1720;
			int leTren = 110;
			int height = 32;
			for(int i = 0; i < nhanvien->dsNhanVien.sl; i++){
				BillNode* tempHD = nhanvien->dsNhanVien.nhanVien[i]->HoaDon->First;
				while(tempHD !=NULL){
					if(stt >= 0 + (currentPageNumber-1)*20 && stt<= 19+(currentPageNumber-1)*20){
						DisplayBillToWatch(tempHD, leTrai+45, leTrai+125, leTrai+325, leTrai+1230, leTrai+ 930, leTren + 70 + height/2 + (stt%20)*height);
					}
					tempHD = tempHD->next;
				}
			}
			
		}
		void DisplayBillToWatch(BillNode* a, int x1, int x2, int x3, int x4, int x5, int y)
		{
			int leTrai  = 200;
			int lePhai = 1720;
			int leTren = 110;
			int height = 32;
			Button<BillTab> select(1640,y + 15, textwidth("xem"), textheight("xem"), WHITE, addbutton_oncolor, "xem", &BillTab::Watch, BLACK);
			
			setcolor(BLACK);
			setbkcolor(smallwindow_bg_color);
			outtextxy(x1, y, (char*)toString(++stt).c_str());
			outtextxy(x2, y, (char*)toString(a->data.soHD).c_str());
			//Employee* temp = nhanvien->dsNhanVien.Search_MaNV(nhanvien->dsNhanVien, )
			//outtextxy(x3, y, (char*)toString(a->data.).c_str());// ten nhan vien
			outtextxy(x4, y, (char*)toString(a->data.loai).c_str());
			outtextxy(x5, y, (char*)(toString(a->data.date.day)+"/"+toString(a->data.date.month)+"/"+toString(a->data.date.year)).c_str());//ngay lap
			select.Action(this);
		}
		void Display1DetailBill(DBNode*p,int x1,int x2,int x3,int x4,int x5, int x6, int x7, int y){
			settextstyle(6, HORIZ_DIR, 1);
			setbkcolor(WHITE);
			setcolor(LIGHTGREEN);
			outtextxy(x1, y, (char*)toString(p->data.MAVT).c_str());
			MaterialNode* temp = vattu->CayVatTu->Search_Material(vattu->CayVatTu->root, p->data.MAVT);
			outtextxy(x2, y, (char*)toString(temp->data.TenVT).c_str());
			outtextxy(x3, y, (char*)toString(temp->data.DVTinh).c_str());
			outtextxy(x4, y, (char*)toString(p->data.Soluong).c_str());
			outtextxy(x5, y, (char*)toString((long long)p->data.Dongia).c_str());
			outtextxy(x6, y, (char*)toString(p->data.VAT).c_str());
			
			outtextxy(1660 - textwidth((char*)toString((long long)(p->data.Soluong * p->data.Dongia * (100 + p->data.VAT)/100)).c_str()), y, (char*)toString((long long)(p->data.Soluong * p->data.Dongia * (100 + p->data.VAT)/100)).c_str());
			outtextxy(1680, y, "dong");
			Button<BillTab> cancelCTHD = Button<BillTab>(x7, y+5, textwidth("X"), textheight("X"), RED, RED, "X", &BillTab::xoaChiTietHoaDon, WHITE);
			Button<BillTab>edit = Button<BillTab>(x7-5 -textwidth("EDIT"),y+5,textwidth("EDIT"),textheight("EDIT"),RED,RED,"EDIT",&BillTab::Edit,BLACK);
			currentNodeCTHD = p;
			edit.Action(this);
			cancelCTHD.Action(this);
		}
		void DisplayListDetailBill(){
			int stt = 0;
			duyetCTHD = dscthd->First;
			int dong = 0;
			while(duyetCTHD!=NULL){
				if(stt >= 16*(currentPageNumberCTHD-1) && stt <= 16*currentPageNumberCTHD -1){
					Display1DetailBill( duyetCTHD, 40, 195, 695, 895, 1045, 1265, 1850, 410 + dong*34);
					dong++;
				}
				else if(stt > 16*currentPageNumberCTHD-1){
					break;
				}
				duyetCTHD = duyetCTHD->next;
				stt++;
			}
		}
		void Edit()
		{			
			InitEdit();			
		}
		void EditDirect()
		{
			DrawInputWindow("Sua thong tin hoa don");
			if(!initedit)
			{
				contentedit[0].CustomInit((char*)toString(nodeNeedEdit->data.MAVT).c_str());
				contentedit[1].CustomInit((char*)toString(nodeNeedEdit->data.Soluong).c_str());
				contentedit[2].CustomInit((char*)toString(nodeNeedEdit->data.Dongia).c_str());
				contentedit[3].CustomInit((char*)toString(nodeNeedEdit->data.VAT).c_str());
				initedit = true;
			}
			contentedit[0].Action(fieldPointer);
			if(!contentedit[0].CheckString())
			{
				isok0 = false;
			}
			contentedit[1].Action(fieldPointer);
			if(!contentedit[1].CheckString())
			{
				isok0 = false;
			}
			contentedit[2].Action(fieldPointer);
			if(!contentedit[2].CheckString())
			{
				isok0 = false;
			}
			contentedit[3].Action(fieldPointer);
			if(!contentedit[3].CheckString())
			{
				isok0 = false;
			}
			savechange.Action(this);
			close.Action(this);
		}
		void SaveChange()
		{
			
			if(contentedit[0].CheckString()&&contentedit[1].CheckString()&&contentedit[2].CheckString()&&contentedit[3].CheckString())
			{
				// if(MessageBox(NULL,"Du Lieu Vua Thay Doi Ban Co Muon Luu Khong ?","THONG BAO",MB_ICONWARNING|MB_OKCANCEL) == IDOK)
				// {
				// 	nodeNeedEdit->data.MAVT = toString(m_code);
				// 	nodeNeedEdit->data.VAT = toFloat(VAT); 
				// 	nodeNeedEdit->data.Soluong = toFloat(m_quantity);
				// 	nodeNeedEdit->data.Dongia = toFloat(m_price);
				// 	nodeNeedEdit = NULL;
				// 	initedit = false;
				// }
			}
		}
		void Close()
		{
			initedit = false;
			state = EMPTY;
		}
		void AddBillAction(){
			setcolor(BLACK); 
			rectangle(15, 100, screenWidth-15, screenHeight-50);
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(20, 110, 1900, 330);
			setcolor(BLACK);
			setfillstyle(SOLID_FILL, 11);
			bar(20, 350, 1900,400);
			rectangle(20, 110, 1900, 330);
			rectangle(20, 350, 1900, 950);
			settextstyle(6,HORIZ_DIR, 3);
			setbkcolor(WHITE);
			setcolor(2);
			outtextxy(screenWidth/2 - textwidth("LAP HOA DON")/2, 82, "LAP HOA DON");
			outtextxy(80, 965, (char*)("Page "+ toString(currentPageNumberCTHD)+"/"+ toString(pageNumberCTHD)).c_str());
			outtextxy(300, 965, (char*)("So CTHD: " +toString(dscthd->soluong)).c_str());
			settextstyle(8, HORIZ_DIR,3);
			AddDetailBill.Action(this);
			Payment.Action(this);
			nextPageCTHD.Action(this);
			previousPageCTHD.Action(this);
			setcolor(GREEN);
			setbkcolor(WHITE);
			outtextxy(1200, 960, "TONG THANH TOAN:");
			outtextxy(1660 - textwidth((char*)toString(total).c_str()),960, (char*)toString(total).c_str());
			outtextxy(1680, 960, "dong");
			setcolor(BLACK);
			setbkcolor(11);
			outtextxy(35, 360, "MA VAT TU");
			outtextxy(200, 360, "TEN VAT TU");
			outtextxy(700, 360, "DON VI TINH");
			outtextxy(900, 360, "SO LUONG");
			outtextxy(1050, 360, "DON GIA(dong)");
			outtextxy(1270, 360, "VAT(%) ");
			outtextxy(1400, 360, "THANH TIEN");
			outtextxy(1780, 360, "OPTION");
			selectNV.Action(this);
			selectVT.Action(this);
			if(loaiHD == 'N'){
				NButton.Action(this);
			}
			else{
				XButton.Action(this);
			}
			info[0].Action(fieldPointer);
			if(!info[0].CheckString())
			{
				isok = false;
			}
			info[1].Action(fieldPointer);
			if(!info[1].CheckString())
			{
				isok = false;
			}
			Employee* nvTam = nhanvien->Search_NV_ToAddBill(toString(maNV));
			if(nvTam==NULL){
				info[1].Announcement("Khong tim thay nhan vien",false);
			}
			info[2].Action(fieldPointer);
			if(!info[2].CheckString())
			{
				isok = false;
			}
			info[3].Action(fieldPointer);
			if(!info[3].CheckString())
			{
				isok = false;
			}
			info[4].Action(fieldPointer);
			if(!info[4].CheckString())
			{
				isok = false;
			}
			info[5].Action(fieldPointer);
			if(!info[5].CheckString())
			{
				isok = false;
			}
			info[6].Action(fieldPointer);
			if(!info[6].CheckString())
			{
				isok = false;
			}
			MaterialNode* tempo = vattu->CayVatTu->Search_Material(vattu->CayVatTu->root, toString(m_code));
			if(tempo == NULL){
				info[6].Announcement("Khong tim thay vat tu", false);
			}
			info[7].Action(fieldPointer);
			if(!info[7].CheckString())
			{
				isok = false;
			}
			info[8].Action(fieldPointer);
			if(!info[8].CheckString())
			{
				isok = false;
			}
			info[9].Action(fieldPointer);
			if(!info[9].CheckString())
			{
				isok = false;
			}
			info[10].Action(fieldPointer);
			if(!info[10].CheckString())
			{
				isok = false;
			}
			setcolor(BLACK);
			outtextxy(35,  250,  "LOAI HOA DON:");
			duyetCTHD = dscthd->First;
			if(duyetCTHD!= NULL){
				DisplayListDetailBill();				
			}			
			setcolor(BLACK);
			line(1750, 210, 1750,330);
			line(20, 210, 1900,210);
			line(180, 350, 180, 950);
			line(680, 350, 680, 950);
			line(880, 350, 880, 950);
			line(1030, 350, 1030, 950);
			line(1250, 350, 1250, 950);
			line(1370, 350, 1370, 950);
			line(1750, 350, 1750, 950);
		}		
	public:
		BillTab(): Tab(){};
		BillTab(int x, int y, int w, int h, int basiccolor, int oncolor, char *txt, MaterialTab* materialtab, StaffTab* stafftab) : Tab(x, y, w, h,basiccolor, oncolor, txt)
		{
			currentPageNumber = 1;
			pageNumber = 1;
			vattu = materialtab;
			nhanvien = stafftab;
			state = EMPTY;
			addButton =Button<BillTab>(195, 62, 160, 30, addbutton_basic_color, addbutton_oncolor , "Them hoa don", &BillTab::InitAddBill, WHITE);
			printButton =Button<BillTab>(365, 62, 160, 30, addbutton_basic_color, addbutton_oncolor , "In hoa don", &BillTab::InitPrintBill, WHITE);
			//khoi tao khung de nhap
			info[0]= InputField(300, 160, 20, 30, fieldborder_basic_color, YELLOW, "SO HOA DON: ", soHD);
			info[1]= InputField(650, 160, 10, 30, fieldborder_basic_color, YELLOW, "MA NHAN VIEN: ", maNV);
			info[2]= InputField(1150, 160, 50, 30, fieldborder_basic_color, YELLOW, "HO TEN NV: ", tenNV);// chuc nang moi
			info[3]= InputField(1570, 160, 2, 30, fieldborder_basic_color, YELLOW, "NGAY:", day);
			info[4]= InputField(1700, 160, 2, 30, fieldborder_basic_color, YELLOW, "THANG:", month);
			info[5]= InputField(1820, 160, 4, 30, fieldborder_basic_color, YELLOW, "NAM:", year);
			stt = 0;
			loaiHD = 'N';
			info[6]= InputField(420, 260, 10, 30, fieldborder_basic_color, YELLOW, "MA VT: ", m_code);
			info[7]= InputField(860, 260, 40, 30, fieldborder_basic_color, YELLOW, "TEN VT: ", m_name);
			info[8]= InputField(1300, 260, 10, 30, fieldborder_basic_color, YELLOW, "SO LUONG: ", m_quantity);
			info[9]= InputField(1540, 260, 10, 30, fieldborder_basic_color, YELLOW, "DON GIA: ", m_price);
			info[10]= InputField(1720, 260, 3, 30, fieldborder_basic_color, YELLOW, "VAT(%): ", VAT);
			CatchTime();
			info[3].CustomInit((char*)toString(currentTime.day).c_str());
			info[4].CustomInit((char*)toString(currentTime.month).c_str());
			info[5].CustomInit((char*)toString(currentTime.year).c_str());
			NButton= Button<BillTab>(220, 260, textwidth("NHAP"), textheight("NHAP"),LIGHTGRAY, YELLOW,"NHAP", &BillTab::SetHoaDonXuat, BLACK);
			XButton = Button<BillTab>(220, 260, textwidth("XUAT"), textheight("XUAT"), LIGHTGRAY, YELLOW, "XUAT", &BillTab::SetHoaDonNhap, BLACK);
			AddDetailBill = Button<BillTab>(1820, 260, textwidth("THEM CTHD"), textheight("THEM CTHD"), YELLOW, 11,"THEM CTHD", &BillTab::ThemChiTietHoaDon, BLACK);
			Payment = Button<BillTab>(screenWidth/2, 980, textwidth("THANH TOAN HOA DON"), textheight("THANH TOAN HOA DON"), YELLOW, 11, "THANH TOAN HOA DON", &BillTab::ThanhToanHoaDon, BLACK);
			fieldPointer = &info[0];
			duyetCTHD = dscthd->First;
			pageNumberCTHD = 1;
			currentPageNumberCTHD = 1;
			// noi dung can edit
			contentedit[0] = InputField(screenWidth/2-150, 250, 10, 30, fieldborder_basic_color, fieldborder_on_color, "Ma vat tu: ", m_code);
			contentedit[1] = InputField(screenWidth/2-150 , 340, 10, 30, fieldborder_basic_color, fieldborder_on_color, "So luong: ", m_quantity);
			contentedit[2] = InputField(screenWidth/2 - 150, 430, 10, 30, fieldborder_basic_color, fieldborder_on_color, "Don gia: ", m_price);
			contentedit[3] = InputField(screenWidth/2 + 120, 430, 3, 30, fieldborder_basic_color, fieldborder_on_color, "VAT: ", VAT);
			
			close=Button<BillTab>(screenWidth/2 + 460,200,30,30,close_basic_color,close_basic_color,"X",&BillTab::Close);
			savechange =Button<BillTab>(screenWidth/2,500,680,40,tab_on_color,tab_basic_color,"Luu thong tin",&BillTab::SaveChange);

			previousPageCTHD = Button<BillTab>(60, 980, textwidth("<<"), textheight("<<"), LIGHTGRAY, BLUE, "<<", &BillTab::PreviousPageCTHD, WHITE);
			nextPageCTHD = Button<BillTab>(220, 980, textwidth(">>"), textheight(">>"), LIGHTGRAY, BLUE, ">>", &BillTab::NextPageCTHD, WHITE);
			selectNV = Button<BillTab>(690, 125, textwidth("Chon nhan vien"), textheight("Chon nhan vien"), GREEN, 11, "Chon nhan vien", &BillTab::chonNhanVien, BLACK);
			selectVT = Button<BillTab>(440, 225, textwidth("Chon vat tu"), textheight("Chon vat tu"), GREEN, 11, "Chon vat tu", &BillTab::chonVatTu, BLACK);
			total = 0;
		}
		void PrintAction(){
			int leTrai  = 200;
			int lePhai = 1720;
			int leTren = 150;
			int height = 32;
			setcolor(LIGHTBLUE);
			setbkcolor(WHITE);
			settextstyle(8, HORIZ_DIR, 5);
			outtextxy(screenWidth/2- textwidth("DANH SACH HOA DON")/2, 100, "DANH SACH HOA DON");
			// ve Background
			setfillstyle(SOLID_FILL, smallwindow_bg_color);
			bar(leTrai, leTren, lePhai, leTren + 34 + height/2 + height*20);
			setfillstyle(SOLID_FILL, LIGHTGREEN);			
			bar(leTrai, leTren, lePhai, leTren + 34);
			setbkcolor(title_bg_color);
			setcolor(BLACK);
			settextstyle(8, HORIZ_DIR, 3);
			outtextxy(leTrai + 35, leTren + 5 , "STT");
			outtextxy(leTrai + 130, leTren + 5 , "SO HOA DON");
			outtextxy(leTrai + 195 + 300, leTren + 5 , "TEN NHAN VIEN");
			outtextxy(leTrai + 60 + 900, leTren + 5 , "NGAY LAP");
			outtextxy(leTrai + 60 + 1100, leTren + 5 , "LOAI HOA DON");
			outtextxy(leTrai + 50 + 1350, leTren + 5, "OPTION");
			outtextxy(screenWidth/2 - textwidth((char*)("PAGE " + toString(currentPageNumber)+"/"+toString(pageNumber)).c_str())/2, leTren + 34 + height/2 + height*20 +30, (char*)("PAGE " + toString(currentPageNumber)+"/"+toString(pageNumber)).c_str() );			
			DisplayListBill();
			stt = 0;
			//ve khung
			setcolor(bg_border_color);
			line(leTrai, leTren, lePhai, leTren); 
			line(leTrai, leTren + 34, lePhai, leTren + 34);
			line(leTrai, leTren + 34 + height/2 + height * 20, lePhai, leTren+34 + height/2 +height*20);
			line(leTrai, leTren, leTrai, leTren + 34 + height/2 + height*20);
			line(leTrai + 25 + 90, leTren, leTrai + 25 + 90, leTren + 34 + height/2 + height*20);
			line(leTrai + 25 +290, leTren, leTrai + 25 + 290, leTren + 34 + height/2 + height*20);
			line(leTrai + 25 + 890, leTren, leTrai + 25 + 890, leTren + 34 + height/2 + height*20);
			line(leTrai + 25 + 1090, leTren, leTrai + 25 + 1090, leTren + 34 + height/2 + height*20);
			line(leTrai + 25 + 1340, leTren, leTrai + 25 + 1340, leTren + 34 + height/2 + height*20);
			line(lePhai, leTren, lePhai, leTren + 34 + height/2 + height*20);
		}
		void Action(){
			addButton.Action(this);
			printButton.Action(this);
			switch(state){
				case ADD:
					AddBillAction();
					break;
				case PRINT:
					PrintAction();
					break;
				case SELECT_EMPLOYEE:
					if(employeeToSelect == NULL){
						nhanvien->PrintActionToSelect();
					}
					else{
						info[1].CustomInit(employeeToSelect->id.c_str());
						info[2].CustomInit(toString(employeeToSelect->HO + " " + employeeToSelect->TEN).c_str());
						state = ADD;
						employeeToSelect = NULL;
					}
					break;
				case SELECT_MATERIAL:
					if(mNodeToSelect == NULL){
						vattu->PrintActionToSelect();
					}
					else{
						info[6].CustomInit(mNodeToSelect->data.MaVT.c_str());
						info[7].CustomInit(mNodeToSelect->data.TenVT.c_str());
						state = ADD;
						mNodeToSelect = NULL;
					}
					break;
				case EDIT:
					if(nodeNeedEdit==NULL)
					{
						state = ADD;
					}
					else
					{
						EditDirect();
					}
					break;
				
		
			}			
			// nhap du lieu
			int c=GetInput();
			int index=fieldPointer-info;
			if(fieldPointer!=NULL) {
				if(c==-1) fieldPointer->DeleteChar();
				else if(c==1||c==2){
					if(state==ADD){
						
						if(c==1) --index;
						else ++index;
						index=max(0,index);
						index=min(index,10);
						fieldPointer=&info[index];
					}
					
				}

				else if(c!=0)
				{
					if(index ==0)
					{
						if((c >= 97 &&c<=122))
						{
							c-=32;
							fieldPointer->AddChar((char)c);
						}
						else if(c<=57 && c>=48)
						{
							fieldPointer->AddChar((char)c);
						}
					}
					else if(index ==1)
					{
						if((c >= 97 &&c<=122))
						{
							c-=32;
							fieldPointer->AddChar((char)c);
						}
						else if(c<=57 && c>=48)
						{
							fieldPointer->AddChar((char)c);
						}
					}
					else if(index ==2)
					{
						if( (c >= 65 && c<=90 )||(c >= 97 &&c<=122) || c==32)
						{
							fieldPointer->AddChar((char)c);
						}
						fieldPointer->DuaVeDangThuong(tenNV);
					}
					else if(index ==6)
					{
						if((c >= 97 &&c<=122))
						{
							c-=32;
							fieldPointer->AddChar((char)c);
						}
						else if(c<=57 && c>=48)
						{
							fieldPointer->AddChar((char)c);
						}
					}
					else if(index == 7)
					{
						if( (c >= 65 && c<=90 )||(c >= 97 &&c<=122) || c==32)
						{
							fieldPointer->AddChar((char)c);
						}
						fieldPointer->DuaVeDangThuong(tenNV);
					}
					else if(index == 8)
					{
						if(c<=57 && c>=48)
						{
							fieldPointer->AddChar((char)c);
						}	
					}
					else if(index ==9)
					{
						if(c<=57 && c>=48)
						{
							fieldPointer->AddChar((char)c);
						}
					}
					else if(index== 10)
					{
						if(c<=57 && c>=48)
						{
							fieldPointer->AddChar((char)c);
						}
					}
					else{
						fieldPointer->AddChar((char)c);// neu khong co dong nay thi sua ben initedit se khong ghi dduoc cai gi
					}
				}	
			}
		}
		void WriteDataBillForAllEmployee(){
			ofstream fileOut;
			fileOut.open("nhanvien.txt", ios::trunc|ios::out);
			fileOut << nhanvien->dsNhanVien.sl << endl;
			for(int i = 0; i < nhanvien->dsNhanVien.sl; i++){
				fileOut << nhanvien->dsNhanVien.nhanVien[i]->HO << endl;
				fileOut << nhanvien->dsNhanVien.nhanVien[i]->TEN << endl;
				fileOut << nhanvien->dsNhanVien.nhanVien[i]->id << endl;
				fileOut << nhanvien->dsNhanVien.nhanVien[i]->PHAI << endl;
				// string fileName = nhanvien->dsNhanVien.nhanVien[i]->id + ".txt";
				BillNode* tmp = nhanvien->dsNhanVien.nhanVien[i]->HoaDon->First;
				fileOut << nhanvien->dsNhanVien.nhanVien[i]->HoaDon->sl << endl;
				while(tmp!=NULL){
					fileOut << tmp->data.soHD << endl;
					fileOut << tmp->data.loai << endl;
					fileOut << tmp->data.date.day << endl;
					fileOut << tmp->data.date.month << endl;
					fileOut << tmp->data.date.year << endl;
					DBNode* writeDB = tmp->data.dscthd.First;
					fileOut << tmp->data.dscthd.soluong << endl;
					while(writeDB != NULL){
						fileOut << writeDB->data.MAVT << endl;
						fileOut << writeDB->data.Soluong << endl;
						fileOut << writeDB->data.Dongia << endl;
						fileOut << writeDB->data.VAT << endl;
						writeDB = writeDB->next;
					}
					tmp = tmp->next;
				}
			}
			fileOut.close();
		}
		void ReadDataBill(){
			ifstream fileIn;
			fileIn.open("nhanvien.txt", ios::in);
			int sonhanvien;
			fileIn >> sonhanvien;
			Employee a;
			string temp;
			string mavt;
			float sl;
			float dongia; 
			float vat;
			int num;
			string sohoadon;
			char loai;
			int ngay;
			int thang;
			int nam;
			// fileIn.ignore();
			// getline(fileIn, temp);
			for(int i = 0; i < sonhanvien; i++){
				// string fileName = nhanvien->dsNhanVien.nhanVien[i]->id + ".txt";			
				getline(fileIn, a.HO);
				if(a.HO == ""){
					break;
				}
				getline(fileIn, a.TEN);
				getline(fileIn, a.id);
				fileIn >> a.PHAI;
				// getline(fileIn, temp);
				fileIn.ignore();
				
				nhanvien->dsNhanVien.Insert_Staff(a);
				pageNumber= nhanvien->dsNhanVien.sl/25 + 1;



				
				DBList cthd;
				while(1){
					getline(fileIn, sohoadon);
					if(sohoadon == ""){
						break;
					}
					fileIn >> loai; 
					fileIn >> ngay;
					fileIn >> thang;
					fileIn >> nam;
					fileIn >> num;			
					for(int j = 0; j < num; j++){
						fileIn.ignore();
						fileIn >> mavt >> sl >> dongia >> vat;
						//fileIn.ignore();
						cthd.Insert_Last_DBList(mavt,sl,dongia,vat);
					}
					nhanvien->dsNhanVien.nhanVien[i]->HoaDon->Insert_HD(sohoadon, ngay, thang, nam, loai, &cthd);
				}
			}
			fileIn.close();	
		}
};
class StatisticalTab: public Tab{
	private:
	protected:
		void DrawUI(){
			Tab::DrawUI();			
		}
	public:
		StatisticalTab(){};
		StatisticalTab(int x, int y, int w, int h, int basiccolor, int oncolor, char *txt) : Tab(x, y, w, h,basiccolor, oncolor, txt){
		}
		void Action(){			
		}		
};
int main(){	
	coordinateXOfCursorMouse =-1; // toa do X cua con tro chuot
	coordinateYOfCursorMouse =-1; // toa do Y cua con tro chuot
	isActive = true;	 
	initwindow(screenWidth, screenHeight, "Quan li vat tu");			// init window graphics kich thuoc 1920 x 1080
	MaterialTab vattu=MaterialTab(5+tab_width/2,tab_height/2+5,tab_width,tab_height,tab_basic_color,tab_on_color,"VAT TU");  // 205	21 400 32
	StaffTab nhanvien=StaffTab(5+tab_width*1.5f,tab_height/2+5,tab_width,tab_height,tab_basic_color,tab_on_color,"NHAN VIEN");
	BillTab hoadon=BillTab(5+tab_width*2.5f,tab_height/2+5,tab_width,tab_height,tab_basic_color,tab_on_color,"HOA DON", &vattu, &nhanvien); //  1005 21	400 32
	StatisticalTab thongke=StatisticalTab(5+ tab_width*3.5f, tab_height/2+5, tab_width, tab_height ,tab_basic_color, tab_on_color, "THONG KE");
	QuitButton quit;
	Tab* tab = &vattu;
	vattu.ReadData();
	nhanvien.ReadData();
	hoadon.ReadDataBill();
	while(isActive){
		setactivepage(1 - getactivepage());
		cleardevice();
		DrawBG();   // ve thanh cua so, khung backgroud va khung chua cac nut chuc nang
		UpdateMouseFlag(); // cap nhat toa do con tro chuot
		vattu.OnClick(tab);
		nhanvien.OnClick(tab);
		hoadon.OnClick(tab);
		thongke.OnClick(tab);
		quit.quitButton.Action(&quit);
		tab->Action();
		clearmouseclick(WM_LBUTTONDOWN);
		setvisualpage(getactivepage());
		delay(20);	
	}
	nhanvien.WriteData();
	vattu.SaveData();
	hoadon.WriteDataBillForAllEmployee();
	closegraph();
	return 0;
}
