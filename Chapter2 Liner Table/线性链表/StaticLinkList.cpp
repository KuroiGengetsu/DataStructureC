#include "../../preference.h"
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1000    // 链表的最大长度

typedef char ElemType;  // 借用书上的 "例 2-3", 输入字符

typedef struct {
    ElemType    data;
    int         cur;
} component, SLinkList[MAXSIZE];

// - - - - - 基本操作的函数原型 - - - - -
void InitSpace_SL(SLinkList &space);
    // 将一维数组 space 中各分量链成一个备用链表, space[0].cur 为指针
    // "0" 表示空指针
int Malloc_SL(SLinkList &space);
    // 若备用空间链表非空, 则返回分配的结点下标, 否则返回 0
void Free_SL(SLinkList &space, int k);
    // 将下标为 k 的空间结点会受到备用链表
int LocateElem_SL(SLinkList S, ElemType e);
    // 在静态单链线性表 L 中查找第 i 个值为 e 的元素
    // 若找到, 则返回它在 L 中的位序, 否则返回 0
void difference(SLinkList &space, int &S);
    // 一次输入集合 A 和 B 的元素, 在一维数组 space 中建立表示集合 (A-B)∪(B-A)
    // 的静态链表, S 为其头指针, 假设备用空间足够大, space[0] 为其头指针
void TestPrint(SLinkList &space);
    // 打印出类似于 图2.11 的表

// - - - - - 应用示例 - - - - -
// 请输入 A = (c, b, e, g, f, d), B = (a, b, n, f)
int main() {
    SLinkList space;
    int S;
    // 某 bug: 请输入: 6 4cbegfdabnf敲下回车, 数字之后、字母之间不要有回车
    // 假如在敲完 4 之后敲下回车, 这个换行符会留在输入缓冲区中, 作为 A 的第一个元素
    // 所以请注意一下。 这个 BUG 可以考虑用 getchar() 解决, 但是这不在讨论范围内, 重点是数据结构
    difference(space, S);
    TestPrint(space);
    return 0;
}


// - - - - - 基本操作实现 - - - - -
void InitSpace_SL(SLinkList &space) {
    // 将一维数组 space 中各分量链成一个备用链表, space[0].cur 为指针
    // "0" 表示空指针
    for(int i = 0; i < MAXSIZE - 1; ++i) {
        space[i].cur = i + 1;
        space[i].data = ' ';
    }
    space[MAXSIZE-1].cur = 0;
}  // Malloc_SL

int Malloc_SL(SLinkList &space) {
    // 若备用空间链表非空, 则返回分配的结点下标, 否则返回 0
    int i = space[0].cur;
    if(space[0].cur)
        space[0].cur = space[i].cur;
    return i;
}  // Malloc_SL

void Free_SL(SLinkList &space, int k) {
    // 将下标为 k 的空间结点会受到备用链表
    space[k].cur = space[0].cur;
    space[0].cur = k;
}  // Free_SL

int LocateElem_SL(SLinkList S, ElemType e) {
    // 在静态单链线性表 L 中查找第 i 个值为 e 的元素
    // 若找到, 则返回它在 L 中的位序, 否则返回 0
    int i = S[0].cur;
    while(i && S[i].data != e)
        i = S[i].cur;
    return i;
}  // LocateElem_SL

void difference(SLinkList &space, int &S) {
    // 一次输入集合 A 和 B 的元素, 在一维数组 space 中建立表示集合 (A-B)∪(B-A)
    // 的静态链表, S 为其头指针, 假设备用空间足够大, space[0] 为其头指针
    InitSpace_SL(space);                // 初始化备用空间
    S = Malloc_SL(space);               // 生成 S 的头结点
    int r = S;                          // r 指向 S 的当前最后结点
    int m, n;                           // m 指 A 的元素个数, n 指 B 的元素个数
    printf("Please enter the number of elements of set A and set B, m & n: ");
    scanf("%d%d", &m, &n);              // 输入 A B 元素的个数
    printf("Enter the elements of set A(a total of %d): ", m);
    for(int j = 1; j <= m; ++j) {       // 建立集合 A 的链表
        int i = Malloc_SL(space);       // 分配结点
        scanf("%c", &space[i].data);    // 输入 A 元素的值
        space[r].cur = i;               // 插入到表尾
        r = i;
    }  // for
    space[r].cur = 0;                   // 尾结点的指针为空
    TestPrint(space);
    printf("Enter the elements of set B(a total of %d): ", n);
    for(int j = 1; j <= n; ++j) {       // 一次输入 B 的元素, 若不在当前表中, 则插入, 否则删除
        char b;
        scanf("%c", &b);
        int p = S, k = space[S].cur;    // k 指向集合 A 中第一个结点
        while(k != space[r].cur && space[k].data != b) {    // 在当前表中查找
            p = k;
            k = space[k].cur;
        }  // while
        if(k == space[r].cur) {         // 当前表中不存在该元素, 插入在 r 所指结点之后,
            int i = Malloc_SL(space);   // 且 r 的位置不变
            space[i].data = b;
            space[i].cur = space[r].cur;
            space[r].cur = i;
        }  // if
        else {                          // 该元素已在表中, 删除该元素
            space[p].cur = space[k].cur;
            Free_SL(space, k);
            if(r == k)                  // 若删除的是 r 所指向的结点, 则需修改尾指针
                r = p;
        }  // else
    }  // for
}  // difference

void TestPrint(SLinkList &space) {
    // 打印出类似于 图2.11 的表
    printf("i----data----cur\n");
    for(int i = 0; i < 11; i++) {
        printf("%d----%c----%d\n", i, space[i].data, space[i].cur);
    }
}