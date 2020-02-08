#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

// A node with three children
typedef struct threeEdges{
    int type, edgeNum;
    void *left, *right, *middle;
}threeEdges;

// Node with two children
typedef struct twoEdges{
    int type, edgeNum;
    void *left, *right;
}twoEdges;

// Node with a child
typedef struct oneEdge{
    int type, edgeNum;
    void* middle;
}oneEdge;

// Node without a child
typedef struct noEdge{
    int type, edgeNum;
    char* data;
}noEdge;

threeEdges* createThreeEdgeNode(int type){
    threeEdges* newNode = (threeEdges*)malloc(sizeof(threeEdges));
    newNode->type = type;
    newNode->edgeNum = 3;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->middle = NULL;
    return newNode;
}

twoEdges* createTwoEdgeNode(int type){
    twoEdges* newNode = (twoEdges*)malloc(sizeof(twoEdges));
    newNode->type = type;
    newNode->edgeNum = 2;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

oneEdge* createOneEdgeNode(int type){
    oneEdge* newNode = (oneEdge*)malloc(sizeof(oneEdge));
    newNode->type = type;
    newNode->edgeNum = 1;
    newNode->middle = NULL;
    return newNode;
}

noEdge* createNoEdgeNode(){
    noEdge* newNode = (noEdge*)malloc(sizeof(noEdge));
    newNode->edgeNum = 0;
    return newNode;
}

// function definitions

threeEdges* openCondition(threeEdges* head);
threeEdges* openThreeEdgedExpression(threeEdges* head);
twoEdges* openTwoEdgedExpression(twoEdges* head);
oneEdge* openOneEdgedExpression(oneEdge* head);
noEdge* openOneEdgedNode(oneEdge* head);
void printThreeEdgedNode(threeEdges* head);
void printTwoEdgedNode(twoEdges* head);
void printOneEdgedNode(oneEdge* head);
void printNoEdgedNode(noEdge* head);
void destroyThreeEdgedNode(threeEdges* head);
void destroyTwoEdgedNode(twoEdges* head);
void destroyOneEdgedNode(oneEdge* head);
void destroyNoEdgedNode(noEdge* head);

// get a random line from given files

char* getRandomLine(char* file){
    int randomVal = rand() % 10; // max line number is 10

    FILE* fileRead = fopen(file, "r"); 
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fileRead)) != -1 && randomVal > 0) randomVal--;

    if(randomVal > 0){
        rewind(fileRead);
        while((read = getline(&line, &len, fileRead)) != -1 && randomVal > 0) randomVal--;
    }

    fclose(fileRead);

    return strtok(line, "\n\r");
}

// print functions

void printThreeEdgedNode(threeEdges* head){
    // print left node
    printf("(");
    if((*(threeEdges*)(head->left)).edgeNum == 3)
        printThreeEdgedNode(head->left);
    else if((*(threeEdges*)(head->left)).edgeNum == 2)
        printTwoEdgedNode(head->left);
    else if((*(threeEdges*)(head->left)).edgeNum == 1)
        printOneEdgedNode(head->left);
    
    printf(")");
    // print middle node
    printOneEdgedNode(head->middle);
    printf("(");
    // print right node
    if((*(threeEdges*)(head->right)).edgeNum == 3)
        printThreeEdgedNode(head->right);
    else if((*(threeEdges*)(head->right)).edgeNum == 2)
        printTwoEdgedNode(head->right);
    else if((*(threeEdges*)(head->right)).edgeNum == 1)
        printOneEdgedNode(head->right);
    printf(")");
    return;
}

void printTwoEdgedNode(twoEdges* head){
    // print left node
    printOneEdgedNode(head->left);
    printf("(");
    // print right node
    if((*(twoEdges*)(head->right)).edgeNum == 3)
        printThreeEdgedNode(head->right);
    else if((*(twoEdges*)(head->right)).edgeNum == 2)
        printTwoEdgedNode(head->right);
    else if((*(twoEdges*)(head->right)).edgeNum == 1)
        printOneEdgedNode(head->right);
    printf(")");
    return;
}

void printOneEdgedNode(oneEdge* head){
    enum types{alg, cond, expr, op, pre_op, rel_op, set_op, var};
    if(head->type == expr)
        printOneEdgedNode(head->middle);
    else
        printNoEdgedNode(head->middle);
    return;
}

void printNoEdgedNode(noEdge* head){
    printf("%s", head->data);
    return;
}

void destroyThreeEdgedNode(threeEdges* head){
    // Destroy left node
    if((*(threeEdges*)(head->left)).edgeNum == 3)
        destroyThreeEdgedNode(head->left);
    else if((*(threeEdges*)(head->left)).edgeNum == 2)
        destroyTwoEdgedNode(head->left);
    else if((*(threeEdges*)(head->left)).edgeNum == 1)
        destroyOneEdgedNode(head->left);
    // Destroy middle node
    destroyOneEdgedNode(head->middle);
    // Destroy right node
    if((*(threeEdges*)(head->right)).edgeNum == 3)
        destroyThreeEdgedNode(head->right);
    else if((*(threeEdges*)(head->right)).edgeNum == 2)
        destroyTwoEdgedNode(head->right);
    else if((*(threeEdges*)(head->right)).edgeNum == 1)
        destroyOneEdgedNode(head->right);
    free(head);
    return;
}

void destroyTwoEdgedNode(twoEdges* head){
    // Destroy left node
    destroyOneEdgedNode(head->left);
    // Destroy right node
    if((*(threeEdges*)(head->right)).edgeNum == 3)
        destroyThreeEdgedNode(head->right);
    else if((*(threeEdges*)(head->right)).edgeNum == 2)
        destroyTwoEdgedNode(head->right);
    else if((*(threeEdges*)(head->right)).edgeNum == 1)
        destroyOneEdgedNode(head->right);
    free(head);
    return;
}

void destroyOneEdgedNode(oneEdge* head){
    // Destroy middle node
    enum types{alg, cond, expr, op, pre_op, rel_op, set_op, var};
    if(head->type == expr)
        destroyOneEdgedNode(head->middle);
    else
        destroyNoEdgedNode(head->middle);
    free(head);
    return;
}

void destroyNoEdgedNode(noEdge* head){
    // Destroy itself
    if(head->data)
        free(head->data);
    free(head);
    return;
}
// extend functions

threeEdges* openCondition(threeEdges* head){
    enum types{alg, cond, expr, op, pre_op, rel_op, set_op, var};

    int randomVal = rand() % 2 + 1;

    if(randomVal == 1){ // (<cond><set-op><cond>) ---> getting this
        threeEdges* leftNode = createThreeEdgeNode(cond);
        leftNode = openCondition(leftNode);
        oneEdge* middleNode = createOneEdgeNode(set_op);
        middleNode->middle = openOneEdgedNode(middleNode);
        threeEdges* rightNode = createThreeEdgeNode(cond);
        rightNode = openCondition(rightNode);
        // add the newly created nodes to the tree
        head->left = leftNode;
        head->right = rightNode;
        head->middle = middleNode;
    }else{ // (<expr><rel-op><expr>) ---> getting this
        randomVal = rand() % 3 + 1; // select randomly for left expression node
        // first create the left expression node
        if(randomVal == 1){ // one edged expression node
            oneEdge* leftNode = createOneEdgeNode(expr);
            leftNode = openOneEdgedExpression(leftNode);
            head->left = leftNode;
        }else if(randomVal == 2){ // two edged expression node
            twoEdges* leftNode = createTwoEdgeNode(expr);
            leftNode = openTwoEdgedExpression(leftNode);
            head->left = leftNode;
        }else{ // three edged expression node
            threeEdges* leftNode = createThreeEdgeNode(expr);
            leftNode = openThreeEdgedExpression(leftNode);
            head->left = leftNode;
        }
        randomVal = rand() % 3 + 1; // select randomly for right expression node
        // then create the right expression node
        if(randomVal == 1){ // one edged expression node
            oneEdge* rightNode = createOneEdgeNode(expr);
            rightNode = openOneEdgedExpression(rightNode); // extend again
            head->right = rightNode;
        }else if(randomVal == 2){ // two edged expression node
            twoEdges* rightNode = createTwoEdgeNode(expr);
            rightNode = openTwoEdgedExpression(rightNode);
            head->right = rightNode;
        }else{ // three edged expression node
            threeEdges* rightNode = createThreeEdgeNode(expr);
            rightNode = openThreeEdgedExpression(rightNode); // extend again
            head->right = rightNode;
        }
        // create the middle node which is <rel-op>
        oneEdge* middleNode = createOneEdgeNode(rel_op);
        middleNode->middle = openOneEdgedNode(middleNode); // extend again
        head->middle = middleNode;
    }
    return head;
}

threeEdges* openThreeEdgedExpression(threeEdges* head){ // (<expr><op><expr>)   ----> getting this
    enum types{alg, cond, expr, op, pre_op, rel_op, set_op, var};

    int randomVal = rand() % 3 + 1; // to select random extension type

    // first extend the left expression node
    if(randomVal == 1){ // one edged expression
        oneEdge* leftNode = createOneEdgeNode(expr);
        leftNode = openOneEdgedExpression(leftNode); // extend again
        head->left = leftNode;
    }else if(randomVal == 2){ // two edged expression
        twoEdges* leftNode = createTwoEdgeNode(expr);
        leftNode = openTwoEdgedExpression(leftNode); // extend again
        head->left = leftNode;
    }else{ // three edged expression
        threeEdges* leftNode = createThreeEdgeNode(expr);
        leftNode = openThreeEdgedExpression(leftNode); // extend again
        head->left = leftNode;
    }
    randomVal = rand() % 3 + 1;
    // then extend the right expression node
    if(randomVal == 1){ // one edged expression
        oneEdge* rightNode = createOneEdgeNode(expr);
        rightNode = openOneEdgedExpression(rightNode); // extend again
        head->right = rightNode;
    }else if(randomVal == 2){ // two edged expression
        twoEdges* rightNode = createTwoEdgeNode(expr);
        rightNode = openTwoEdgedExpression(rightNode); // extend again
        head->right = rightNode;
    }else{ // three edged expression
        threeEdges* rightNode = createThreeEdgeNode(expr);
        rightNode = openThreeEdgedExpression(rightNode); // extend again
        head->right = rightNode;
    }
    // create the middle node <op>
    oneEdge* middleNode = createOneEdgeNode(op);
    middleNode->middle = openOneEdgedNode(middleNode); // extend <op>
    head->middle = middleNode;
    return head;
}

twoEdges* openTwoEdgedExpression(twoEdges* head){ // <pre-op>(<expr>)   ----> getting this
    enum types{alg, cond, expr, op, pre_op, rel_op, set_op, var};
    int randomVal = rand() % 2 + 1;

    // extend the right expression node
    if(randomVal == 1){ // one edged expression
        oneEdge* rightNode = createOneEdgeNode(expr);
        rightNode = openOneEdgedExpression(rightNode); // extend again
        head->right = rightNode;
    }else if(randomVal == 2){ // two edged expression
        twoEdges* rightNode = createTwoEdgeNode(expr);
        rightNode = openTwoEdgedExpression(rightNode); // extend again
        head->right = rightNode;
    }else{ // three edged expression
        threeEdges* rightNode = createThreeEdgeNode(expr);
        rightNode = openThreeEdgedExpression(rightNode); // extend again
        head->right = rightNode;
    }
    // create the left <pre-op> node
    oneEdge* leftNode = createOneEdgeNode(pre_op);
    leftNode->middle = openOneEdgedNode(leftNode); // extend <pre-op>
    head->left = leftNode;
    return head;
}

oneEdge* openOneEdgedExpression(oneEdge* head){ // <var> ----> getting this
    enum types{alg, cond, expr, op, pre_op, rel_op, set_op, var};

    oneEdge* middleNode = createOneEdgeNode(var);
    middleNode->middle = openOneEdgedNode(middleNode);
    head->middle = middleNode;
    return head;
}

noEdge* openOneEdgedNode(oneEdge* head){
    enum types{alg, cond, expr, op, pre_op, rel_op, set_op, var};
    
    noEdge* leafNode = createNoEdgeNode();
    leafNode->type = head->type;
    char* data;

    if(head->type == op)
        data = getRandomLine("op");
    else if(head->type == pre_op)
        data = getRandomLine("pre_op");
    else if(head->type == rel_op)
        data = getRandomLine("rel_op");
    else if(head->type == set_op)
        data = getRandomLine("set_op");
    else if(head->type == var)
        data = getRandomLine("var");

    if(data){
        leafNode->data = (char*)malloc(sizeof(char) * strlen(data) + 1);
        leafNode->data = strcpy(leafNode->data, data);
        free(data);
    }
        
    return leafNode;
}

void main(){
    srand(time(NULL));
    enum types{alg, cond, expr, op, pre_op, rel_op, set_op, var};
    threeEdges* root = createThreeEdgeNode(cond); // create root condition
    root = openCondition(root); // extend 
    printf("if(");
    printThreeEdgedNode(root); // print
    printf(") {}\n");
    destroyThreeEdgedNode(root); // destroy

    return;
}

