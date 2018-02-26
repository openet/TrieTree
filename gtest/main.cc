#include <gtest/gtest.h>

int main(int argc, char **argv) {

    testing::InitGoogleTest(&argc, argv);

    int result = -1;
    try
    {
        result = RUN_ALL_TESTS();
    }
    catch(const std::exception& exc)
    {
        std::cout << "Tests execution has failed:" << exc.what() << std::endl;
    }

    return result;

    return 0;
}
