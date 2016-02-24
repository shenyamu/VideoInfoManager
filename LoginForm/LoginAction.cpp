#include "LoginAction.h"
#include "../LoginForm/LoginForm.h"
#include "../DbCon/DbCon.h"
#include "../LoginForm/LoginDb.h"


ActionEnter::ActionEnter(Form *pWin):ActionListen(pWin)
{
	
	
}

void ActionEnter::DoAction(int &key)
{
    Control *pNotic;// 提示框指针	
	char sql[256] = "";// sql验证语句
	sprintf(sql,"select role_id from Tbl_user,Tbl_user_role where user_name = \"%s\" and user_pwd = \"%s\" and Tbl_user.user_id = Tbl_user_role.user_id and Tbl_user.user_stat =1",
		    ((LoginForm *)pWin)->pName,((LoginForm  *)pWin)->pWd);
	//查询登录用户的角色ID 
	(DbSingles::GetSingle())->GetData(sql,Login_Callback,((LoginForm *)pWin)->role_id);
	// 打开数据库并验证登录用户
	if (strcmp(((LoginForm *)pWin)->role_id,"") !=0)
	{
       
		pNotic = new Notic(NULL,5,14,LINES/2-4,COLS/2-6,(char *)"登录成功",5);
		pNotic->show();
		usleep(700000);
		delete pNotic;//登陆成功或者失败都得释放提示框指针
		pWin->flag = false;
		//登陆成功标志，用来退出登录窗口的keylisten函数
	}
	else
	{
		pNotic = new Notic(NULL,5,14,LINES/2-4,COLS/2-6,(char *)"登录失败",5);
		pNotic->show();
		usleep(1000000);
		delete pNotic;
		memset(((LoginForm  *)pWin)->pWd,0,sizeof(((LoginForm  *)pWin)->pWd));
		pWin->show();		
		key = 0;
		
    }
	
	
}


ActionCancel::ActionCancel(Form *pWin):ActionListen(pWin)
{
	
}

void ActionCancel::DoAction(int &key)
{
    delete pWin;
    endwin();// 退出Ncurses，释放占用内存
    exit(0); //正常退出，关闭所有文件，终止正在执行的程序
}
