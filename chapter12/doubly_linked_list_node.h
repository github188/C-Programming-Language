//
// Created by 谭伟 on 2017/9/29.
//

#ifndef C_PROGRAMMING_LANGUAGE_DOUBLY_LINKED_LIST_NODE_H
#define C_PROGRAMMING_LANGUAGE_DOUBLY_LINKED_LIST_NODE_H


typedef struct NODE {
    struct NODE *fwd;
    struct NODE *bwd;
    int          value;
} Node;

#endif //C_PROGRAMMING_LANGUAGE_DOUBLY_LINKED_LIST_NODE_H
