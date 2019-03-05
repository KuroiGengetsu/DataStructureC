#include "../../preference.h"
#include <stdio.h>
#include <stdlib.h>

typedef char* ElemType;

typedef struct LNode {
    ElemType        data;
    struct LNode    *next;
}LNode, *LinkList;

// - - - - - 基本操作的函数原型 - - - - -
// - - - - - 应用示例 - - - - -
// - - - - - 基本操作实现 - - - - -