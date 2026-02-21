#pragma once
#include<vector>
#include<string>
#include"Huffman.h"
const int OK = 1;
const int ERROR = 0;

// 定义文件头结构，保存原文件基本信息
typedef struct
{
	unsigned char type[4]; // 文件类型
	int length; // 原文件长度
	int weight[256]; // 权值 
}HEAD;

typedef std::string FilePath;

// 缓冲区暂存编码后的信息
typedef std::vector<unsigned char> Buffer;

// 定义Compress类，处理文件
class Compress
{
private:FilePath changedFile; // 原文件文件名
	   HEAD FileHead;
	   Huffman huffman;
public:Compress(FilePath FilePath);
	  void BeginCompress(); // Compress类与外部的接口，接受传入的原文件调用类方法进行压缩
private:int InitHead(); // 初始化文件头
	   int Encode(Buffer& bitStr); //  将原文件内容压缩到bitStr中
	   char Str2byte(std::string binStr); // 将8位"01"串转换成1个二进制字节
	   int WriteFile(const Buffer bitStr, int& new_len); // 文件头与压缩后的数据写入新文件
};