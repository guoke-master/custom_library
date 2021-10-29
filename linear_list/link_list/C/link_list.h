/***********************************************************************************************************************************************
 * File name:	link_list.h
 * Author:	guoke
 * Date:	2021.10.30
 * Description:	C语言双向循环链表通用库的实现的头文件，该文件包含了双向循环链表类型的声明、节点结构体的声明和链表API的声明，实现在文件link_list.c中。为了发挥双向循环链表的优势，该实现刻意弱化了下标标识节点位置，而是更多地通过游标来指示节点位置。
 * History:	1. 2021.10.30 创建并完成初始版本
 **********************************************************************************************************************************************/
#ifndef _LINK_LIST_H_
#define _LINK_LIST_H_

#ifdef __cplusplus
extern "C"{
#endif

typedef void	LINK_LIST;			// 对外的链式线性表类型

typedef struct LINK{				// 链表的指针域，使用该链表时，请将该结构体放在业务结构体第一个元素位置
	struct LINK* next;				// 指向下一节点
	struct LINK* prior;				// 指向前一节点
}LINK;



/*
 * Function:		LinkList_Create()
 * Description:		构造一个空的链表
 * Time complexity:	O(1)
 * Input:	
 * Output:	
 * Return:			LINK_LIST*类型，创建成功则返回链表地址，否则返回NULL
 */
LINK_LIST* LinkList_Create();



/*
 * Function:		LinkList_Destroy()
 * Description:		销毁链表空间
 * Time complexity:	O(1)
 * Input:	
 *		link_list:	LINK_LIST*类型，链表的地址	
 * Output:	
 * Return:			int类型，操作成功返回0，否则返回其他值
 */
int LinkList_Destroy(LINK_LIST* link_list);



/*
 * Function:		LinkList_Clear()
 * Description:		将链表置为空表
 * Time complexity:	O(1)
 * Input:	
 *		link_list:	LINK_LIST*类型，链表的地址	
 * Output:	
 * Return:			int类型，操作成功返回0，否则返回其他值
 */
int LinkList_Clear(LINK_LIST* link_list);



/*
 * Function:		LinkList_GetLength()
 * Description:		获取链表长度
 * Time complexity:	O(1)
 * Input:	
 *		link_list:	LINK_LIST*类型，链表的地址	
 * Output:	
 * Return:			int类型，操作成功返回0，否则返回其他值
 */
int LinkList_GetLength(LINK_LIST* link_list);



/*
 * Function:		LinkList_IsEmpty()
 * Description:		判断链表是否为空表
 * Time complexity:	O(1)
 * Input:	
 *		link_list:	LINK_LIST*类型，链表的地址	
 * Output:	
 * Return:			int类型，操作成功返回0，否则返回其他值
 */
int LinkList_IsEmpty(LINK_LIST* link_list);



/*
 * Function:		LinkList_ResetSlider()
 * Description:		重置链表的游标。如果链表中有节点，游标指向第一个节点；如果链表中没有节点，游标置NULL
 * Time complexity:	O(1)
 * Input:	
 *		link_list:	LINK_LIST*类型，链表的地址	
 * Output:	
 * Return:			int类型，操作成功返回0，否则返回其他值
 */
int LinkList_ResetSlider(LINK_LIST* link_list);



/*
 * Function:		LinkList_GetSlider()
 * Description:		返回链表游标指向的节点地址
 * Time complexity:	O(1)
 * Input:	
 *		link_list:	LINK_LIST*类型，链表的地址	
 * Output:	
 * Return:			LINK*类型。如果操作成功，返回游标指向的节点指针。如果操作失败，返回NULL
 */
LINK* LinkList_GetSlider(LINK_LIST* link_list);



/*
 * Function:		LinkList_SliderForward()
 * Description:		返回当前游标指向的节点的地址，游标指向其后继节点
 * Time complexity:	O(1)
 * Input:	
 *		link_list:	LINK_LIST*类型，链表的地址	
 * Output:	
 * Return:			LINK*类型。如果操作成功，返回游标指向的节点指针。如果操作失败，返回NULL
 */
LINK* LinkList_SliderForward(LINK_LIST* link_list);



/*
 * Function:		LinkList_SliderBackward()
 * Description:		返回当前游标指向的节点的地址，游标指向其前驱节点
 * Time complexity:	O(1)
 * Input:	
 *		link_list:	LINK_LIST*类型，链表的地址	
 * Output:	
 * Return:			LINK*类型。如果操作成功，返回游标指向的节点指针。如果操作失败，返回NULL
 */
LINK* LinKList_SliderBackward(LINK_LIST* link_list);



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
int LinkList_InsertBeforeSlider(LINK_LIST* link_list, LINK* node);



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
int LinkList_InsertAfterSlider(LINK_LIST* link_list, LINK* node);



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
LINK* LinkList_DeleteSlider(LINK_LIST* link_list);



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
int LinkList_SetSlider(LINK_LIST* link_list, LINK* node);



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
int LinkList_Traverse(LINK_LIST* link_list,	int (*visit)(LINK* node));


#ifdef __cplusplus
}
#endif

#endif
