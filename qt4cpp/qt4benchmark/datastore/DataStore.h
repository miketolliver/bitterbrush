#pragma once

#include "datastore/IDataStore.h"

namespace benchmark
{

class DataStore
{
public:

    static RESULT CreateInstance(
            std::string  filename,
            IDataStore** dataStore );
};

} // namespace mersive
