#ifndef _LOGINFORM_H_
#define _LOGINFORM_H_

#include "../Control/Control.h"
#include "../List/List.h"

class LoginForm:public Form
{
public:
    LoginForm(int height,int width,int starty,int startx,int contype);
	char *pName;
	char *pWd;
	char role_id[10];// 登录用户的角色ID
};



#endif
