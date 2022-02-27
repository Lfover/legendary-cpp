#pragma once

#include <iostream>
using namespace std;
//插入结点
bool Insert()
{
	if (roor == nullptr)
	{

	}
	//查找插入结点的位置
	Node* cur = root;
	Node* parent = nullptr;
	while (cur)
	{
		parent = cur;
		if (data < cur->data)
			cur = cur->left;
		else if (data > cur->data)
			cur = cur->right;
		else
			return false;
	}
	//位置已经找到了，charity新节点

}

//查找值为data的元素
Node* Find(const T& data)
{
	Node* cur = root;
	while (cur)
	{
		if (data == cur->data)
			return cur;
		else if (data < cur->data)
			cur = cur->left;
		else
			cur = cur->right;
	}
	return nullptr;
}
//删除值为data的元素
bool Erase(const T& data)
{
	if (nullptr == root)
	{
		return false;
	}
	Node* cur = root;
	//先查找到值为data的结点
	while (cur)
	{
		if (data == cur->data)
			break;
		else if (data < cur->data)
			cur = cur->left;
		else
			cur = cur->right;
	}
	//两种情况，可能找到了，可能没找到
	//1.没找到
	if (nullptr == cur)
		return false;
	//2.找到了，就是cur这个结点

}

//测试二叉搜索树
void TestBSTree()
{
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	BSTree<int> t;
	for (auto e : a)
		t.Insert(e);
	t.InOrder();
}