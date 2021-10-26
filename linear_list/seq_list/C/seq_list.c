#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "seq_list.h"


// 顺序线性表的元数据节点
typedef struct SEQ_LIST_METADATA{
	int length;					// 顺序线性表元素个数
	int	capacity;				// 顺序线性表容量
	SEQ_LIST_ELEM* elems;		// 存储第一个数据元素的地址
}SEQ_LIST_METADATA;



/* 构造一个空的容量为capacity的顺序线性表，操作失败返回NULL */
SEQ_LIST* SeqList_Create(int capacity)
{
	SEQ_LIST_METADATA* internal_seq_list = NULL;

	// 参数检查
	if (capacity <= 0)
	{
		printf("func SeqList_Create() err: capacity <= 0\n");
		return NULL;
	}

	// 申请元数据结点空间
	internal_seq_list = (SEQ_LIST_METADATA*)malloc(sizeof(SEQ_LIST_METADATA));
	if (internal_seq_list == NULL)
	{
		printf("func SeqList_Create() err: internal_seq_list == NULL\n");
		return NULL;
	}
	
	// 给申请的空间赋值
	memset(internal_seq_list, 0, sizeof(SEQ_LIST_METADATA));
	internal_seq_list->capacity = capacity;

	// 申请数据元素空间
	internal_seq_list->elems = (SEQ_LIST_ELEM*)malloc(sizeof(SEQ_LIST_ELEM) * internal_seq_list->capacity);
	if (internal_seq_list->elems == NULL)
	{
		printf("func SeqList_Create() err: internal_seq_list->elems == NULL\n");
		return NULL;
	}

	// 数据元素空间赋初值
	memset(internal_seq_list->elems, 0, sizeof(SEQ_LIST_ELEM) * internal_seq_list->capacity);

	// 将内部实现的地址转换为外部地址类型并返回
	return (SEQ_LIST*)internal_seq_list;
}



/* 销毁顺序线性表空间，操作成功返回0，否则返回其他值 */
int SeqList_Destroy(SEQ_LIST* seq_list)
{
	// 将外部的地址转换为内部的地址
	SEQ_LIST_METADATA* internal_seq_list = (SEQ_LIST_METADATA*)seq_list;

	// 参数检查
	if (seq_list == NULL)
	{
		printf("func SeqList_Destroy() err: seq_list == NULL\n");
		return -1;
	}
	else
	{
		// 释放存储数据元素的空间
		if (internal_seq_list->elems != NULL)
		{
			free(internal_seq_list->elems);
			internal_seq_list->elems = NULL;
		}

		// 释放元数据节点的空间
		free(internal_seq_list);
		internal_seq_list = NULL;
	}
	return 0;
}



/* 将顺序线性表置为空表，操作成功返回0，否则返回其他值 */
int SeqList_Clear(SEQ_LIST* seq_list)
{
	// 将外部的地址转换为内部的地址
	SEQ_LIST_METADATA* internal_seq_list = (SEQ_LIST_METADATA*)seq_list;

	// 参数检查
	if (seq_list == NULL)
	{
		printf("func SeqList_Clear() err: seq_list == NULL\n");
		return -1;
	}

	// 将线性表长度置零
	internal_seq_list->length = 0;

	return 0;
}



/* 若顺序线性表为空表，则返回1，否则返回0，操作失败则返回负数 */
int SeqList_IsEmpty(SEQ_LIST* seq_list)
{
	// 将外部的地址转换为内部的地址
	SEQ_LIST_METADATA* internal_seq_list = (SEQ_LIST_METADATA*)seq_list;

	// 参数检查
	if (seq_list == NULL)
	{
		printf("func SeqList_IsEmpty() err: seq_list == NULL\n");
		return -1;
	}

	// 检查线性表长度并返回结果
	return ((internal_seq_list->length == 0) ? 1 : 0);
}



/* 返回顺序线性表中元素个数，操作失败则返回负数 */
int SeqList_GetLength(SEQ_LIST* seq_list)
{
	// 将外部的地址转换为内部的地址
	SEQ_LIST_METADATA* internal_seq_list = (SEQ_LIST_METADATA*)seq_list;

	// 参数检查
	if (seq_list == NULL)
	{
		printf("func SeqList_GetLength() err: seq_list == NULL\n");
		return -1;
	}

	// 返回线性表元素个数
	return internal_seq_list->length;
}



/* 返回顺序线性表的容量，操作失败则返回负数 */
int SeqList_GetCapacity(SEQ_LIST* seq_list)
{
	// 将外部的地址转换为内部的地址
	SEQ_LIST_METADATA* internal_seq_list = (SEQ_LIST_METADATA*)seq_list;

	// 参数检查
	if (seq_list == NULL)
	{
		printf("func SeqList_GetCapacity() err: seq_list == NULL\n");
		return -1;
	}

	// 返回线性表容量
	return internal_seq_list->capacity;
}



/* 返回顺序线性表第pos个数据元素的值，操作失败则返回NULL */
SEQ_LIST_ELEM SeqList_GetElem(SEQ_LIST* seq_list, int pos) 
{
	// 将外部的地址转换为内部的地址
	SEQ_LIST_METADATA* internal_seq_list = (SEQ_LIST_METADATA*)seq_list;

	// 参数检查
	if (seq_list == NULL)
	{
		printf("func SeqList_GetElem() err: seq_list == NULL\n");
		return NULL;
	}

	// 位置合法性检查
	if (pos < 0 || pos >= internal_seq_list->length)
	{
		printf("func SeqList_GetElem() err: pos < 0 || pos >= internal_seq_list->length\n");
		return NULL;
	}

	// 返回下标为pos的数据元素
	return internal_seq_list->elems[pos];
}



/* 返回顺序线性表中第1个与elem满足关系compare()的数据元素的下标。若这样的数据元素不存在，则返回-1 */
int SeqList_LocateElem(SEQ_LIST* seq_list, SEQ_LIST_ELEM elem, int (*compare)(SEQ_LIST_ELEM, SEQ_LIST_ELEM))
{
	// 将外部的地址转换为内部的地址
	SEQ_LIST_METADATA* internal_seq_list = (SEQ_LIST_METADATA*)seq_list;

	int i = 0, func_status = 0;

	// 参数检查
	if (seq_list == NULL || elem == NULL || compare == NULL)
	{
		printf("func SeqList_LocateElem() err: seq_list == NULL || elem == NULL || compare == NULL\n");
		return -1;
	}

	// 遍历所有数据元素，根据compare()函数的返回值确定返回的下标
	for(i = 0; i < internal_seq_list->length; ++i)
	{
		func_status = compare(elem, internal_seq_list->elems[i]);	// 比较每个元素
		if (func_status == 1)		// 匹配第一个元素之后跳出循环
		{
			break;
		}
		else if(func_status < 0)	// compare()函数执行出错，停止本函数执行
		{
			printf("func SeqList_LocateElem() err: func_status < 0\n");
			return -2;
		}
	}

	// 返回第一个匹配的元素的下标
	return i;
}



/* 如果current_elem是顺序线性表的元素，且不是第一个，则返回它的前驱元素，否则操作失败，返回NULL */
SEQ_LIST_ELEM SeqList_PriorELem(SEQ_LIST* seq_list, SEQ_LIST_ELEM current_elem)
{
	// 将外部的地址转换为内部的地址
	SEQ_LIST_METADATA* internal_seq_list = (SEQ_LIST_METADATA*)seq_list;

	int i = 0;

	// 参数检查
	if (seq_list == NULL || current_elem == NULL)
	{
		printf("func SeqList_PriorELem() err: seq_list == NULL || current_elem == NULL\n");
		return NULL;
	}

	// 遍历所有数据元素，找到第一个与current_elem匹配的元素
	for(i = 0; i < internal_seq_list->length && internal_seq_list->elems[i] != current_elem; ++i){}

	// 判断找到的下标的合法性
	if (i == 0 || i >= internal_seq_list->length)
	{
		printf("func SeqList_PriorELem() err: i == 0 || i >= internal_seq_list->length\n");
		return NULL;
	}
	
	// 返回current_elem元素的前驱元素
	return internal_seq_list->elems[i - 1];
}



/* 如果current_elem是顺序线性表的元素，且不是最后一个，则返回它的后继元素，否则操作失败，返回NULL */
SEQ_LIST_ELEM SeqList_NextElem(SEQ_LIST* seq_list, SEQ_LIST_ELEM current_elem)
{
	// 将外部的地址转换为内部的地址
	SEQ_LIST_METADATA* internal_seq_list = (SEQ_LIST_METADATA*)seq_list;

	int i = 0;

	// 参数检查
	if (seq_list == NULL || current_elem == NULL)
	{
		printf("func SeqList_NextElem() err: seq_list == NULL || current_elem == NULL\n");
		return NULL;
	}

	// 遍历所有数据元素，找到第一个与current_elem匹配的元素
	for(i = 0; i < internal_seq_list->length && internal_seq_list->elems[i] != current_elem; ++i){}

	// 判断找到的下标的合法性
	if (i == internal_seq_list->length - 1 || i >= internal_seq_list->length)
	{
		printf("func SeqList_PriorELem() err: i == internal_seq_list->length - 1 || i >= internal_seq_list->length\n");
		return NULL;
	}
	
	// 返回current_elem元素的后继元素
	return internal_seq_list->elems[i + 1];
}



/* 在顺序线性表中第pos个位置之前插入新的数据元素elem，顺序线性表长度加1；成功则返回插入位置，失败则返回-1 */
int SeqList_Insert(SEQ_LIST* seq_list, int pos, SEQ_LIST_ELEM elem)
{
	// 将外部的地址转换为内部的地址
	SEQ_LIST_METADATA* internal_seq_list = (SEQ_LIST_METADATA*)seq_list;

	int i = 0;

	// 参数检查
	if (seq_list == NULL || elem == NULL)
	{
		printf("func SeqList_Insert() err: seq_list == NULL || elem == NULL\n");
		return -1;
	}

	// 线性表容量检查
	if (internal_seq_list->length >= internal_seq_list->capacity)
	{
		printf("func SeqList_Insert() err: internal_seq_list->length >= internal_seq_list->capacity\n");
		return -2;
	}

	// 插入位置合法性检查
	if (pos < 0 || pos > internal_seq_list->length)
	{
		printf("func SeqList_Insert() err: pos < 0 || pos > internal_seq_list->length\n");
		return -3;
	}

	// 插入操作之前准备工作：将插入位置即其之后的元素往后移动一个位置
	for(i = 0; i < internal_seq_list->length - pos; ++i)
	{
		internal_seq_list->elems[internal_seq_list->length - i] = internal_seq_list->elems[internal_seq_list->length - i - 1];
	}

	// 插入操作
	internal_seq_list->elems[pos] = elem;

	// 线性表长度加1
	internal_seq_list->length++;
			
	return pos;
}



/* 删除顺序线性表中下标为pos的元素，并返回其值，顺序线性表长度-1；如果操作失败，返回NULL */
SEQ_LIST_ELEM SeqList_Delete(SEQ_LIST* seq_list, int pos)
{
	// 将外部的地址转换为内部的地址
	SEQ_LIST_METADATA* internal_seq_list = (SEQ_LIST_METADATA*)seq_list;

	int i = 0;
	SEQ_LIST_ELEM deleted_elem = NULL;

	// 参数检查
	if (seq_list == NULL)
	{
		printf("func SeqList_Delete() err: seq_list == NULL\n");
		return NULL;
	}

	// 线性表长度检查
	if (internal_seq_list->length <= 0)
	{
		printf("func SeqList_Delete() err: internal_seq_list->length <= 0\n");
		return NULL;
	}

	// 删除位置合法性检查
	if (pos < 0 || pos > internal_seq_list->length - 1)
	{
		printf("func SeqList_Delete() err: pos < 0 || pos > internal_seq_list->length - 1\n");
		return NULL;
	}

	// 删除之前先缓存被删除元素
	deleted_elem = internal_seq_list->elems[pos];

	// 删除并将删除位置之后所有元素先前移动一位
	for (i = 0; i < internal_seq_list->length - pos - 1; ++i)
	{
		internal_seq_list->elems[pos + i] = internal_seq_list->elems[pos + i + 1];
	}
	internal_seq_list->elems[internal_seq_list->length - 1] = NULL;

	// 线性表长度减一
	internal_seq_list->length--;

	return deleted_elem;
}



/* 依次对顺序线性表的每个元素调用visit()，一旦visit()失败，则操作失败。操作成功返回0，否则返回其他值 */
int SeqList_Traverse(SEQ_LIST* seq_list, int (*visit)(SEQ_LIST_ELEM))
{
	// 将外部的地址转换为内部的地址
	SEQ_LIST_METADATA* internal_seq_list = (SEQ_LIST_METADATA*)seq_list;

	int i = 0;
	int func_status = 0;

	// 参数检查
	if (seq_list == NULL || visit == NULL)
	{
		printf("func SeqList_Traverse() err: seq_list == NULL || visit == NULL\n");
		return -1;
	}

	// 遍历所有数据元素
	for (i = 0; i < internal_seq_list->length; ++i)
	{
		func_status = visit(internal_seq_list->elems[i]);
		if (func_status != 0)
		{
			printf("func SeqList_Traverse() err: func_status != 0\n");
			return -2;
		}
	}

	return 0;
}
