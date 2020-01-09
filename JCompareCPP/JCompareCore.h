#pragma once

#include <mutex>
#include <string>
#include <vector>

struct CompareElement
{
    int srcStartIndex;//Line number from source file
    int dstStartIndex;//Line number from destination file
    int lineCountOfSameContext;//Line count which indicates how many lines are same from srcLineNo and dstLineNo.

    CompareElement() : srcStartIndex(-1), dstStartIndex(-1), lineCountOfSameContext(0) {}
};

class JCompareCore
{
public:
    JCompareCore(void);
    ~JCompareCore(void);

    void AddSourceLine(const std::string& str);
    void AddDestinationLine(const std::string& str);
    void DoCompare();

    size_t GetResultCount() { return compareResult_.size(); }
    CompareElement GetResultElement(size_t i)
    {
        if(i >= compareResult_.size())
        {
            CompareElement res;
            return res;
        }
        return compareResult_[i];
    }

protected:
    void FindLongestCommonSubsequences(int srcBegin, int srcEnd, int dstBegin, int dstEnd);

private:
    std::mutex mutexCounter_;
    std::vector<size_t> srcHashVec_;
    std::vector<size_t> dstHashVec_;
    std::vector<CompareElement> compareResult_;
};

