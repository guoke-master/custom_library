/******************************************************************************************************************************************
 * File name:	test.cpp
 * Author:	guoke
 * Date:	2021.11.13
 * Description:	C++线性表链式存储库link_list.cpp、link_list.h的API测试程序
 * History:	1. 2021.11.13 创建并完成初始版本
 *****************************************************************************************************************************************/

#include <iostream>
#include <cstring>
#include <string>
#include "link_list.cpp"

using namespace std;


// TEACHER类型
class TEACHER{
private:
	int age;
	string name;
public:
	TEACHER():age(0),name(""){}											// Constructor
	TEACHER(int _age, const string _name):age(_age),name(_name){}		// Constructor with parameter
	TEACHER(const TEACHER& t):age(t.age),name(t.name){}					// Copy constructor

public:
	/* 输出类信息 */
	int PrintInfo(){cout << "age = " << age << "\tname = " << name << endl; return 0;}

public:
	/* 重载赋值操作符 */
	TEACHER& operator=(const TEACHER& t);
	
	/* 重载==操作符，调用者为TEACHER类 */
	bool operator==(const TEACHER& t);

	/* 重载==操作符，调用者为const TEACHER类 */
	bool operator==(const TEACHER& t) const;
};

// 打印TEACHER类信息
int PrintTeacher(TEACHER& t);

int main(void)
{
	// 创建几个TEACHER对象以备测试
	cout << "\n***************************************** 创建几个TEACHER对象以备测试 **********************************" << endl;
	TEACHER t1(21, "teacher_01"), t2(22, "teacher_02"), t3(23, "teacher_03"), t4(24, "teacher_04"), t5(25, "teacher_05");
	t1.PrintInfo();
	t2.PrintInfo();
	t3.PrintInfo();
	t4.PrintInfo();
	t5.PrintInfo();

	// 链表测试开始
	cout << "\n***************************************** 链表测试开始 **********************************" << endl;
	
	// 创建链表
	cout << "\n***************************************** 创建链表 **********************************" << endl;
	LINK_LIST<TEACHER> teacher_list;
	cout << "length = " << teacher_list.GetLength() << endl;

	// TEACHER tmp_teacher;
	// teacher_list.GetSlider(tmp_teacher);

	// 使用InsertAfterSlider()方法插入元素
	cout << "\n*****************************************  使用InsertAfterSlider()方法插入元素 **********************************" << endl;
	TEACHER tmp;
	teacher_list.ResetSlider();

	teacher_list.InsertAfterSlider(t1);
	cout << "length = " << teacher_list.GetLength() << endl;
	teacher_list.GetSlider(tmp);
	tmp.PrintInfo();
	
	teacher_list.InsertAfterSlider(t2);
	cout << "length = " << teacher_list.GetLength() << endl;
	teacher_list.GetSlider(tmp);
	tmp.PrintInfo();
	
	teacher_list.InsertAfterSlider(t3);
	cout << "length = " << teacher_list.GetLength() << endl;
	teacher_list.GetSlider(tmp);
	tmp.PrintInfo();
	
	teacher_list.InsertAfterSlider(t4);
	cout << "length = " << teacher_list.GetLength() << endl;
	teacher_list.GetSlider(tmp);
	tmp.PrintInfo();
	
	teacher_list.InsertAfterSlider(t5);
	cout << "length = " << teacher_list.GetLength() << endl;
	teacher_list.GetSlider(tmp);
	tmp.PrintInfo();

	// 遍历链表
	cout << "\n***************************************** 遍历链表 **********************************" << endl;
	teacher_list.Traverse(PrintTeacher);
	
	// 初始化并向前移动游标
	cout << "\n***************************************** 初始化并向前移动游标 **********************************" << endl;
	teacher_list.ResetSlider();

	for (int i = 0; i < teacher_list.GetLength(); ++i)
	{
		teacher_list.SliderForward(tmp);
		tmp.PrintInfo();
	}

	// 初始化并向后移动游标
	cout << "\n***************************************** 初始化并向后移动游标 **********************************" << endl;
	teacher_list.ResetSlider();
	teacher_list.SliderBackward(tmp);

	for (int i = 0; i < teacher_list.GetLength(); ++i)
	{
		teacher_list.SliderBackward(tmp);
		tmp.PrintInfo();
	}

	// 清空链表
	cout << "\n***************************************** 清空链表 **********************************" << endl;
	if (!teacher_list.IsEmpty())
	{
		cout << "链表非空，清空链表："<< endl;
		cout << "清空之前：length = " << teacher_list.GetLength() << endl;
		teacher_list.Clear();
	}

	if (teacher_list.IsEmpty())
	{
		cout << "链表为空：length = " << teacher_list.GetLength() << endl;
	}

	// 使用InsertBeforeSlider()方法插入元素
	cout << "\n*****************************************  使用InsertBeforeSlider()方法插入元素 **********************************" << endl;
	teacher_list.ResetSlider();

	teacher_list.InsertBeforeSlider(t1);
	cout << "length = " << teacher_list.GetLength() << endl;
	teacher_list.GetSlider(tmp);
	tmp.PrintInfo();
	
	teacher_list.InsertBeforeSlider(t2);
	cout << "length = " << teacher_list.GetLength() << endl;
	teacher_list.GetSlider(tmp);
	tmp.PrintInfo();
	
	teacher_list.InsertBeforeSlider(t3);
	cout << "length = " << teacher_list.GetLength() << endl;
	teacher_list.GetSlider(tmp);
	tmp.PrintInfo();
	
	teacher_list.InsertBeforeSlider(t4);
	cout << "length = " << teacher_list.GetLength() << endl;
	teacher_list.GetSlider(tmp);
	tmp.PrintInfo();
	
	teacher_list.InsertBeforeSlider(t5);
	cout << "length = " << teacher_list.GetLength() << endl;
	teacher_list.GetSlider(tmp);
	tmp.PrintInfo();

	// 遍历链表
	cout << "\n***************************************** 遍历链表 **********************************" << endl;
	teacher_list.Traverse(PrintTeacher);
	
	// 初始化并向前移动游标
	cout << "\n***************************************** 初始化并向前移动游标 **********************************" << endl;
	teacher_list.ResetSlider();

	for (int i = 0; i < teacher_list.GetLength(); ++i)
	{
		teacher_list.SliderForward(tmp);
		tmp.PrintInfo();
	}

	// 初始化并向后移动游标
	cout << "\n***************************************** 初始化并向后移动游标 **********************************" << endl;
	teacher_list.ResetSlider();
	teacher_list.SliderBackward(tmp);

	for (int i = 0; i < teacher_list.GetLength(); ++i)
	{
		teacher_list.SliderBackward(tmp);
		tmp.PrintInfo();
	}

	// 设置游标位置并获取游标指向结点数据
	cout << "\n***************************************** 设置游标位置并获取游标指向结点数据 **********************************" << endl;
	teacher_list.ResetSlider();
	teacher_list.SetSlider(t2);
	teacher_list.GetSlider(tmp);
	tmp.PrintInfo();

	// 删除数据
	cout << "\n***************************************** 删除数据 **********************************" << endl;
	teacher_list.ResetSlider();

	while(teacher_list.GetLength())
	{
		teacher_list.DeleteSlider(tmp);
		tmp.PrintInfo();
		cout << "length = " << teacher_list.GetLength() << endl;
	}

	cout << "Hello world!" << endl;
	return 0;
}


/* Class of TEACHER overloads = */
TEACHER& TEACHER::operator=(const TEACHER& t)
{
	this->age = t.age;
	this->name = t.name;
	return *this;
}

/* Class of TEACHER overloads == */
bool TEACHER::operator==(const TEACHER& t)
{
	return (age == t.age && name == t.name) ? true : false;
}

bool TEACHER::operator==(const TEACHER& t) const
{
	return (age == t.age && name == t.name) ? true : false;
}



// 打印TEACHER类信息
int PrintTeacher(TEACHER& t)
{
	t.PrintInfo();
	return 0;
}
