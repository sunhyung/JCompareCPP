// JCompareCPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "JCompareCore.h"

#include <iostream>
#include <fstream>
#include <filesystem>

int main(int argc, _TCHAR* argv[])
{
    namespace fs = std::filesystem;

    if (argc < 3)
    {
        std::cout << "Usage: JCompareCPP.exe <source file path> <target file path>" << std::endl;
        return -1;
    }

    fs::path srcPath = argv[1];
    fs::path tarPath = argv[2];
    JCompareCore core;

    if (!fs::is_regular_file(srcPath))
    {
        std::cerr << "The source file is not regular file" << std::endl;
        return -1;
    }

    if (!fs::is_regular_file(tarPath))
    {
        std::cerr << "The target file is not regular file" << std::endl;
        return -1;
    }
    
    // Read from the source file
    std::ifstream srcFile(srcPath.c_str());
    if (!srcFile.is_open())
    {
        std::cerr << "Cannot open the source file." << std::endl;
        return -1;
    }

    std::string line;
    while (std::getline(srcFile, line))
    {
        core.AddSourceLine(line);
    }

    // Read from the target file
    std::ifstream tarFile(tarPath.c_str());
    if (!tarFile.is_open())
    {
        std::cerr << "Cannot open the target file." << std::endl;
        return -1;
    }

    while (std::getline(tarFile, line))
    {
        core.AddDestinationLine(line);
    }

    // GO!
    core.DoCompare();

    for(size_t i = 0; i < core.GetResultCount(); i++)
    {
        CompareElement ce = core.GetResultElement(i);
        std::cout << "Source line : " << ce.srcStartIndex + 1;
        std::cout << ", Destination line : " << ce.dstStartIndex + 1;
        std::cout << ", Line count of same contents : " << ce.lineCountOfSameContext;
        std::cout << std::endl;
    }
    return 0;
}

