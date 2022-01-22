#include "TestManager.h"
#include "ComparatorFactory.h"

#include "Comparator.h"
#include <iostream>

#include <QVariantMap>

TestManager::TestManager()
    : QObject(nullptr)
{
    m_comporator = ComparatorFactory::getComparator(ComparatorFactory::CompIndexes::binary);
}


void TestManager::startTest(const QString& leftPath, const QString& rightPath)
{
    m_leftPath  = leftPath;
    m_rightPath = rightPath;

//    m_newData = true;
//    m_flag.notify_one();
}


void TestManager::compareFolders(const QString& leftPath, const QString& rightPath)
{
//    while (true)
//    {
//        std::unique_lock <std::mutex> lock(m_locker);
//        while (m_newData)
//            m_flag.wait(lock);


    std::unordered_map <std::wstring, std::wstring> coincidences;

    try
    {
        if (m_comporator == nullptr)
            std::wcerr << L"Comparator is not set" << std::endl;

        for (auto const& first_entry : std::filesystem::directory_iterator{ leftPath.toStdWString() })
        {
            if (m_utils.isFileExists(first_entry))
            {
                for (auto const& second_entry : std::filesystem::directory_iterator{ rightPath.toStdWString() })
                {
                    auto got = coincidences.find(second_entry.path());
                    if (got != coincidences.end())
                        continue;

                    if (m_utils.isFileExists(second_entry))
                    {
                        if (first_entry.file_size() == second_entry.file_size())
                        {
                            if (m_comporator->compareFiles(first_entry.path(), second_entry.path()))
                                coincidences.insert(std::pair(second_entry.path(), first_entry.path()));
                        }
                    }
                    else
                        std::wcerr << std::wstring(L"Can not find file: ") + second_entry.path().wstring() << std::endl;
                }
            }
            else
                std::wcerr << std::wstring(L"Can not find file: ") + first_entry.path().wstring() << std::endl;
        }
    }
    catch (std::exception e)
    {
        throw;
    }

    m_result.clear();

    auto it = coincidences.begin();
    while (it != coincidences.end())
    {
        m_result.append(QString::fromStdWString(it->second));
        m_result.append(QString::fromStdWString(it->first));

        coincidences.erase(it);
        it = coincidences.begin();
    }

    emit resultModelChanged();
}

void TestManager::changeSelectionMethod(int idx)
{
    m_comporator = ComparatorFactory::getComparator(static_cast <ComparatorFactory::CompIndexes> (idx));
}
