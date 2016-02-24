#include "../Control/Control.h"
#include "../DbCon/DbCon.h"
#include "../UserForm/UserForm.h"// 刷新权限界面
#include "../TableForm/TableForm.h"// 刷新报表统计界面
#include "../ClientForm/ClientDb.h"
#include <string.h>

/**************************************************************************************
 Control组件基类公有成员函数的定义

***************************************************************************************/

Control::Control(WINDOW *pFather,int height,int width,int starty,int startx,int contype)
{
	if (pFather == NULL)
	{
		this->pCon = newwin(height,width,starty,startx);
		
	}
	else
	{
		this->pCon = derwin(pFather,height,width,starty,startx);
	}
	this->height = height;
	this->width = width;
	this->starty = starty;
	this->startx = startx;
	this->contype = contype;
	this->pFather  = pFather;
}


Control::~Control()
{
	delwin(this->pCon);
}


WINDOW* Control::GetHandle()
{
   return pCon;
}

int Control::GetType()
{
    return contype;
}

char * Control::Getdata()
{

	return data;
}


void Control::KeyListen(int &key)
{

}

void Control::GetFocus()
{

}


/****************************************************************************************
 Label标签派生类公有成员函数的定义

*****************************************************************************************/
Label::	Label(WINDOW *pFather,int height,int width,int starty,int startx,char *data,int contype)
              :Control(pFather,height,width,starty,startx,contype)
{
	this->data = new char[strlen(data)+1];
	strcpy(this->data,data);
}
Label::~Label()
{
	delete []data;
}

void Label::show()
{
	if (width > 20 && width <=60)
	{
		wbkgd(this->pCon,COLOR_PAIR(7));
		mvwprintw(this->pCon,height/2,(width-strlen(data))/2,"%s",data);
	}
	else if (width > 60)
	{
		wbkgd(this->pCon,COLOR_PAIR(2));
		mvwprintw(this->pCon,height/2,4,"%s",data);
	}
	else
	{
		wbkgd(this->pCon,COLOR_PAIR(2));
		mvwprintw(this->pCon,height/2,(width-strlen(data))/2,"%s",data);
	}
	wrefresh(this->pCon);
}

/****************************************************************************************
 Combobox下拉框派生类公有成员的定义

****************************************************************************************/

ComboxItem::ComboxItem(WINDOW *pFather,int height,int width,int starty,int startx,int contype,char *ID,char *Name)
						:Control(pFather,height,width,starty,startx,contype)
{
	strcpy(this->ID,ID);
	strcpy(this->Name,Name);
}

void ComboxItem::show()
{
 	wbkgd(this->pCon,COLOR_PAIR(1));
	wclear(pCon);
 	mvwprintw(this->pCon,0,(width-strlen(Name))/2,"%s",Name);
 	wrefresh(this->pCon);
}

void ComboxItem::GetFocus()
{
	wbkgd(this->pCon,COLOR_PAIR(3));
	keypad(this->pCon,true);
	mvwprintw(this->pCon,0,(width-strlen(Name))/2,"%s",Name);
	wrefresh(this->pCon);
}

int Combobox::Add_CallBack(void *pData,int cols,char **colvalu,char **colname)
{
	pList head = (pList)pData;
	Control *pCom;
	static int line = 0;
	int y,x;
	getbegyx(Combobox::pBox->GetHandle(),y,x);	
	if (head->pNext == NULL)
	{
		line = y+3;
	}
	pCom = new ComboxItem(NULL,1,13,line,x+1,6,colvalu[0],colvalu[1]);
	List_add(head,pCom);
	line = line + 1;
	return 0;
}

Combobox *Combobox::pBox = NULL;
Combobox::Combobox(WINDOW *pFather,int height,int width,int starty,int startx,int contype,char *sql)
					:Control(pFather,height,width,starty,startx,contype)
{
	Combobox::pBox = this;
	pNode = List_init(NULL);	
	this->data = new char[12];// 为下拉框的内容申请空间
	memset(this->data,0,sizeof(this->data));// 清空下拉框的内容
	strcpy(this->ID,"");					// 初始化下拉框内容的ID
    (DbSingles::GetSingle())->GetData(sql,Combobox::Add_CallBack,pNode);
}

Combobox::~Combobox()
{
	List_free(pNode);
}

void Combobox::show()
{
	pList pTemp;
	ComboxItem *Data;
	pTemp = pNode->pNext;
	while(pTemp && strcmp(this->ID,"") !=0 )
	{
		Data = (ComboxItem *)(pTemp->pData);
		if (strcmp(Data->ID,this->ID) == 0)
		{
			strcpy(this->data,Data->Name);
			break;
		}
		else
			pTemp = pTemp->pNext;
	}
	wclear(pCon);
	wbkgd(this->pCon,COLOR_PAIR(2));
	box(this->pCon,0,0);
	mvwprintw(this->pCon,1,1,this->data);
	mvwprintw(this->pCon,1,width-2,"+");
	wrefresh(this->pCon);
}


void Combobox::showmin()
{
	wclear(pCon);
	wbkgd(this->pCon,COLOR_PAIR(2));
	box(this->pCon,0,0);
	mvwprintw(this->pCon,1,1,data);
	mvwprintw(this->pCon,1,width-2,"-");
	wrefresh(this->pCon);
}


void Combobox::GetFocus()
{
	curs_set(0);
    wstandout(this->pCon);
	keypad(this->pCon,true);
	mvwprintw(this->pCon,1,width-2,"+");
	wrefresh(this->pCon);
}

void Combobox::MenuClear()
{
	Control *fp;
	pList pTemp;
	pTemp = pNode->pNext;
	while (pNode->pNext)
	{
		fp = (Control *)(pTemp->pData);
		wclear(fp->GetHandle());
		wbkgd(fp->GetHandle(),COLOR_PAIR(2));
		wrefresh(fp->GetHandle());
		pTemp = pTemp->pNext;
		if (pTemp == pNode->pNext)
		{
			break;
		}
	}
}



void Combobox::KeyListen(int &key)
{
	Control *fp;
	pList pTemp;

	if (key == 10)
	{
		showmin();
		pTemp = pNode->pNext;
		while (pNode->pNext)
		{
			fp = (Control *)(pTemp->pData);
			fp->show();
			pTemp = pTemp->pNext;
			if (pTemp == pNode->pNext)
			{
				break;
			}
		}
		while(pTemp)
		{
			fp = (Control *)(pTemp->pData);
			fp->GetFocus();
			key = wgetch(fp->GetHandle());
			if (key == 10)
			{
				strcpy(this->data,((ComboxItem *)fp)->Name);
				strcpy(this->ID,((ComboxItem *)fp)->ID);
				MenuClear();
				if (UserPower::pPower != NULL)
				{
					UserPower::pPower->show();
				}
				else if (TableForm::pTableForm != NULL)
				{
					TableForm::pTableForm->show();
					wclear(TableForm::pTable->GetHandle());
					wrefresh(TableForm::pTable->GetHandle());
				}
				break;
			}
			switch(key)
			{ 
			case KEY_DOWN:
				pTemp = pTemp->pNext;
				break;
			case KEY_UP:
				pTemp = pTemp->pRev;
				break;
			}
			fp->show();
	   
		}

	}
}

/*************************************************************************************
 Notic提示框类公有成员的定义

*************************************************************************************/
Notic::Notic(WINDOW *pFather,int height,int width,int starty,int startx,char *data,int contype)
			:Control(pFather,height,width,starty,startx,contype)
{
	this->data = new char[strlen(data)+1];
	strcpy(this->data,data);
}

Notic::~Notic()
{
	delete []data;
}


void Notic::show()
{
	wclear(this->pCon);
	wbkgd(this->pCon,COLOR_PAIR(7));
	box(this->pCon,0,0);
	mvwprintw(this->pCon,height/2,(width-strlen(data))/2,"%s",data);
	wrefresh(this->pCon);
}


/****************************************************************************************
 Edit编辑框派生类公有成员函数的定义

****************************************************************************************/
Edit::Edit(WINDOW *pFather,int height,int width,int starty,int startx,int len,int type,int contype,bool pwd)
            :Control(pFather,height,width,starty,startx,contype)
{
	this->len = len;
	this->type = type;
	this->pwd = pwd;
	this->data = new char[this->len+1];// new申请的空间没有清零，存有任意值
	memset(this->data,0,sizeof(this->data));// 清空编辑框的内容指针，防止打印有误
}

Edit::~Edit()
{
    delete []data;
}

void Edit::show()
{
	wclear(pCon);
    wbkgd(pCon,COLOR_PAIR(2));
	box(this->pCon,0,0);
    mvwprintw(pCon,1,1,data);
	wrefresh(this->pCon);
}



void Edit::GetFocus()
{
	curs_set(1);
	keypad(pCon,TRUE);	
	mvwprintw(pCon,1,strlen(data)+1,"");
	wrefresh(pCon);
}



void Edit::KeyListen(int &key)
{
    int y,x;
	getyx(pCon,y,x);
	if (key == KEY_LEFT && x != 1)
	{
		mvwprintw(pCon,y,x-1,"");
		wrefresh(pCon);
	}
	else if (key == KEY_RIGHT && x<=strlen(data))
	{
		mvwprintw(pCon,y,x+1,"");
		wrefresh(pCon);
	}
  if(type == 1)
  {
      if(((key>='0'&&key<='9')||(key>='a'&&key<='z')||(key>='A'&&key<='Z'))
         &&(strlen(data) < len))
      {	
 		  if (x == strlen(data)+1)
 		  {
 			   waddch(pCon,key);
               data[strlen(data)] = key;
               data[strlen(data)+1] = '\0';

 		  }
 		  else
		  {
			  char temp[10];
			  y = x;
			  strcpy(temp,data);
			  data[x-1] = key;
			  for (;temp[x-1]!='\0';x++)
			  {
				  data[x] = temp[x-1];
			  }
                  data[x] = '\0'; 
				  mvwprintw(pCon,1,1,data);
		          mvwprintw(pCon,1,y+1,"");
		  }
          
		      wrefresh(pCon);
      }

  }
  else if(((key>='0'&&key<='9')||(key>='a'&&key<='z')||(key>='A'&&key<='Z'))
         &&(strlen(data) < len))
  { 
          waddch(pCon,'*');
          data[strlen(data)] = key;
          data[strlen(data)+1] = '\0';   
  }
   if(key == KEY_BACKSPACE && strlen(data) > 0)
   {
	   if ( x == strlen(data)+1)
	   {
		   wprintw(pCon,"\b \b");
		   data[strlen(data)-1] = '\0';
	   }
	   else if(x != 1 && type == 1)
	   {
		   y = x;
	       for (;data[x-1]!='\0';x++)
	       {
			   data[x-2] = data[x-1];
	       }
		   data[x-2] = '\0';
		   wclear(pCon);
		   box(pCon,0,0);
		   mvwprintw(pCon,1,1,data);
		   mvwprintw(pCon,1,y-1,"");
	   }   
   }
}



/***************************************************************************************
 Button按钮派生类公有成员函数的定义

****************************************************************************************/
Button::Button(WINDOW *pFather,int height,int width,int starty,int startx,char *data,int contype)
              :Control(pFather,height,width,starty,startx,contype)
{
	pShadow = derwin(pFather,height,width,starty+1,startx+1);
	this->data = new char[strlen(data)+1];
	strcpy(this->data,data);
}

Button::~Button()
{
	delete []data;
	delete pAct;
	delwin(pShadow);
}

void Button::show()
{
	wbkgd(this->pShadow,COLOR_PAIR(4));
	wrefresh(this->pShadow);

	wbkgd(this->pCon,COLOR_PAIR(3));
	box(this->pCon,0,0);
	mvwprintw(this->pCon,1,(width-strlen(data))/2,"%s",data);
	wrefresh(this->pCon);
}


void Button::GetFocus()
{
	curs_set(0);
	keypad(pCon,true);
	wstandout(this->pCon);
	mvwprintw(this->pCon,1,(width-strlen(data))/2,"%s",data);
	wrefresh(pCon);
	
}


void Button::AddAction(ActionListen *pAct)
{
	this->pAct = pAct;
}


void Button::KeyListen(int &key)
{
    int y,x;
    if(key == 10)
    {
         wbkgd(pCon,COLOR_PAIR(5));
         getbegyx(pCon,y,x);
	     wrefresh(pCon);
	     mvwin(pCon,y+1,x+1);
         wbkgd(pCon,COLOR_PAIR(3));
	     GetFocus();
	     usleep(300000);
	     mvwin(pCon,y,x);
         show();
		 usleep(80000);
         pAct->DoAction(key);
    }

}


/************************************************************************************
ActionListen事件监听类构造函数的定义

************************************************************************************/
ActionListen::ActionListen(Form *pWin)
{
    this->pWin = pWin;
}



/*************************************************************************************
 Form窗口类公有成员的定义

*************************************************************************************/
Form::Form(int height,int width,int starty,int startx,int contype)
           :Control(NULL,height,width,starty,startx,contype)
{
    pfirst = List_init(NULL);
	pShadow = derwin(stdscr,height,width,starty+1,startx+1);
	flag = true;
}

Form::~Form()
{
    List_free(pfirst);//释放窗口的控件链表
	delwin(pShadow);
}


void Form::show()
{
    Control *fp;
    pList pTemp;
	wbkgd(this->pShadow,COLOR_PAIR(4));
	wrefresh(this->pShadow);
    box(pCon,0,0);
    wbkgd(pCon,COLOR_PAIR(2));
    wrefresh(pCon);

    pTemp = pfirst->pNext;
	while (pfirst->pNext)
	{
		fp = (Control *)(pTemp->pData);
		fp->show();
		pTemp = pTemp->pNext;
		if (pTemp == pfirst->pNext)
		{
			break;
		}
	}

}


void Form::KeyListen(int &key)
{
    pList pTemp,pTemp1;
    Control *fp;
    key = KEY_DOWN;
    pTemp = pfirst->pNext;
    while(flag)
    {
       fp = (Control *)(pTemp->pData);
       if(fp->GetType() != 1 && fp->GetType() != 4)
       {
		   if (key==KEY_DOWN || key== KEY_UP || key=='\t'|| key==10)
		   {
			   fp->GetFocus();
		   }	   
	   key = wgetch(fp->GetHandle());
       switch(key)
       { 
       case '\t':
			pTemp = pTemp->pNext;
	        break;
       case KEY_DOWN:
			pTemp = pTemp->pNext;
            break;
       case KEY_UP:
			pTemp = pTemp->pRev;
            break;
	   case 27:	// Esc键
			pTemp1 = pTemp;
			pTemp = pTemp->pNext;
			while (((Control *)(pTemp->pData))->GetType() != 4)
			{
				pTemp = pTemp->pNext;
				if (pTemp == pTemp1)
				{
					pTemp = pTemp1;
					break;
				}
			}
			if (pTemp != pTemp1)
			{
				 fp->show();
				((Control *)(pTemp->pData))->KeyListen(key);
				pTemp = pTemp1;
				fp->GetFocus();
			}
				break;
       default:
				fp->KeyListen(key);
				if (fp->GetType() == 6)
				{
					fp->show();
 					((Control *)(pTemp->pNext->pNext->pData))->show();
				}
				break;		      
       }	   
       if(fp->GetType() == 3 || fp->GetType() == 6)
       {
		   if (key == KEY_DOWN || key == KEY_UP || key == '\t')// 实现按钮的动态跳转
           fp->show();
		   else if (key == 0)// 登录失败光标定位到编辑框
		   {
			   key = KEY_DOWN;
			   pTemp = pfirst->pNext;
		   }
		   
       }

       }
       else
       {
           if(key == KEY_DOWN || key == '\t')
           pTemp = pTemp->pNext;
           else
           pTemp = pTemp->pRev;

       }

    }
}

/***************************************************************************************
 Table报表派生类公有成员的定义

****************************************************************************************/
Table::Table(WINDOW *pFather,int height,int width,int starty,int startx,int contype)
 			:Control(pFather,height,width,starty,startx,contype)
{
	this->precord = List_init(NULL);
	this->pNode = NULL;
	this->sum = 0;
	this->count = 1;
	this->n = 0;
	pLable = new Label(NULL,1,61,LINES-3,1,(char *)"总共0  条记录，共0  页，当前第0  页，当前页有0  条记录",1);
}

Table::~Table()
{
	List_free(precord);
}


void Table::show()
{
	pList pTemp;
	TableItem *pTable;
	wbkgd(this->pCon,COLOR_PAIR(2));
	wclear(this->pCon);//清空表格里的内容
	wrefresh(this->pCon);
	pTemp = precord->pNext;
	while (precord->pNext)
	{
		pTable = (TableItem *)(pTemp->pData);
		if (this->tabtype == 1)
		{
			pTable->show();//显示每一条记录
		}
		else if (this->tabtype == 2)
		{
			pTable->ClientShow();
		}
		else
			pTable->TableShow();		
		pTemp = pTemp->pNext;
		if (pTemp == precord->pNext)
		{
			break;
		}
	}
	wclear(pLable->GetHandle());
	sprintf(pLable->Getdata(),"总共%d条记录，共%d页，当前第%d页，当前页有%d条记录",sum,sum%10 != 0?(sum/10+1):(sum/10),n/10+1,List_count(precord));
	pLable->show();
}


void Table::UpdataTable()
{
	pList pTemp;
	char sql[256] = "";
	TableItem *pTable;
	int icount = 1;
	List_free(this->precord);
	precord = List_init(NULL);	
	if (sum == 0)
	{
		show();
		return;
	}
	RunSql(this->flag-1);
	show();
	pTemp = precord->pNext;
	pNode = NULL;
	while (pTemp)
	{		
		if (icount == this->count)
		{
			pTable = (TableItem *)(pTemp->pData);
			pTable->SelectFocus();
			pNode = pTable;
			break;
		}
		else
		{
			pTemp = pTemp->pNext;
			icount++;
		}
	}

}


void Table::KeyListen(int &key)
{
	int icount = 1;
	int list_count;
	char sql[300] = "";	
	static pList pTemp = NULL;
	Notic *pNotic;
	TableItem *pTableItem;
	if (key == 10)
	{
		this->count = 1;
		this->sum = 0;
		this->pNode = NULL;
		List_free(this->precord);
		precord = List_init(NULL);
		RunSql(this->flag);
		if (this->sum == 0)
		{	
			show();
			pNotic = new Notic(pCon,3,32,2,12,(char *)"未查到相关记录，按任意键继续",5);
			pNotic->show();
			wgetch(pCon);
			wclear(pCon);
			wrefresh(pCon);
			delete pNotic;
			return;
		}

		n = 0;
		RunSql(this->flag-1);
		show();		
	}
	    pTemp = precord->pNext;
		while (pTemp)
		{		
			if (icount == this->count)
			{
				break;
			}
			else
			{
				pTemp = pTemp->pNext;
				icount++;
			}
		}
		while (pTemp)
	{			
		pTableItem = (TableItem *)(pTemp->pData);
		pTableItem->GetFocus();
		key = wgetch(pTableItem->GetHandle());	
		switch(key)
		{
		case KEY_DOWN:
			pTemp = pTemp->pNext;
			if (pTemp == precord->pNext)
			{
				this->count = 1;
			}
			else 
				this->count = this->count+1;
			break;
		case KEY_UP:
			pTemp = pTemp->pRev;
			this->count = this->count-1;
			if (this->count == 0)
			{
				list_count = List_count(precord);
				this->count = list_count;
			}
			break;
		}
		if (this->tabtype == 1)
		{
				pTableItem->show();
		}
		else if (this->tabtype == 2)
		{
				pTableItem->ClientShow();
		}
		else
		{
				pTableItem->TableShow();
		}
		if ((key == KEY_NPAGE && (n+10) < sum)||(key == KEY_PPAGE && (n-10) >= 0))
		{
			if (key == KEY_NPAGE)
			{
				n = n + 10;
			}
			else
				n = n - 10;
			List_free(this->precord);
			precord = List_init(NULL);
			RunSql(this->flag-1);
			show();
			pTemp = precord->pNext;	
			this->count = 1;
		}
		else if (key == 10)
		{
			pTableItem->SelectFocus();
			this->pNode = pTableItem;
			return;
		}
	}

}


void Table::RunSql(int flag)
{
	char sql[888] = "";	
	switch(flag)
	{
	case 1:
		sprintf(sql,"select video_id,sum(play_count) as count from Tbl_video_details where video_id in(select video_id from Tbl_video_message where channel_id like \"%%%s%\" and area_id like \"%%%s%\" and type_id like \"%%%s%\") and play_time >= \"%s\" and play_time <= \"%s\" group by video_id order by count desc limit 10 offset %d",TableForm::pTableForm->channel_id,TableForm::pTableForm->area_id,TableForm::pTableForm->type_id,TableForm::pTableForm->startdate,TableForm::pTableForm->enddate,n);	
		(DbSingles::GetSingle())->GetData(sql,Census_CallBack,precord);
		break;
	case 2:
		sprintf(sql,"select video_id,sum(play_count) as count from Tbl_video_details where video_id in(select video_id from Tbl_video_message where channel_id like \"%%%s%\" and area_id like \"%%%s%\" and type_id like \"%%%s%\") and play_time >= \"%s\" and play_time <= \"%s\" group by video_id order by count desc",TableForm::pTableForm->channel_id,TableForm::pTableForm->area_id,TableForm::pTableForm->type_id,TableForm::pTableForm->startdate,TableForm::pTableForm->enddate);
		(DbSingles::GetSingle())->GetData(sql,Census_CallBack,NULL);
		break;
	case 5:
		 sprintf(sql,"select * from Tbl_user where user_name like \"%%%s%\" and user_account like \"%%%s%\" and user_stat = 1 limit 10 offset %d",user_name,user_account,n);
		 (DbSingles::GetSingle())->GetData(sql,Search_CallBack,this->precord);
		break;
	case 6:
		sprintf(sql,"select * from Tbl_user where user_name like \"%%%s%\" and user_account like \"%%%s%\" and user_stat = 1",user_name,user_account);
		(DbSingles::GetSingle())->GetData(sql,Search_CallBack,NULL);
		break;
	case 7:
		sprintf(sql,"select * from Tbl_cuser where user_name like \"%%%s%\" and user_account like \"%%%s%\" and user_stat = 1 limit 10 offset %d",user_name,user_account,n);
		(DbSingles::GetSingle())->GetData(sql,Client_CallBack,this->precord);
		break;
	case 8:
		sprintf(sql,"select * from Tbl_cuser where user_name like \"%%%s%\" and user_account like \"%%%s%\" and user_stat = 1",user_name,user_account);
		(DbSingles::GetSingle())->GetData(sql,Client_CallBack,NULL);
		break;
	}
}

/***************************************************************************************
 TableItem报表记录派生类公有成员的定义

****************************************************************************************/
TableItem::TableItem(WINDOW *pFather,int height,int width,int starty,int startx,int contype,char *user_id,char *user_name,char *user_account,char *user_remark,char *role,char *logintime)
					:Control(pFather,height,width,starty,startx,contype)
{
	this->user_id = new char[strlen(user_id)+1];
	strcpy(this->user_id,user_id);
	this->user_name = new char[strlen(user_name)+1];
	strcpy(this->user_name,user_name);
	this->user_account = new char[strlen(user_account)+1];
	strcpy(this->user_account,user_account);
	this->user_remark = new char[strlen(user_remark)+1];
	strcpy(this->user_remark,user_remark);
	this->role_id = new char[strlen(role)+1];
	strcpy(this->role_id,role);
	this->logintime = new char[strlen(logintime)+1];
	strcpy(this->logintime,logintime);
}

TableItem::~TableItem()
{
	delete []user_id;
	delete []user_name;
	delete []user_account;
	delete []user_remark;
	delete []role_id;
}


void TableItem::show()// 显示一条记录
{
	wbkgd(pCon,COLOR_PAIR(2));
	mvwprintw(pCon,0,1,"%s",user_id);
	mvwprintw(pCon,0,14,"%s",user_name);
	mvwprintw(pCon,0,29,"%s",user_account);
	mvwprintw(pCon,0,43,"%s",user_remark);
	mvwprintw(pCon,0,56,"%s",logintime);
	wrefresh(pCon);
}


void TableItem::ClientShow()
{
	wbkgd(pCon,COLOR_PAIR(2));
	mvwprintw(pCon,0,1,"%s",user_id);
	mvwprintw(pCon,0,12,"%s",user_name);
	mvwprintw(pCon,0,27,"%s",user_account);
	mvwprintw(pCon,0,38,"%s",logintime);
	mvwprintw(pCon,0,53,"%s",user_remark);
	wrefresh(pCon);
}

void TableItem::TableShow()
{
	wbkgd(pCon,COLOR_PAIR(2));
	mvwprintw(pCon,0,1,"%s",user_id);
	mvwprintw(pCon,0,14,"%s",user_name);
	mvwprintw(pCon,0,29,"%s",user_account);
	mvwprintw(pCon,0,43,"%s",user_remark);
	mvwprintw(pCon,0,57,"%s",role_id);
	mvwprintw(pCon,0,70,"%s",logintime);
	wrefresh(pCon);
}


void TableItem::GetFocus()// 记录的焦点停留
{
	wbkgd(pCon,COLOR_PAIR(3));
	curs_set(0);
	keypad(pCon,true);
	wrefresh(pCon);
}


void TableItem::SelectFocus()// 按回车，选定一条记录后的样式
{
	wbkgd(pCon,COLOR_PAIR(1));
	wrefresh(pCon);
}
