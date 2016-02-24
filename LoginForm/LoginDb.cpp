#include <string.h>
#include "../LoginForm/LoginDb.h"

int Login_Callback(void *pData,int cols,char **colvalu,char **colname)
{

    char *role_id;
	role_id = (char *)pData;
	strcpy(role_id,colvalu[0]);
	return 0;
}
