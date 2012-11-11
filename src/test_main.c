#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"main.h"
#include"testRunner.h"

extern unsigned int
_list_mem_count( const char list[][MAX_LEN] );
extern int
strlist_cmp( const char listA[][MAX_LEN], const char listB[][MAX_LEN] );

static int
test__list_mem_count_001( void )
{
    int     ret = 0;
    char    listA[SIZE][MAX_LEN];

    memset( listA, 0x00, sizeof( listA ) );
    TEST_ASSERT_EQUALS( 0, _list_mem_count( (const char (*)[MAX_LEN])listA ) );

    printf( "sizeof( listA ) = %d\n", sizeof( listA ) );
    memset( listA, 0x00, sizeof( listA ) );
    strncpy( listA[0], "a", MAX_LEN - 1 );
    strncpy( listA[1], "b", MAX_LEN - 1 );
    strncpy( listA[2], "c", MAX_LEN - 1 );

    TEST_ASSERT_EQUALS( 3, _list_mem_count( (const char (*)[MAX_LEN])listA ) );

    memset( listA, 0x00, sizeof( listA ) );
    strncpy( listA[0], "a", MAX_LEN - 1 );
    strncpy( listA[1], "b", MAX_LEN - 1 );
    strncpy( listA[2], "c", MAX_LEN - 1 );
    strncpy( listA[3], "d", MAX_LEN - 1 );

    TEST_ASSERT_EQUALS( 4, _list_mem_count( (const char (*)[MAX_LEN])listA ) );

    return 0;
}

static int
test_strlist_cmp_001(void)
{
    int     ret = 0;
    char    listA[SIZE][MAX_LEN];
    char    listB[SIZE][MAX_LEN];

    // #001
    memset( listA, 0x00, sizeof( listA ) );
    memset( listB, 0x00, sizeof( listB ) );

    strncpy( listA[0], "a", MAX_LEN - 1 );
    strncpy( listA[1], "b", MAX_LEN - 1 );
    strncpy( listA[2], "c", MAX_LEN - 1 );

    strncpy( listB[0], "a", MAX_LEN - 1 );
    strncpy( listB[1], "b", MAX_LEN - 1 );
    strncpy( listB[2], "c", MAX_LEN - 1 );

    TEST_ASSERT_EQUALS( 0,
            strlist_cmp(    (const char (*)[MAX_LEN])listA,
                            (const char (*)[MAX_LEN])listB ) );

    return 0;

}

static int
test_strlist_cmp_002(void)
{
    int     ret = 0;
    char    listA[SIZE][MAX_LEN];
    char    listB[SIZE - 1][MAX_LEN];

    // #001
    memset( listA, 0x00, sizeof( listA ) );
    memset( listB, 0x00, sizeof( listB ) );

    strncpy( listA[0], "a", MAX_LEN - 1 );
    strncpy( listA[1], "b", MAX_LEN - 1 );
    strncpy( listA[2], "c", MAX_LEN - 1 );

    strncpy( listB[0], "a", MAX_LEN - 1 );
    strncpy( listB[1], "b", MAX_LEN - 1 );

    TEST_ASSERT_EQUALS( 1,
            strlist_cmp(    (const char (*)[MAX_LEN])listA,
                            (const char (*)[MAX_LEN])listB ) );

    return 0;
}

static int
test_strlist_cmp_003(void)
{
    int     ret = 0;
    char    listA[SIZE][MAX_LEN];
    char    listB[SIZE][MAX_LEN];

    // #001
    memset( listA, 0x00, sizeof( listA ) );
    memset( listB, 0x00, sizeof( listB ) );

    strncpy( listA[0], "a", MAX_LEN - 1 );
    strncpy( listA[1], "b", MAX_LEN - 1 );
    strncpy( listA[2], "c", MAX_LEN - 1 );

    strncpy( listB[0], "a", MAX_LEN - 1 );
    strncpy( listB[1], "b", MAX_LEN - 1 );
    strncpy( listB[2], "d", MAX_LEN - 1 );

    TEST_ASSERT_EQUALS( 1,
            strlist_cmp(    (const char (*)[MAX_LEN])listA,
                            (const char (*)[MAX_LEN])listB ) );

    return 0;
}

static int
test_strlist_cmp_004(void)
{
    int     ret = 0;
    char    listA[SIZE][MAX_LEN];
    char    listB[SIZE][MAX_LEN];

    // #001
    memset( listA, 0x00, sizeof( listA ) );
    memset( listB, 0x00, sizeof( listB ) );

    strncpy( listA[0], "a", MAX_LEN - 1 );
    strncpy( listA[1], "b", MAX_LEN - 1 );
    strncpy( listA[2], "c", MAX_LEN - 1 );

    strncpy( listB[0], "a", MAX_LEN - 1 );
    strncpy( listB[1], "c", MAX_LEN - 1 );
    strncpy( listB[2], "b", MAX_LEN - 1 );

    TEST_ASSERT_EQUALS( 0,
            strlist_cmp(    (const char (*)[MAX_LEN])listA,
                            (const char (*)[MAX_LEN])listB ) );

    return 0;
}

static int
test__list_mem_count(void)
{
    printf( "\n*** %s 001 ***\n", __func__ );
    test__list_mem_count_001();     // 正常系
}
static int
test_strlist_cmp(void)
{
    printf( "\n*** %s 001 ***\n", __func__ );
    test_strlist_cmp_001();     // 正常系
    printf( "\n*** %s 002 ***\n", __func__ );
    test_strlist_cmp_002();     // リストのメンバー数不一致
    printf( "\n*** %s 003 ***\n", __func__ );
    test_strlist_cmp_003();     // メンバー不一致あり（メンバー数一致）
    printf( "\n*** %s 004 ***\n", __func__ );
    test_strlist_cmp_004();     // リストメンバ未ソート（メンバー数一致）正常系
    return 0;
}

static unsigned int
testFunctions(void)
{
    int ret = 0;

    test__list_mem_count();
    test_strlist_cmp();
    return 0;
}

int
main(void)
{
    return (int)testRunner(testFunctions);
}
