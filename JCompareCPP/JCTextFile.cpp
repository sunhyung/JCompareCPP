#include "JCTextFile.h"

std::wstring JCTextFile::s2ws(const std::string& s)
{
    std::string curLocale = setlocale(LC_ALL, ""); 
    const char* _Source = s.c_str();
    size_t _Dsize = mbstowcs(NULL, _Source, 0) + 1;
    wchar_t *_Dest = new wchar_t[_Dsize];
    wmemset(_Dest, 0, _Dsize);
    mbstowcs(_Dest,_Source,_Dsize);
    std::wstring result = _Dest;
    delete []_Dest;
    setlocale(LC_ALL, curLocale.c_str());
    return result;
}

int JCTextFile::FindChar(const char* str, char ch)
{
	int pos = -1;
	while(*str != '\0')
	{
		pos++;
		if(*str == ch)
		{
			break;
		}
		str++;
	}
	return pos;
}

JCTextFile::JCTextFile(void) : pHandle_(NULL), filePath_(_T(""))
{
}


JCTextFile::~JCTextFile(void)
{
	Close();
}

bool JCTextFile::Open(const TCHAR* filePath)
{
	pHandle_ = _tfopen(filePath, _T("r"));
	if(pHandle_ == NULL)
	{
		return false;
	}

	filePath_ = filePath;
	return true;
}

void JCTextFile::Close()
{
	if(pHandle_ != NULL)
	{
		fclose(pHandle_);
		pHandle_ = NULL;
	}
}

tstring JCTextFile::ReadLn()
{
	if(pHandle_ == NULL)
	{
		return _T("");
	}

	if(IsEof() == true)
	{
		return _T("");
	}

	const int BUFF_SIZE = 256;
	char buff[BUFF_SIZE] = {'\0',};
	int curPos = ftell(pHandle_);
	tstring result = _T("");

	while(IsEof() == false)
	{
		int readSize = fread(buff, sizeof(char), BUFF_SIZE - 1, pHandle_);
		buff[readSize] = '\0';
		int posLf = FindChar(buff, '\n');
		if(posLf > -1)
		{
			//Found line feed in the buffer
			buff[posLf] = '\0';
#ifdef _UNICODE
			string tmp = buff;
			result = result + s2ws(tmp);
#else
			result = result + buff;
#endif
			fseek(pHandle_, curPos, SEEK_SET);//Go back where file pointer was
			fseek(pHandle_, strlen(buff) + 2, SEEK_CUR);//And then move forawrd
			break;
		}
		else
		{
#ifdef _UNICODE
				string tmp = buff;
				result = result + s2ws(tmp);
#else
				result = result + buff;
#endif
		}
	}
	return result;
}

bool JCTextFile::IsEof()
{
	return feof(pHandle_);
}

