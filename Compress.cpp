#include<fstream>
#include<iostream>
#include"Compress.h"
using namespace std;

Compress::Compress(FilePath FileToProcess)
{
	changedFile = FileToProcess;
}
/*
Compress::~Compress()
{

}*/

void Compress::BeginCompress()
{
	Buffer bitStr; // 临时存放压缩好的内容
	int len = 0; // 压缩后的文件总大小

	InitHead();
	cout << FileHead.length << "bytes" << endl;

	huffman.MakeHuffmanTree(FileHead.weight);
	huffman.MakeHuffmanCode();
	
	//huffman.TestHuffmanCode();
	Encode(bitStr);

	WriteFile(bitStr, len);

	cout << len << "bytes" << endl;
	printf("压缩比率：%.4lf%%", 100.0 * len / FileHead.length);
}

int Compress::InitHead()
{
	unsigned char ch;
	
	// 初始化文件头
	FileHead.type[0] = 'H';
	FileHead.type[1] = 'U';
	FileHead.type[2] = 'F';
	FileHead.type[3] = '\0';
	FileHead.length = 0; // 原文件长度
	for (int i = 0; i < N; i++)
		FileHead.weight[i] = 0;

	// 二进制打开文件，用于读操作
	ifstream inFile(changedFile, ios::binary | ios::in);

	if (!inFile)
	{
		cerr << "原文件打开失败！" << endl;
		return ERROR;
	}

	// 逐字符扫描文件，得到权重
	while (inFile.read(reinterpret_cast<char*>(&ch), 1))
	{
		FileHead.weight[ch]++;
		FileHead.length++;
	}

	// 关闭文件
	inFile.close();
	return OK;
}

// 将binStr的前8位转成1位
char Compress::Str2byte(string binStr)
{
	unsigned char res = 0x00;
	
	for (int i = 0; i < 8; i++)
	{
		res = res << 1; // 左移1位
		if (binStr[i] == '1')
			res |= 0x01; // 按位或
	}

	return res;
}

int Compress::Encode(Buffer& bitStr)
{
	// 二进制打开文件，用于读操作
	ifstream inFile(changedFile, ios::binary | ios::in);
	if (!inFile)
	{
		cerr << "文件打开失败！" << endl;
		return ERROR;
	}

	// 创建一个局部工作区，暂存“01”串，当工作区累计到8位时开始压缩
	string bitWorkArea = ""; 
	unsigned char ch;

	while (inFile.read(reinterpret_cast<char*>(&ch), 1))
	{
		bitWorkArea += huffman.HC[ch];

		while (bitWorkArea.length() >= 8)
		{
			bitStr.push_back(static_cast<unsigned char>(Str2byte(bitWorkArea.substr(0, 8))));
			bitWorkArea.erase(0, 8); // 将处理好的8位移除
		}
	}

	// 工作区有剩余（不足8位），补'0'成8位后再处理
	if (!bitWorkArea.empty())
	{
		while (bitWorkArea.length() < 8)
			bitWorkArea += '0';

		bitStr.push_back(static_cast<unsigned char>(Str2byte(bitWorkArea)));
	}

	inFile.close();
	return OK;
}

int Compress::WriteFile(const Buffer bitStr, int& new_len)
{
	changedFile += ".huf"; // 生成新文件名

	// 二进制打开文件，用于写操作
	ofstream outFile(changedFile, ios::binary | ios::out);
	if (!outFile)
	{
		cerr << "文件创建失败！" << endl;
		return ERROR;
	}

	// 写入文件头
	outFile.write(reinterpret_cast<const char*>(&FileHead), sizeof(HEAD));
	// 写入压缩后的编码
	outFile.write(reinterpret_cast<const char*>(bitStr.data()), bitStr.size());
	
	outFile.close();

	cout << "成功生成压缩文件：" << changedFile << endl;
	new_len = sizeof(HEAD) +  bitStr.size();

	return OK;
}