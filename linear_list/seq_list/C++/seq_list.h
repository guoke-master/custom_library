/***********************************************************************************************************************************************
 * File name:	seq_list.h
 * Author:	guoke
 * Date:	2021.10.27
 * Description:	C++线性表顺序实现的头文件，该文件声明了模板类SEQ_LIST，其实现包含在文件seq_list.cpp文件中。
 * History:	1. 2021.10.27 创建并完成初始版本
 **********************************************************************************************************************************************/

#ifndef _SEQ_LIST_H_
#define _SEQ_LIST_H_

template <typename T>
class SEQ_LIST{
private:
	int length;				// 线性表长度
	int capacity;			// 线性表容量
	T* elems;				// 存储数据元素的空间
public:
	/*
	 * Function:		SEQ_LIST()
	 * Description:		构造函数
	 * Time complexity:	O(1)
	 * Input:	
	 *		capacity:	int类型，指明顺序线性表的容量
	 * Output:
	 * Return:
	 */
	SEQ_LIST(int capacity);

	/*
	 * Function:		SEQ_LIST()
	 * Description:		拷贝构造函数
	 * Time complexity:	如果数据元素的类型T的等号操作的时间复杂度是O(m)，则该函数的时间复杂度为O(n*m)
	 * Input:
	 *		seq_list:	const SEQ_LIST&类型，深拷贝该线性表的内容给本线性表
	 * Output:
	 * Return:
	 */
	SEQ_LIST(const SEQ_LIST<T>& seq_list);

	/*
	 * Function:		~SEQ_LIST()
	 * Description:		析构函数
	 * Time complexity:	O(1)
	 * Input:
	 * Output:
	 * Return:
	 */
	~SEQ_LIST();

public:
	/*
	 * Function:		Clear()
	 * Description:		将顺序线性表置为空表
	 * Time complexity:	O(1)
	 * Input:	
	 * Output:	
	 * Return:			int类型，操作成功返回0，否则返回负数
	 */
	int Clear();


	/*
	 * Function:		IsEmpty()
	 * Description:		判断顺序线性表是否为空表
	 * Time complexity:	O(1)
	 * Input:	
	 * Output:	
	 * Return:			int类型，若顺序线性表为空表，则返回1，否则返回0，操作失败则返回负数
	 */
	int IsEmpty();


	/*
	 * Function:		GetLength()
	 * Description:		返回顺序线性表中元素个数
	 * Time complexity:	O(1)
	 * Input:	
	 * Output:	
	 * Return:			int类型，操作成功返回顺序线性表长度，否则返回负数
	 */
	int GetLength();


	/*
	 * Function:		GetCapacity()
	 * Description:		返回顺序线性表的容量
	 * Time complexity:	O(1)
	 * Input:	
	 * Output:	
	 * Return:			int类型，操作成功返回顺序线性表容量，否则返回负数
	 */
	int GetCapacity();


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
	int GetElem(int pos, T& out_elem); 


	/*
	 * Function:		LocateElem()
	 * Description:		返回顺序线性表中数据元素elem的下标
	 * Time complexity:	如果数据元素类型重载的==操作时间复杂度是O(m)，则本函数的时间复杂度是O(n*m)
	 * Input:	
	 *		elem:		const T&类型，获取该数据元素在顺序线性表中的位置
	 * Output:	
	 * Return:			int类型，操作成功返回数据元素elem的下标，否则返回负数
	 */
	int LocateElem(const T& elem);  


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
	int PriorELem(const T& current_elem, T& out_elem);


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
	int NextElem(const T& current_elem, T& out_elem);


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
	int Insert(int pos, const T& elem);


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
	int Delete(int pos, T& out_elem);


	/*
	 * Function:		Traverse()
	 * Description:		依次对顺序线性表的每个元素调用visit()，一旦visit()失败，则操作失败
	 * Time complexity:	如果visit()时间复杂度为O(m)，则本函数时间复杂度为O(n*m)
	 * Input:	
	 *		visit:		int(*)(SEQ_LIST_ELEM)类型，函数指针，以数据元素为参数，成功执行返回非负数，否则返回负数
	 * Output:	
	 * Return:			int类型，操作成功则返回0，否则返回负数
	 */
	int Traverse(int (*visit)(T&));
};
	

#endif
