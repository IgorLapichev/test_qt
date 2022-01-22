#pragma once

#include <string>
#include <filesystem>

class Utils
{
public:
    std::wstring getPath();
    bool isFileExists(std::filesystem::directory_entry entry);
    std::string to_string(std::wstring str);
};
