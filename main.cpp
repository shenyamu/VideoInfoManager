#include <ncurses.h>
#include "Control/Control.h"
#include "LoginForm/LoginForm.h"
#include "MenuForm/MenuForm.h"

int main()
{
    LoginForm *pLog;
	MenuForm *pMenu;
    int key;
    initscr();
    raw();
    noecho();
    start_color();
    init_pair(1,COLOR_WHITE,COLOR_BLUE);
    init_pair(2,COLOR_BLACK,COLOR_WHITE);//窗口前后背景色
    init_pair(3,COLOR_WHITE,COLOR_RED);  //按钮前后背景色
    init_pair(4,COLOR_BLACK,COLOR_BLACK);//阴影框前后背景色
    init_pair(5,COLOR_WHITE,COLOR_WHITE);
	init_pair(6,COLOR_BLACK,COLOR_GREEN);//二级菜单前后背景色
	init_pair(7,COLOR_RED,COLOR_WHITE);  //提示框前后背景色
 
	while (1)
	{	
		clear();
		wbkgd(stdscr,COLOR_PAIR(1));
		attron(A_BOLD);
		mvprintw(LINES-1,11,"<上下、Tab> 控件切换  |  <左右> 编辑框定位  |  <Enter> 按下按钮");
		refresh();
		pLog = new LoginForm(17,52,(LINES-17)/2,(COLS-52)/2,1);// 新建登录框
		pLog->show();
        pLog->KeyListen(key);
		delete pLog;// 登陆成功，释放登录框，注销后可重建
		
	    pMenu = new MenuForm(LINES,COLS,0,0,1,pLog->role_id);// 新建菜单界面
	    pMenu->show();
	    pMenu->KeyListen(key);
		delete pMenu; // 选择注销功能后释放空间
		
	}		
		return 0;
}
