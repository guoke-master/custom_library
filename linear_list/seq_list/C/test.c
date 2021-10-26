/******************************************************************************************************************************************
 * File name:	test.c
 * Author:	guoke
 * Date:	2021.10.26
 * Description:	C语言线性表顺序存储库seq_list.c、seq_list.h的API测试程序
 *				其实现包含在文件seq_list.c文件中。
 * History:	1. 2021.10.26 创建并完成初始版本
 *****************************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "seq_list.h"

// TEACHER类型
typedef struct TEACHER{
	int age;
	char name[32];
}TEACHER;

// TEACHER类型的print函数
int TeacherPrint(SEQ_LIST_ELEM t);

// TEACHER类型的比较函数
int TeacherCompare(SEQ_LIST_ELEM t1,SEQ_LIST_ELEM t2);

int main(void)
{
	SEQ_LIST* seq_list = NULL;
	TEACHER* tmp = NULL;
	int func_status = 0;
	int i = 0;

	// 创建几个TEACHER类型以备测试
	printf("\n*************** 创建几个TEACHER类型以备测试 ***************\n");
	TEACHER t1, t2, t3, t4, t5;
	t1.age = 21;
	t2.age = 22;
	t3.age = 23;
	t4.age = 24;
	t5.age = 25;
	strcpy(t1.name, "teacher_01");
	strcpy(t2.name, "teacher_02");
	strcpy(t3.name, "teacher_03");
	strcpy(t4.name, "teacher_04");
	strcpy(t5.name, "teacher_05");

	TeacherPrint((SEQ_LIST_ELEM)&t1);
	TeacherPrint((SEQ_LIST_ELEM)&t2);
	TeacherPrint((SEQ_LIST_ELEM)&t3);
	TeacherPrint((SEQ_LIST_ELEM)&t4);
	TeacherPrint((SEQ_LIST_ELEM)&t5);
	
	// 线性表测试开始
	printf("\n************** 线性表测试开始 ****************\n");
	
	// 创建链表
	printf("\n创建链表：\n");
	seq_list = SeqList_Create(100);
	if (seq_list == NULL)
	{
		printf("func main() err: seq_list == NULL\n");
		return -1;
	}

	// 插入元素
	printf("\n插入元素：\n");
	SeqList_Insert(seq_list, 0, (SEQ_LIST_ELEM)&t1);
	printf("length = %d\tcapacity = %d\n", SeqList_GetLength(seq_list), SeqList_GetCapacity(seq_list));
	SeqList_Insert(seq_list, 0, (SEQ_LIST_ELEM)&t2);
	printf("length = %d\tcapacity = %d\n", SeqList_GetLength(seq_list), SeqList_GetCapacity(seq_list));
	SeqList_Insert(seq_list, 0, (SEQ_LIST_ELEM)&t3);
	printf("length = %d\tcapacity = %d\n", SeqList_GetLength(seq_list), SeqList_GetCapacity(seq_list));
	SeqList_Insert(seq_list, 0, (SEQ_LIST_ELEM)&t4);
	printf("length = %d\tcapacity = %d\n", SeqList_GetLength(seq_list), SeqList_GetCapacity(seq_list));
	SeqList_Insert(seq_list, 0, (SEQ_LIST_ELEM)&t5);
	printf("length = %d\tcapacity = %d\n", SeqList_GetLength(seq_list), SeqList_GetCapacity(seq_list));

	// 获取元素
	printf("\n获取元素：\n");
	for (i = 0; i < SeqList_GetLength(seq_list); ++i)
	{
		tmp = (TEACHER*)SeqList_GetElem(seq_list, i);
		TeacherPrint((SEQ_LIST_ELEM)tmp);
	}
		
	// 清空线性表
	// printf("\n清空线性表：\n");
	// SeqList_Clear(seq_list);
	// printf("length = %d\tcapacity = %d\n", SeqList_GetLength(seq_list), SeqList_GetCapacity(seq_list));

	
	// 遍历元素
	printf("\n遍历元素：\n");
	SeqList_Traverse(seq_list, TeacherPrint); 

	// 定位元素
	printf("\n定位元素：\n");
	printf("t1 in position: %d\n", SeqList_LocateElem(seq_list, &t1, TeacherCompare)); 
	printf("t2 in position: %d\n", SeqList_LocateElem(seq_list, &t2, TeacherCompare)); 
	printf("t3 in position: %d\n", SeqList_LocateElem(seq_list, &t3, TeacherCompare)); 
	printf("t4 in position: %d\n", SeqList_LocateElem(seq_list, &t4, TeacherCompare)); 
	printf("t5 in position: %d\n", SeqList_LocateElem(seq_list, &t5, TeacherCompare)); 

	// 前驱和后继
	printf("\n前驱和后继：\n");
	tmp = (TEACHER*)SeqList_PriorELem(seq_list, &t1);
	printf("t1的前驱：");
	TeacherPrint((SEQ_LIST_ELEM)tmp);
	tmp = (TEACHER*)SeqList_PriorELem(seq_list, &t2);
	printf("t2的前驱：");
	TeacherPrint((SEQ_LIST_ELEM)tmp);
	tmp = (TEACHER*)SeqList_PriorELem(seq_list, &t3);
	printf("t3的前驱：");
	TeacherPrint((SEQ_LIST_ELEM)tmp);
	tmp = (TEACHER*)SeqList_PriorELem(seq_list, &t4);
	printf("t4的前驱：");
	TeacherPrint((SEQ_LIST_ELEM)tmp);

	tmp = (TEACHER*)SeqList_NextElem(seq_list, &t5);
	printf("t5的后继：");
	TeacherPrint((SEQ_LIST_ELEM)tmp);
	tmp = (TEACHER*)SeqList_NextElem(seq_list, &t4);
	printf("t4的后继：");
	TeacherPrint((SEQ_LIST_ELEM)tmp);
	tmp = (TEACHER*)SeqList_NextElem(seq_list, &t3);
	printf("t3的后继：");
	TeacherPrint((SEQ_LIST_ELEM)tmp);
	tmp = (TEACHER*)SeqList_NextElem(seq_list, &t2);
	printf("t2的后继：");
	TeacherPrint((SEQ_LIST_ELEM)tmp);

	// 删除节点
	printf("\n删除节点：\n");
	while(!SeqList_IsEmpty(seq_list))
	{
		tmp = (TEACHER*)SeqList_Delete(seq_list, 0);
		printf("length = %d\tcapacity = %d\t", SeqList_GetLength(seq_list), SeqList_GetCapacity(seq_list));
		printf("删除节点：\t");
		TeacherPrint((SEQ_LIST_ELEM)tmp);
	}


	// 销毁链表
	printf("\n销毁链表：\n");
	func_status = SeqList_Destroy(seq_list);
	if (func_status != 0)
	{
		printf("func main() err: func_status != 0\n");
		return func_status;
	}


	printf("Hello world!\n");
	return 0;
}


// TEACHER类型的print函数
int TeacherPrint(SEQ_LIST_ELEM t)
{
	// 将SEQ_LIST_ELEM类型的指针转换为TEACHER类型的指针
	TEACHER* t1 = (TEACHER*)t;
	// 参数检查
	if (t == NULL)
	{
		printf("func TeacherPrint() err: t == NULL\n");
		return -1;
	}

	// 打印
	printf("age = %d\t name = %s\n", t1->age, t1->name);
	return 0;
}

// TEACHER类型的比较函数
int TeacherCompare(SEQ_LIST_ELEM t1, SEQ_LIST_ELEM t2)
{
	// 参数检查
	if (t1 == NULL || t2 == NULL)
	{
		printf("func TeacherCompare() err: t1 == NULL || t2 == NULL\n");
		return -1;
	}

	return (t1 == t2)?1:0; 
}

