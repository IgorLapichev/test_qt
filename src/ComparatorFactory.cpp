#pragma once

#include "ComparatorFactory.h"

std::shared_ptr<BaseComparator> ComparatorFactory::getComparator(CompIndexes idx)
{
    std::shared_ptr<BaseComparator> comparotor;
    switch (idx)
    {
    case CompIndexes::binary:
    {
        comparotor = std::make_shared <BinaryComparator>();
        break;
    }
    case CompIndexes::hash:
    {
        comparotor = std::make_shared <HashComparator>();
        break;
    }
    }

    return comparotor;
}
