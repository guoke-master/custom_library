/******************************************************************************************************************************************
 * File name:	test.cpp
 * Author:	guoke
 * Date:	2021.10.27
 * Description:	C++线性表顺序存储库seq_list.cpp、seq_list.h的API测试程序
 * History:	1. 2021.10.27 创建并完成初始版本
 *****************************************************************************************************************************************/

#include <iostream>
#include <string>
#include "seq_list.cpp"

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
	int PrintInfo(){cout << "age = " << age << "\tname = " << name << endl; return 0;}

public:
	TEACHER& operator=(const TEACHER& t);
	
	bool operator==(const TEACHER& t);
	bool operator==(const TEACHER& t) const;
};

// 打印函数，用作函数指针传入线性表内部
int PrintTeacher(TEACHER& t)
{
	return t.PrintInfo();
}
	
int main(void)
{
	// 创建几个TEACHER类型以备测试
	cout << "*************************** 创建几个TEACHER类型以备测试 *************************" << endl;
	TEACHER t1(21,"t1"), t2(22,"t2"), t3(23,"t3"), t4(24,"t4"), t5(25,"t5");
	
	t1.PrintInfo();
	t2.PrintInfo();
	t3.PrintInfo();
	t4.PrintInfo();
	t5.PrintInfo();

	// 线性表测试开始
	cout<< "*************************** 线性表测试开始 ***************************" << endl;
	
	// 创建一个顺序线性表
	cout << "\n创建一个顺序线性表：" << endl;
	SEQ_LIST<TEACHER> seq_list(128);
	cout << "length = " << seq_list.GetLength() << "\tcapacity = " << seq_list.GetCapacity() << endl;
	
	// 插入元素
	cout << "\n插入元素：" << endl;
	seq_list.Insert(0, t1);
	cout << "length = " << seq_list.GetLength() << "\tcapacity = " << seq_list.GetCapacity() << endl;
	seq_list.Insert(0, t2);
	cout << "length = " << seq_list.GetLength() << "\tcapacity = " << seq_list.GetCapacity() << endl;
	seq_list.Insert(0, t3);
	cout << "length = " << seq_list.GetLength() << "\tcapacity = " << seq_list.GetCapacity() << endl;
	seq_list.Insert(0, t4);
	cout << "length = " << seq_list.GetLength() << "\tcapacity = " << seq_list.GetCapacity() << endl;
	seq_list.Insert(0, t5);
	cout << "length = " << seq_list.GetLength() << "\tcapacity = " << seq_list.GetCapacity() << endl;

	// 获取元素
	cout << "\n获取元素：" << endl;
	for(int i = 0; i < seq_list.GetLength(); ++i)
	{
		TEACHER tmp;
		seq_list.GetElem(i, tmp);
		tmp.PrintInfo();
	}

	// 清空元素
	// cout << "\n清空元素：" << endl;
	// seq_list.Clear();
	// cout << "length = " << seq_list.GetLength() << "\tcapacity = " << seq_list.GetCapacity() << endl;
	
	// 前驱和后继
	cout << "\n前驱和后继：" << endl;

	TEACHER tmp;

	seq_list.PriorELem(t1,tmp);
	cout << "The prior element of teacher t1 is :\t" ;
	tmp.PrintInfo();
	seq_list.PriorELem(t2,tmp);
	cout << "The prior element of teacher t2 is :\t" ;
	tmp.PrintInfo();
	seq_list.PriorELem(t3,tmp);
	cout << "The prior element of teacher t3 is :\t" ;
	tmp.PrintInfo();
	seq_list.PriorELem(t4,tmp);
	cout << "The prior element of teacher t4 is :\t" ;
	tmp.PrintInfo();
	
	cout << endl;

	seq_list.NextElem(t2, tmp);
	cout << "The next element of teacher t2 is :\t" ;
	tmp.PrintInfo();
	seq_list.NextElem(t3, tmp);
	cout << "The next element of teacher t3 is :\t" ;
	tmp.PrintInfo();
	seq_list.NextElem(t4, tmp);
	cout << "The next element of teacher t4 is :\t" ;
	tmp.PrintInfo();
	seq_list.NextElem(t5, tmp);
	cout << "The next element of teacher t5 is :\t" ;
	tmp.PrintInfo();

	// 定位元素
	cout << "\n定位元素：" << endl;

	cout << "t1 in position: " << seq_list.LocateElem(t1) << endl;
	cout << "t2 in position: " << seq_list.LocateElem(t2) << endl;
	cout << "t3 in position: " << seq_list.LocateElem(t3) << endl;
	cout << "t4 in position: " << seq_list.LocateElem(t4) << endl;
	cout << "t5 in position: " << seq_list.LocateElem(t5) << endl;

	// 遍历元素
	cout <<"\n遍历元素：" << endl;
	seq_list.Traverse(PrintTeacher);


	// 删除元素
	cout << "\n删除元素："<< endl;
	while (seq_list.GetLength() != 0)
	{
		TEACHER tmp;
		seq_list.Delete(0, tmp);
		cout << "length = " << seq_list.GetLength() << "\tcapacity = " << seq_list.GetCapacity() << "\t";
		tmp.PrintInfo();
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
