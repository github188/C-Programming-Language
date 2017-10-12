//
// Created by 谭伟 on 2017/9/29.
//

#include <stdlib.h>
#include <stdio.h>
#include "doubly_linked_list_node.h"

int
dll_insert(Node *rootp, int value)
{
    Node * this;
    Node * next;
    Node * newnode;

    for (this = rootp; (next = this->fwd) != NULL ; this = next) {
        if (next->value == value)
            return 0;
        if (next->value > value)
            break;
    }

    newnode = (Node *)malloc(sizeof(Node));
    if (newnode == NULL) {
        return -1;
    }
    newnode->value = value;

    if (next != NULL) {
        if (this != rootp) {
            newnode->fwd = next;
            this->fwd = newnode;
            newnode->bwd = this;
            next->bwd = newnode;
        }
        else {
            newnode->fwd = next;
            rootp->fwd = newnode;
            newnode->bwd = NULL;
            next->bwd = newnode;
        }
    } else {
        if (this != rootp) {
            newnode->fwd = NULL;
            this->fwd = newnode;
            newnode->bwd = this;
            rootp->bwd = newnode;
        } else {
            newnode->fwd = NULL;
            rootp->fwd = newnode;
            newnode->bwd = NULL;
            rootp->bwd = newnode;
        }
    }
    return 1;
}