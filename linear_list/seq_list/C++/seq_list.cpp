/*****************************************************************************************************************************
 * File name:	seq_list.cpp
 * Author:	guoke
 * Date:	2021.10.27
 * Description:	C++线性表顺序实现的源文件，该文件包含了seq_list.h中模板类SEQ_LIST的实现。
 * History:	1. 2021.10.27 创建并完成初始版本
 ****************************************************************************************************************************/

#include <iostream>
#include <cstring>
#include "seq_list.h"

using namespace std;

/*
 * Function:		SEQ_LIST()
 * Description:		构造函数
 * Time complexity:	O(1)
 * Input:	
 *		capacity:	int类型，指明顺序线性表的容量
 * Output:
 * Return:
 */
template <typename T>
SEQ_LIST<T>::SEQ_LIST(int capacity)
{
	// 输入检查
	if (capacity <= 0)
	{
		cout << "func SEQ_LIST<T>::SEQ_LIST() err: capacity <= 0" << endl;
		return;
	}

	// 初始化参数
	this->capacity = capacity;
	this->length = 0;

	// 申请节点空间
	this->elems = new T[this->capacity];
	if (this->elems == NULL)
	{
		cout << "func SEQ_LIST<T>::SEQ_LIST() err: capacity <= 0" << endl;
		return;
	}
	memset(this->elems, 0, sizeof(T)*this->capacity);
}



/*
 * Function:		SEQ_LIST()
 * Description:		拷贝构造函数
 * Time complexity:	如果数据元素的类型T的等号操作的时间复杂度是O(m)，则该函数的时间复杂度为O(n*m)
 * Input:
 *		seq_list:	const SEQ_LIST&类型，深拷贝该线性表的内容给本线性表
 * Output:
 * Return:
 */
template <typename T>
SEQ_LIST<T>::SEQ_LIST(const SEQ_LIST<T>& seq_list)
{
	// 复制数据
	this->capacity = seq_list.capacity;
	this->length = seq_list.length;
	
	// 申请空间
	this->elems = new T[this->capacity];
	if (this->elems == NULL)
	{
		cout << "func SEQ_LIST<T>::SEQ_LIST() err: this->elems == NULL" << endl;
		return;
	}

	// 复制数据
	for (int i = 0; i < seq_list.length; ++i)
	{
		this->elems[i] = seq_list.elems[i];		// T类型的等号操作
	}
}



/*
 * Function:		~SEQ_LIST()
 * Description:		析构函数
 * Time complexity:	O(1)
 * Input:
 * Output:
 * Return:
 */
template <typename T>
SEQ_LIST<T>::~SEQ_LIST()
{
	// 释放空间
	if (this->elems != NULL)
	{
		delete[] this->elems;
		this->elems = NULL;
	}

	// 空间归零
	this->length = 0;
	this->capacity = 0;
}



/*
 * Function:		Clear()
 * Description:		将顺序线性表置为空表
 * Time complexity:	O(1)
 * Input:	
 * Output:	
 * Return:			int类型，操作成功返回0，否则返回负数
 */
template <typename T>
int SEQ_LIST<T>::Clear()
{
	// 线性表长度清0
	this->length = 0;

	// 数据元素空间置零
	memset(this->elems, 0, sizeof(T) * this->capacity);

	return 0;
}



/*
 * Function:		IsEmpty()
 * Description:		判断顺序线性表是否为空表
 * Time complexity:	O(1)
 * Input:	
 * Output:	
 * Return:			int类型，若顺序线性表为空表，则返回1，否则返回0，操作失败则返回负数
 */
template <typename T>
int SEQ_LIST<T>::IsEmpty()
{
	return (this->length > 0) ? 0 : 1;
}



/*
 * Function:		GetLength()
 * Description:		返回顺序线性表中元素个数
 * Time complexity:	O(1)
 * Input:	
 * Output:	
 * Return:			int类型，操作成功返回顺序线性表长度，否则返回负数
 */
template <typename T>
int SEQ_LIST<T>::GetLength()
{
	return this->length;
}



/*
 * Function:		GetCapacity()
 * Description:		返回顺序线性表的容量
 * Time complexity:	O(1)
 * Input:	
 * Output:	
 * Return:			int类型，操作成功返回顺序线性表容量，否则返回负数
 */
template <typename T>
int SEQ_LIST<T>::GetCapacity()
{
	return this->capacity;
}



/*
 * Function:		GetElem()
 * Description:		获取顺序线性表第pos个数据元素的值
 * Time complexity:	如果数据元素类型的等号操作符时间复杂的是O(m)，则本函数的时间复杂度是O(m)
 * Input:	
 *		pos:		int类型，需要获取的数据元素的下标
 * Output:	
 *		out_elem:	T&类型，将pos下标位置的数据元素赋值给out_elem
 * Return:			int类型，操作成功返回pos，操作失败返回负数
 */
template <typename T>
int SEQ_LIST<T>::GetElem(int pos, T& out_elem)
{
	// 参数检查
	if (pos < 0 || pos >= this->length)
	{
		cout << "func SEQ_LIST<T>::GetElem() err: pos < 0 || pos >= this->length" << endl;
		return -1;
	}

	// 通过引用将数据元素传递出去
	out_elem = this->elems[pos];		// 调用数据元素类的重载的等号操作符
	return 0;
}



/*
 * Function:		LocateElem()
 * Description:		返回顺序线性表中数据元素elem的下标
 * Time complexity:	如果数据元素类型重载的==操作时间复杂度是O(m)，则本函数的时间复杂度是O(n*m)
 * Input:	
 *		elem:		const T&类型，获取该数据元素在顺序线性表中的位置
 * Output:	
 * Return:			int类型，操作成功返回数据元素elem的下标，否则返回负数
 */
template <typename T>
int SEQ_LIST<T>::LocateElem(const T& elem)
{
	int pos = 0;

	// 遍历所有数据元素
	for(pos = 0; pos < this->length; ++pos)
	{
		// 调用数据元素类型重载的==操作
		if (elem == this->elems[pos])
		{
			break;
		}
	}

	// 判断elem是否在线性表中
	if (pos >= this->length)
	{
		return -1;
	}

	return pos;
}



/*
 * Function:		PriorElem()
 * Description:		如果current_elem是顺序线性表的元素，且不是第一个，则获取它的前驱元素
 * Time complexity:	如果数据元素类型重载的==操作时间复杂度是O(m)，数据元素类型重载的赋值操作时间复杂度是O(t)，则本函数时间复杂度是MAX(O(n*m), O(t))
 * Input:	
 *		current_elem:		const T&类型，以该元素作为参考，获取其前驱元素
 * Output:	
 *		out_elem:			T&类型，用来接收current_elem的前驱元素
 * Return:			int类型，操作成功返回0，操作失败返回负数
 */
template <typename T>
int SEQ_LIST<T>::PriorELem(const T& current_elem, T& out_elem)
{
	// 确定current_elem的下标
	int pos = 0;
	for(pos = 0; pos < this->length; ++pos)
	{
		if (current_elem == this->elems[pos])
		{
			break;
		}
	}
	
	// 判断位置的合法性
	if (pos < 0)						// 线性表没有元素current_elem
	{
		cout << " func SEQ_LIST<T>::PriorElem() err: pos < 0" << endl;
		return -1;
	}
	else if (pos == 0)					// current_elem是线性表中第一个元素
	{
		cout << "func SEQ_LIST<T>::PriorElem() err: pos == 0" << endl;
		return -2;
	}
	else								// 位置合法
	{
		// 数据元素类型重载的赋值操作
		out_elem = this->elems[pos - 1];
		return 0;
	}
}



/*
 * Function:		NextElem()
 * Description:		如果current_elem是顺序线性表的元素，且不是最后一个，则获取它的后继元素
 * Time complexity:	如果数据元素类型重载的==操作时间复杂度是O(m)，数据元素类型重载的赋值操作时间复杂度是O(t)，则本函数时间复杂度是MAX(O(n*m), O(t))
 * Input:	
 *		current_elem:		const T&类型，以该元素作为参考，获取其后继元素
 * Output:	
 *		out_elem:			T&类型，用来接收current_elem的后继元素
 * Return:			int类型，操作成功返回0，操作失败返回负数
 */
template <typename T>
int SEQ_LIST<T>::NextElem(const T& current_elem, T& out_elem)
{
	// 确定current_elem的下标
	int pos = 0;
	for(pos = 0; pos < this->length; ++pos)
	{
		if (current_elem == this->elems[pos])
		{
			break;
		}
	}
	
	// 判断位置的合法性
	if (pos < 0)								// 线性表没有元素current_elem
	{
		cout << " func SEQ_LIST<T>::PriorElem() err: pos < 0" << endl;
		return -1;
	}
	else if (pos == this->length - 1)			// current_elem是线性表中最后一个元素
	{
		cout << "func SEQ_LIST<T>::PriorElem() err: pos == this->length - 1" << endl;
		return -2;
	}
	else										// 位置合法
	{
		// 数据元素类型重载的赋值操作
		out_elem = this->elems[pos + 1];		
		return 0;
	}
}



/*
 * Function:		Insert()
 * Description:		在顺序线性表中第pos个位置之前插入新的数据元素elem，顺序线性表长度加1
 * Time complexity:	如果数据元素类型重载的赋值操作时间复杂度为O(m)，则本函数时间复杂度为O(n*m)
 * Input:	
 *		pos:		int类型，将数据元素插入下标为pos的位置
 *		elem:		const T&类型，插入顺序线性表的元素
 * Output:	
 * Return:			int类型，插入成功则返回插入元素下标，插入失败则返回负数
 */
template <typename T>
int SEQ_LIST<T>::Insert(int pos, const T& elem)
{
	// 线性表容量检查
	if (this->length >= this->capacity)
	{
		cout << "func SEQ_LIST<T>::Insert() err: this->length >= this->capacity" << endl;
		return -1;
	}

	// 插入位置合法性检查
	if (pos < 0 || pos > length)
	{
		cout << "func SEQ_LIST<T>::Insert() err: pos < 0 || pos > length" << endl;
		return -2;
	}

	// pos以及pos之后的元素向后移动一位
	for(int i = 0; i < this->length - pos; ++i)
	{
		this->elems[this->length - i] = this->elems[this->length - i - 1];		// 数据元素类型重载的赋值操作
	}

	// 插入
	this->elems[pos] = elem;													// 数据元素类型重载的赋值操作

	// 线性表长度加1
	this->length++;

	return pos;
}


/*
 * Function:		Delete()
 * Description:		删除顺序线性表中下标为pos的元素，并获取其值，顺序线性表长度-1
 * Time complexity:	如果数据元素类型重载的赋值操作时间复杂度为O(m)，则本函数时间复杂度为O(n*m)
 * Input:	
 *		pos:		int类型，将数据元素插入下标为pos的位置
 * Output:	
 *		out_elem:	T&类型，用来接收被删除的数据元素
 * Return:			int类型，删除成功则返回删除元素下标，插入失败则返回负数
 */
template <typename T>
int SEQ_LIST<T>::Delete(int pos, T& out_elem)
{
	// 线性表容量检查
	if (this->length <= 0)
	{
		cout << "func SEQ_LIST<T>::Delete() err: this->length <= 0" << endl;
		return -1;
	}

	// 删除位置合法性检查
	if (pos < 0 || pos >= this->length)
	{
		cout << "func SEQ_LIST<T>::Delete() err: pos < 0 || pos >= this->length" << endl;
		return -2;
	}

	// 将删除数据元素通过引用传出去
	out_elem = this->elems[pos];								// 数据元素类型重载的赋值操作

	// 将删除的元素之后的所有元素前移一位
	for(int i = 0; i < this->length - pos - 1; ++i)
	{
		this->elems[pos + i] = this->elems[pos + i + 1];		// 数据元素类型重载的赋值操作
	}

	// 线性表长度减1
	this->length--;

	return pos;
}


/*
 * Function:		Traverse()
 * Description:		依次对顺序线性表的每个元素调用visit()，一旦visit()失败，则操作失败
 * Time complexity:	如果visit()时间复杂度为O(m)，则本函数时间复杂度为O(n*m)
 * Input:	
 *		visit:		int(*)(SEQ_LIST_ELEM)类型，函数指针，以数据元素为参数，成功执行返回非负数，否则返回负数
 * Output:	
 * Return:			int类型，操作成功则返回0，否则返回负数
 */
template <typename T>
int SEQ_LIST<T>::Traverse(int (*visit)(T&))
{
	// 参数检查
	if (visit == NULL)
	{
		cout << "SEQ_LIST<T>::Traverse() err: visit == NULL" << endl;
		return -1;
	}

	// 遍历所有数据元素并调用函数visit()
	for(int i = 0; i < this->length; ++i)
	{
		int func_status = visit(this->elems[i]);
		if (func_status < 0)
		{
			cout << "SEQ_LIST<T>::Traverse() err: func_status < 0" << endl;
			return -1;
		}
	}
	return 0;
}

