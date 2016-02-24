#include "../Control/Control.h"
#include "../TableForm/TableDb.h"

class TableForm:public Form	//报表统计界面
{
public:
	TableForm(int height,int width,int starty,int startx,int contype);
	static Table *pTable;
	static TableForm *pTableForm;
	char *channel_id;
	char *area_id;
	char *type_id;
	char *menu_id;
	char startdate[20];
	char enddate[20];
};

