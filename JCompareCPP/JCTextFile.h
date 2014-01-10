#pragma once
#include <stdio.h>
#include <string>
#include <tchar.h>

#ifdef _UNICODE
#define tstring wstring
#else
#define tstring string
#endif

using namespace std;

//This class offers functions only open, close and read text. If you need to write function, just add in the class
class JCTextFile
{
private:
	FILE* pHandle_;
	tstring filePath_;

	std::wstring s2ws(const std::string& s);
	int FindChar(const char* str, char ch);

public:
	JCTextFile(void);
	~JCTextFile(void);

	bool Open(const TCHAR* filePath);
	void Close();
	tstring ReadLn();
	bool IsEof();
};

