#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct VizierRecord{
    char name[50];
    int start_year;
    int end_year;
    int income;
} VizierRecord;

typedef struct Node {
    VizierRecord data;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    int height;
} Node;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(Node* node) {
    return node ? node->height : -1;
}


Node* search(Node* root, int target_year) {
    if(root == NULL) {
        printf("No record found!");
        return NULL;
    }

    if(root -> data.start_year > target_year) {
        return search(root -> left, target_year);
    } else if( root -> data.start_year < target_year) {
        return search(root -> right, target_year);
    }

    return root;
}



Node* findSuccessor(Node* node) {
    if (node == NULL) return NULL;

    if(node -> right != NULL) {
        Node* curr = node -> right;
        while(curr -> left != NULL) {
            curr = curr -> left;
        }
        return curr;
    }

    Node* curr = node;
    Node* parent = node -> parent;

    while (parent != NULL && curr == parent->right) {
        curr = parent;
        parent = parent->parent;
    }

    return parent;

}

Node* findPredecessor(Node* node) {
    if (node == NULL) return NULL;


    if (node->left != NULL) {
        Node* curr = node->left;
        while (curr->right != NULL)
            curr = curr->right;
        return curr;
    }


    Node* curr = node;
    Node* parent = node->parent;

    while (parent != NULL && curr == parent->left) {
        curr = parent;
        parent = parent->parent;
    }

    return parent;
}


static void printSuccessors(Node* root, int window) {



    return;
}
static void printPredecessors(Node* root, int window) {
    Node* pred = findPredecessor(root);
    Node* succ = findSuccessor(root);

    for (int i = 0; i < window; i++) {
        if (pred == NULL) {
            printf("Not enough predecessors.\n");
            return;
        }
        printf("  (<<) PREDECESSOR: %s, (%d Akce) \n", pred->data.name, pred->data.income);
        pred = findPredecessor(pred);
    }
    for(int i = 0; i < window; ++i) {
        if(succ == NULL) {
            printf("Not enough predecessors.\n");
            return;
        }
        printf("  (>>) SUCCESSOR: %s, (%d Akce) \n", succ -> data.name, succ -> data.income);
        succ = findSuccessor(succ);

    }

}



static VizierRecord const history [] = {
    { " Lutfi Pasa " , 1539 , 1541 , 155000} ,
    { " Mahmud Pasa " , 1456 , 1468 , 4000000} ,
    { " Piri Mehmed " , 1518 , 1523 , 145000} ,
    { " Candarli Ali " , 1387 , 1406 , 82000} ,
    { " Sokollu Mehmed " , 1565 , 1579 , 2000000} ,
    { " Pargali Ibrahim " , 1523 , 1536 , 3000000} ,
    { " Koca Sinan " , 1580 , 1582 , 210000} ,
    { " Alaeddin Pasa " , 1320 , 1331 , 50000} ,
    { " Kemankes Mustafa " , 1638 , 1644 , 230000} ,
    { " Gedik Ahmed " , 1474 , 1477 , 115000} ,
    { " Koprulu Mehmed " , 1656 , 1661 , 260000} ,
    { " Ayas Mehmed " , 1536 , 1539 , 160000} ,
    { " Kuyucu Murad " , 1606 , 1611 , 220000} ,
    { " Candarli Halil " , 1364 , 1387 , 75000} ,
    { " Rustem Pasa " , 1544 , 1553 , 2800000} ,
    { " M erz if onl u Kara " , 1676 , 1683 , 290000} ,
    { " Semiz Ali " , 1561 , 1565 , 170000} ,
    { " Ferhad Pasa " , 1591 , 1592 , 190000} ,
    { " Nevsehirli Damat " , 1718 , 1730 , 240000} ,
};

int height(Node* node) {
    return node ? node->height : -1;
}

Node* rightRotate(Node* root) {

    Node* leftNode = root -> left;
    Node* temp = leftNode -> right;

    leftNode -> right = root;
    root -> left = temp;

    leftNode -> parent = root -> parent;
    root -> parent = leftNode;
    if (temp != NULL) temp->parent = root;

    if (leftNode -> parent != NULL) {
        if (leftNode -> parent -> left == root) {
            leftNode -> parent -> left = leftNode;
        }
        else {
            leftNode -> parent -> right = leftNode;
        }
    }
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    leftNode->height = 1 + max(getHeight(leftNode->left), getHeight(leftNode->right));
    return leftNode;
}

Node* leftRotate(Node* root) {

    Node* rightNode = root -> right;
    Node* temp = rightNode -> left;

    rightNode -> left = root;
    root -> right = temp;

    rightNode -> parent = root -> parent;
    root-> parent = rightNode;
    if(temp != NULL) temp -> parent = root;

    if(rightNode -> parent != NULL) {
        if(rightNode-> parent -> left == root) {
            rightNode-> parent -> left = rightNode;
        }
        else {
            rightNode-> parent -> right = rightNode;
        }
    }
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    rightNode->height = 1 + max(getHeight(rightNode->left), getHeight(rightNode->right));

    return rightNode;
}

Node* insertVizier(Node* root, VizierRecord record) {
if(root == NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode -> left = NULL;
        newNode -> right = NULL;
        newNode -> parent = NULL;

        strcpy(newNode -> data.name, record.name);
        newNode -> data.income = record.income;
        newNode -> data.end_year = record.end_year;
        newNode -> data.start_year = record.start_year;
        newNode -> height = 0;

        return newNode;
    }
    else if(root -> data.start_year > record.start_year) {
        root -> left = insertVizier(root->left, record);
        if (root->left != NULL) root->left->parent = root;

    }
    else if (root -> data.start_year < record.start_year) {
        root -> right = insertVizier(root -> right, record);
        if (root->right != NULL) root->right->parent = root;
    }

    root -> height = 1 + max(height(root->left), height(root->right));

    int bf = getHeight(root->left) - getHeight(root->right);


    if (bf > 1) {
        int leftBF = getHeight(root->left->left) - getHeight(root->left->right);

        if (leftBF >= 0)
            return rightRotate(root);
        else {
            root->left = leftRotate(root->left);
            root->left->parent = root;
            return rightRotate(root);
        }
    }

    if (bf < -1) {
        int rightBF = getHeight(root->right->left) - getHeight(root->right->right);

        if (rightBF <= 0)
            return leftRotate(root);
        else {
            root->right = rightRotate(root->right);
            root->right->parent = root;
            return leftRotate(root);
        }
    }



    return root;
}



int main() {
    Node* root = NULL;
    int n = sizeof(history) / sizeof(history[0]);

    for (int i = 0; i < n; i++)
        root = insertVizier(root, history[i]);

    int start_year;
    int window;
    printf("Please write the start year: ");
    scanf("%d", &start_year);
    printf("Please write the window size: ");
    scanf("%d", &window);

    Node* x = search(root, start_year);

    if (x) {
        printf("--- QUERY:  %d (%s) --- \n", start_year, x -> data.name);
        printf("[ TARGET ] \n");
        printf("   > %s (%d Akce) \n\n", x-> data.name, x -> data.income);
        printf("[ NEIGHBOR COMPARISON (WINDOW: %d) ] \n", window);

        printPredecessors(x, window);
        printSuccessors(x, window);
    }

    return 0;
}