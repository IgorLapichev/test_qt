#pragma once

#include <memory>
#include "Comparator.h"

class ComparatorFactory
{
public:
    enum class CompIndexes
    {
        binary = 0,
        hash
    };

    static std::shared_ptr<BaseComparator> getComparator(CompIndexes idx);

private:
};
