#include<iostream>
#include<stack>
#include"Compress.h"
using namespace std;

int main()
{
	cout << "=========Huffman文件压缩=========" << endl;
	cout << "输入文件名：";
	FilePath FileToProcess = "E:\\cap.bmp";
	//FilePath FileToProcess;
	//cin >> FileToProcess;

	Compress processor(FileToProcess);
	processor.BeginCompress(); // 压缩文件

	
	return 0;
}