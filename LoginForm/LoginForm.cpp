#include <string.h>
#include "../LoginForm/LoginForm.h"
#include "../LoginForm/LoginAction.h"

LoginForm::LoginForm(int height,int width,int starty,int startx,int contype)
                    :Form(height,width,starty,startx,contype)
{
	
    Control *pCom;
    ActionListen *pAction;
	strcpy(role_id,"");
    pCom = new Label(this->pCon,3,30,1,8,(char *)"视频点播器【服务器后台管理】",1);
    List_add(pfirst,pCom);
	pCom = new Label(this->pCon,3,10,4,8,(char *)"用户名：",1);
    List_add(pfirst,pCom);
	pCom = new Label(this->pCon,3,10,7,8,(char *)"密  码：",1);
    List_add(pfirst,pCom);
    pCom = new Edit(this->pCon,3,20,4,18,10,1,2,true);
	pName = pCom->Getdata();
    List_add(pfirst,pCom);
    pCom = new Edit(this->pCon,3,20,7,18,6,2,2);
    pWd = pCom->Getdata();
    List_add(pfirst,pCom);
    pCom = new Button(this->pCon,3,10,11,10,(char *)"  登录  ",3);
    pAction = new ActionEnter(this);
    ((Button *)pCom)->AddAction(pAction);
    List_add(pfirst,pCom);
    pCom = new Button(this->pCon,3,10,11,27,(char *)"  取消  ",3);
    pAction = new ActionCancel(this);
    ((Button *)pCom)->AddAction(pAction);
    List_add(pfirst,pCom);

}


