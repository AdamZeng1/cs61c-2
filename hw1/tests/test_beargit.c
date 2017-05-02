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

void test_power(void) {
    TEST_ASSERT_EQUAL(1, power(100000, 0));
    TEST_ASSERT_EQUAL(2, power(2, 1));
    TEST_ASSERT_EQUAL(27, power(3, 3));
    TEST_ASSERT_EQUAL_UINT32(3486784401l, power(3, 20));
    TEST_ASSERT_EQUAL_UINT32(3486784401l, power(3, 20));
}

void test_base3_to_long(void) {
    TEST_ASSERT_EQUAL(0l, base3_to_long("1111"));
    TEST_ASSERT_EQUAL(1l, base3_to_long("1116"));
    TEST_ASSERT_EQUAL(2l, base3_to_long("111c"));
    TEST_ASSERT_EQUAL(3l, base3_to_long("1161"));
    TEST_ASSERT_EQUAL(9l, base3_to_long("1611"));
    TEST_ASSERT_EQUAL(14l, base3_to_long("166c"));
}

void test_long_to_base3(void) {
    int size = 4;
    char result[size];

    long_to_base3(result, 0l, size);
    TEST_ASSERT_EQUAL_STRING("1111", result);
    
    long_to_base3(result, 1l, size);
    TEST_ASSERT_EQUAL_STRING("1116", result);
    
    long_to_base3(result, 2l, size);
    TEST_ASSERT_EQUAL_STRING("111c", result);
    
    long_to_base3(result, 3l, size);
    TEST_ASSERT_EQUAL_STRING("1161", result);
    
    long_to_base3(result, 9l, size);
    TEST_ASSERT_EQUAL_STRING("1611", result);
    
    long_to_base3(result, 14l, size);
    TEST_ASSERT_EQUAL_STRING("166c", result);
}

void test_next_commit_id(void) {
    char commit_id[COMMIT_ID_BYTES] = "0000000000000000000000000000000000000000";
    // commit 0
    next_commit_id(commit_id);
    TEST_ASSERT_EQUAL_STRING("1111111111111111111111111111111111111111", commit_id);
    
    // commit 1
    next_commit_id(commit_id);
    TEST_ASSERT_EQUAL_STRING("1111111111111111111111111111111111111116", commit_id);
    
    // commit 2
    next_commit_id(commit_id);
    TEST_ASSERT_EQUAL_STRING("111111111111111111111111111111111111111c", commit_id);
    
    // commit 3
    next_commit_id(commit_id);
    TEST_ASSERT_EQUAL_STRING("1111111111111111111111111111111111111161", commit_id);

    int i;
    for (i=4; i < 27; i++)
        next_commit_id(commit_id);
    
    // commit 27
    next_commit_id(commit_id);
    TEST_ASSERT_EQUAL_STRING("1111111111111111111111111111111111116111", commit_id);
}

int main(void) {
    UNITY_BEGIN();
    /* RUN_TEST(test_status_returns_zero); */
    RUN_TEST(test_is_commit_msg_ok);
    RUN_TEST(test_power);
    RUN_TEST(test_next_commit_id);
    RUN_TEST(test_base3_to_long);
    RUN_TEST(test_long_to_base3);
    return UNITY_END();
}
