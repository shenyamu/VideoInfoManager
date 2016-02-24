/************************************************************************
* 版权所有  (c)2008,   卓越计算机职业培训学校。
* 文件名称： List.c

  * 内容摘要：
  *     本文件实现关于链表基本操作的功能。
  * 历史记录：
  *     创建日期：2013-08-05   修改人：沈永木
*************************************************************************/
#include <stdio.h>
#include <malloc.h>
#include <string.h> //memset()头文件
#include "../List/List.h"
#include "../Control/Control.h"

pList List_init(void * data)
{
	pList head;
	head = (pList) malloc(sizeof(struct List));// 申请结点空间
	if (head == NULL)
	{
		printf("Memory error.\n");
		return NULL;
	}
	memset(head,0,sizeof(struct List));// 清零
	head->pData = data;// 数据域赋值
	return head;
}




void List_add(pList head,void *pData)
{
	pList ps,pNew,pt;
	if (head->pNext != NULL&&head->pData != NULL)
	{
		printf("头结点没有初始化");
		return;
	}
	pNew = List_init(pData);
	ps = head;
	pt = head;
	while(head->pNext)
	{
		ps = pt;
		pt=pt->pNext;
		if (pt->pNext == head->pNext)
			break;
	}

	pt->pNext = pNew;
	((head->pNext)->pRev) = pNew;
	pNew->pRev = ps->pNext;
	pNew->pNext = head->pNext;
}



int  List_count(pList head)
{
	pList pL;
	int nCount = 0;
	pL=head->pNext;
	while(pL)
	{
		nCount++;
		pL=pL->pNext;
		if(pL == head->pNext)
			break;
	}
	return nCount;
}



void List_free(pList head)
{
	pList pd,
	pt = head->pNext;
	while(pt)
	{
		pd=pt->pNext;
		delete (Control *)(pt->pData);// 先释放数据域空间
		free(pt);// 再释放结点空间
		if (pd == head->pNext)
	    break;
		pt = pd;
	}
		free(head);// 最后释放头结点
}
