#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 5
#define COLS 6

// Non-terminal symbols
enum NonTerminals { E, Eprime, T, Tprime, F };

// Terminal symbols
enum Terminals { k, plus, mult, leftParen, rightParen, endMarker };

// Parsing table
int table[ROWS][COLS];

// Structure for nodes in the parse tree
struct TreeNode {
    char value[10];
    struct TreeNode *children[3]; // Maximum three children per node
    int numChildren;
};

// Function to create a new tree node
struct TreeNode *createNode(const char *value) {
    struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    strcpy(newNode->value, value);
    newNode->numChildren = 0;
    return newNode;
}

// Function to add a child to a tree node
void addChild(struct TreeNode *parent, struct TreeNode *child) {
    if (parent->numChildren < 3) {
        parent->children[parent->numChildren++] = child;
    } else {
        printf("Error: Maximum children limit exceeded for node %s\n", parent->value);
    }
}

// Function to initialize parsing table
void initializeTable() {
    memset(table, -1, sizeof(table));

    // Productions:
    // E  -> T E'
    table[E][k] = 1;
    table[E][leftParen] = 1;
    // E' -> + T E' | ε
    table[Eprime][plus] = 2;
    table[Eprime][rightParen] = 3;
    table[Eprime][endMarker] = 3;
    // T  -> F T'
    table[T][k] = 4;
    table[T][leftParen] = 4;
    // T' -> * F T' | ε
    table[Tprime][mult] = 5;
    table[Tprime][plus] = 6;
    table[Tprime][rightParen] = 6;
    table[Tprime][endMarker] = 6;
    // F  -> ( E ) | id
    table[F][k] = 7;
    table[F][leftParen] = 8;
}

// Display parsing table
void displayTable() {
    printf("Parsing Table:\n");
    printf("------------------------------------------------------\n");
    printf("      id    +    *    (    )    $\n");
    printf("------------------------------------------------------\n");
    
    for (int i = 0; i < ROWS; ++i) {
        switch(i) {
            case 0: printf("E   |"); break;
            case 1: printf("E'  |"); break;
            case 2: printf("T   |"); break;
            case 3: printf("T'  |"); break;
            case 4: printf("F   |"); break;
        }

        for (int j = 0; j < COLS; ++j) {
            if (table[i][j] != -1)
                printf(" %2d |", table[i][j]);
            else
                printf("    |");
        }
        printf("\n");
    }
    printf("------------------------------------------------------\n");
}

// Function to parse input and build parse tree
struct TreeNode *parseInput(const char *input) {
    struct TreeNode *root = createNode("E"); // Root of the parse tree
    struct TreeNode *currentNode = root;
    int stack[100]; // Stack to store state numbers
    int top = -1;
    stack[++top] = 0; // Starting state

    int inputIndex = 0;
    int X, a;
    X = stack[top];

    while (X != endMarker) {
        a = (input[inputIndex] == '+') ? plus : ((input[inputIndex] == '*') ? mult : ((input[inputIndex] == '(') ? leftParen : ((input[inputIndex] == ')') ? rightParen : ((input[inputIndex] == 'k') ? k : -1))));

        if (X >= 0 && X < ROWS) {
            if (a >= 0 && a < COLS) {
                if (table[X][a] != -1) {
                    int productionIndex = table[X][a];
                    switch (productionIndex) {
                        case 1: // E -> T E'
                        case 4: // T -> F T'
                            addChild(currentNode, createNode(input[inputIndex] == 'k' ? "k" : "("));
                            currentNode = currentNode->children[currentNode->numChildren - 1];
                            stack[++top] = productionIndex;
                            break;
                        case 2: // E' -> + T E'
                        case 5: // T' -> * F T'
                            addChild(currentNode, createNode(input[inputIndex] == '+' ? "+" : "*"));
                            currentNode = currentNode->children[currentNode->numChildren - 1];
                            stack[++top] = productionIndex;
                            break;
                        case 3: // E' -> ε
                        case 6: // T' -> ε
                            top--;
                            break;
                        case 7: // F -> id
                            addChild(currentNode, createNode("k"));
                            break;
                        case 8: // F -> ( E )
                            addChild(currentNode, createNode("("));
                            currentNode = currentNode->children[currentNode->numChildren - 1];
                            stack[++top] = productionIndex;
                            break;
                        case 9: // F -> id
                            addChild(currentNode, createNode(input[inputIndex] == 'k' ? "k" : ")"));
                            break;
                    }
                } else {
                    printf("Accepted\n");
                    return NULL;
                }
            } else {
                printf("Invalid input symbol.\n");
                return NULL;
            }
        } else {
            printf("Invalid symbol popped from stack.\n");
            return NULL;
        }
        X = stack[top];
        if (a != -1 && input[inputIndex] != '\0') {
            inputIndex++;
        }
    }

    return root;
}

// Function to print parse tree (DFS traversal)
void printParseTree(struct TreeNode *root, int level) {
    if (root == NULL) return;

    for (int i = 0; i < level; ++i)
        printf("  ");
    printf("%s\n", root->value);

    for (int i = 0; i < root->numChildren; ++i)
        printParseTree(root->children[i], level + 1);
}

int main() {
    initializeTable();
    displayTable();

    const char *input = "k+k*k"; // Input string
    printf("Input: %s\n", input);

    struct TreeNode *parseTree = parseInput(input);
    if (parseTree != NULL) {
        printf("\nParse Tree:\n");
        printParseTree(parseTree, 0);
    }

    return 0;
}
