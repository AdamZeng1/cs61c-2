#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/stat.h>

#include "../Unity/src/unity.h"
#include "../beargit.h"
/* #include "../util.h" */

// covers empty .index file
/* void test_status_returns_zero(void) { */
    /* beargit_init(); */
    /* TEST_ASSERT_EQUAL(0, beargit_status()); */
/* } */

void test_is_commit_msg_ok(void) {
    // empty msg
    TEST_ASSERT_FALSE(is_commit_msg_ok(""));

    // strlen(msg) == 1
    TEST_ASSERT_FALSE(is_commit_msg_ok("1"));

    // lower case go_bears
    TEST_ASSERT_FALSE(is_commit_msg_ok("go bears!"));

    // msg == go_bears
    TEST_ASSERT_TRUE(is_commit_msg_ok("GO BEARS!"));

    // 1 char short
    TEST_ASSERT_FALSE(is_commit_msg_ok("GO BEARS and a commit msg"));

    // start of str
    TEST_ASSERT_TRUE(is_commit_msg_ok("GO BEARS! and a commit msg"));

    // end of str
    TEST_ASSERT_TRUE(is_commit_msg_ok(" and a commit msgGO BEARS!"));

    // middle of str, + false positive
    TEST_ASSERT_TRUE(is_commit_msg_ok(" GO BEARand a comGO BEARS!mit msg"));
}

int main(void) {
    UNITY_BEGIN();
    /* RUN_TEST(test_status_returns_zero); */
    RUN_TEST(test_is_commit_msg_ok);
    return UNITY_END();
}
