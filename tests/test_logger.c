#include "unity.h"
#include "logger.h"
#include "main.h"

void setUp(void) { }

void test_demo(void)
{
    TEST_ASSERT_TRUE(TRUE);
}

void tearDown(void) { }

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_demo);

    return UNITY_END();
}
