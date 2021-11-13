/*****************************************************************************************************************************
 * File name:	link_list.cpp
 * Author:	guoke
 * Date:	2021.11.13
 * Description:	C++线性表链式存储（双向循环链表）的源文件，该文件包含了link_list.h中模板类LIST_NODE和LINK_LIST的实现。
 * History:	1. 2021.11.13 创建并完成初始版本
 ****************************************************************************************************************************/

#include <iostream>
#include <cstring>
#include "link_list.h"

using namespace std;

/****************************************************************** LIST_NODE类型API ****************************************************************/

/*
 * Function:		LIST_NODE()
 * Description:		LIST_NODE类的无参构造函数，数据域调用其无参构造函数，指针域都指向自己
 * Time complexity:	与类T的无参构造函数时间复杂度相同
 * Input:
 * Output:
 * Return:
 */
template <typename T>
LIST_NODE<T>::LIST_NODE()
{
	this->next = this;							// 指向自己
	this->prior = this;							// 指向自己
}



/*
 * Function:		LIST_NODE()
 * Description:		LIST_NODE类的有参构造函数，数据域由调用者指定，调用类T的拷贝构造函数，指针域都指向自己
 * Time complexity:	与类T的拷贝构造函数复杂度相同
 * Input:
 *		my_data:	const T&类型，初始化结点的数据域的数据
 * Output:
 * Return:
 */
template <typename T>
LIST_NODE<T>::LIST_NODE(const T& my_data):data(my_data)		// 调用类T拷贝构造函数
{
	this->next = this;
	this->prior = this;
}



/*
 * Function:		LIST_NODE()
 * Description:		LIST_NODE类的拷贝构造函数，只拷贝结点的数据域，指针域都指向自己
 * Time complexity:	与类T的重载的赋值操作符时间复杂度相同
 * Input:
 *		list_node:	const LIST_NODE<T>&类型，要拷贝的结点
 * Output:
 * Return:
 */
template <typename T>
LIST_NODE<T>::LIST_NODE(const LIST_NODE<T>& list_node)
{
	// 拷贝数据，但是不拷贝指针
	this->data = list_node.data;		// 调用类T的重载赋值操作符
	this->next = this;
	this->prior = this;
}



/*
 * Function:		SetNextNode()
 * Description:		设置该结点的后继结点
 * Time complexity:	O(1)
 * Input:
 *		node:		LIST_NODE<T>*类型，后继结点的地址
 * Output:
 * Return:			int类型，操作成功返回0，操作失败返回负数
 */
template <typename T>
int LIST_NODE<T>::SetNextNode(LIST_NODE<T>* node)
{
	// 设置后继结点
	this->next = node;
	return 0;
}



/*
 * Function:		SetPriorNode()
 * Description:		设置该结点的前驱结点
 * Time complexity:	O(1)
 * Input:
 *		node:		LIST_NODE<T>*类型，前驱结点的地址
 * Output:
 * Return:			int类型，操作成功返回0，操作失败返回负数
 */
template <typename T>
int LIST_NODE<T>::SetPriorNode(LIST_NODE<T>* node)
{
	// 设置前驱结点
	this->prior = node;
	return 0;
}



/*
 * Function:		SetData()
 * Description:		设置该结点的数据域的值
 * Time complexity:	与类T的重载的赋值操作符时间复杂度相同
 * Input:
 *		data:		const T&类型，要设置的数据域的值
 * Output:
 * Return:			int类型，操作成功返回0，操作失败返回负数
 */
template <typename T>
int LIST_NODE<T>::SetData(const T& data)
{
	this->data = data;			// 调用类T重载的赋值操作
	return 0;
}



/*
 * Function:		GetNodeData()
 * Description:		获取该结点的数据域的值
 * Time complexity:	与类T的重载的赋值操作符时间复杂度相同
 * Input:
 * Output:
 *		out_data:	T&类型，通过该引用将该结点的数据传给调用者
 * Return:			int类型，操作成功返回0，操作失败返回负数
 */
template <typename T>
int LIST_NODE<T>::GetNodeData(T& out_data) const
{
	out_data = this->data;		// 调用类T重载的赋值操作
	return 0;
}



/*
 * Function:		GetNextNode()
 * Description:		获取该结点的后继结点的地址
 * Time complexity:	O(1)
 * Input:
 * Output:
 * Return:			LIST_NODE<T>*类型，操作成功返回其后继结点的地址，操作失败返回NULL
 */
template <typename T>
LIST_NODE<T>* LIST_NODE<T>::GetNextNode() const
{
	return this->next;
}



/*
 * Function:		GetPriorNode()
 * Description:		获取该结点的前驱结点的地址
 * Time complexity:	O(1)
 * Input:
 * Output:
 * Return:			LIST_NODE<T>*类型，操作成功返回其前驱结点的地址，操作失败返回NULL
 */
template <typename T>
LIST_NODE<T>* LIST_NODE<T>::GetPriorNode() const
{
	return this->prior;
}


/****************************************************************** LINK_LIST类型API ****************************************************************/

/*
 * Function:		LINK_LIST()
 * Description:		LINK_LIST类的无参构造函数，头结点调用LIST_NODE类的无参构造函数，length和slider置0
 * Time complexity:	与类LIST_NODE的无参构造函数时间复杂度相同，LIST_NODE类无参构造函数同类T的无参构造函数时间复杂度相同
 * Input:
 * Output:
 * Return:
 */
template <typename T>
LINK_LIST<T>::LINK_LIST():header(), length(0), slider(NULL)
{
	this->header.SetNextNode(NULL);
}



/*
 * Function:		~LINK_LIST()
 * Description:		LINK_LIST类的析构函数，调用Clear()清空链表结点
 * Time complexity:	
 * Input:
 * Output:
 * Return:
 */
template <typename T>
LINK_LIST<T>::~LINK_LIST()
{
	// 将链表置为空表
	this->Clear();
}



/*
 * Function:		Clear()
 * Description:		调用DeleteSlider()逐个删除结点，将链表置为空表
 * Time complexity:	假设类T的时间复杂度是O(m)，则该函数的时间复杂的为O(n*m)
 * Input:
 * Output:
 * Return:			int类型，操作成功返回0，操作失败返回负数
 */
template <typename T>
int LINK_LIST<T>::Clear()
{
	// 重置游标
	this->ResetSlider();

	// 删除结点
	while(this->length != 0)
	{
		T deleted_data;
		this->DeleteSlider(deleted_data);	// 与类T重载的赋值操作符时间复杂度相同
	}
	return 0;
}



/*
 * Function:		GetLength()
 * Description:		获取链表长度
 * Time complexity:	O(1)
 * Input:
 * Output:
 * Return:			int类型，操作成功返回链表长度，操作失败返回负数
 */
template <typename T>
int LINK_LIST<T>::GetLength() const
{
	return this->length;
}



/*
 * Function:		IsEmpty()
 * Description:		判断链表是否为空表
 * Time complexity:	O(1)
 * Input:
 * Output:
 * Return:			bool类型，如果链表为空表返回true，如果链表不为空表则返回false
 */
template <typename T>
bool LINK_LIST<T>::IsEmpty() const
{
	return (this->length == 0) ? true : false;
}



/*
 * Function:		ResetSlider()
 * Description:		重置链表的游标，如果链表中有结点，游标指向第一个结点；如果链表中没有结点，游标置NULL
 * Time complexity:	O(1)
 * Input:
 * Output:
 * Return:			int类型，操作成功返回0，操作失败返回负数
 */
template <typename T>
int LINK_LIST<T>::ResetSlider()
{
	// 如果链表为空表，游标置NULL
	if (this->length == 0)
	{
		this->slider = NULL;
	}
	// 如果链表不为空，游标指向第一个结点
	else
	{
		this->slider = this->header.GetNextNode();
	}
	return 0;
}



/*
 * Function:		GetSlider()
 * Description:		获取链表游标指向的结点数据 
 * Time complexity:	与类T的重载的赋值操作符的时间复杂度相同
 * Input:
 * Output:
 *		out_data:	T&类型，通过该引用，将游标指向的结点的数据传给调用者
 * Return:			int类型，操作成功返回0，操作失败返回负数
 */
template <typename T>
int LINK_LIST<T>::GetSlider(T& out_data) const
{
	// 如果链表为空表时，报错
	if (this->length == 0)
	{
		cout << "func LINK_LIST<T>::GetSlider() err: this->length == 0" << endl;
		return -1;
	}
	// 如果链表不为空表时，返回游标指向结点的数据
	else
	{
		this->slider->GetNodeData(out_data);		// 与类T的重载的赋值操作符的时间复杂度相同
	}

	return 0;
}



/*
 * Function:		SliderForward()
 * Description:		获取当前游标指向的结点的数据，游标指向其后继结点
 * Time complexity:	与类T的重载的赋值操作符的时间复杂度相同
 * Input:
 * Output:
 *		out_data:	T&类型，通过该引用，将游标指向的结点的数据传给调用者
 * Return:			int类型，操作成功返回0，操作失败返回负数
 */
template <typename T>
int LINK_LIST<T>::SliderForward(T& out_data)
{
	// 如果链表为空表，报错
	if (this->length == 0)
	{
		cout << "func LINK_LIST<T>::SliderForward() err: this->length == 0" << endl;
		return -1;
	}
	// 如果链表不为空表，缓存当前游标指向结点的数据，游标指向其后继结点
	else
	{
		this->slider->GetNodeData(out_data);
		this->slider = this->slider->GetNextNode();
	}

	return 0;
}



/*
 * Function:		SliderBackward()
 * Description:		获取当前游标指向的结点的数据，游标指向其前驱结点
 * Time complexity:	与类T的重载的赋值操作符的时间复杂度相同
 * Input:
 * Output:
 *		out_data:	T&类型，通过该引用，将游标指向的结点的数据传给调用者
 * Return:			int类型，操作成功返回0，操作失败返回负数
 */
template <typename T>
int LINK_LIST<T>::SliderBackward(T& out_data)
{
	// 如果链表为空表，报错
	if (this->length == 0)
	{
		cout << "func LINK_LIST<T>::SliderBackward() err: this->length == 0" << endl;
		return -1;
	}
	// 如果链表不为空表，缓存当前游标指向结点的数据，游标指向其前驱结点
	else
	{
		this->slider->GetNodeData(out_data);
		this->slider = this->slider->GetPriorNode();
	}

	return 0;
}



/*
 * Function:		InsertBeforeSlider()
 * Description:		在游标指向的结点前面插入一个结点，并将游标指向插入的结点，在第一个结点之前插入的话，头结点会指向插入的结点
 * Time complexity:	与类T的重载的赋值操作符的时间复杂度相同
 * Input:
 *		data:		const T&类型，插入的数据
 * Output:
 * Return:			int类型，操作成功返回0，操作失败返回负数
 */
template <typename T>
int LINK_LIST<T>::InsertBeforeSlider(const T& data)
{
	// 申请结点空间并调用构造函数初始化结点空间
	LIST_NODE<T>* list_node = new LIST_NODE<T>(data);				// 类LIST_NODE的拷贝构造函数，与类T重载的赋值操作符时间复杂度相同
	if (list_node == NULL)
	{
		cout << "func LINK_LIST<T>::InsertBeforeSlider() err: list_node == NULL" << endl;
		return -1;
	}

	// 如果链表为空表，slider初始值为NULL
	if ( this->length == 0)
	{
		this->header.SetNextNode(list_node);
		list_node->SetNextNode(list_node);
		list_node->SetPriorNode(list_node);
	}
	// 如果链表不为空，slider初始指向某个结点
	else
	{
		LIST_NODE<T>* slider_prior = this->slider->GetPriorNode();	// 临时变量，指向初始slider指向结点的前驱结点
		
		// 设置结点的next指针
		list_node->SetNextNode(this->slider);
		slider_prior->SetNextNode(list_node);

		// 设置结点的prior指针
		this->slider->SetPriorNode(list_node);
		list_node->SetPriorNode(slider_prior);
	}

	// 插入完成之后slider指向插入结点
	this->slider = list_node;
	
	// 如果插入之前slider指向第一个结点，那么插入之后，插入的结点变成头结点
	if (this->header.GetNextNode() == this->slider->GetNextNode())
	{
		this->header.SetNextNode(this->slider);
	}

	// 链表长度加1
	this->length ++;
	
	return 0;
}



/*
 * Function:		InsertAfterSlider()
 * Description:		在游标指向的结点后面插入一个结点，并将游标指向插入的结点
 * Time complexity:	与类T的重载的赋值操作符的时间复杂度相同
 * Input:
 *		data:		const T&类型，插入的数据
 * Output:
 * Return:			int类型，操作成功返回0，操作失败返回负数
 */
template <typename T>
int LINK_LIST<T>::InsertAfterSlider(const T& data)
{
	// 申请结点空间并调用构造函数初始化结点空间
	LIST_NODE<T>* list_node = new LIST_NODE<T>(data);				// 临时变量，指向初始slider指向结点的前驱结点
	if (list_node == NULL)
	{
		cout << "func LINK_LIST<T>::InsertAfterSlider() err: list_node == NULL" << endl;
		return -1;
	}

	// 如果链表为空表，slider初始值为NULL
	if ( this->length == 0)
	{
		this->header.SetNextNode(list_node);
		list_node->SetNextNode(list_node);
		list_node->SetPriorNode(list_node);
	}
	// 如果链表不为空，slider初始指向某个结点
	else
	{
		LIST_NODE<T>* slider_next = this->slider->GetNextNode();	// 临时变量，指向初始slider指向结点的后继结点
		
		// 设置结点的next指针
		list_node->SetNextNode(slider_next);
		this->slider->SetNextNode(list_node);
		
		// 设置prior指针
		slider_next->SetPriorNode(list_node);
		list_node->SetPriorNode(this->slider);
	}

	// 插入完成之后slider指向插入结点
	this->slider = list_node;
	
	// 链表长度加1
	this->length ++;

	return 0;
}



/*
 * Function:			DeleteSlider()
 * Description:			删除游标指向的结点，获取删除结点的数据，游标指向删除结点的后继结点。如果删除的是第一个结点，被删除结点的后继结点将会变成第一个结点。如果删除之后链表变为空表，游标置NULL
 * Time complexity:		与类T重载的赋值操作符时间复杂度相同
 * Input:
 * Output:
 *		deleted_data:	T&类型，通过该引用将删除的结点数据传出给调用者
 * Return:				int类型，操作成功返回0，操作失败返回负数
 */
template <typename T>
int LINK_LIST<T>::DeleteSlider(T& deleted_data)
{
	// 如果链表为空表，报错
	if (this->length == 0)
	{
		cout << "func LINK_LIST<T>::DeleteSlider() err: this->length == 0" << endl;
		return -1;
	}

	// 缓存结点数据，通过引用传出
	// 暂存结点地址，并通过引用传出结点数据
	LIST_NODE<T>* deleted_node = this->slider;
	deleted_node->GetNodeData(deleted_data);							// 与类T重载的赋值操作符时间复杂度相同
	
	// 如果删除结点之后链表变为空表，则删除之后游标置NULL
	if (this->length == 1)
	{
		this->slider == NULL;
		this->header.SetNextNode(NULL);									// 删除结点
	}
	// 如果删除结点之后还有其他结点, 游标指向其后继结点
	else if (this->length > 1)
	{
		// 删除结点并移动游标
		LIST_NODE<T>* slider_prior = this->slider->GetPriorNode();		// 删除之前，游标的前驱结点的地址
		this->slider = this->slider->GetNextNode();						// 移动游标
		slider_prior->SetNextNode(this->slider);						// 删除结点
		this->slider->SetPriorNode(slider_prior);

		// 如果删除的结点是链表的第一个结点，则将头结点指向删除之前的第二个结点（即删除之后游标指向的结点）
		if (this->header.GetNextNode() == deleted_node)
		{
			this->header.SetNextNode(this->slider);
		}
	}

	// 释放删除结点空间
	delete deleted_node;

	// 链表长度减1
	this->length --;

	return 0;
}



/*
 * Function:		SetSlider()
 * Description:		如果链表中存在某个结点包含数据data，将游标指向第一个包含该数据的结点
 * Time complexity:	假设类T重载的==操作符时间复杂度为O(m)，则该函数时间复杂度为O(n*m)
 * Input:
 *		data:		const T&类型，在链表中匹配该数据
 * Output:
 * Return:			int类型，操作成功返回0，操作失败返回负数
 */
template <typename T>
int LINK_LIST<T>::SetSlider(const T& data)
{
	// 如果链表为空表，报错
	if (this->length == 0)
	{
		cout << "func LINK_LIST<T>::SetSlider() err: this->length == 0" << endl;
		return -1;
	}

	// 重置游标
	this->ResetSlider();

	// 遍历链表，查找第一个包含data的结点
	int i = 0;
	for (i = 0; i < this->length; ++i)
	{
		T current_node_data;								// 定义一个临时变量暂存游标指向结点的数据。调用类型T的构造函数。
		this->slider->GetNodeData(current_node_data);		// 获取当前结点的数据

		// 判断当前结点的数据是否等于data，如果是，跳出循环，游标指向第一个包含数据data的结点。调用类型T的重载==操作
		if (data == current_node_data)						// 类T重载的==操作符
		{
			break;
		}
		
		// 游标指向其后继结点
		this->slider = this->slider->GetNextNode();
	}

	// 如果没有找到，报错
	if (i >= this->length)
	{
		cout << " func LINK_LIST<T>::SetSlider() err: i >= this->length" << endl;
		return -2;
	}

	return 0;
}



/*
 * Function:		Traverse()
 * Description:		遍历链表，每个结点的数据data作为参数，调用函数visit()
 * Time complexity:	假设类T重载的赋值操作符时间复杂度为O(m)，visit()的时间复杂度为O(t)，则本函数时间复杂度为O(n*m + n*t)
 * Input:
 *		visit:		int (*)(T& data)类型，函数指针，以类T的引用为参数
 * Output:
 * Return:			int类型，操作成功返回0，操作失败返回负数
 */
template <typename T>
int LINK_LIST<T>::Traverse(int (*visit)(T& data))
{
	// 如果链表为空表，直接退出
	if (this->length == 0)
	{
		return 0;
	}

	// 链表不为空的情况下
	// 重置游标
	this->ResetSlider();

	// 遍历链表
	for (int i = 0; i < this->length; ++i)
	{
		T current_node_data;								// 用来暂存当前结点的数据
		this->slider->GetNodeData(current_node_data);

		// 结点数据作为参数，调用visit()，并用func_status监控visit()运行情况
		int func_status = visit(current_node_data);
		if (func_status != 0)
		{
			cout << "func LINK_LIST<T>::Traverse() err: func_status != 0" << endl;
			return -1;
		}

		// 游标指向其后继结点
		this->slider = this->slider->GetNextNode();
	}
	return 0;
}
