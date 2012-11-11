#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"main.h"

#ifdef __UT
#define STATIC
#else
#define STATIC static
#endif

STATIC unsigned int _list_mem_count( const char list[][MAX_LEN] )
{
    int __cnt = 0;
    while( strnlen( list[ __cnt ], MAX_LEN - 1) != 0 )
    {
        #ifdef __UT
        printf( "list[ %d ] = %s\n", __cnt, list[ __cnt ] );
        #endif
        __cnt++;
    }
    return __cnt;
}
/*! @brief リストメンバ数計算関数.
 *      文字列リストのメンバ数の計算を行う関数.
 *  @param [in] listA
 *  @return     listAのメンバ数
 */
#if 0
STATIC int
_list_mem_count( (const char list[][MAX_LEN]) )
{
    int __cnt = 0;
    while( list[ __cnt ] != NULL )
    {
        __cnt++;
    }
    return __cnt;
}
#endif

/*! @brief 文字列リスト比較関数.
 *      2つの文字列リストの比較を行う関数.
 *  @param [in] listA
 *  @param [in] listB
 *  @return     一致するかどうかのみ判定
 *  @retval 0   一致
 *  @retval 非0 不一致
 */
STATIC int
strlist_cmp( const char listA[][MAX_LEN], const char listB[][MAX_LEN] )
{
    int __listA_mem = 0;
    int __listB_mem = 0;
    int __cnt = 0;
    int __ret = 0;

    #ifdef __UT
    printf( "*** %s() start ***\n", __func__ );
    #endif

    // ソートするリストの要素数を計算する
    __listA_mem = _list_mem_count( listA );
    __listB_mem = _list_mem_count( listB );

    #ifdef __UT
    printf( "listA member size  = %d\n", __listA_mem );
    printf( "listB member size  = %d\n", __listB_mem );
    #endif

    if( __listA_mem != __listB_mem )
    {
        #ifdef __UT
        printf( "listA size = %d\n", __listA_mem );
        printf( "listB size = %d\n", __listB_mem );
        printf( "not match list size.\n" );
        #endif
        __ret = 1;
        goto EXIT;
    }
    // リストを整列させる
    qsort( (char *)listA[0], __listA_mem, MAX_LEN,(int(*)(const void*, const void*)) strcmp );
    qsort( (char *)listB[0], __listB_mem, MAX_LEN, (int(*)(const void*, const void*))strcmp );

    // リストの各要素を比較する
    // __listA_mem == __listB_mem 以外は、上のif文で弾いている
    for( __cnt = 0; __cnt < __listA_mem; __cnt++ )
    {
        __ret = strcmp( listA[ __cnt ], listB[ __cnt ]);
        if( 0 != __ret )
        {
            #ifdef __UT
            printf( "not match list member.\n" );
            printf( "listA[ %d ] = %s\n", __cnt, listA[ __cnt ] );
            printf( "listB[ %d ] = %s\n", __cnt, listB[ __cnt ] );
            #endif
            __ret = 1;
            goto EXIT;
        }
    }

    #ifdef __UT
    printf( "match list member.\n" );
    #endif

    __ret = 0;
  EXIT:
    #ifdef __UT
    printf( "%s() return %d\n", __func__, __ret );
    printf( "*** %s() end ***\n", __func__ );
    #endif
    return __ret;
}

#ifdef __UT
int
main_dummy(void)
#else
/*! @brief メイン関数.
 *  @param [in] なし
 *  @return     0
 */
int
main(void)
#endif
{
    int ret = 0;
    char    listA[SIZE][MAX_LEN];
    char    listB[SIZE][MAX_LEN];

    ret = strlist_cmp( (const char (*)[MAX_LEN])listA, (const char (*)[MAX_LEN])listB );

    return 0;
}
