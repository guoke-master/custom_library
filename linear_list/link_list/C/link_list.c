/***********************************************************************************************************************************************
 * File name:	link_list.c
 * Author:	guoke
 * Date:	2021.10.30
 * Description:	C语言双向循环链表API的实现，声明在文件link_list.h中
 * History:	1. 2021.10.30 创建并完成初始版本
 **********************************************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link_list.h"


/* 链表头结点 */
typedef struct LINK_LIST_METADATA{
	LINK	link;			// 指针域
	int		length;			// 记录链表长度
	LINK*	slider;			// 游标，指向链表中的节点，用来辅助定位
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

	return header;
}



/*
 * Function:		LinkList_Destroy()
 * Description:		销毁链表空间
 * Time complexity:	O(1)
 * Input:	
 *		link_list:	LINK_LIST*类型，链表的地址	
 * Output:	
 * Return:			int类型，操作成功返回0，否则返回其他值
 */
int LinkList_Destroy(LINK_LIST* link_list)
{
	// 将LINK_LIST类型的地址转换为LINK_LIST_METADATA类型的地址
	LINK_LIST_METADATA* header = (LINK_LIST_METADATA*)link_list;

	// 参数检查
	if (link_list == NULL)
	{
		printf("func LinkList_Destroy() err: link_list == NULL\n");
		return -1;
	}

	// 释放空间
	free(header);

	return 0;
}



/*
 * Function:		LinkList_Clear()
 * Description:		将链表置为空表
 * Time complexity:	O(1)
 * Input:	
 *		link_list:	LINK_LIST*类型，链表的地址	
 * Output:	
 * Return:			int类型，操作成功返回0，否则返回其他值
 */
int LinkList_Clear(LINK_LIST* link_list)
{
	// 将LINK_LIST类型的地址转换为LINK_LIST_METADATA类型的地址
	LINK_LIST_METADATA* header = (LINK_LIST_METADATA*)link_list;

	// 参数检查
	if (link_list == NULL)
	{
		printf("func LinkList_Clear() err: link_list == NULL\n");
		return -1;
	}

	// 头结点元数据更新
	header->link.next = NULL;
	header->link.prior = NULL;
	header->length = 0;
	header->slider = NULL;

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
 * Description:		重置链表的游标。如果链表中有节点，游标指向第一个节点；如果链表中没有节点，游标置NULL
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

	// 如果链表中没有节点，slider置NULL
	if (header->length == 0)
	{
		header->slider = NULL;
	}
	// 如果链表中有节点，slider指向第一个节点
	else
	{
		header->slider = header->link.next;
	}

	return 0;
}



/*
 * Function:		LinkList_GetSlider()
 * Description:		返回链表游标指向的节点地址
 * Time complexity:	O(1)
 * Input:	
 *		link_list:	LINK_LIST*类型，链表的地址	
 * Output:	
 * Return:			LINK*类型。如果操作成功，返回游标指向的节点指针。如果操作失败，返回NULL
 */
LINK* LinkList_GetSlider(LINK_LIST* link_list)
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

	// 返回游标指向的节点
	return header->slider;
}


/*
 * Function:		LinkList_SliderForward()
 * Description:		返回当前游标指向的节点的地址，游标指向其后继节点
 * Time complexity:	O(1)
 * Input:	
 *		link_list:	LINK_LIST*类型，链表的地址	
 * Output:	
 * Return:			LINK*类型。如果操作成功，返回游标指向的节点指针。如果操作失败，返回NULL
 */
LINK* LinkList_SliderForward(LINK_LIST* link_list)
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

	// 游标指向其后继节点
	header->slider = header->slider->next;
	
	return header->slider->prior;
}



/*
 * Function:		LinkList_SliderBackward()
 * Description:		返回当前游标指向的节点的地址，游标指向其前驱节点
 * Time complexity:	O(1)
 * Input:	
 *		link_list:	LINK_LIST*类型，链表的地址	
 * Output:	
 * Return:			LINK*类型。如果操作成功，返回游标指向的节点指针。如果操作失败，返回NULL
 */
LINK* LinKList_SliderBackward(LINK_LIST* link_list)
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

	// 游标指向其前驱节点
	header->slider = header->slider->prior;

	return header->slider->next;
}



/*
 * Function:		LinkList_InsertBeforeSlider()
 * Description:		在游标指向的节点前面插入一个节点，并将游标指向插入的节点，在第一个节点之前插入的话，头结点会变成插入的节点
 * Time complexity:	O(1)
 * Input:	
 *		link_list:	LINK_LIST*类型。链表的地址。	
 *		node:		LINK*类型。插入节点的地址。
 * Output:	
 * Return:			int类型，操作成功返回0，否则返回其他值
 */
int LinkList_InsertBeforeSlider(LINK_LIST* link_list, LINK* node)
{
	// 将LINK_LIST类型的地址转换为LINK_LIST_METADATA类型的地址
	LINK_LIST_METADATA* header = (LINK_LIST_METADATA*)link_list;

	// 参数检查
	if (link_list == NULL || node == NULL)
	{
		printf("func LinkList_InsertBeforeSlider() err: link_list == NULL || node == NULL\n");
		return -1;
	}

	// 如果插入之前链表没有节点，此时游标指向NULL
	if (header->length == 0)
	{
		header->link.next = node;
		node->next = node;
		node->prior = node;
		header->slider = node;
	}
	// 如果插入之前链表存在节点，此时游标指向某个节点
	else if(header->length > 0)
	{
		// 修改next指针
		node->next = header->slider;
		header->slider->prior->next = node;

		// 修改prior指针
		node->prior = header->slider->prior;
		header->slider->prior = node;

		// 修改游标指向
		header->slider = node;
	}

	// 如果插入之前游标指向第一个节点，插入之后头结点指向会发生改变
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
 * Description:		在游标指向的节点后面插入一个节点，并将游标指向插入的节点。
 * Time complexity:	O(1)
 * Input:	
 *		link_list:	LINK_LIST*类型。链表的地址。	
 *		node:		LINK*类型。插入节点的地址。
 * Output:	
 * Return:			int类型，操作成功返回0，否则返回其他值
 */
int LinkList_InsertAfterSlider(LINK_LIST* link_list, LINK* node)
{
	// 将LINK_LIST类型的地址转换为LINK_LIST_METADATA类型的地址
	LINK_LIST_METADATA* header = (LINK_LIST_METADATA*)link_list;

	// 参数检查
	if (link_list == NULL || node == NULL)
	{
		printf("func LinkList_InsertAfterSlider() err: link_list == NULL || node == NULL\n");
		return -1;
	}

	// 如果插入之前链表没有节点，此时游标指向NULL
	if (header->length == 0)
	{
		header->link.next = node;
		node->next = node;
		node->prior = node;
		header->slider = node;
	}
	// 如果插入之前链表存在节点，此时游标指向某个节点
	else if(header->length > 0)
	{
		// 修改next指针 
		node->next = header->slider->next;
		header->slider->next = node;

		// 修改prior指针
		node->prior = header->slider;
		node->next->prior = node;

		// 修改slider指向
		header->slider = node;
	}

	// 链表长度加1
	header->length++;
		
	return 0;
}



/*
 * Function:		LinkList_DeleteSlider()
 * Description:		删除游标指向的节点，返回删除节点的地址，游标指向删除节点的后继节点。如果删除的是第一个节点，第一个节点的后继节点就会变成第一个节点。如果删除的是链表最后一个节点，游标置NULL
 * Time complexity:	O(1)
 * Input:	
 *		link_list:	LINK_LIST*类型。链表的地址。	
 *		node:		LINK*类型。插入节点的地址。
 * Output:	
 * Return:			LINK*类型。如果操作成功，返回被删除的节点的地址。如果操作失败，返回NULL
 */
LINK* LinkList_DeleteSlider(LINK_LIST* link_list)
{
	LINK* deleted_node = NULL;

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

	// 缓存被删除的节点
	deleted_node = header->slider;

	// 如果删除该节点之后链表变为空表，删除之后slider置空
	if( header->length == 1)
	{
		header->link.next = NULL;
		header->link.prior = NULL;
		header->slider = NULL;
	}
	// 如果删除该节点之后链表仍存在节点，slider指向删除节点的后一个节点
	else if(header->length > 1)
	{
		// 删除节点
		header->slider->prior->next = header->slider->next;
		header->slider->next->prior = header->slider->prior;

		// 移动游标
		header->slider = header->slider->next;
		
		// 如果删除的是第一个节点，头结点指向会发生改变
		if (deleted_node == header->link.next)
		{
			header->link.next = header->slider;
		}
	}

	// 链表长度减1
	header->length--;

	return deleted_node;
}



/*
 * Function:		LinkList_SetSlider()
 * Description:		如果node是链表中节点，则将游标指向该节点
 * Time complexity:	O(n)
 * Input:	
 *		link_list:	LINK_LIST*类型。链表的地址。	
 *		node:		LINK*类型。游标最后指向的节点
 * Output:	
 * Return:			int类型，操作成功返回0，否则返回其他值
 */
int LinkList_SetSlider(LINK_LIST* link_list, LINK* node)
{
	LINK* current_ptr = NULL;
	int i = 0;

	// 将LINK_LIST类型的地址转换为LINK_LIST_METADATA类型的地址
	LINK_LIST_METADATA* header = (LINK_LIST_METADATA*)link_list;

	// 参数检查
	if (link_list == NULL || node == NULL)
	{
		printf("func LinkList_SetSlider() err: link_list == NULL || node == NULL\n");
		return -1;
	}

	// 遍历
	current_ptr = (LINK*)header;
	for (i = 0; i < header->length; ++i)
	{
		current_ptr = current_ptr->next;
		if (current_ptr == node)
		{
			break;
		}
	}

	// 如果node不在节点中，报错
	if (i >= header->length)
	{
		printf( "func LinkList_SetSlider() err: i >= header->length\n");
		return -2;
	}

	// 移动slider指针指向node节点
	header->slider = current_ptr;

	return 0;
}



/*
 * Function:		LinkList_Traverse()
 * Description:		遍历链表，每个节点执行visit()操作
 * Time complexity:	O(n)
 * Input:	
 *		link_list:	LINK_LIST*类型。链表的地址。	
 *		visit:		int (*)(LINK*)类型，函数指针，每个节点执行的操作
 * Output:	
 * Return:			int类型，操作成功返回0，否则返回其他值
 */
int LinkList_Traverse(LINK_LIST* link_list,	int (*visit)(LINK* node))
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
		func_status = visit(current_ptr);
		if (func_status != 0)
		{
			printf("func LinkList_Traverse() err: func_status != 0\n");
			return -2;
		}
	}

	return 0;
}
