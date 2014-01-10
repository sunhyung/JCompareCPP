#pragma once

#include <tchar.h>
#include <vector>

using namespace std;

struct CompareElement
{
	int srcStartIndex;//Line number from source file
	int dstStartIndex;//Line number from destination file
	int lineCountOfSameContext;//Line count which indicates how many lines are same from srcLineNo and dstLineNo.

	CompareElement() : srcStartIndex(-1), dstStartIndex(-1), lineCountOfSameContext(0) {}
};

class JCompareCore
{
private:
	vector<unsigned int>srcHashVec_;
	vector<unsigned int>dstHashVec_;
	vector<CompareElement>compareResult_;

protected:
	void FindLongestCommonSubsequences(int srcBegin, int srcEnd, int dstBegin, int dstEnd);

public:
	JCompareCore(void);
	~JCompareCore(void);

	void AddSourceLine(const TCHAR* str);
	void AddDestinationLine(const TCHAR* str);
	void DoCompare();

	size_t GetResultCount() { return compareResult_.size(); }
	CompareElement GetResultElement(int i)
	{
		if(i < 0 || i >= compareResult_.size())
		{
			CompareElement res;
			return res;
		}
		return compareResult_[i]; 
	}
};

