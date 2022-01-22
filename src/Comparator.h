#pragma once

#include <filesystem>
#include <array>

#include "openssl\md5.h"

#define READ_BUFFER_SIZE (1024 * 8)

class BaseComparator
{
public:
    virtual bool compareFiles(const std::filesystem::path& firstFile, const std::filesystem::path& secondFile) = 0;
};

class BinaryComparator : public BaseComparator
{
public:
    virtual bool compareFiles(const std::filesystem::path& firstFile, const std::filesystem::path& secondFile);
};

class HashComparator : public BaseComparator
{
private:
    std::array <unsigned char, MD5_DIGEST_LENGTH> getFileMD5(const std::wstring& filePath);

public:
    virtual bool compareFiles(const std::filesystem::path& firstFile, const std::filesystem::path& secondFile);
};
