#include "world.h"
#include <gmock/gmock.h>

class MyMock: public Country{
        public:
                MOCK_METHOD(int, upInfected, (int inf));
};

TEST(Country_test, Test_get_noc)
{
        MyMock mock(100, 1, 1);
        EXPECT_CALL(mock, upInfected(100));
}