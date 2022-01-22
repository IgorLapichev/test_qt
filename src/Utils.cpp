#include "Utils.h"

#include <iostream>

std::wstring Utils::getPath()
{
    std::wstring path;

    std::wcout << L"Input folder path" << std::endl;
    std::getline(std::wcin, path);

    if (!std::filesystem::exists(path))
    {
        throw "This folder does not exist";
    }

    return path;
}

bool Utils::isFileExists(std::filesystem::directory_entry entry)
{
    return entry.exists() && !entry.is_directory();
}

std::string Utils::to_string(std::wstring str) {
    char* chars = (char*)str.c_str();
    return std::string(chars);
}
