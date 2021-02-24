#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vertex* Vertex;
struct vertex {
   Vertex left;
   int key;
   Vertex right;
};

int isEmpty(Vertex);
Vertex createsVertex(int);
int addVertex(Vertex*, int);
int removeVertex(Vertex*, int);
Vertex predecessor(Vertex*);
Vertex successor(Vertex*);
int search(Vertex *, int);
void preorder(Vertex);
void inorder(Vertex);
void postorder(Vertex);
void displayNested(Vertex);
void displayIndented(Vertex, int);
void buildTree(Vertex *, char *);
void charcat(char *, char);
void clearTree(Vertex *);
int rotateVertex(Vertex *, int, int);
int leftRotation(Vertex *);
int rightRotation(Vertex *);

int main()
{
   Vertex root = NULL;

   // char *tree = "50(30(20(10),40), 70(60,80(,90)))";
   char* tree = "4(2(1,3),6(5,7))";

   printf("========================Binary Search Tree - BST========================\n");

   buildTree(&root, tree);

   //removeVertex(&root, 2);
   //removeVertex(&root, 1);

   printf("\nNested representation: ");
   displayNested(root);

   printf("\nIndented representation: \n");
   displayIndented(root, 0);
   printf("\n");

   printf("Traversals:");
   printf("\n  Preorder: ");
   preorder(root);
   printf("\n  Inorder: ");
   inorder(root);
   printf("\n  Postorder: ");
   postorder(root);
   printf("\n");

   clearTree(&root);
   
   printf("========================================================================\n\n");


   system("pause");
   return EXIT_SUCCESS;
}


int isEmpty(Vertex root) {
   return root == NULL;
}


Vertex createsVertex(int key) {
   Vertex newVertex = NULL;
   if (newVertex = (Vertex)malloc(sizeof(struct vertex))) {
      newVertex->left = NULL;
      newVertex->key = key;
      newVertex->right = NULL;
   }
   return newVertex;
}

int addVertex(Vertex* root_ptr, int data) {

   Vertex root = *root_ptr;

   if (isEmpty(root)) {
      root = createsVertex(data);
      *root_ptr = root;
      return 1;
   } else {
      if (data < root->key) {
         return addVertex(&root->left, data);
      } else {
         if (data == root->key) {
            return 0;
         } else {
            return addVertex(&root->right, data);
         }
      }
   }
}


int removeVertex(Vertex* root_ptr, int data) {
   Vertex root; //root: vértice que será removido

   if (*root_ptr == NULL) // árvore nula ou elemento a ser removido não está na árvore
      return 0;

   if (data == (*root_ptr)->key) { // vértice encontrado! A remover ...
      root = *root_ptr; // root aponta para a Raiz atual, que é o vértice a ser removido
      if ((*root_ptr)->right == NULL) { // vértice de grau 0, ou de grau 1, com sub-arvore esquerda
         *root_ptr = (*root_ptr)->left; // Raiz atual (vértice que será removido) passa a apontar para sua única sub-árvore, neste caso, a esquerda. No caso de grau 0, a sub-árvore esquerda também será nula, o que fará com que a árvore final seja nula (vazia)
      }
      else {
         if ((*root_ptr)->left == NULL)   // vértice de grau 1, com sub-árvore direita
            *root_ptr = (*root_ptr)->right; // Raiz atual (vértice que será removido) passa a apontar para sua única sub-árvore, neste caso, a direita
         else { //remoção através da troca de posição entre o elemento a ser eliminado e seu antecessor
            root = predecessor(&(root->left)); // "isola" o antecessor para ser eliminado
            (*root_ptr)->key = root->key;       // coloca a chave do antecessor na raiz da árvore ou sub-árvore
         }
      }
      free(root); // libera a memória
      return 1;
   }
   else
   {
      if (data < (*root_ptr)->key) // vértice a ser removido é menor do que a raiz da árvore ou da subárvore
         return removeVertex(&((*root_ptr)->left), data);
      else // (root->key < x) vértice a ser removido é maior do que a raiz da árvore ou da subárvore
         return removeVertex(&((*root_ptr)->right), data);
   }
}


Vertex predecessor(Vertex *root_ptr) {
   Vertex root = *root_ptr;
   if (!root->right) { // se root->right é nulo, então root é o antecessor
      *root_ptr = (*root_ptr)->left;
      return root;
   }
   else
      return predecessor(&(root->right));
}


Vertex successor(Vertex *root_ptr) {
   Vertex root = *root_ptr;
   if (!root->left) {
      *root_ptr = (*root_ptr)->right;
      return root;
   } else
      return successor(&(root->left));
}


int search(Vertex *root_ptr, int data) {
   Vertex root = *root_ptr;
   if (root) {
      if (data < root->key)
         return search(&root->left, data);
      else {
         if (data == root->key)
            return 1;
         else
            return search(&root->right, data);
      }
   }
   return 0;
}


void preorder(Vertex root_ptr) {
   Vertex root = root_ptr;
   if (root) {
      printf("%d  ", root->key);
      preorder(root->left);
      preorder(root->right);
   }
}


void inorder(Vertex root_ptr) {
   Vertex root = root_ptr;
   if (root) {
      inorder(root->left);
      printf("%d  ", root->key);
      inorder(root->right);
   }
}


void postorder(Vertex root_ptr) {
   Vertex root = root_ptr;
   if (root) {
      postorder(root->left);
      postorder(root->right);
      printf("%d  ", root->key);
   }
}


void displayNested(Vertex root_ptr) {
   Vertex root = root_ptr;
   if (root) {
      printf("%d", root->key);
      if (root->left || root->right) {
         printf("(");
         displayNested(root->left);
         if (root->right) {
            printf(",");
            displayNested(root->right);
         }
         printf(")");
      }
   }
}


void displayIndented(Vertex root_ptr, int tabs) {
   Vertex root = root_ptr;
   int i;
   if (root == NULL)
      return;
   for (i = 0; i < tabs; i++)
      printf("  ");
   printf("%d\n", root->key);
   displayIndented(root->left, tabs + 1);
   displayIndented(root->right, tabs + 1);
}

void buildTree(Vertex *root_ptr, char *tree) {
   int i, j, data;
   int size = strlen(tree);
   char aux[5] = "";
   for (i = 0; i < size; i++) {
      strcpy(aux, "");
      while ((((tree[i] != '(' && tree[i] != ')') && tree[i] != ',') && tree[i] != ' ') && tree[i] != '\0') {
         charcat(aux, tree[i]);
         i++;
      }
      if (strlen(aux) > 0) {
         data = atoi(aux);
         addVertex(root_ptr, data);
      }
   }
}


void charcat(char *palavra, char caractere)
{
   int tam = strlen(palavra);
   palavra[tam] = caractere;
   palavra[tam + 1] = '\0';
}


void clearTree(Vertex *root_ptr) {
   Vertex root = *root_ptr;
   if (root != NULL) {
      clearTree(&root->left);
      clearTree(&root->right);
      free(root);
      *root_ptr = NULL;
   }
}


int rotateVertex(Vertex *root_ptr, int data, int direction) {
   if (*root_ptr != NULL) {
      if ((*root_ptr)->key == data) { // vertice a ser rotacionado foi encontrado
         if (direction > 0)
            leftRotation(root_ptr);
         else
            rightRotation(root_ptr);
      } else {
         if (data < (*root_ptr)->key)
            rotateVertex(&(*root_ptr)->left, data, direction);
         else
            rotateVertex(&(*root_ptr)->right, data, direction);
      }
   } else
      return 0;
}


int leftRotation(Vertex *V) {
   Vertex root; // elemento que tomara o lugar de V, quando V rotacionar
   if (*V && (*V)->right) {                        // se existe um elemento para rotacionar e esse elemento possui filho à direita
      root = (*V)->right;      // guardando referencia
      (*V)->right = root->left; // o filho direito de V passa a ser o filho esquerdo de root
      root->left = *V;
      (*V) = root;
      return 1;
   }
   return 0;
}


int rightRotation(Vertex *V) {
   Vertex root;
   if (*V && (*V)->left) {
      root = (*V)->left;
      (*V)->left = root->right;
      root->right = *V;
      (*V) = root;
      return 1;
   }
   return 0;
}
