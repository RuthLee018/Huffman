#pragma once
#include<string>

const int N = 256;
const int MAX = 0x7FFFFFFF;

// 定义Huffman树的结点
typedef struct
{
	int weight; // 结点权值
	int parent;
	int lchild, rchild;
}HTNode, * HuffmanTree;

// 定义Huffman编码表
typedef std::string* HuffmanCode;

// 定义Huffman类，包括Huffman树HT和编码表HC
class Huffman
{
private:HuffmanTree HT;
public:HuffmanCode HC;
public:Huffman();
	  ~Huffman();
	  void MakeHuffmanTree(int* WeightList); // 构建Huffman树
	  void MakeHuffmanCode(); // 构建Huffman编码表
	  void TestHuffmanCode();
	  void TestHuffmanTree(int i);
private:void Select(int i, int& s1, int& s2); // 辅助函数，每次选出HT[0...i-1]中权值最小的结点
};