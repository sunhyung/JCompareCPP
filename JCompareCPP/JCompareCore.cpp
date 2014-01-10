#include "JCompareCore.h"
#include "CRC32.h"
#include <algorithm>
#include <math.h>

//Compare function for JCompareCore::compareResult_
bool less_than_key (const CompareElement& struct1, const CompareElement& struct2)
{
	return (struct1.lineCountOfSameContext < struct2.lineCountOfSameContext);
}

JCompareCore::JCompareCore(void)
{
}


JCompareCore::~JCompareCore(void)
{
}

void JCompareCore::AddSourceLine(const TCHAR* str)
{
	srcHashVec_.push_back(GetStringCheckSum(str));
}

void JCompareCore::AddDestinationLine(const TCHAR* str)
{
	dstHashVec_.push_back(GetStringCheckSum(str));
}

void JCompareCore::FindLongestCommonSubsequences(int srcBegin, int srcEnd, int dstBegin, int dstEnd)
{
	CompareElement bestElement;
	int bestLen = -1;
	int srcIndex = srcBegin;
	int dstIndex = dstBegin;

	while (dstIndex <= dstEnd)
	{
		//If the remain length of destination is less than the bestLen, break while loop
		if ((dstEnd - dstIndex + 1) < bestElement.lineCountOfSameContext)
		{
			break;
		}

		srcIndex = srcBegin;
		while(srcIndex <= srcEnd)
		{
			int maxLen = min(srcEnd - srcIndex + 1, dstEnd - dstIndex + 1);

			//actual compare lines here
			//
			int curLongestMatch = 0;
			for(int i = 0; i < maxLen; i++)
			{
				if(srcHashVec_[srcIndex + i] != dstHashVec_[dstIndex + i])
				{
					break;
				}
				curLongestMatch++;
			}

			if(curLongestMatch > bestElement.lineCountOfSameContext)
			{
				bestElement.srcStartIndex = srcIndex;
				bestElement.dstStartIndex = dstIndex;
				bestElement.lineCountOfSameContext = curLongestMatch;
			}
			srcIndex++;
		}//end while srcIndex

		dstIndex++;
	}// end while dstIndex

	if (bestElement.dstStartIndex < 0)
	{
		return;
	}
	else
	{
		compareResult_.push_back(bestElement);

		//Try to compare above the best matching chunk
		if (srcBegin < bestElement.srcStartIndex && dstBegin < bestElement.dstStartIndex)
		{
			FindLongestCommonSubsequences(srcBegin, bestElement.srcStartIndex - 1, dstBegin, bestElement.dstStartIndex - 1);
		}

		//Try to compare below the best matching chunk
		int lowerSrcStart = bestElement.srcStartIndex + bestElement.lineCountOfSameContext;
		int lowerDstStart = bestElement.dstStartIndex + bestElement.lineCountOfSameContext;
		if(srcEnd > lowerSrcStart && dstEnd > lowerDstStart)
		{
				FindLongestCommonSubsequences (lowerSrcStart, srcEnd, lowerDstStart, dstEnd);
		}
	}
}

void JCompareCore::DoCompare()
{
	FindLongestCommonSubsequences (0, srcHashVec_.size() - 1, 0, dstHashVec_.size() - 1);

	//Sort the results in ascending order by source line number
	std::sort(compareResult_.begin(), compareResult_.end(), less_than_key);
}
