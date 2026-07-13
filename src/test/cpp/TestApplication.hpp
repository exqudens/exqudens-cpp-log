#pragma once

#include <cstdint>

#include "test_lib_export.hpp"

class TEST_LIB_EXPORT TestApplication {

    private:

        inline static const char* LOGGER_ID = "TestApplication";

    public:

        static int32_t run(int32_t argc, char** argv);

};
