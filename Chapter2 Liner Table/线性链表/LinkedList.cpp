#include "../../preference.h"
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct LNode {          // 结点类型
    ElemType        data;
    struct LNode    *next;
} *Link, *Position;

typedef struct {
    Link    head, tail;         // 分别指向线性链表中的头结点和最后一个结点
    int     len;                // 只是线性链表中数据元素的个数
} LinkList;


// - - - - - 基本操作的函数原型 - - - - -
Status MakeNode(Link &p, ElemType e);
    // 分配由 p 指向的 值为 e 的结点, 并返回 OK; 若分配失败, 则返回 ERROR
void FreeNode(Link &p);
    // 释放 p 所指结点
Status InitList(LinkList &L);
    // 构造一个空的线性链表
Status DestroyList(LinkList &L);
    // 销毁线性链表 L, L 不再存在
Status ClearList(LinkList &L);
    // 将线性链表 L 重置为空表, 并释放元链表的结点空间
Status InsFirst(Link h, Link s);
    // 已知 h 指向线性链表的头结点, 将 s 所指结点插入在第一个结点之前
Status DelFirst(Link h, Link &q);
    // 已知 h 指向线性链表的头结点, 删除链表中的第一个结点并以 q 返回
Status Append(LinkList &L, Link s);
    // 将指针 s 所指(彼此以指针相链)的一串结点链接在线性链表的最后一个结点
    // 之后, 并改变链表 L 的尾指针指向新的尾结点
Status Remove(LinkList &L, Link &q);
    // 删除线性链表中的尾结点并以 q 返回, 改变链表 L 的尾指针指向新的尾结点
Status InsBefore(LinkList &L, Link &p, Link s);
    // 已知 p 指向线性链表 L 中的一个结点, 将 s 所指结点插入在 p 所指结点之前,
    // 并修改指针 p 指向新插入的结点
Status InsAfter(LinkList &L, Link &p, Link s);
    // 已知 p 指向线性链表中的一个结点, 将 s 所指结点插入在 p 所指结点之后,
    // 并修改指针 p 指向新插入的结点
Status SetCurElem(Link &p, ElemType e);
    // 已知 p 指向线性链表中的一个结点, 用 e 更新 p 所指向结点中数据元素的值
ElemType GetCurElem(Link p);
    // 已知 p 指向线性链表中的一个结点, 返回 p 所指向的结点中数据元素的值
Status ListEmpty(LinkList L);
    // 若线性链表 L 为空表, 返回 TRUE, 否则返回 FALSE
int ListLength(LinkList L);
    // 返回线性链表 L 中元素个数
Position GetHead(LinkList L);
    // 返回线性链表 L 中头结点的位置
Position GetLast(LinkList L);
    // 返回线性链表 L 中最后一个结点的位置
Position PriorPos(LinkList L, Link p);
    // 已知 p 指向线性链表中的一个结点, 返回 p 所指结点的直接前驱的位置
    // 若无前驱, 则返回 NULL
Position NextPos(LinkList L, Link p);
    // 已知 p 指向线性链表中的一个结点, 返回 p 所指结点的直接后继的位置
    // 若无后继, 则返回 NULL
Status LocatePos(LinkList L, int i, Link &p);
    // 返回 p 指示线性链表 L 中第 i 个结点的位置并返回 OK, i 值不合法时返回 ERROR
Position LocateElem(LinkList L, ElemType e, Status (*compare)(ElemType, ElemType));
    // 返回线性链表 L 中第 1 个与 e 满足函数 compare() 判定关系的元素的位置
    // 若不存在这样的元素, 则返回 NULL
Status ListTraverse(LinkList L, Status (*visit)(ElemType));
    // 依次对 L 的每个元素调用函数 visit(), 一旦 visit() 失败, 则操作失败


// - - - - - 应用示例 - - - - -
int main() {

    return 0;
}


// - - - - - 基本操作实现 - - - - -
Status MakeNode(Link &p, ElemType e) {
    // 分配由 p 指向的 值为 e 的结点, 并返回 OK; 若分配失败, 则返回 ERROR
    p = (Link)malloc(sizeof(struct LNode));
    if(!p)
        return ERROR;
    p->data = e;
    return OK;
}

void FreeNode(Link &p) {
    // 释放 p 所指结点
    free(p);
}
Status InitList(LinkList &L) {
    // 构造一个空的线性链表
    L.head = (Link)malloc(sizeof(struct LNode));    // 申请空间
    if(!L.head)                                     // 失败返回 ERROR
        return ERROR;
    L.head->next = NULL;
    L.tail = L.head;
    L.len = 0;
    return OK;
}

Status DestroyList(LinkList &L) {
    // 销毁线性链表 L, L 不再存在
    Link p;
    while(L.head != L.tail) {
        p = L.head->next;
        free(L.head);
        L.head = p;
    }
    free(L.tail);
    return OK;
}

Status ClearList(LinkList &L) {
    // 将线性链表 L 重置为空表, 并释放元链表的结点空间
    if(ListEmpty(L))    // 原本就是空表
        return OK;
    Link p1 = L.head->next, p2;
    L.head = NULL;
    while(p1 != L.tail) {
        p2 = p1->next;
        free(p1);
        p1 = p2;
    }
    free(p1);
    L.tail = NULL;
    return OK;
}

Status InsFirst(Link h, Link s) {
    // 已知 h 指向线性链表的头结点, 将 s 所指结点插入在第一个结点之前
    Link p = h->next;
    h->next = s;
    s->next = p;
    return OK;
}

Status DelFirst(Link h, Link &q) {
    // 已知 h 指向线性链表的头结点, 删除链表中的第一个结点并以 q 返回
    q = h->next;
    h->next = q->next;
    return OK;
}

Status Append(LinkList &L, Link s) {
    // 将指针 s 所指(彼此以指针相链)的一串结点链接在线性链表的最后一个结点
    // 之后, 并改变链表 L 的尾指针指向新的尾结点
    L.tail->next = s;
    while(L.tail->next != NULL)
        L.tail = L.tail->next;
    return OK;
}

Status Remove(LinkList &L, Link &q) {
    // 删除线性链表中的尾结点并以 q 返回, 改变链表 L 的尾指针指向新的尾结点
    if(ListEmpty(L)) {
        q = NULL;
        return ERROR;
    }
    q = L.head->next;
    while(q->next != L.tail)
        q = q->next;
    L.tail = q;
    q = q->next;
    L.tail->next = NULL;
    return OK;
}

Status InsBefore(LinkList &L, Link &p, Link s) {
    // 已知 p 指向线性链表 L 中的一个结点, 将 s 所指结点插入在 p 所指结点之前,
    // 并修改指针 p 指向新插入的结点
    Link q = L.head;
    while(q->next != p)
        q = q->next;
    q->next = s;
    s->next = p->next;
    p = q;
    return OK;
}

Status InsAfter(LinkList &L, Link &p, Link s) {
    // 已知 p 指向线性链表中的一个结点, 将 s 所指结点插入在 p 所指结点之后,
    // 并修改指针 p 指向新插入的结点
    s->next = p->next;
    p->next = s;
    return OK;
}

Status SetCurElem(Link &p, ElemType e) {
    // 已知 p 指向线性链表中的一个结点, 用 e 更新 p 所指向结点中数据元素的值
    p->data = e;
    return OK;
}

ElemType GetCurElem(Link p) {
    // 已知 p 指向线性链表中的一个结点, 返回 p 所指向的结点中数据元素的值
    return p->data;
}

Status ListEmpty(LinkList L) {
    // 若线性链表 L 为空表, 返回 TRUE, 否则返回 FALSE
    return (L.head == L.tail);
}

int ListLength(LinkList L) {
    // 返回线性链表 L 中元素个数
    int i = 0;
    Link q = L.head;
    while(q != L.tail) {
        i++;
        q = q->next;
    }
    return i;
}

Position GetHead(LinkList L) {
    // 返回线性链表 L 中头结点的位置
    return L.head;
}

Position GetLast(LinkList L) {
    // 返回线性链表 L 中最后一个结点的位置
    return L.tail;
}

Position PriorPos(LinkList L, Link p) {
    // 已知 p 指向线性链表中的一个结点, 返回 p 所指结点的直接前驱的位置
    // 若无前驱, 则返回 NULL
    if(L.head == p)
        return NULL;
    Link q = L.head;
    while(q->next != p)
        q = q->next;
    return q;
}

Position NextPos(LinkList L, Link p) {
    // 已知 p 指向线性链表中的一个结点, 返回 p 所指结点的直接后继的位置
    // 若无后继, 则返回 NULL
    return p->next;
}

Status LocatePos(LinkList L, int i, Link &p) {
    // 返回 p 指示线性链表 L 中第 i 个结点的位置并返回 OK, i 值不合法时返回 ERROR
    if(i < 1 || i > ListLength(L))
        return ERROR;
    p = L.head;
    while(i--)
        p = p->next;
    return OK;
}

Position LocateElem(LinkList L, ElemType e, Status (*compare)(ElemType, ElemType)) {
    // 返回线性链表 L 中第 1 个与 e 满足函数 compare() 判定关系的元素的位置
    // 若不存在这样的元素, 则返回 NULL
    if(ListEmpty(L))
        return NULL;
    Link q = L.head->next;
    while(q != NULL && !compare(e, q->data)) {
        q = q->next;
    }
    return q;
}

Status ListTraverse(LinkList L, Status (*visit)(ElemType)) {
    // 依次对 L 的每个元素调用函数 visit(), 一旦 visit() 失败, 则操作失败
    if(ListEmpty(L))
        return ERROR;
    Link q = L.head->next;
    while(q != L.tail) {
        if(!visit(q->data))
            return INFEASIBLE;
    }
    return OK;
}
