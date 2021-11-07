/***********************************************************************************************************************************************
 * File name:	link_list.h
 * Author:	guoke
 * Date:	2021.10.30
 * Description:	C语言双向循环链表通用库的实现的头文件，该文件包含了双向循环链表类型的声明、结点结构体的声明和链表API的声明，实现在文件link_list.c中。为了发挥双向循环链表的优势，该实现刻意弱化了下标标识结点位置，而是更多地通过游标来指示结点位置。
 * History:	1. 2021.10.30 创建并完成初始版本
 *			2. 2021.11.07 对用户隐藏链表指针域，用户的业务数据中不在需要包含指针域
 **********************************************************************************************************************************************/

#ifndef _LINK_LIST_H_
#define _LINK_LIST_H_

#ifdef __cplusplus
extern "C"{
#endif

typedef void	LINK_LIST;			// 对外的链式线性表类型
typedef void*	LIST_NODE;			// 对外展示的结点类型


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
 * Time complexity:	O(n)
 * Input:	
 *		link_list:	LINK_LIST*类型，链表的地址	
 * Output:	
 * Return:			int类型，操作成功返回0，否则返回其他值
 */
int LinkList_Destroy(LINK_LIST* link_list);



/*
 * Function:		LinkList_Clear()
 * Description:		将链表置为空表
 * Time complexity:	O(n)
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
 * Description:		重置链表的游标。如果链表中有结点，游标指向第一个结点；如果链表中没有结点，游标置NULL
 * Time complexity:	O(1)
 * Input:	
 *		link_list:	LINK_LIST*类型，链表的地址	
 * Output:	
 * Return:			int类型，操作成功返回0，否则返回其他值
 */
int LinkList_ResetSlider(LINK_LIST* link_list);



/*
 * Function:		LinkList_GetSlider()
 * Description:		获取链表游标指向的结点数据
 * Time complexity:	O(1)
 * Input:	
 *		link_list:	LINK_LIST*类型，链表的地址	
 * Output:	
 * Return:			LIST_NODE类型。如果操作成功，返回游标指向的结点数据。如果操作失败，返回NULL
 */
LIST_NODE LinkList_GetSlider(LINK_LIST* link_list);


/*
 * Function:		LinkList_SliderForward()
 * Description:		获取当前游标指向的结点的数据，游标指向其后继结点
 * Time complexity:	O(1)
 * Input:	
 *		link_list:	LINK_LIST*类型，链表的地址	
 * Output:	
 * Return:			LIST_NODE类型。如果操作成功，返回游标指向的结点数据。如果操作失败，返回NULL
 */
LIST_NODE LinkList_SliderForward(LINK_LIST* link_list);



/*
 * Function:		LinkList_SliderBackward()
 * Description:		返回当前游标指向的结点的数据，游标指向其前驱结点
 * Time complexity:	O(1)
 * Input:	
 *		link_list:	LINK_LIST*类型，链表的地址	
 * Output:	
 * Return:			LIST_NODE类型。如果操作成功，返回游标指向的结点数据。如果操作失败，返回NULL
 */
LIST_NODE LinKList_SliderBackward(LINK_LIST* link_list);



/*
 * Function:		LinkList_InsertBeforeSlider()
 * Description:		在游标指向的结点前面插入一个结点，并将游标指向插入的结点，在第一个结点之前插入的话，头结点会指向插入的结点
 * Time complexity:	O(1)
 * Input:	
 *		link_list:	LINK_LIST*类型。链表的地址。	
 *		list_node:	LIST_NODE类型。插入的数据。
 * Output:	
 * Return:			int类型，操作成功返回0，否则返回其他值
 */
int LinkList_InsertBeforeSlider(LINK_LIST* link_list, LIST_NODE list_node);



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
int LinkList_InsertAfterSlider(LINK_LIST* link_list, LIST_NODE list_node);



/*
 * Function:		LinkList_DeleteSlider()
 * Description:		删除游标指向的结点，获取删除结点的数据，游标指向删除结点的后继结点。如果删除的是第一个结点，被删除结点的后继结点将会变成第一个结点。如果删除之后链表变成空表，游标置NULL
 * Time complexity:	O(1)
 * Input:	
 *		link_list:	LINK_LIST*类型。链表的地址。	
 * Output:	
 * Return:			LIST_NODE类型。如果操作成功，返回被删除的结点的数据。如果操作失败，返回NULL
 */
LIST_NODE LinkList_DeleteSlider(LINK_LIST* link_list);



/*
 * Function:		LinkList_SetSlider()
 * Description:		如果链表中存在某个结点包含数据list_node，将游标指向第一个包含该数据的结点
 * Time complexity:	O(n)
 * Input:	
 *		link_list:	LINK_LIST*类型。链表的地址。	
 *		list_node:	LIST_NODE类型。游标最后指向的结点
 * Output:	
 * Return:			int类型，操作成功返回0，否则返回其他值
 */
int LinkList_SetSlider(LINK_LIST* link_list, LIST_NODE list_node);



/*
 * Function:		LinkList_Traverse()
 * Description:		遍历链表，每个结点的数据作为参数，调用函数visit()
 * Time complexity:	O(n)
 * Input:	
 *		link_list:	LINK_LIST*类型。链表的地址。	
 *		visit:		int (*)(LIST_NODE)类型，函数指针，每个结点的数据执行的操作
 * Output:	
 * Return:			int类型，操作成功返回0，否则返回其他值
 */
int LinkList_Traverse(LINK_LIST* link_list,	int (*visit)(LIST_NODE node));

#ifdef __cplusplus
}
#endif

#endif
