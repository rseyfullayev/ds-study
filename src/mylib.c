#include "../include/mylib.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    int bf;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
} TreeNode;


// Right Rotation

TreeNode* rightRotate(TreeNode* root) {

    TreeNode* leftNode = root -> left;
    TreeNode* temp = leftNode -> right;

    leftNode -> right = root;
    root -> left = temp;

    return leftNode;
}

// Left Rotation

TreeNode* leftRotate(TreeNode* root) {

    TreeNode* rightNode = root -> right;
    TreeNode* temp = rightNode -> left;

    rightNode -> left = root;
    root -> right = temp;

    return root-> right;
}


int height(TreeNode* root) {
    if(root == NULL) {
        return 0;
    }
    return 1 + max(height(root-> right) + height ( root-> left));
}



TreeNode* insertNode(TreeNode* root, int data) {
    if(root == NULL) {
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        newNode -> left = NULL;
        newNode -> right = NULL;
        newNode -> data = data;
        newNode -> bf = 0;

        return newNode;
    }
    else if(root -> data > data) {
        root -> left = insertNode(root->left, data);
    }
    else if (root -> data < data) {
        root -> right = insertNode(root -> right, data);
    }

    // Calculate the BF

    root -> bf = height(root->left) - height(root -> right);


    // Rotations if necessary


    if(root -> bf > 1 && root -> left -> bf >= 0) {
        root = rightRotate(root);
    }
    else if(root -> bf > 1 && root -> left -> bf <= 0) {
        root -> left = leftRotate(root-> left);
        root = rightRotate(root);
    }
    else if(root -> bf < -1 && root -> right -> bf <= 0) {
        root = leftRotate(root);
    }
    else {
        root -> right = rightRotate(root->right);
        root = leftRotate(root);
    }



    return root;
}

TreeNode* findLeastSuccessor(TreeNode* root) {
    if(root -> left == NULL) {
        return root;
    }
    return findLeastSuccessor(root -> left);
}
TreeNode* search(TreeNode* root, int data) {
    if(root -> data == data) {
        return root;
    }
    else if( root -> data > data) {
        return search(root -> left, data);
    }
    else if( root -> data < data) {
        return search(root -> right, data);
    }
    else {
        printf("No Node found!");
        return NULL;
    }

}

TreeNode* delete(TreeNode* root, int data) {
    if(root == NULL) {
        printf("Nothing to delete!");
    }
    else if(root -> data > data) {
        root -> left = delete(root->left, data);
    }
    else if (root -> data < data) {
        root -> right = delete(root -> right, data);
    }
    else {
        // No child case
        if( root -> left == NULL && root -> right == NULL) {
            free(root);
            return NULL;
        }
        else if(root -> left != NULL && root -> right != NULL) {
            TreeNode* leastSuccessor = findLeastSuccessor(root -> right);
            root -> data = leastSuccessor -> data;
            root -> right = delete(root -> right, leastSuccessor-> data);
        }
        else {
            // One child case
            if(root -> left != NULL) {
                TreeNode* temp = root -> left;
                free(root);
                return temp;
            } else {
                TreeNode* temp = root -> right;
                free(root);
                return temp;
            }

        }
    }

    root -> bf = height(root->left) - height(root -> right);


    // Rotations if necessary


    if(root -> bf > 1 && root -> left -> bf >= 0) {
        root = rightRotate(root);
    }
    else if(root -> bf > 1 && root -> left -> bf <= 0) {
        root -> left = leftRotate(root-> left);
        root = rightRotate(root);
    }
    else if(root -> bf < -1 && root -> right -> bf <= 0) {
        root = leftRotate(root);
    }
    else {
        root -> right = rightRotate(root->right);
        root = leftRotate(root);
    }


    return root;
}

int main() {


    return 0;
}