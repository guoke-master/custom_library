/***********************************************************************************************************************************************
 * File name:	link_list.c
 * Author:	guoke
 * Date:	2021.10.30
 * Description:	C语言双向循环链表API的实现，声明在文件link_list.h中
 * History:	1. 2021.10.30 创建并完成初始版本
 *			2. 2021.11.07 对用户隐藏链表指针域，用户的业务数据中不在需要包含指针域
 **********************************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link_list.h"


/* 链表的指针域 */
typedef struct LINK{
	struct LINK* next;				// 指向下一结点
	struct LINK* prior;				// 指向前一结点
}LINK;


/* 链表内部实现的结点类型 */
typedef struct NODE{
	LINK link;						// 指针域
	LIST_NODE data;					// 数据域，实际上是一个指针类型
}NODE;


/* 链表头结点 */
typedef struct LINK_LIST_METADATA{
	LINK	link;					// 指针域
	int		length;					// 记录链表长度
	LINK*	slider;					// 游标，指向链表中的结点，用来辅助定位
}LINK_LIST_METADATA;



/*
 * Function:		LinkList_Create()
 * Description:		构造一个空的链表
 * Time complexity:	O(1)
 * Input:	
 * Output:	
 * Return:			LINK_LIST*类型，创建成功则返回链表地址，否则返回NULL
 */
LINK_LIST* LinkList_Create()
{
	// 申请头结点空间
	LINK_LIST_METADATA* header = (LINK_LIST_METADATA*)malloc(sizeof(LINK_LIST_METADATA));
	if (header == NULL)
	{
		printf("func LinkList_Create() err: header == NULL\n");
		return NULL;
	}

	// 给申请的空间赋初值
	memset(header, 0, sizeof(LINK_LIST_METADATA));

	return (LINK_LIST*)header;
}



/*
 * Function:		LinkList_Destroy()
 * Description:		销毁链表空间
 * Time complexity:	O(n)
 * Input:	
 *		link_list:	LINK_LIST*类型，链表的地址	
 * Output:	
 * Return:			int类型，操作成功返回0，否则返回其他值
 */
int LinkList_Destroy(LINK_LIST* link_list)
{
	int func_status = 0;

	// 将LINK_LIST类型的地址转换为LINK_LIST_METADATA类型的地址
	LINK_LIST_METADATA* header = (LINK_LIST_METADATA*)link_list;

	// 参数检查
	if (link_list == NULL)
	{
		printf("func LinkList_Destroy() err: link_list == NULL\n");
		return -1;
	}

	// 清空链表
	func_status = LinkList_Clear(link_list);
	if (func_status != 0)
	{
		printf("func LinkList_Destroy() err: func_status != 0\n");
		return -2;
	}

	// 释放头结点空间
	free(header);
	header = NULL;

	return 0;
}



/*
 * Function:		LinkList_Clear()
 * Description:		将链表置为空表
 * Time complexity:	O(n)
 * Input:	
 *		link_list:	LINK_LIST*类型，链表的地址	
 * Output:	
 * Return:			int类型，操作成功返回0，否则返回其他值
 */
int LinkList_Clear(LINK_LIST* link_list)
{
	LIST_NODE deleted_node_data = NULL;

	// 将LINK_LIST类型的地址转换为LINK_LIST_METADATA类型的地址
	LINK_LIST_METADATA* header = (LINK_LIST_METADATA*)link_list;

	// 参数检查
	if (link_list == NULL)
	{
		printf("func LinkList_Clear() err: link_list == NULL\n");
		return -1;
	}

	// 遍历整个链表，删除所有结点并释放空间
	LinkList_ResetSlider(link_list);			// 重置游标使其指向第一个结点
	while(header->length != 0)
	{
		deleted_node_data = LinkList_DeleteSlider(link_list);		// 删除游标指向的结点并释放空间
		if (deleted_node_data == NULL)
		{
			printf("func LinkList_Clear() err: deleted_node_data == NULL\n");
			return -2;
		}
	}

	return 0;
}



/*
 * Function:		LinkList_GetLength()
 * Description:		获取链表长度
 * Time complexity:	O(1)
 * Input:	
 *		link_list:	LINK_LIST*类型，链表的地址	
 * Output:	
 * Return:			int类型，操作成功返回0，否则返回其他值
 */
int LinkList_GetLength(LINK_LIST* link_list)
{
	// 将LINK_LIST类型的地址转换为LINK_LIST_METADATA类型的地址
	LINK_LIST_METADATA* header = (LINK_LIST_METADATA*)link_list;

	// 参数检查
	if (link_list == NULL)
	{
		printf("func LinkList_GetLength() err: link_list == NULL\n");
		return -1;
	}

	// 返回链表长度
	return header->length;
}



/*
 * Function:		LinkList_IsEmpty()
 * Description:		判断链表是否为空表
 * Time complexity:	O(1)
 * Input:	
 *		link_list:	LINK_LIST*类型，链表的地址	
 * Output:	
 * Return:			int类型，操作成功返回0，否则返回其他值
 */
int LinkList_IsEmpty(LINK_LIST* link_list)
{
	// 将LINK_LIST类型的地址转换为LINK_LIST_METADATA类型的地址
	LINK_LIST_METADATA* header = (LINK_LIST_METADATA*)link_list;

	// 参数检查
	if (link_list == NULL)
	{
		printf("func LinkList_IsEmpty() err: link_list == NULL\n");
		return -1;
	}

	return (header->length == 0) ? 1 : 0;
}



/*
 * Function:		LinkList_ResetSlider()
 * Description:		重置链表的游标。如果链表中有结点，游标指向第一个结点；如果链表中没有结点，游标置NULL
 * Time complexity:	O(1)
 * Input:	
 *		link_list:	LINK_LIST*类型，链表的地址
 * Output:	
 * Return:			int类型，操作成功返回0，否则返回其他值
 */
int LinkList_ResetSlider(LINK_LIST* link_list)
{
	// 将LINK_LIST类型的地址转换为LINK_LIST_METADATA类型的地址
	LINK_LIST_METADATA* header = (LINK_LIST_METADATA*)link_list;

	// 参数检查
	if (link_list == NULL)
	{
		printf("func LinkList_ResetSlider() err: link_list == NULL\n");
		return -1;
	}

	// 如果链表中没有结点，slider置NULL
	if (header->length == 0)
	{
		header->slider = NULL;
	}
	// 如果链表中有结点，slider指向第一个结点
	else
	{
		header->slider = header->link.next;
	}

	return 0;
}



/*
 * Function:		LinkList_GetSlider()
 * Description:		返回链表游标指向的结点数据
 * Time complexity:	O(1)
 * Input:	
 *		link_list:	LINK_LIST*类型，链表的地址	
 * Output:	
 * Return:			LIST_NODE类型。如果操作成功，返回游标指向的结点数据。如果操作失败，返回NULL
 */
LIST_NODE LinkList_GetSlider(LINK_LIST* link_list)
{
	// 将LINK_LIST类型的地址转换为LINK_LIST_METADATA类型的地址
	LINK_LIST_METADATA* header = (LINK_LIST_METADATA*)link_list;

	// 参数检查
	if (link_list == NULL)
	{
		printf("func LinkList_GetSlider() err: link_list == NULL\n");
		return NULL;
	}

	// 判断链表是否为空表，如果为空表，报错 */
	if (header->length == 0)
	{
		printf("func LinkList_GetSlider() err: header->length == 0\n");
		return NULL;
	}

	// 返回游标指向的结点的数据
	return ((NODE*)(header->slider))->data;
}


/*
 * Function:		LinkList_SliderForward()
 * Description:		返回当前游标指向的结点的数据，游标指向其后继结点
 * Time complexity:	O(1)
 * Input:	
 *		link_list:	LINK_LIST*类型，链表的地址	
 * Output:	
 * Return:			LIST_NODE类型。如果操作成功，返回游标指向的结点数据。如果操作失败，返回NULL
 */
LIST_NODE LinkList_SliderForward(LINK_LIST* link_list)
{
	// 将LINK_LIST类型的地址转换为LINK_LIST_METADATA类型的地址
	LINK_LIST_METADATA* header = (LINK_LIST_METADATA*)link_list;

	// 参数检查
	if (link_list == NULL)
	{
		printf("func LinkList_SliderForward() err: link_list == NULL\n");
		return NULL;
	}

	// 判断链表是否为空表，如果为空表，报错 */
	if (header->length == 0)
	{
		printf("func LinkList_SliderForward() err: header->length == 0\n");
		return NULL;
	}

	// 游标指向其后继结点
	header->slider = header->slider->next;
	
	return ((NODE*)(header->slider->prior))->data;
}



/*
 * Function:		LinkList_SliderBackward()
 * Description:		返回当前游标指向的结点的地址，游标指向其前驱结点
 * Time complexity:	O(1)
 * Input:	
 *		link_list:	LINK_LIST*类型，链表的地址	
 * Output:	
 * Return:			LIST_NODE类型。如果操作成功，返回游标指向的结点数据。如果操作失败，返回NULL
 */
LIST_NODE LinKList_SliderBackward(LINK_LIST* link_list)
{
	// 将LINK_LIST类型的地址转换为LINK_LIST_METADATA类型的地址
	LINK_LIST_METADATA* header = (LINK_LIST_METADATA*)link_list;

	// 参数检查
	if (link_list == NULL)
	{
		printf("func LinKList_SliderBackward() err: link_list == NULL\n");
		return NULL;
	}

	// 判断链表是否为空表，如果为空表，报错 */
	if (header->length == 0)
	{
		printf("func LinKList_SliderBackward() err: header->length == 0\n");
		return NULL;
	}

	// 游标指向其前驱结点
	header->slider = header->slider->prior;

	return ((NODE*)(header->slider->next))->data;
}



/*
 * Function:		LinkList_InsertBeforeSlider()
 * Description:		在游标指向的结点前面插入一个结点，并将游标指向插入的结点，在第一个结点之前插入的话，头结点会变成插入的结点
 * Time complexity:	O(1)
 * Input:	
 *		link_list:	LINK_LIST*类型。链表的地址。	
 *		list_node:	LIST_NODE类型。插入的数据。
 * Output:	
 * Return:			int类型，操作成功返回0，否则返回其他值
 */
int LinkList_InsertBeforeSlider(LINK_LIST* link_list, LIST_NODE list_node)
{
	// 指向内部结点的指针
	NODE* node = NULL;

	// 将LINK_LIST类型的地址转换为LINK_LIST_METADATA类型的地址
	LINK_LIST_METADATA* header = (LINK_LIST_METADATA*)link_list;

	// 参数检查
	if (link_list == NULL || list_node == NULL)
	{
		printf("func LinkList_InsertBeforeSlider() err: link_list == NULL || list_node == NULL\n");
		return -1;
	}

	// 申请一个内部结点的空间，并将数据域置为list_node
	node = (NODE*)malloc(sizeof(NODE));
	if (node == NULL)
	{
		printf("func LinkList_InsertBeforeSlider() err: node == NULL\n");
		return -2;
	}
	node->data = list_node;

	// 如果插入之前链表没有结点，此时游标指向NULL
	if (header->length == 0)
	{
		header->link.next = (LINK*)node;		// 将内部结点连接在头结点之后
		node->link.next = (LINK*)node;			// 内部结点的link域的next指针指向自己
		node->link.prior = (LINK*)node;			// 内部结点的link域的prior指针指向自己
		header->slider = (LINK*)node;			// 游标指向插入的内部结点
	}
	// 如果插入之前链表存在结点，此时游标指向某个结点
	else if(header->length > 0)
	{
		// 修改next指针
		node->link.next = header->slider;
		header->slider->prior->next = (LINK*)node;

		// 修改prior指针
		node->link.prior = header->slider->prior;
		header->slider->prior = (LINK*)node;

		// 修改游标指向
		header->slider = (LINK*)node;
	}

	// 如果插入之前游标指向第一个结点，插入之后头结点指向会发生改变
	if (header->link.next == header->slider->next)
	{
		header->link.next = header->slider;
	}

	// 链表长度加1
	header->length++;

	return 0;
}



/*
 * Function:		LinkList_InsertAfterSlider()
 * Description:		在游标指向的结点后面插入一个结点，并将游标指向插入的结点。
 * Time complexity:	O(1)
 * Input:	
 *		link_list:	LINK_LIST*类型。链表的地址。	
 *		list_node:	LIST_NODE类型。插入的数据。
 * Output:	
 * Return:			int类型，操作成功返回0，否则返回其他值
 */
int LinkList_InsertAfterSlider(LINK_LIST* link_list, LIST_NODE list_node)
{
	// 指向内部结点的指针
	NODE* node = NULL;

	// 将LINK_LIST类型的地址转换为LINK_LIST_METADATA类型的地址
	LINK_LIST_METADATA* header = (LINK_LIST_METADATA*)link_list;

	// 参数检查
	if (link_list == NULL || list_node == NULL)
	{
		printf("func LinkList_InsertAfterSlider() err: link_list == NULL || list_node == NULL\n");
		return -1;
	}

	// 申请一个内部结点的空间，并将数据域置为list_node
	node = (NODE*)malloc(sizeof(NODE));
	if (node == NULL)
	{
		printf("func LinkList_InsertBeforeSlider() err: node == NULL\n");
		return -2;
	}
	node->data = list_node;

	// 如果插入之前链表没有结点，此时游标指向NULL
	if (header->length == 0)
	{
		header->link.next = (LINK*)node;
		node->link.next = (LINK*)node;
		node->link.prior = (LINK*)node;
		header->slider = (LINK*)node;
	}
	// 如果插入之前链表存在结点，此时游标指向某个结点
	else if(header->length > 0)
	{
		// 修改next指针 
		node->link.next = header->slider->next;
		header->slider->next = (LINK*)node;

		// 修改prior指针
		node->link.prior = header->slider;
		node->link.next->prior = (LINK*)node;

		// 修改slider指向
		header->slider = (LINK*)node;
	}

	// 链表长度加1
	header->length++;
		
	return 0;
}



/*
 * Function:		LinkList_DeleteSlider()
 * Description:		删除游标指向的结点，返回删除结点的数据，游标指向删除结点的后继结点。如果删除的是第一个结点，被删除结点的后继结点将会变成第一个结点。如果删除之后链表变成空表，游标置NULL
 * Time complexity:	O(1)
 * Input:	
 *		link_list:	LINK_LIST*类型。链表的地址。	
 * Output:	
 * Return:			LIST_NODE类型。如果操作成功，返回被删除的结点的数据。如果操作失败，返回NULL
 */
LIST_NODE LinkList_DeleteSlider(LINK_LIST* link_list)
{
	NODE*		deleted_node = NULL;
	LIST_NODE	deleted_node_data = NULL;

	// 将LINK_LIST类型的地址转换为LINK_LIST_METADATA类型的地址
	LINK_LIST_METADATA* header = (LINK_LIST_METADATA*)link_list;

	// 参数检查
	if (link_list == NULL)
	{
		printf("func LinkList_DeleteSlider() err: link_list == NULL\n");
		return NULL;
	}

	// 判断链表是否为空表
	if (header->length <= 0)
	{
		printf("func LinkList_DeleteSlider() err: header->length <= 0\n");
		return NULL;
	}

	// 缓存被删除的结点
	deleted_node = (NODE*)header->slider;

	// 如果删除该结点之后链表变为空表，删除之后slider置空
	if( header->length == 1)
	{
		header->link.next = NULL;
		header->link.prior = NULL;
		header->slider = NULL;
	}
	// 如果删除该结点之后链表仍存在结点，slider指向删除结点的后一个结点
	else if(header->length > 1)
	{
		// 删除结点
		header->slider->prior->next = header->slider->next;
		header->slider->next->prior = header->slider->prior;

		// 移动游标
		header->slider = header->slider->next;
		
		// 如果删除的是第一个结点，头结点指向会发生改变
		if (deleted_node == (NODE*)header->link.next)
		{
			header->link.next = header->slider;
		}
	}

	// 链表长度减1
	header->length--;

	// 释放删除结点的空间
	if (deleted_node != NULL)
	{
		deleted_node_data = deleted_node->data;
		free(deleted_node);
		deleted_node = NULL;

		return deleted_node_data;
	}
	else
	{
		printf("func LinkList_DeleteSlider() err: deleted_node == NULL\n");
		return NULL;
	}
}



/*
 * Function:		LinkList_SetSlider()
 * Description:		如果list_node是链表中结点的数据，则将游标指向该结点
 * Time complexity:	O(n)
 * Input:	
 *		link_list:	LINK_LIST*类型。链表的地址。	
 *		list_node:	LIST_NODE类型。游标最后指向的结点
 * Output:	
 * Return:			int类型，操作成功返回0，否则返回其他值
 */
int LinkList_SetSlider(LINK_LIST* link_list, LIST_NODE list_node)
{
	LINK* current_ptr = NULL;
	int i = 0;

	// 将LINK_LIST类型的地址转换为LINK_LIST_METADATA类型的地址
	LINK_LIST_METADATA* header = (LINK_LIST_METADATA*)link_list;

	// 参数检查
	if (link_list == NULL || list_node == NULL)
	{
		printf("func LinkList_SetSlider() err: link_list == NULL || list_node == NULL\n");
		return -1;
	}

	// 遍历
	current_ptr = (LINK*)header;
	for (i = 0; i < header->length; ++i)
	{
		current_ptr = current_ptr->next;
		if (((NODE*)current_ptr)->data == list_node)
		{
			break;
		}
	}

	// 如果node不在结点中，报错
	if (i >= header->length)
	{
		printf( "func LinkList_SetSlider() err: i >= header->length\n");
		return -2;
	}

	// 移动slider指针指向list_node所在结点
	header->slider = current_ptr;

	return 0;
}



/*
 * Function:		LinkList_Traverse()
 * Description:		遍历链表，每个结点的数据执行visit()操作
 * Time complexity:	O(n)
 * Input:	
 *		link_list:	LINK_LIST*类型。链表的地址。	
 *		visit:		int (*)(LIST_NODE)类型，函数指针，每个结点的数据执行的操作
 * Output:	
 * Return:			int类型，操作成功返回0，否则返回其他值
 */
int LinkList_Traverse(LINK_LIST* link_list,	int (*visit)(LIST_NODE node))
{
	LINK* current_ptr = NULL;
	int i = 0;
	int func_status = 0;

	// 将LINK_LIST类型的地址转换为LINK_LIST_METADATA类型的地址
	LINK_LIST_METADATA* header = (LINK_LIST_METADATA*)link_list;

	// 参数检查
	if (link_list == NULL || visit == NULL)
	{
		printf("func LinkList_Traverse() err: link_list == NULL || visit == NULL\n");
		return -1;
	}

	// 遍历链表 
	current_ptr = (LINK*)header;
	for (i = 0; i < header->length; ++i)
	{
		current_ptr = current_ptr->next;
		func_status = visit(((NODE*)current_ptr)->data);
		if (func_status != 0)
		{
			printf("func LinkList_Traverse() err: func_status != 0\n");
			return -2;
		}
	}

	return 0;
}
