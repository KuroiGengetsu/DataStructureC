#include "../../preference.h"
#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE  100 // 线性表存储空间的初始分配量
#define LISTINCREMENT   10  // 线性表存储空间的分配增量

typedef int ElemType;
    // 暂时用 int 示例, 可更改

typedef struct {
    ElemType    *elem;  // 存储空间基址
    int length;     // 当前长度
    int listsize;   // 当前分配的存储容量
} SqList;

// - - - - - 基本操作的函数原型 - - - - -
Status InitList_Sq(SqList &L);
    // 构造一个空的线性表 L
Status ListInsert_Sq(SqList &L, int i, ElemType e);
    // 在顺序线性表中第 i 个位置之前插入新的元素 e
    // i 的合法值为 1 <= i <= ListLength_Sq(L) + 1;
Status ListDelete_Sq(SqList &L, int i, ElemType &e);
    // 在顺序线性表 L 中删除第 i 个元素
    // i 的合法值为 1 <= i <= ListLength_Sq(L)
Status LocateElem_Sq(SqList L, ElemType e,
    Status(*compare)(ElemType, ElemType));
    // 在顺序线性表 L 中查找第一个值与 e 满足函数 compare() 的元素的位序
    // 若找到, 则返回其在 L 中的位序, 否则返回 0
Status MergeList_Sq(SqList La, SqList Lb, SqList &Lc);
    // 已知顺序线性表 La 和 Lb 的元素按值非递减排列
    // 归并 La 和 Lb 得到新的顺序线性表 Lc, Lc 的元素也按值非递减排列
Status PrintList_SQ(SqList L);
    // 打印顺序线性表的数据
Status DestroyList_Sq(SqList &L);
    // 销毁线性表

// - - - - - 应用示例 - - - - -
int main() {
    SqList La, Lb, Lc;
    // 初始化线性表
    InitList_Sq(La);
    InitList_Sq(Lb);
    InitList_Sq(Lc);

    ListInsert_Sq(La, 1, 1);
    ListInsert_Sq(La, 2, 3);
    ListInsert_Sq(La, 3, 6);
    ListInsert_Sq(La, 4, 11);
    ListInsert_Sq(La, 5, 13);
    ListInsert_Sq(La, 6, 55);
    ListInsert_Sq(La, 7, 77);
    ListInsert_Sq(Lb, 1, 3);
    ListInsert_Sq(Lb, 2, 4);
    ListInsert_Sq(Lb, 3, 5);
    ListInsert_Sq(Lb, 4, 11);
    ListInsert_Sq(Lb, 5, 78);

    // 打印 La 和 Lb
    PrintList_SQ(La);
    PrintList_SQ(Lb);

    // 合并
    MergeList_Sq(La, Lb, Lc);
    ElemType e1, e2;
    ListDelete_Sq(Lc, 2, e1);
    ListDelete_Sq(Lc, 6, e2);
    PrintList_SQ(Lc);
    printf("The two elements that were deleted are %d and %d\n",
        e1, e2);

    // 销毁 La, Lb, Lc
    DestroyList_Sq(La);
    DestroyList_Sq(Lb);
    DestroyList_Sq(Lc);
    return 0;
}


// - - - - - 基本操作实现 - - - - -
Status  InitList_Sq(SqList &L) {
    // 构造一个空的线性表 L
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if(!L.elem)
        exit(OVERFLOW);                 // 存储空间分配失败
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}

Status ListInsert_Sq(SqList &L, int i, ElemType e) {
    // 在顺序线性表中第 i 个位置之前插入新的元素 e
    // i 的合法值为 1 <= i <= ListLength_Sq(L) + 1;
    if(i < 1 || i > L.length + 1)
        return ERROR;                   // i 值不合法
    if(L.length >= L.listsize) {
        // 当前存储空间已满, 增加分配
        ElemType * newbase;
        newbase = (ElemType *)realloc(L.elem,
            (L.listsize + LISTINCREMENT) * sizeof(ElemType));
        if(!newbase)                    // 存储分配失败
            exit(OVERFLOW);
        L.elem = newbase;               // 新基址
        L.listsize += LISTINCREMENT;    // 增加存储容量
    }
    ElemType *p, *q = &(L.elem[i-1]);       // q 为插入位置
    for(p = &(L.elem[L.length-1]); p >= q; --p)
        *(p+1) = *p;                    // 插入位置以及之后的元素右移
    *q = e;                             // 插入 e
    ++L.length;                         // 表长增 1
    return OK;
}  // ListInsert_Sq

Status ListDelete_Sq(SqList &L, int i, ElemType &e) {
    // 在顺序线性表 L 中删除第 i 个元素
    // i 的合法值为 1 <= i <= ListLength_Sq(L)
    if((i < 1) || (i > L.length))
        return ERROR;                   // i 值不合法
    ElemType *q, *p = &(L.elem[i-1]);   // p 为被删除元素的位置
    e = *p;                             // 被删除元素的值赋给 e
    q = L.elem + L.length -1;           // 表尾元素的位置
    for(++p; p <= q; ++p)               // 被删除元素之后的元素左移
        *(p-1) = *p;
    --L.length;                         // 表长减 1
    return OK;
}  // ListDelete_Sq

Status LocateElem_Sq(SqList L, ElemType e,
    Status(*compare)(ElemType, ElemType)) {
    // 在顺序线性表 L 中查找第一个值与 e 满足函数 compare() 的元素的位序
    // 若找到, 则返回其在 L 中的位序, 否则返回 0
    int i = 1;              // i 的初值为第一个元素的位序
    ElemType *p = L.elem;   // p 的初值为第一个元素的存储位置
    while(i <= L.length && !(*compare)(*p++, e))
        ++i;
    if(i <= L.length)
        return i;
    else
        return 0;
}  // LocateElem_Sq

Status MergeList_Sq(SqList La, SqList Lb, SqList &Lc) {
    // 已知顺序线性表 La 和 Lb 的元素按值非递减排列
    // 归并 La 和 Lb 得到新的顺序线性表 Lc, Lc 的元素也按值非递减排列
    ElemType *pa = La.elem, *pb = Lb.elem, *pc, *pa_last, *pb_last;
    Lc.length = La.length + Lb.length;
    Lc.listsize = Lc.length;
    Lc.elem = (ElemType *)malloc(Lc.listsize * sizeof(ElemType));
    pc = Lc.elem;
    if(!Lc.elem)        // 存储分配失败
        exit(OVERFLOW);
    pa_last = La.elem + La.length - 1;
    pb_last = Lb.elem + Lb.length - 1;
    while(pa <= pa_last && pb <= pb_last) {  // 归并
        if(*pa <= *pb)
            *pc++ = *pa++;
        else
            *pc++ = *pb++;
    }
    while(pa <= pa_last)    // 插入 La 的剩余元素
        *pc++ = *pa++;
    while(pb <= pb_last)     // 插入 Lb 的剩余元素
        *pc++ = *pb++;
    return OK;
}  // MergeList

Status PrintList_SQ(SqList L) {
    // 打印顺序线性表的数据
    int i, count = 0;
    for(i=0; i<L.length; i++) {
        count++;
        printf("%d\t", L.elem[i]);
        if(count == 5) {
            printf("\n");
            count = 0;
        }
    }
    printf("\n");
    return OK;
}

Status DestroyList_Sq(SqList &L) {
    // 销毁线性表
    free(L.elem);
    return OK;
}
