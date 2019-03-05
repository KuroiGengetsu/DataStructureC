#include "../../preference.h"
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct LNode {
    ElemType        data;
    struct LNode    *next;
}LNode, *LinkList;

// - - - - - 基本操作的函数原型 - - - - -
void CreateList_L(LinkList &L, int n);
    // 逆位序输入 n 个元素的值, 建立带表头结点的单链线性表 L
Status ListInsert_L(LinkList &L, int i, ElemType e);
    // 在带头结点的单链线性表 L 中第 i 个位置之前插入元素 e
Status ListDelete_L(LinkList &L, int i, ElemType &e);
    // 在带头结点的单链线性表 L 中删除第 i 个元素, 并由 e 返回其值
Status GetElem_L(LinkList L, int i, ElemType &e);
    // L 为带头结点的单链线性表的头指针
    // 当第 i 个元素存在时, 其值赋给 e 并返回 OK, 否则返回 ERROR
void MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc);
    // 已知单链线性表 La 和 Lb 的元素按值非递减排列
    // 归并 La 和 Lb 得到新的单链线性表 Lc, Lc 的元素也按值非递减排列
void DestroyList_L(LinkList &L);
    // 销毁链表
void PrintList_L(LinkList L);
    // 打印链表

// - - - - - 应用示例 - - - - -
int main() {
    LinkList La, Lb, Lc;
    // 记得输入非递增的值, 因为是逆位序输入
    CreateList_L(La, 3);
    CreateList_L(Lb, 5);
    PrintList_L(La);
    PrintList_L(Lb);
    MergeList_L(La, Lb, Lc);
    PrintList_L(Lc);
    DestroyList_L(Lc);
    return 0;
}


// - - - - - 基本操作实现 - - - - -
void CreateList_L(LinkList &L, int n) {
    // 逆位序输入 n 个元素的值, 建立带表头结点的单链线性表 L
    printf("Please input %d numbers: ", n);
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;     // 先建立一个带头结点的单链表
    for(int i = n; i > 0; i--) {
        LinkList p = (LinkList)malloc(sizeof(LNode));   // 生成新结点
        scanf("%d", &p->data);                          // 输入元素值
        p->next = L->next;                              // 插入到表头
        L->next = p;
    }
    printf("Input Over.\n");
}  // CreateList_L

Status ListInsert_L(LinkList &L, int i, ElemType e) {
    // 在带头结点的单链线性表 L 中第 i 个位置之前插入元素 e
    LinkList p = L, s;
    int j = 0;
    while(p && j < i-1) {   // 寻找第 i-1 个结点
        p = p->next;
        ++j;
    }
    if(!p || j > i-1)       // i 小于 1 或者大于 (表长+1)
        return ERROR;
    s = (LinkList)malloc(sizeof(LNode));    // 生成新结点
    s->data = e;                            // 插入 L 中
    s->next = p->next;
    p->next = s;
    return OK;
}  // ListInsert_L

Status ListDelete_L(LinkList &L, int i, ElemType &e) {
    // 在带头结点的单链线性表 L 中删除第 i 个元素, 并由 e 返回其值
    LinkList p = L, q;
    int j = 0;
    while(p->next && j < i-1) {     // 寻找第 i 个结点, 并令 p 指向其前趋
        p = p->next;
        ++j;
    }
    if(!p->next || j > i-1)         // 删除位置不合理
        return ERROR;
    q = p->next;
    p->next = q->next;
    e = q->data;
    free(q);
    return OK;
}  // ListDelete_L

Status GetElem_L(LinkList L, int i, ElemType &e) {
    // L 为带头结点的单链线性表的头指针
    // 当第 i 个元素存在时, 其值赋给 e 并返回 OK, 否则返回 ERROR
    LinkList p = L->next;
    int j = 1;
    while(p && j < i) {
        p = p->next;
        ++j;
    }
    if(!p || j>i)       // 第 i 个元素不存在
        return ERROR;
    e = p->data;
    return OK;
}  // GetElem_L

void MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc) {
    // 已知单链线性表 La 和 Lb 的元素按值非递减排列
    // 归并 La 和 Lb 得到新的单链线性表 Lc, Lc 的元素也按值非递减排列
    LinkList pa, pb, pc;
    pa = La->next;
    pb = Lb->next;
    Lc = La;
    pc = La;            // 用 La 的头结点作为 Lc 的头结点
    while(pa && pb) {
        if(pa->data <= pb->data) {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }
        else {
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
    }
    pc->next = pa? pa:pb;   // 插入剩余段
    free(Lb);               // 释放 Lb 的头结点
}  // MergeList_L

void DestroyList_L(LinkList &L) {
    // 销毁链表
    LinkList p = L, q=L;
    while(p->next != NULL) {
        p = p->next;
        free(q);
        q = p;
    }
    free(p);
}  // DestroyList_L

void PrintList_L(LinkList L) {
    // 打印链表
    L = L->next;
    while(L != NULL) {
        printf("%d ", L->data);
        L = L->next;
    }
    printf("\n");
}  // PrintList_L
