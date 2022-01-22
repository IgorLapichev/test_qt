#include "Comparator.h"
#include "Utils.h"

#include <fstream>

bool BinaryComparator::compareFiles(const std::filesystem::path& firstFile, const std::filesystem::path& secondFile)
{
    auto result = true;

    std::basic_ifstream<std::byte> firstStream(secondFile, std::ios::in | std::ios_base::binary);
    std::basic_ifstream<std::byte> secondStream(secondFile, std::ios::in | std::ios_base::binary);

    std::array <std::byte, READ_BUFFER_SIZE> bufferFirst;
    std::array <std::byte, READ_BUFFER_SIZE> bufferSecond;

    while (firstStream.good() || secondStream.good())
    {
        firstStream.read(bufferFirst.data(), READ_BUFFER_SIZE);
        std::streamsize numRead1 = firstStream.gcount();

        secondStream.read(bufferSecond.data(), READ_BUFFER_SIZE);

        if (!std::equal(std::begin(bufferFirst), std::begin(bufferFirst) + numRead1, std::begin(bufferSecond)))
            result = false;
    }

    firstStream.close();
    secondStream.close();

    return result;
}

bool HashComparator::compareFiles(const std::filesystem::path& firstFile, const std::filesystem::path& secondFile)
{
    auto md5FirstData = getFileMD5(firstFile);
    auto md5SecondData = getFileMD5(secondFile);

    if (!std::equal(std::begin(md5FirstData), std::begin(md5FirstData) + MD5_DIGEST_LENGTH, std::begin(md5SecondData)))
        return false;
    return true;
}

std::array <unsigned char, MD5_DIGEST_LENGTH> HashComparator::getFileMD5(const std::wstring& filePath)
{
    std::array <std::byte, READ_BUFFER_SIZE> buf;
    std::basic_ifstream <std::byte> file(filePath, std::ios::in | std::ifstream::binary);

    MD5_CTX md5Context;
    MD5_Init(&md5Context);
    while (file.good())
    {
        file.read(buf.data(), sizeof(buf));
        MD5_Update(&md5Context, buf.data(), file.gcount());
    }

    std::array <unsigned char, MD5_DIGEST_LENGTH> md5Result;
    MD5_Final(md5Result.data(), &md5Context);

    file.close();
    return md5Result;
}
