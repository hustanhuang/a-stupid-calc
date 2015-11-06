#include "tokens.h"

#include <stdlib.h>

tokenNode *createTokenNode()
{
    tokenNode *thisNode = malloc(sizeof(tokenNode));
    thisNode->token = NULL;
    thisNode->prev = NULL;
    thisNode->next = NULL;
    return thisNode;
}

void freeTokenNode(tokenNode *restrict thisNode)
{
    if (thisNode->prev && thisNode->next) {
        thisNode->prev->next = thisNode->next;
        thisNode->next->prev = thisNode->prev;
    } else {
        if (thisNode->prev) {
            thisNode->prev->next = NULL;
        }
        if (thisNode->next) {
            thisNode->next->prev = NULL;
        }
    }
    free(thisNode);
    return;
}

void freeAllTokenNodes(tokenNode *restrict thisNode)
{
    while (thisNode->prev) {
        thisNode = thisNode->prev;
    }
    while (thisNode->next) {
        thisNode = thisNode->next;
        free(thisNode->prev);
    }
    free(thisNode);
    return;
}

tokenNode *addAfterTokenNode(tokenNode *thisNode)
{
    tokenNode *newNode = malloc(sizeof(tokenNode));
    newNode->token = NULL;
    if (thisNode->next) {
        thisNode->next->prev = newNode;
        newNode->next = thisNode->next;
    } else {
        newNode->next = NULL;
    }
    thisNode->next = newNode;
    newNode->prev = thisNode;
    return newNode;
}
