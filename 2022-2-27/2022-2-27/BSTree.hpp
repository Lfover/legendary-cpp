#pragma once

#include <iostream>
using namespace std;
//������
bool Insert()
{
	if (roor == nullptr)
	{

	}
	//���Ҳ������λ��
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
	//λ���Ѿ��ҵ��ˣ�charity�½ڵ�

}

//����ֵΪdata��Ԫ��
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
//ɾ��ֵΪdata��Ԫ��
bool Erase(const T& data)
{
	if (nullptr == root)
	{
		return false;
	}
	Node* cur = root;
	//�Ȳ��ҵ�ֵΪdata�Ľ��
	while (cur)
	{
		if (data == cur->data)
			break;
		else if (data < cur->data)
			cur = cur->left;
		else
			cur = cur->right;
	}
	//��������������ҵ��ˣ�����û�ҵ�
	//1.û�ҵ�
	if (nullptr == cur)
		return false;
	//2.�ҵ��ˣ�����cur������

}

//���Զ���������
void TestBSTree()
{
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	BSTree<int> t;
	for (auto e : a)
		t.Insert(e);
	t.InOrder();
}