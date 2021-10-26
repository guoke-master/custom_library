#ifndef _SEQ_LIST_H_
#define _SEQ_LIST_H_

#ifdef __cplusplus
extern "C"{
#endif

typedef void SEQ_LIST;				// 对外的顺序线性表的类型
typedef void* SEQ_LIST_ELEM;		// 对外的顺序线性表节点的类型


/* 构造一个空的容量为capacity的顺序线性表，操作失败返回NULL */
SEQ_LIST* SeqList_Create(int capacity);

/* 销毁顺序线性表空间，操作成功返回0，否则返回其他值 */
int SeqList_Destroy(SEQ_LIST* seq_list);

/* 将顺序线性表置为空表，操作成功返回0，否则返回其他值 */
int SeqList_Clear(SEQ_LIST* seq_list);

/* 若顺序线性表为空表，则返回1，否则返回0，操作失败则返回负数 */
int SeqList_IsEmpty(SEQ_LIST* seq_list);

/* 返回顺序线性表中元素个数，操作失败则返回负数 */
int SeqList_GetLength(SEQ_LIST* seq_list);

/* 返回顺序线性表的容量，操作失败则返回负数 */
int SeqList_GetCapacity(SEQ_LIST* seq_list);

/* 返回顺序线性表第pos个数据元素的值，操作失败则返回NULL */
SEQ_LIST_ELEM SeqList_GetElem(SEQ_LIST* seq_list, int pos); 

/* 返回顺序线性表中第1个与elem满足关系compare()的数据元素的下标。若这样的数据元素不存在，则返回-1 */
int SeqList_LocateElem(SEQ_LIST* seq_list, SEQ_LIST_ELEM elem, int (*compare)(SEQ_LIST_ELEM, SEQ_LIST_ELEM));  

/* 如果current_elem是顺序线性表的元素，且不是第一个，则返回它的前驱元素，否则操作失败，返回NULL */
SEQ_LIST_ELEM SeqList_PriorELem(SEQ_LIST* seq_list, SEQ_LIST_ELEM current_elem);

/* 如果current_elem是顺序线性表的元素，且不是最后一个，则返回它的后继元素，否则操作失败，返回NULL */
SEQ_LIST_ELEM SeqList_NextElem(SEQ_LIST* seq_list, SEQ_LIST_ELEM current_elem);

/* 在顺序线性表中第pos个位置之前插入新的数据元素elem，顺序线性表长度加1；成功则返回插入位置，失败则返回-1 */
int SeqList_Insert(SEQ_LIST* seq_list, int pos, SEQ_LIST_ELEM elem);

/* 删除顺序线性表中下标为pos的元素，并返回其值，顺序线性表长度-1；如果操作失败，返回NULL */
SEQ_LIST_ELEM SeqList_Delete(SEQ_LIST* seq_list, int pos);

/* 依次对顺序线性表的每个元素调用visit()，一旦visit()失败，则操作失败。操作成功返回0，否则返回其他值 */
int SeqList_Traverse(SEQ_LIST* seq_list, int (*visit)(SEQ_LIST_ELEM));


#ifdef __cplusplus
}
#endif

#endif
