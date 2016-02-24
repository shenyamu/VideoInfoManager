#include "../MenuForm/MenuDb.h"
#include "../MenuForm/MenuForm.h"
#include "../MenuForm/MenuAction.h"

static int c;

int Menu_Callback(void *pData,int cols,char **colvalu,char **colname)
{
	pList pfirst;
	pfirst = (pList)pData;
    MenuBar *pMenu;
	if (pfirst->pNext == NULL)
	{
		c = 0;
	}
	pMenu = new MenuBar(NULL,3,16,1,c,colvalu[0],colvalu[1],1);
    pMenu->AddAction(colvalu[0]);// 添加一级菜单拥有的二级菜单，colvalu[0]为一级菜单ID
	List_add(pfirst,pMenu);
	c = c + 16;
	return 0;

}


int MenuBar_Callback(void *pData,int cols,char **colvalu,char **colname)
{	
	pList psecond;
	MenuItem *pMenu;
	int menu_sid;
	static int a;
	psecond = (pList)pData;
	if (psecond->pNext == NULL)
	{
		a = 4;
	}   
	pMenu = new MenuItem(NULL,3,16,a,c,colvalu[1],1);
	sscanf(colvalu[0],"%d",&menu_sid);
	pMenu->menu_sid = menu_sid;// 类里存有二级菜单的菜单ID
	List_add(psecond,pMenu);
	a = a + 3;
	return 0;	
}