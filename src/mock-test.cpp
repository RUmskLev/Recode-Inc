#include "virus.h"
#include <gmock/gmock.h>

class MyMock: public Virus{
        public:
                MOCK_METHOD(int, upBlood, ());
};

TEST(Country_test, Test_get_noc)
{
        MyMock mock;
        EXPECT_CALL(mock, upBlood());
        mock.upBlood();
}