#ifndef TOKENS_H_
#define TOKENS_H_

struct tokennode {
    char *token;
    struct tokennode *prev;
    struct tokennode *next;
};

typedef struct tokennode tokenNode;

tokenNode *createTokenNode();
void freeTokenNode(tokenNode *thisNode);
void freeAllTokenNodes(tokenNode *thisNode);

tokenNode *addAfterTokenNode(tokenNode *thisNode);

#endif
