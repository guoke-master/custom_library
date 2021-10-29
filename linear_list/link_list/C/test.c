/***********************************************************************************************************************************************
 * File name:	test.c
 * Author:	guoke
 * Date:	2021.10.30
 * Description:	C语言双向循环链表通用局link_list.h、link_list.cAPI的测试程序
 * History:	1. 2021.10.30 创建并完成初始版本
 **********************************************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link_list.h"

// TEACHER结构体
typedef struct TEACHER{
	LINK link;				// 链表的指针域，如果想使用链表库，需要将该结构体放在业务节点的第一个位置
	int age;
	char name[32];
}TEACHER;

// TEACHER类型的print函数
int TeacherPrint(LINK* t);

int main(void)
{
	// 链表指针
	LINK_LIST* link_list = NULL;

	int list_length = 0;
	LINK* list_slider = NULL;
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

	TeacherPrint((LINK*)(&t1));
	TeacherPrint((LINK*)(&t2));
	TeacherPrint((LINK*)(&t3));
	TeacherPrint((LINK*)(&t4));
	TeacherPrint((LINK*)(&t5));

	// 线性表测试开始
	printf("\n************** 线性表测试开始 ****************\n");

	// 创建链表
	printf("\n创建链表：\n");
	link_list = LinkList_Create();
	list_length = LinkList_GetLength(link_list);
	// list_slider = LinkList_GetSlider(link_list);
	printf("length = %d\n", list_length);


	// 插入元素
	printf("\n插入元素：\n");
	LinkList_InsertBeforeSlider(link_list, (LINK*)(&t1));
	list_length = LinkList_GetLength(link_list);
	list_slider = LinkList_GetSlider(link_list);
	printf("length = %d, slider is ", list_length);
	TeacherPrint(list_slider);
	
	LinkList_InsertBeforeSlider(link_list, (LINK*)(&t2));
	list_length = LinkList_GetLength(link_list);
	list_slider = LinkList_GetSlider(link_list);
	printf("length = %d, slider is ", list_length);
	TeacherPrint(list_slider);

	LinkList_InsertBeforeSlider(link_list, (LINK*)(&t3));
	list_length = LinkList_GetLength(link_list);
	list_slider = LinkList_GetSlider(link_list);
	printf("length = %d, slider is ", list_length);
	TeacherPrint(list_slider);

	LinkList_InsertBeforeSlider(link_list, (LINK*)(&t4));
	list_length = LinkList_GetLength(link_list);
	list_slider = LinkList_GetSlider(link_list);
	printf("length = %d, slider is ", list_length);
	TeacherPrint(list_slider);

	LinkList_InsertBeforeSlider(link_list, (LINK*)(&t5));
	list_length = LinkList_GetLength(link_list);
	list_slider = LinkList_GetSlider(link_list);
	printf("length = %d, slider is ", list_length);
	TeacherPrint(list_slider);

	// 初始化并移动游标
	printf("\n初始化并移动游标:\n");

	LinkList_ResetSlider(link_list);
	for(i = 0; i < list_length; ++i)
	{
		list_slider = LinkList_SliderForward(link_list);
		TeacherPrint(list_slider);
	}

	LinkList_ResetSlider(link_list);
	LinKList_SliderBackward(link_list);
	for(i = 0; i < list_length; ++i)
	{
		list_slider = LinKList_SliderBackward(link_list);
		TeacherPrint(list_slider);
	}

	// 链表的判空和清空链表
	printf("\n链表的判空和清空链表：\n");
	if (!LinkList_IsEmpty(link_list))
	{
		printf("清空链表:\t");
		LinkList_Clear(link_list);
		list_length = LinkList_GetLength(link_list);
		printf("length = %d\t",list_length);
	}

	if(LinkList_IsEmpty(link_list))
	{
		printf("链表已空!\n");
	}

	// 第二种方法插入元素
	printf("\n第二种方法插入元素：\n");
	LinkList_InsertAfterSlider(link_list, (LINK*)(&t1));
	list_length = LinkList_GetLength(link_list);
	list_slider = LinkList_GetSlider(link_list);
	printf("length = %d, slider is ", list_length);
	TeacherPrint(list_slider);

	LinkList_InsertAfterSlider(link_list, (LINK*)(&t2));
	list_length = LinkList_GetLength(link_list);
	list_slider = LinkList_GetSlider(link_list);
	printf("length = %d, slider is ", list_length);
	TeacherPrint(list_slider);

	LinkList_InsertAfterSlider(link_list, (LINK*)(&t3));
	list_length = LinkList_GetLength(link_list);
	list_slider = LinkList_GetSlider(link_list);
	printf("length = %d, slider is ", list_length);
	TeacherPrint(list_slider);

	LinkList_InsertAfterSlider(link_list, (LINK*)(&t4));
	list_length = LinkList_GetLength(link_list);
	list_slider = LinkList_GetSlider(link_list);
	printf("length = %d, slider is ", list_length);
	TeacherPrint(list_slider);

	LinkList_InsertAfterSlider(link_list, (LINK*)(&t5));
	list_length = LinkList_GetLength(link_list);
	list_slider = LinkList_GetSlider(link_list);
	printf("length = %d, slider is ", list_length);
	TeacherPrint(list_slider);

	// 初始化并移动游标
	printf("\n初始化并移动游标:\n");

	LinkList_ResetSlider(link_list);
	for(i = 0; i < list_length; ++i)
	{
		list_slider = LinkList_SliderForward(link_list);
		TeacherPrint(list_slider);
	}

	LinkList_ResetSlider(link_list);
	LinKList_SliderBackward(link_list);
	for(i = 0; i < list_length; ++i)
	{
		list_slider = LinKList_SliderBackward(link_list);
		TeacherPrint(list_slider);
	}

	// 遍历节点
	printf("\n遍历结点：\n");
	LinkList_Traverse(link_list, TeacherPrint);

	// 删除节点
	printf("\n删除节点：\n");
	LinkList_ResetSlider(link_list);

	while(!LinkList_IsEmpty(link_list))
	{
		list_slider = LinkList_DeleteSlider(link_list);
		list_length = LinkList_GetLength(link_list);
		printf("length = %d\t", list_length);
		printf("删除节点：\t");
		TeacherPrint(list_slider);
	}

	// 销毁链表
	printf("\n销毁链表：\n");
	LinkList_Destroy(link_list);


	printf("Hello world!\n");
	return 0;
}

// TEACHER类型的print函数
int TeacherPrint(LINK* t)
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
