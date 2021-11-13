/*****************************************************************************************************************************
 * File name:	link_list.h
 * Author:	guoke
 * Date:	2021.11.13
 * Description:	C++线性表链式存储（双向循环链表）的头文件，该文件包含了模板类LIST_NODE和LINK_LIST的声明，其实现包含在文件link_list.cpp中。
 * History:	1. 2021.11.13 创建并完成初始版本
 ****************************************************************************************************************************/

#ifndef _LINK_LIST_H_
#define _LINK_LIST_H_

/****************************************************************** LIST_NODE类型，双向循环链表中的结点 ****************************************************************/
template <typename T>
class LIST_NODE{
private:
	LIST_NODE*	next;								// 指向后继结点
	LIST_NODE*	prior;								// 指向前驱结点
	T			data;								// 数据域

public:
	/*
	 * Function:		LIST_NODE()
	 * Description:		LIST_NODE类的无参构造函数，数据域调用其无参构造函数，指针域都指向自己
	 * Time complexity:	与类T的无参构造函数时间复杂度相同
	 * Input:
	 * Output:
	 * Return:
	 */
	LIST_NODE();

	/*
	 * Function:		LIST_NODE()
	 * Description:		LIST_NODE类的有参构造函数，数据域由调用者指定，调用类T的拷贝构造函数，指针域都指向自己
	 * Time complexity:	与类T的拷贝构造函数复杂度相同
	 * Input:
	 *		my_data:	const T&类型，初始化结点的数据域的数据
	 * Output:
	 * Return:
	 */
	LIST_NODE(const T& my_data);

	/*
	 * Function:		LIST_NODE()
	 * Description:		LIST_NODE类的拷贝构造函数，只拷贝结点的数据域，指针域都指向自己
	 * Time complexity:	与类T的重载的赋值操作符时间复杂度相同
	 * Input:
	 *		list_node:	const LIST_NODE<T>&类型，要拷贝的结点
	 * Output:
	 * Return:
	 */
	LIST_NODE(const LIST_NODE& list_node);

public:
	/*
	 * Function:		SetNextNode()
	 * Description:		设置该结点的后继结点
	 * Time complexity:	O(1)
	 * Input:
	 *		node:		LIST_NODE<T>*类型，后继结点的地址
	 * Output:
	 * Return:			int类型，操作成功返回0，操作失败返回负数
	 */
	int SetNextNode(LIST_NODE* node);

	/*
	 * Function:		SetPriorNode()
	 * Description:		设置该结点的前驱结点
	 * Time complexity:	O(1)
	 * Input:
	 *		node:		LIST_NODE<T>*类型，前驱结点的地址
	 * Output:
	 * Return:			int类型，操作成功返回0，操作失败返回负数
	 */
	int SetPriorNode(LIST_NODE* node);

	/*
	 * Function:		SetData()
	 * Description:		设置该结点的数据域的值
	 * Time complexity:	与类T的重载的赋值操作符时间复杂度相同
	 * Input:
	 *		data:		const T&类型，要设置的数据域的值
	 * Output:
	 * Return:			int类型，操作成功返回0，操作失败返回负数
	 */
	int SetData(const T& data);

	/*
	 * Function:		GetNodeData()
	 * Description:		获取该结点的数据域的值
	 * Time complexity:	与类T的重载的赋值操作符时间复杂度相同
	 * Input:
	 * Output:
	 *		out_data:	T&类型，通过该引用将该结点的数据传给调用者
	 * Return:			int类型，操作成功返回0，操作失败返回负数
	 */
	int GetNodeData(T& out_data) const;

	/*
	 * Function:		GetNextNode()
	 * Description:		获取该结点的后继结点的地址
	 * Time complexity:	O(1)
	 * Input:
	 * Output:
	 * Return:			LIST_NODE<T>*类型，操作成功返回其后继结点的地址，操作失败返回NULL
	 */
	LIST_NODE* GetNextNode() const;

	/*
	 * Function:		GetPriorNode()
	 * Description:		获取该结点的前驱结点的地址
	 * Time complexity:	O(1)
	 * Input:
	 * Output:
	 * Return:			LIST_NODE<T>*类型，操作成功返回其前驱结点的地址，操作失败返回NULL
	 */
	LIST_NODE* GetPriorNode() const;
};



/****************************************************************** LINK_LIST类型，双向循环链表 ****************************************************************/
template <typename T>
class LINK_LIST{
private:
	LIST_NODE<T>	header;				// 头结点，数据域置0，前驱指针指向自己，后继指针指向链表第一个结点
	int				length;				// 链表长度
	LIST_NODE<T>*	slider;				// 游标，用来辅助定位

public:
	/*
	 * Function:		LINK_LIST()
	 * Description:		LINK_LIST类的无参构造函数，头结点调用LIST_NODE类的无参构造函数，length和slider置0
	 * Time complexity:	与类LIST_NODE的无参构造函数时间复杂度相同，LIST_NODE类无参构造函数同类T的无参构造函数时间复杂度相同
	 * Input:
	 * Output:
	 * Return:
	 */
	LINK_LIST();

	/*
	 * Function:		~LINK_LIST()
	 * Description:		LINK_LIST类的析构函数，调用Clear()清空链表结点
	 * Time complexity:	
	 * Input:
	 * Output:
	 * Return:
	 */
	~LINK_LIST();

public:
	/*
	 * Function:		Clear()
	 * Description:		调用DeleteSlider()逐个删除结点，将链表置为空表
	 * Time complexity:	假设类T的时间复杂度是O(m)，则该函数的时间复杂的为O(n*m)
	 * Input:
	 * Output:
	 * Return:			int类型，操作成功返回0，操作失败返回负数
	 */
	int Clear();

	/*
	 * Function:		GetLength()
	 * Description:		获取链表长度
	 * Time complexity:	O(1)
	 * Input:
	 * Output:
	 * Return:			int类型，操作成功返回链表长度，操作失败返回负数
	 */
	int GetLength() const;

	/*
	 * Function:		IsEmpty()
	 * Description:		判断链表是否为空表
	 * Time complexity:	O(1)
	 * Input:
	 * Output:
	 * Return:			bool类型，如果链表为空表返回true，如果链表不为空表则返回false
	 */
	bool IsEmpty() const;

	/*
	 * Function:		ResetSlider()
	 * Description:		重置链表的游标，如果链表中有结点，游标指向第一个结点；如果链表中没有结点，游标置NULL
	 * Time complexity:	O(1)
	 * Input:
	 * Output:
	 * Return:			int类型，操作成功返回0，操作失败返回负数
	 */
	int ResetSlider();

	/*
	 * Function:		GetSlider()
	 * Description:		获取链表游标指向的结点数据 
	 * Time complexity:	与类T的重载的赋值操作符的时间复杂度相同
	 * Input:
	 * Output:
	 *		out_data:	T&类型，通过该引用，将游标指向的结点的数据传给调用者
	 * Return:			int类型，操作成功返回0，操作失败返回负数
	 */
	int GetSlider(T& out_data) const;

	/*
	 * Function:		SliderForward()
	 * Description:		获取当前游标指向的结点的数据，游标指向其后继结点
	 * Time complexity:	与类T的重载的赋值操作符的时间复杂度相同
	 * Input:
	 * Output:
	 *		out_data:	T&类型，通过该引用，将游标指向的结点的数据传给调用者
	 * Return:			int类型，操作成功返回0，操作失败返回负数
	 */
	int SliderForward(T& out_data);

	/*
	 * Function:		SliderBackward()
	 * Description:		获取当前游标指向的结点的数据，游标指向其前驱结点
	 * Time complexity:	与类T的重载的赋值操作符的时间复杂度相同
	 * Input:
	 * Output:
	 *		out_data:	T&类型，通过该引用，将游标指向的结点的数据传给调用者
	 * Return:			int类型，操作成功返回0，操作失败返回负数
	 */
	int SliderBackward(T& out_data);

	/*
	 * Function:		InsertBeforeSlider()
	 * Description:		在游标指向的结点前面插入一个结点，并将游标指向插入的结点，在第一个结点之前插入的话，头结点会指向插入的结点
	 * Time complexity:	与类T的重载的赋值操作符的时间复杂度相同
	 * Input:
	 *		data:		const T&类型，插入的数据
	 * Output:
	 * Return:			int类型，操作成功返回0，操作失败返回负数
	 */
	int InsertBeforeSlider(const T& data);

	/*
	 * Function:		InsertAfterSlider()
	 * Description:		在游标指向的结点后面插入一个结点，并将游标指向插入的结点
	 * Time complexity:	与类T的重载的赋值操作符的时间复杂度相同
	 * Input:
	 *		data:		const T&类型，插入的数据
	 * Output:
	 * Return:			int类型，操作成功返回0，操作失败返回负数
	 */
	int InsertAfterSlider(const T& data);

	/*
	 * Function:			DeleteSlider()
	 * Description:			删除游标指向的结点，获取删除结点的数据，游标指向删除结点的后继结点。如果删除的是第一个结点，被删除结点的后继结点将会变成第一个结点。如果删除之后链表变为空表，游标置NULL
	 * Time complexity:		与类T重载的赋值操作符时间复杂度相同
	 * Input:
	 * Output:
	 *		deleted_data:	T&类型，通过该引用将删除的结点数据传出给调用者
	 * Return:				int类型，操作成功返回0，操作失败返回负数
	 */
	int DeleteSlider(T& deleted_data);

	/*
	 * Function:		SetSlider()
	 * Description:		如果链表中存在某个结点包含数据data，将游标指向第一个包含该数据的结点
	 * Time complexity:	假设类T重载的==操作符时间复杂度为O(m)，则该函数时间复杂度为O(n*m)
	 * Input:
	 *		data:		const T&类型，在链表中匹配该数据
	 * Output:
	 * Return:			int类型，操作成功返回0，操作失败返回负数
	 */
	int SetSlider(const T& data);

	/*
	 * Function:		Traverse()
	 * Description:		遍历链表，每个结点的数据data作为参数，调用函数visit()
	 * Time complexity:	假设类T重载的赋值操作符时间复杂度为O(m)，visit()的时间复杂度为O(t)，则本函数时间复杂度为O(n*m + n*t)
	 * Input:
	 *		visit:		int (*)(T& data)类型，函数指针，以类T的引用为参数
	 * Output:
	 * Return:			int类型，操作成功返回0，操作失败返回负数
	 */
	int Traverse(int (*visit)(T& data));
};
#endif
