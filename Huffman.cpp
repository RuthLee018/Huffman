#include"Huffman.h"
#include<string>
#include<iostream>
using namespace std;

Huffman::Huffman()
{
	// 开辟空间
	HT = new HTNode[2 * N - 1];
	HC = new string[N];

}

Huffman::~Huffman()
{
	delete[]HT;
	delete[]HC;
}

/*
void Huffman::Select(int i, int& s)
{
	int min = MAX;

	for (int j = 0; j < i; j++)
		if (HT[j].weight < min && HT[j].parent == -1)
		{
			min = HT[j].weight;
			s = j;
		}
}
*/

void Huffman::Select(int i, int& s1, int& s2) 
{
	int min1 = MAX, min2 = MAX;
	s1 = s2 = -1;
	for (int j = 0; j < i; j++) 
	{
		if (HT[j].parent == -1)
		{
			if (HT[j].weight < min1) 
			{
				min2 = min1; 
				s2 = s1;
				min1 = HT[j].weight; 
				s1 = j;
			}
			else if (HT[j].weight < min2) 
			{
				min2 = HT[j].weight; 
				s2 = j;
			}
		}
	}
}

void Huffman::MakeHuffmanTree(int* WeightList)
{
	int s1, s2;

	// 初始化叶子结点
	for (int i = 0; i < N; i++)
	{
		HT[i].weight = WeightList[i];
		HT[i].parent = -1;
		HT[i].lchild = HT[i].rchild = -1;
	}

	// 初始化非叶子结点
	for (int i = N; i < 2 * N - 1; i++)
	{
		HT[i].weight = 0;
		HT[i].parent = -1;
		HT[i].lchild = HT[i].rchild = -1;
	}

	// 开始构建Huffman树
	for (int i = N; i < 2 * N - 1; i++)
	{
		Select(i, s1, s2);
		HT[s1].parent = HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
}

// 从叶子到根逆向求256个字节各自的编码
void Huffman::MakeHuffmanCode()
{
	int i, cur_parent;
	char ch;
	string str;

	for (int cur_byte = 0; cur_byte < N; cur_byte++)
	{
		i = cur_byte;
		cur_parent = HT[i].parent;
		str = "";

		while (cur_parent != -1)
		{
			if (HT[cur_parent].lchild == i)
				ch = '0';
			else
				ch = '1';
		
			str = ch + str; // 逆向构建字符串
			//HC[cur_byte] = ch + HC[cur_byte]; 
			i = cur_parent;
			cur_parent = HT[i].parent;
		}

		HC[cur_byte] = str;
	}
}

// 先序遍历Huffman树
void Huffman::TestHuffmanTree(int i)
{
	if (i >= 0 && i <= 2 * N - 2)
	{
		cout << HT[i].weight << " ";

		TestHuffmanTree(HT[i].lchild);
		TestHuffmanTree(HT[i].rchild);
	}
}

void Huffman::TestHuffmanCode()
{
	for (int i = 0; i < N; i++)
		cout << HC[i] << endl;
}

