// 三元组
#include "../preference.h"
#include <stdio.h>
#include <stdlib.h>
// 设定 ElemType
typedef int ElemType;

// Triplet 类型为 ElemType *
typedef ElemType * Triplet;

// - - - - - 基本操作的函数原型 - - - - -

Status InitTriplet(Triplet &T, ElemType v1, ElemType v2, ElemType v3);
    // 操作结果: 构造了三元组 T, 元素 e1 e2 e3 分别被赋以参数 v1 v2 v3 的值
Status DestroyTriplet(Triplet &T);
    // 操作结果: 三元组被销毁
Status Get(Triplet T, int i, ElemType &e);
    // 初始条件: 三元组已存在, 1 <= i <= 3
    // 操作结果: 用 e 返回 T 的第 i 元 的值
Status Put(Triplet &T, int i, ElemType e);
    // 初始条件: 三元组已存在, 1 <= i <= 3
    // 操作结果: 改变 T 的第 i 元的值为 e
Status IsAscending(Triplet T);
    // 初始条件: 三元组已存在
    // 操作结果: 如果 T 的三个元素按升序排列, 则返回 1, 否则返回 0
Status IsDescending(Triplet T);
    // 初始条件: 三元组已存在
    // 操作结果: 如果 T 的三个元素按降序排列, 则返回 1, 否则返回 0
Status Max(Triplet T, ElemType &e);
    // 初始条件: 三元组已存在
    // 操作结果: 用 e 返回 T 的三个元素中的最大值
Status Min(Triplet T, ElemType &e);
    // 初始条件: 三元组已存在
    // 操作结果: 用 e 返回 T 的三个元素中的最小值
Status PrintTriplet(Triplet T);
    // 初始条件: 三元组已存在
    // 操作结果: 屏幕上打印出 T 的三个元素的值


// - - - - - 应用示例 - - - - -
int main() {
    ElemType e1;
    Triplet T1;
    InitTriplet(T1, 1, 2, 3);
    PrintTriplet(T1);
    Put(T1, 1, 15);
    Get(T1, 1, e1);
    PrintTriplet(T1);
    DestroyTriplet(T1);
    return 0;
}


// - - - - - 基本操作实现 - - - - -
Status InitTriplet(Triplet &T, ElemType v1, ElemType v2, ElemType v3) {
    // 构造三元组 T, 依次置 T 的三个元素的值为 v1, v2, v3
    T = (ElemType *)malloc(3 * sizeof(ElemType));  // 分配三个元素的存储空间
    if(!T) {
        // 分配存储空间失败
        exit(OVERFLOW);
    }
    T[0] = v1;
    T[1] = v2;
    T[2] = v3;
    return OK;
}  // InitTriplet

Status DestroyTriplet(Triplet &T) {
    // 销毁三元组 T
    free(T);
    T = NULL;
    return OK;
}  // DestroyTriplet

Status Get(Triplet T, int i, ElemType &e) {
    // 1<=i<=3, 用 e 返回 T 的第 i 元的值
    if(i < 1 || i > 3) {
        return ERROR;
    }
    e = T[i-1];
    return OK;
}  // Get

Status Put(Triplet &T, int i, ElemType e) {
    // 1<=i<=3, 置 T 的第 i 元的值为 e
    if(i < 1 || i > 3) {
        return ERROR;
    }
    T[i-1] = e;
    return OK;
}  // Put

Status IsAscending(Triplet T) {
    // 如果 T 的三个元素按升序排列, 则返回 1, 否则返回 0
    return (T[0] <= T[1] && T[1] <= T[2]);
}  // IsAscending

Status IsDescending(Triplet T) {
    // 如果 T 的三个元素按降序排列, 则返回 1, 否则返回 0
    return (T[0] >= T[1] && T[1] >= T[2]);
}  // IsDescending

Status Max(Triplet T, ElemType &e) {
    // 用 e 返回 T 的最大元素的值
    if(T[0] >= T[1] && T[0] >= T[2])
        e = T[0];
    else
        e = (T[1] >= T[2]) ? T[1] : T[2];
    return OK;
}  // Max

Status Min(Triplet T, ElemType &e) {
    // 用 e 返回 T 的最小元素的值
    if(T[0] <= T[1] && T[0] <= T[2])
        e = T[0];
    else
        e = (T[1] <= T[2]) ? T[1] : T[2];
    return OK;
}  // Min

Status PrintTriplet(Triplet T) {
    // 三元组已存在, 在屏幕上打印出 T 的三个元素的值
    ElemType e;
    printf("\n%d\t%d\t%d\n", T[0], T[1], T[2]);
    if(IsAscending(T)) {
        printf("The triple is ascending.\n");
    }
    else if(IsDescending(T)) {
        printf("The triple is descending.\n");
    }
    else {
        printf("The triple is neither ascending nor descending.\n");
    }
    Max(T, e);
    printf("The maximum value of this triple is %d, ", e);
    Min(T, e);
    printf("the minimum value is %d.\n\n", e);
    return OK;
}  // PrintTriplet