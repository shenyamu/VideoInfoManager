#include <string.h>
#include "../TableForm/TableForm.h"
#include "../TableForm/TableAction.h"


Table *TableForm::pTable = NULL;
TableForm *TableForm::pTableForm =NULL;
TableForm::TableForm(int height,int width,int starty,int startx,int contype)
					:Form(height,width,starty,startx,contype)
{
	this->pTableForm = this;
	Control *pCom;
	ActionListen *pAction;
	char sql[512] = "";
	mvwhline(this->pCon,7,0,0,COLS);
	mvwhline(this->pCon,9,0,0,COLS);
	mvwhline(this->pCon,LINES-4,0,0,COLS);
	pCom = new Table(this->pCon,10,COLS-2,10,1,4);
	TableForm::pTable = (Table *)pCom;
	TableForm::pTable->tabtype = 3;	//报表类的表格，用3代替
	List_add(pfirst,pCom);
    
	pCom = new Label(this->pCon,3,8,1,1,(char *)"频道:",1);
	List_add(pfirst,pCom);
	strcpy(sql,"select * from Tbl_video_channel");
	pCom = new Combobox(this->pCon,3,15,1,9,6,sql);
    this->channel_id = ((Combobox *)pCom)->ID;
	List_add(pfirst,pCom);
	pCom = new Label(this->pCon,3,8,4,1,(char *)"分类:",1);
	List_add(pfirst,pCom);
	strcpy(sql,"select type_id,type_name from Tbl_video_type");
	pCom = new Combobox(this->pCon,3,15,4,9,6,sql);
    this->type_id = ((Combobox *)pCom)->ID;
	List_add(pfirst,pCom);
	pCom = new Label(this->pCon,3,8,1,27,(char *)"地区:",1);
	List_add(pfirst,pCom);
	strcpy(sql,"select distinct area_id,area_name from Tbl_video_area");
	pCom = new Combobox(this->pCon,3,15,1,35,6,sql);
	this->area_id = ((Combobox *)pCom)->ID;
	List_add(pfirst,pCom);
	pCom = new Label(this->pCon,3,8,4,27,(char *)"排序:",1);
	List_add(pfirst,pCom);
	strcpy(sql,"select * from Tbl_video_menu");
	pCom = new Combobox(this->pCon,3,15,4,35,6,sql);
	this->menu_id = ((Combobox *)pCom)->ID;
	List_add(pfirst,pCom);
	pCom = new Button(this->pCon,3,8,2,53,(char *)" 确定 ",3);
  	pAction = new TableAction(this);
  	((Button *)pCom)->AddAction(pAction);
	List_add(pfirst,pCom);
	pCom = new Button(this->pCon,3,8,2,65,(char *)" 取消 ",3);
 	pAction = new ActionReturn(this);
 	((Button *)pCom)->AddAction(pAction);
	List_add(pfirst,pCom);
	pCom = new Label(this->pCon,1,8,8,0,(char *)"序号",1);
	List_add(pfirst,pCom);   
	pCom = new Label(this->pCon,1,8,8,14,(char *)"视频名称",1);
	List_add(pfirst,pCom); 
	pCom = new Label(this->pCon,1,8,8,28,(char *)"播放次数",1);
	List_add(pfirst,pCom);   
	pCom = new Label(this->pCon,1,8,8,42,(char *)"频道",1);
	List_add(pfirst,pCom);  
	pCom = new Label(this->pCon,1,8,8,56,(char *)"地区",1);
	List_add(pfirst,pCom); 
	pCom = new Label(this->pCon,1,8,8,69,(char *)"分类",1);
	List_add(pfirst,pCom); 
	pCom = new Label(this->pCon,1,60,LINES-2,1,(char *)"选择:Up/Down  翻页:PageUp/PageDown  确认:Enter  重选记录:Esc",1);
	List_add(pfirst,pCom); 
	mvwvline(this->pCon,8,10,0,1);
	mvwvline(this->pCon,8,24,0,1);
	mvwvline(this->pCon,8,39,0,1);
	mvwvline(this->pCon,8,53,0,1);
	mvwvline(this->pCon,8,67,0,1);
	
}
