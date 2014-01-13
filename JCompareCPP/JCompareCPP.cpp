// JCompareCPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "JCompareCore.h"
#include "JCTextFile.h"

int _tmain(int argc, _TCHAR* argv[])
{
	TCHAR *srcFile = _T("Put a source file path to compare");
	TCHAR *dstFile = _T("Put a destination file path to compare");
	JCompareCore core;
	JCTextFile src;
	JCTextFile dst;

	if(src.Open(srcFile) == false)
	{
		_tprintf(_T("Cannot open source file\n"));
		return -1;
	}
	while(src.IsEof() == false)
	{
		tstring line = src.ReadLn();
		core.AddSourceLine(line.c_str());
	}
	src.Close();

	if(dst.Open(dstFile) == false)
	{
		_tprintf(_T("Cannot open destination file\n"));
		return -1;
	}
	while(dst.IsEof() == false)
	{
		tstring line = dst.ReadLn();
		core.AddDestinationLine(line.c_str());
	}
	dst.Close();

	core.DoCompare();

	for(int i = 0; i < core.GetResultCount(); i++)
	{
		CompareElement ce = core.GetResultElement(i);
		_tprintf(_T("Source line : %d, Destination line : %d, Line count of same contents : %d\n"), ce.srcStartIndex + 1, ce.dstStartIndex + 1, ce.lineCountOfSameContext);
	}
	return 0;
}

