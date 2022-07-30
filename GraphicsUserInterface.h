#pragma once		
#include<iostream>
#include<graphics.h>
#include<time.h>
#include<string.h>
#include<string>
#include<sstream>

// kich thuoc 
#define screenWidth 1920
#define screenHeight 1080
#define text_width 10
#define text_height 18

#define tab_width 400
#define tab_height 34
#define BORDEROFFSET 2
#define tab_basic_color 3 // xanh lo
#define tab_on_color  2 // green: xanh la cay
#define close_basic_color 4 // red:: do
// color
#define invalid_color 9 //xanh da troi nhat lightblue
#define valid_color 4 // MAU XANH LUC
const int smallwindow_bg_color = 14;
#define fieldborder_on_color 3 // xanh lo
#define smallwindow_bg_color 7 //xam nhat
#define bg_color WHITE	//trang
#define bg_border_color 8  //xam sam
#define title_bg_color 10 //	xanh la cay nhat lightgreen
#define addbutton_basic_color BLUE // xanh da troi:: 1
#define addbutton_oncolor GREEN //xanh la cay 2
#define fieldborder_basic_color 8 // xam sam
using namespace std;



int currentCoordinateXOfTextPointer; // toa do x mà con tro chuot dang tro toi
int currentCoordinateYOfTextPointer; // tao do y ma con tro chuot dang tro toi
int coordinateXOfCursorMouse; // toa do X cua con tro chuot khi click
int coordinateYOfCursorMouse; // toa do Y cua con tro chuot khi click



bool isLeftDown,isLeftUp;	
bool isActive;







// ------------------------------ HAM---------------------------------//////////////////////////
void DrawTabBG(){
	setfillstyle(SOLID_FILL,tab_basic_color);
	bar(0,0,screenWidth,tab_height+BORDEROFFSET+3);
}

 void DrawBG(){
		setfillstyle(SOLID_FILL,bg_color);
		bar(0,0,screenWidth,screenHeight);
		DrawTabBG();
		
		setcolor(tab_on_color);
		for(int i=0;i<BORDEROFFSET;i++){
			rectangle(i,tab_height+BORDEROFFSET+i+3,screenWidth-i-1,screenHeight-i-1);
		}
		setcolor(bg_border_color);
		rectangle(15,43,screenWidth-15,80);
		for(int i = 0; i < 2; i++){
			setcolor(BLACK);
			rectangle(1800 -75-1-i, tab_height/2+2 -17 -1-i, 1800 +75+i,  tab_height/2+2 + 17+1+i );
		}
		
}


bool isappear = true;
void DrawTextPointer(int centerX, int centerY){////////// ham ve con tro van ban khi nhap
	isappear = !isappear;
	if(isappear){
		setcolor(BLACK);
		line(centerX, centerY-10, centerX, centerY + 10);
	}
	delay(1);
}

void UpdateMouseFlag(){
	coordinateXOfCursorMouse=mousex();
	coordinateYOfCursorMouse=mousey();
	isLeftDown=GetAsyncKeyState(VK_LBUTTON)&1;
	isLeftUp=ismouseclick(WM_LBUTTONUP);
}
void DrawInputWindow(char* text){
		int width=1000;
		//
		setfillstyle(SOLID_FILL,smallwindow_bg_color);
		setcolor(smallwindow_bg_color);
		bar(screenWidth/2-width/2,220,screenWidth/2+width/2,550);
		setcolor(bg_border_color);
		rectangle(screenWidth/2-width/2,220,screenWidth/2+width/2,550);
		
		setcolor(WHITE);
		setfillstyle(SOLID_FILL,title_bg_color);
		bar(screenWidth/2-width/2,180,screenWidth/2+width/2,220);
		setbkcolor(title_bg_color);	
		outtextxy(screenWidth/2-textwidth(text)/2,190,text);
}

//
int GetInput(){
//
	int re=0;
	for(int i=65;i<=90;i++){
		if(GetAsyncKeyState((char)(i))& 1 ) {
			if(GetKeyState(VK_CAPITAL)&1)
			return i;
			else return i+32;
		}
	}
	for(int i=48;i<=57;i++){
		if(GetAsyncKeyState((char)i)& 1 ) {
			return i;
		}
	}
	if(GetAsyncKeyState(VK_BACK)& 1 ) return -1;
	if(GetAsyncKeyState(VK_SPACE)&1) return ' ';
	if(GetAsyncKeyState(VK_TAB)&1) return  (int)'\t';
	if(GetAsyncKeyState(VK_UP)&1) return 1;
	if(GetAsyncKeyState(VK_DOWN)&1) return 2;
	return re;
}
/////////// HAM CHUYEN SO THANH CHUOI ////////////////////////////////////////////
string inttostring_(int x){
	int mod;
	string s = "";
	while(x>0){
		mod = x%10;
		switch(mod){
			case 0:
				s = "0" + s;
				break;
			case 1:
				s = "1" + s;
				break;
			case 2:
				s = "2" + s;
				break;
			case 3:
				s = "3" + s;
				break;
			case 4:
				s = "4" + s;
				break;
			case 5:
				s = "5" + s;
				break;
			case 6:
				s = "6" + s;
				break;
			case 7:
				s = "7" + s;
				break;
			case 8:
				s = "8" + s;
				break;
			case 9:
				s = "9" + s;
				break;
			default:
				break;
		}
		x /= 10;
	}
	return s;
}
///////////// HAM CHUYEN STRING THANH MANG KY TU ////////////////////////////////
char *_stringtochar_(string y,char *x)
{
    int i;
    for(i = 0;i < y.length();i++)
    { 
        x[i] = y[i];
    }
    x[i] = '\0';
    return x;
}
string chartostring(char *temp){
	string str= "";
	for(int i = 0; temp[i]!='\0'; i++){
		str = str + temp[i];
	}
	return str;
}
template<class T>
string toString(T x){
	stringstream ss;
	ss << x;
	string str = ss.str();
	return str;
}
template<class T>
float toFloat(T x){
	stringstream ss;
	ss << x;
	float a;
	ss >> a;
	return a;
}




///////////////////////////////////////////////////////////////////////////////////
/////////////////////// -----------User Interface------------------///////////////////////////
class UI{
	private:
	protected:
		int centerX, centerY;
		int width, height;
		int currentColor;
		int basicColor;
		int	onColor;
		int textColor;
		bool OnRange(){
			if(coordinateXOfCursorMouse >= centerX - width/2 && coordinateXOfCursorMouse <= centerX + width/2 && coordinateYOfCursorMouse >= centerY-height/2 && coordinateYOfCursorMouse <= centerY+height/2){
				return true;
			}
			return false;
		}
	public:
		UI(){}
		UI(int x, int y,int w, int h, int basiccolor, int oncolor, int textcolor = WHITE){
			centerX = x;
			centerY = y;
			width = w;
			height = h;
			currentColor = basiccolor;
			basicColor = basiccolor;
			onColor = oncolor;
			textColor = textcolor;
		}
		virtual void DrawUI(){
			setbkcolor(currentColor);
			setfillstyle(SOLID_FILL, currentColor);
			bar(centerX - width/2, centerY - height/2, centerX + width/2, centerY + height/2);
		}
		
		
};


//////////////////////////////////// --------------------------BUTTON --------------///////////////////////////////////
template<class T>
class Button :public UI
{
	private:
		bool animation;
		char text[30];
		typedef void (T::*Function)();
		Function todo;
	public:
		Button(){}
		Button(int x, int y, int w, int h, int basiccolor, int oncolor, char text[30], Function toDo, int textcolor = WHITE): UI(x, y, w, h, basiccolor, oncolor, textcolor){
			strcpy(this->text, text);
			todo = toDo;
			animation = false;
		}

		void DrawUI(){
			UI::DrawUI();
			if(OnRange()){
				// Ve animation fill
				currentColor = onColor;
				setbkcolor(currentColor);
				setfillstyle(SOLID_FILL, currentColor);
				bar(centerX-width/2, centerY-height/2, centerX+width/2, centerY+height/2);
				animation = true;
			}
			
			else {
			
				animation = false;
				currentColor = basicColor;
			}
			setcolor(textColor);
			int w = textwidth(text);
			int h = textheight(text);
			outtextxy(centerX-w/2, centerY-h/2, text);
		}
	
		void Action(T* object){
			DrawUI();
			
			if(OnRange() && isLeftDown){
			
				(object->*todo)();
			}
		}

	
};

///////////////////////////////////////////////////////////////////////////////////////////////////////

// Tab
class Tab: public UI{
	private:
	protected:
		char text[30];
		
	public:
		Tab(): UI(){};
		Tab(int x, int y, int w, int h, int basiccolor, int oncolor, const char* textIn, int textColor = WHITE): UI(x, y, w, h, basiccolor, onColor, textColor){
			strcpy(this->text, textIn);
		}
		
		virtual void DrawUI(){ //ghi de cua UI
			UI::DrawUI();
			setcolor(textColor);
			settextstyle(BOLD_FONT, 0, 3);
			int w=textwidth(text);
			int h=textheight(text);
			outtextxy(centerX-w/2,centerY-h/2,text);//Can le test
		}
		void OnClick(Tab* &tab){
			if((OnRange() && isLeftDown) || tab == this){
				tab = this;
				currentColor = tab_on_color;
			}
			else if(tab!= this){
				currentColor = basicColor;
			}
			Tab::DrawUI();
		}
		virtual void Action()= 0;
		
};
/////////////////////////////////////////////////////////////////////////////////

class InputField: public UI{
	private:
		int index; // vi tri dang nhap
		int maxChar; // so luong ky tu nhap toi da
		char *field; // noi dung nhap
		char announcement[61]; // noi dung thong bao
		char fieldName[41]; // ten muc nhap
		int validAnnouncementColor; // mau thong bao hop le
		int invalidAnnouncementColor; // mau thong bao khong hop le
		int currentAnnouncementColor; // mau thong bao hien tai
		int currentBorderColor;	// mau vien hien tai
	private:
		void DrawUI(){
			//UI::DrawUI();
			settextstyle(10, 0, 1);
			setcolor(textColor);
			setbkcolor(smallwindow_bg_color);
			outtextxy(centerX - width/2 ,centerY - text_height + 7, field);
		
			// Field Name
			setbkcolor(smallwindow_bg_color);
			outtextxy(centerX - width/2 - textwidth(fieldName), (centerY - text_height/2), fieldName); 
			// border
			setcolor(currentBorderColor);
			rectangle(centerX-width/2 -1,centerY-height/2-1,centerX+width/2 +1,centerY+height/2 +1);
			rectangle(centerX-width/2 -2,centerY-height/2-2,centerX+width/2 +2,centerY+height/2 +2);
			//put announcement
			setcolor(currentAnnouncementColor);
			outtextxy(centerX-textwidth(announcement)/2,centerY+height/2+3,announcement);
			}
		void OnClick(InputField* &fieldpointer){
			if((OnRange()&&isLeftDown)||fieldpointer==this){
				currentColor=onColor;
				currentBorderColor=fieldborder_on_color;
				fieldpointer=this;
				
			}
			else  {
				currentColor=basicColor;
				currentBorderColor = fieldborder_basic_color;// mau trang
			}
		}
	public:
		InputField(){};
		InputField(int x, int y, int maxchar, int h, int basiccolor, int oncolor, char *fieldname, char *infield, int textcolor = BLACK ):UI(x, y, maxchar*12, h, basiccolor, oncolor, textcolor){
			maxChar = maxchar;
			strcpy(fieldName, fieldname);
			index = 0;
			field = infield;
			field[index] = '\0';
			announcement[index] = '\0';
			invalidAnnouncementColor = invalid_color;
			validAnnouncementColor = valid_color;
		}
		void AddChar(char c){
			if(index== maxChar) return;
			field[index++] = c;
			field[index] = '\0';

		}
		void DeleteChar(){
			if(index == 0){
				return;
			}
			field[--index] = '\0';
		}
		void Action(InputField* &fieldpointer){
			OnClick(fieldpointer);
			DrawUI();
			if(fieldpointer==this) 	DrawTextPointer(centerX-width/2+textwidth(field),centerY);
		}
		void BlankField(){// lam trong thanh nhap noi dung
			index=0;
			field[0]='\0';
			announcement[0]='\0';
		}
		void CustomInit(const char* text){//Khoi tao field void doan text da co san
			strcpy(field,text);
			index=strlen(field);
			announcement[0]='\0';//blank
		}
		void CustomInit(int val){
			char temp[10];
			_stringtochar_(inttostring_(val), temp);
			strcpy(field,temp);
			index=strlen(field);
			announcement[0]='\0';//blank
		}
		void Announcement(const char* announce,bool isValid){
			strcpy(announcement,announce);
			if(isValid) currentAnnouncementColor=validAnnouncementColor;
			else currentAnnouncementColor= invalidAnnouncementColor;
		}
		bool CheckString(){
			if(strlen(field)==0) {
				Announcement("Khong the trong!",false);
				return false;	
			}
			Announcement("OK",true);
			return true;
		}
		bool CheckInt(){
			if(strlen(field) == 0){
				Announcement("Khong the de trong!", false);
				return false;
			}
			for(int i= 0; i < strlen(field); i++){
				if(!(field[i]>= 48 && field[i] <= 57)){
					Announcement("Chi duoc nhap so", false);
					return false;
				}
			}
			Announcement("OK", true);
			return true;
		}
		void DuaVeDangThuong(char *s)
		{
			for(int i = 0 ; i < strlen(s);i++)
						{
							s[i]= tolower(s[i]);
						}
			s[0] = toupper(s[0]);
			for(int i = 0 ; i < strlen(s);i++)
		{
			if(s[i]==' '&& s[i+1]!=' ')
			{
				s[i+1] = toupper(s[i+1]);
			}
		}
		}
};




//////////////////////////////////////////////////////////////////////////////////
