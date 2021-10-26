/***********************************************************************************************************************************************
 * File name:	seq_list.h
 * Author:	guoke
 * Date:	2021.10.26
 * Description:	C语言线性表顺序实现的头文件，该文件包含了顺序线性表类型的声明、顺序线性表数据元素类型的声明和顺序线性表API的声明，其实现包含在文件seq_list.c文件中。
 * History:	1. 2021.10.26 创建并完成初始版本
 **********************************************************************************************************************************************/

#ifndef _SEQ_LIST_H_
#define _SEQ_LIST_H_

#ifdef __cplusplus
extern "C"{
#endif

typedef void SEQ_LIST;				// 对外的顺序线性表的类型
typedef void* SEQ_LIST_ELEM;		// 对外的顺序线性表节点的类型


/*
 * Function:		SeqList_Create()
 * Description:		构造一个空的容量为capacity的顺序线性表
 * Time complexity:	O(1)
 * Input:	
 *		capacity:	int类型，说明构造的顺序线性表的容量
 * Output:	
 * Return:			SEQ_LIST*类型，创建成功则返回顺序线性表地址，否则返回NULL
 */
SEQ_LIST* SeqList_Create(int capacity);


/*
 * Function:		SeqList_Destroy()
 * Description:		销毁顺序线性表空间
 * Time complexity:	O(1)
 * Input:	
 *		seq_list:	SEQ_LIST*类型，顺序线性表地址
 * Output:	
 * Return:			int类型，操作成功返回0，否则返回其他值
 */
int SeqList_Destroy(SEQ_LIST* seq_list);


/*
 * Function:		SeqList_Clear()
 * Description:		将顺序线性表置为空表
 * Time complexity:	O(1)
 * Input:	
 *		seq_list:	SEQ_LIST*类型，顺序线性表地址
 * Output:	
 * Return:			int类型，操作成功返回0，否则返回其他值
 */
int SeqList_Clear(SEQ_LIST* seq_list);


/*
 * Function:		SeqList_IsEmpty()
 * Description:		判断顺序线性表是否为空表
 * Time complexity:	O(1)
 * Input:	
 *		seq_list:	SEQ_LIST*类型，顺序线性表地址
 * Output:	
 * Return:			int类型，若顺序线性表为空表，则返回1，否则返回0，操作失败则返回负数
 */
int SeqList_IsEmpty(SEQ_LIST* seq_list);


/*
 * Function:		SeqList_GetLength()
 * Description:		返回顺序线性表中元素个数
 * Time complexity:	O(1)
 * Input:	
 *		seq_list:	SEQ_LIST*类型，顺序线性表地址
 * Output:	
 * Return:			int类型，操作成功返回顺序线性表长度，否则返回负数
 */
int SeqList_GetLength(SEQ_LIST* seq_list);


/*
 * Function:		SeqList_GetCapacity()
 * Description:		返回顺序线性表的容量
 * Time complexity:	O(1)
 * Input:	
 *		seq_list:	SEQ_LIST*类型，顺序线性表地址
 * Output:	
 * Return:			int类型，操作成功返回顺序线性表容量，否则返回负数
 */
int SeqList_GetCapacity(SEQ_LIST* seq_list);


/*
 * Function:		SeqList_GetElem()
 * Description:		返回顺序线性表第pos个数据元素的值
 * Time complexity:	O(1)
 * Input:	
 *		seq_list:	SEQ_LIST*类型，顺序线性表地址
 *		pos:		int类型，需要获取的数据元素的下标
 * Output:	
 * Return:			SEQ_LIST_ELEM类型，操作成功返回数据元素，否则返回NULL
 */
SEQ_LIST_ELEM SeqList_GetElem(SEQ_LIST* seq_list, int pos); 


/*
 * Function:		SeqList_LocateElem()
 * Description:		返回顺序线性表中第1个与数据元素elem满足关系compare()的数据元素的下标
 * Time complexity:	如果compare()时间复杂度为m，则本函数时间复杂度为O(n*m)
 * Input:	
 *		seq_list:	SEQ_LIST*类型，顺序线性表地址
 *		elem:		SEQ_LIST_ELEM类型，compare()函数中第一个参数
 *		compare:	int(*)(SEQ_LIST_ELEM, SEQ_LIST_ELEM)类型，函数指针
 * Output:	
 * Return:			int类型，顺序线性表中第1个与数据元素elem满足关系compare()的数据元素的下标。操作失败则返回负数
 */
int SeqList_LocateElem(SEQ_LIST* seq_list, SEQ_LIST_ELEM elem, int (*compare)(SEQ_LIST_ELEM, SEQ_LIST_ELEM));  


/*
 * Function:		SeqList_PriorElem()
 * Description:		如果current_elem是顺序线性表的元素，且不是第一个，则返回它的前驱元素
 * Time complexity:	O(n)
 * Input:	
 *		seq_list:			SEQ_LIST*类型，顺序线性表地址
 *		current_elem:		SEQ_LIST_ELEM类型，以该元素作为参考，获取其前驱元素
 * Output:	
 * Return:			SEQ_LIST_ELEM类型，current_elem的前驱元素，操作失败则返回NULL
 */
SEQ_LIST_ELEM SeqList_PriorELem(SEQ_LIST* seq_list, SEQ_LIST_ELEM current_elem);


/*
 * Function:		SeqList_NextElem()
 * Description:		如果current_elem是顺序线性表的元素，且不是最后一个，则返回它的后继元素
 * Time complexity:	O(n)
 * Input:	
 *		seq_list:			SEQ_LIST*类型，顺序线性表地址
 *		current_elem:		SEQ_LIST_ELEM类型，以该元素作为参考，获取其后继元素
 * Output:	
 * Return:			SEQ_LIST_ELEM类型，current_elem的后继元素，操作失败则返回NULL
 */
SEQ_LIST_ELEM SeqList_NextElem(SEQ_LIST* seq_list, SEQ_LIST_ELEM current_elem);


/*
 * Function:		SeqList_Insert()
 * Description:		在顺序线性表中第pos个位置之前插入新的数据元素elem，顺序线性表长度加1
 * Time complexity:	O(n)
 * Input:	
 *		seq_list:	SEQ_LIST*类型，顺序线性表地址
 *		pos:		int类型，将数据元素插入下标为pos的位置
 *		elem:		SEQ_LIST_ELEM类型，插入顺序线性表的元素
 * Output:	
 * Return:			int类型，插入成功则返回插入位置下标，插入失败则返回负数
 */
int SeqList_Insert(SEQ_LIST* seq_list, int pos, SEQ_LIST_ELEM elem);


/*
 * Function:		SeqList_Delete()
 * Description:		删除顺序线性表中下标为pos的元素，并返回其值，顺序线性表长度-1
 * Time complexity:	O(n)
 * Input:	
 *		seq_list:	SEQ_LIST*类型，顺序线性表地址
 *		pos:		int类型，将数据元素插入下标为pos的位置
 * Output:	
 * Return:			SEQ_LIST_ELEM类型，删除成功则返回删除的元素，插入失败则返回NULL
 */
SEQ_LIST_ELEM SeqList_Delete(SEQ_LIST* seq_list, int pos);


/*
 * Function:		SeqList_Traverse()
 * Description:		依次对顺序线性表的每个元素调用visit()，一旦visit()失败，则操作失败
 * Time complexity:	如果visit()时间复杂度为m，则本函数时间复杂度为O(n*M)
 * Input:	
 *		seq_list:	SEQ_LIST*类型，顺序线性表地址
 *		visit:		int(*)(SEQ_LIST_ELEM)类型，函数指针，以数据元素为参数
 * Output:	
 * Return:			int类型，操作成功则返回0，否则返回其他值
 */
int SeqList_Traverse(SEQ_LIST* seq_list, int (*visit)(SEQ_LIST_ELEM));


#ifdef __cplusplus
}
#endif

#endif
