#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

using namespace std;

//Global Node
struct Node {
    int data;
    Node* left;
    Node* right;
};

void gotoxy(int x,int y);
Node* creatNode(int data);
int getHeight(Node * root);
int getBalanceFactor(Node * n);
Node* rightRotate(Node* root);
Node* leftRotate(Node* root);
Node* insertNode(Node* root, int data);
Node* findMin(Node* root);
Node* finMax(Node* root);
struct Node* deleteNode(Node* root, int data);
void printTreeHelper(Node* root, int x, int y, int offset);
void printTree(Node* root);
bool searchGeneral(Node* root, int data);

int main(){

  Node* root = NULL;

  int option, val;

  do {
    system("cls");
    cout << "**********MENU PRINCIPAL**********" << endl;
    cout << "1. Ingresar dato al arbol" << endl;
    cout << "2. Buscar dato en el arbol" << endl;
    cout << "3. Eliminar dato en el arbol" << endl;
    cout << "4. Mostrar datos del arbol" << endl;
    cout << "5. Mostrar altura del arbol" << endl;
    cout << "0. Exit Program" << endl;

    cin >> option;

    switch (option) {
    case 0:
      break;
    case 1:
      system("cls");
      cout << "**********INGRESO DE DATOS AL ARBOL AVL**********" << endl;
      cout << "Ingrese el valor: ";
      cin >> val;

      root = insertNode(root, val);
      cout << endl;
      getch();
      break;
    case 2:
      system("cls");
      cout << "**********BUSCAR DATO EN EL ARBOL AVL**********" << endl;
      cout << "Ingrese el valor a buscar: ";
      cin >> val;

      if(searchGeneral(root, val) == true){
        cout<< "Se encontro una coincidencia con su numero: " << val;
      } else {
        cout << "No se encontro el numero en el arbol";
      }
      getch();
      break;
    case 3:
      system("cls");
      cout << "**********ELIMINAR DATOS DEL ARBOL AVL**********" << endl;
      cout << "Ingrese el valor a eliminar: ";
      cin >> val;
      //root = recursiveSearch(root, val);
      if (searchGeneral(root, val) == true) {
        root = deleteNode(root, val);
        cout << "Valor eliminado exitosamente" << endl;
      } else {
        cout << "El valor a eliminar no se encontro en el arbol" << endl;
      }
      getch();
      break;
    case 4:
      system("cls");
      cout << "**********IMPRESION 2D ARBOL AVL**********" << endl;
      printTree(root);
      cout << endl;
      getch();
      break;
    case 5:
      system("cls");
      cout << "**********ALTURA DEL ARBOL AVL**********" << endl;
      cout << "Altura : " << getHeight(root) << endl;
      getch();
      break;
    default:
      cout << "Ingrese un numero valido en las opciones dadas" << endl;
    }

  } while (option != 0);

  return 0;
}

// Función para mover el cursor a una posición específica en la consola
void gotoxy(int x,int y){
    HANDLE hcon; // Declarar un manejador de consola
    hcon = GetStdHandle(STD_OUTPUT_HANDLE); // Obtener el manejador de salida estándar
    COORD dwPos; // Crear una estructura COORD para las coordenadas de la posición
    dwPos.X = x; // Establecer la coordenada X
    dwPos.Y= y; // Establecer la coordenada Y
    SetConsoleCursorPosition(hcon,dwPos); // Mover el cursor a la posición especificada
}

// Función para crear un nuevo nodo en un árbol binario
Node* creatNode(int data){
    Node* newNode = new Node(); // Crear un nuevo nodo y asignar memoria para él
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Función para obtener la altura de un nodo en un árbol binario
int getHeight(Node* root) {
    if (root == NULL){ // Si el nodo es NULL, la altura es -1
        return -1;
    } else {
        
        int leftHeight = getHeight(root->left); // Altura SI
        int rightHeight = getHeight(root->right); // Altura SD

        // Retornar la mayor altura entre los subárboles izquierdo y derecho, más uno
        if (leftHeight > rightHeight){
            return (leftHeight + 1);
        } else {
            return (rightHeight + 1);
        }
    }
}

// Función para obtener el factor de balance
int getBalanceFactor(Node* n) {
    if (n == NULL) // Si es NULL, el factor de balance es -1
        return -1;
    // Retorna el factor de balance, altura del subárbol izquierdo menos altura del subárbol derecho
    return getHeight(n->left) - getHeight(n->right);
}

// Rotacion Derecha-Derecha
Node* rightRotate(Node* root) {
    Node * temp1 = root->left; // Almacena hijo izquierdo
    Node * temp2 = temp1->right; // Almacena SD de temp2

    // Realiza rotacion
    temp1->right = root; // Raiz actual como hijo derecho de temp1
    root->left = temp2; // Temp2 como hijo izquierdo de la nueva raiz

    //Retorna nueva raiz del subarbol
    return temp1;
}

// Rotacion Izquierda-Izquierda
Node* leftRotate(Node* root) {
    Node * temp1 = root->right; // Almacena hijo derecho
    Node * temp2 = temp1->left; // Almacena SI en temp2

    // Realiza rotacion
    temp1->left = root; // Raiz actual como hijo derecho de temp1
    root->right = temp2; // Temp2 como hijo derecho de la nueva raiz

    return temp1;
}

// Función para insertar un nodo en el árbol AVL y balancearlo
Node* insertNode(Node* root, int data) {
    if (root == NULL) { // Si el árbol está vacío, crea un nuevo nodo y lo retorna como la nueva raíz
      root = creatNode(data);
      cout << "Value inserted successfully" << endl;
      return root;
    }

    if (data < root->data) { // Menor a la raiz, insertar izquierda
      root->left = insertNode(root->left, data);
    } else if (data > root->data) { // Mayor a la raiz, insertar derecha
      root->right = insertNode(root->right, data);
    } else { 
      cout << "No duplicate values allowed!" << endl;
      return root;
    }

    int balanceFactor = getBalanceFactor(root);

    //Caso 1: Rotacion Izquierda-Izquierda / Left Left Case
    if (balanceFactor > 1 && data < root->left->data)
      return rightRotate(root);

    //Caso 2: Rotacion Derecha-Derecha / Right Right Case
    if (balanceFactor < -1 && data > root->right->data)
      return leftRotate(root);

    //Caso 3: Rotacion Izquierda-Derecha / Left Right Case
    if (balanceFactor > 1 && data > root->left->data) {
      root->left = leftRotate(root->left);
      return rightRotate(root);
    }

    //Caso 4: Rotacion Derecha-Izquierda - Right Left Case
    if (balanceFactor < -1 && data < root->right->data) {
      root->right = rightRotate(root->right);
      return leftRotate(root);
    }

    //Retorna la raiz del arbol//
    return root;
}

Node* findMin(Node* root) {
    if(root == NULL){
        cout << "Error: Tree is empty\n";
        return 0;
    }

	  while(root->left != NULL) {
        root = root->left;
	  }
    
	  return root;
}

Node* finMax(Node* root) {
    if(root == NULL){
        cout << "Error: Tree is empty\n";
        return 0;
    }

	  while(root->right != NULL) {
        root = root->right;
	  }

	  return root;
}

//Función para eliminar un nodo en un árbol AVL
struct Node* deleteNode(Node* root, int data){
    if(root == NULL) { // Si el árbol está vacío, simplemente retorna la raíz
        return root;
    } else if(data < root->data) { // Si es menor que el valor de la raíz, busca en el subárbol izquierdo
        root->left = deleteNode(root->left, data);
    } else if(data > root->data){ // Si es mayor que el valor de la raíz, busca en el subárbol derecho
        root->right = deleteNode(root->right, data);
    } else {
        //Caso 1: Rama sin hijo
        if(root->left == NULL && root->right == NULL){
            delete root;
            root = NULL;
            return root; // Retorna Null
        }
        //Caso 2: Rama con un hijo
        else if(root->left == NULL){ // (derecho)
            struct Node *temp = root; // Nodo a eliminar
            root = root->right; // Remplaza con hijo derecho
            delete temp;
            return root; // Retorna la raiz del subarbol
        } else if(root->right == NULL){ // (izquierdo)
            struct Node *temp = root;
            root = root->left; // Remplaza con hijo izquierdo
            delete temp;
            return root;
        }
        //Caso 3: Rama tiene dos hijos
        else {
            struct Node* temp = finMax(root->left); // Nodo +D del SI
            root->data = temp->data; // Copia valor en la posicion que se eliimnara
            root->left = deleteNode(root->left, temp->data); // Elimina nodo duplica en SI
        }
    }

    int balanceFactor = getBalanceFactor(root);

    if (balanceFactor > 1 && getBalanceFactor(root->left) >= 0) // (RII)
        return rightRotate(root);

    if (balanceFactor > 1 && getBalanceFactor(root->left) < 0) { // (RID)
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balanceFactor < -1 && getBalanceFactor(root->right) <= 0) // (RDD)
        return leftRotate(root);

    if (balanceFactor < -1 && getBalanceFactor(root->right) > 0) { // (RDI)
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void printTreeHelper(Node* root, int x, int y, int offset) {
    if (root == NULL) // Si el nodo es NULL, no hay nada que imprimir
        return;

    gotoxy(x, y); // Posición (x, y) en la consola y imprime el valor del nodo actual
    cout << root->data;

    if (root->left != NULL) { // Hijo Izquierdo
        gotoxy(x - offset / 2, y + 2); // Dibuja diagonal izquierda
        cout << "/";
        // Funcion Recursiva para el hijo izquierdo con una nueva posición y offset reducido
        printTreeHelper(root->left, x - offset, y + 4, offset / 2);
    }

    if (root->right != NULL) { //Hijo Derecho
        gotoxy(x + offset / 2, y + 2); // Dibuja diagonal derecha
        cout << "\\";
        printTreeHelper(root->right, x + offset, y + 4, offset / 2);
    }
}

// Función principal para iniciar la impresión del árbol
void printTree(Node* root) {
    // Coordenada horizontal inicial, ajustable para centrar el árbol
    int initial_x = 40; // Adjust this value for horizontal centering

    // Coordenada vertical inicial, comienza a imprimir desde la parte superior de la consola
    int initial_y = 2;  // Start printing from the top of the console

    // Offset inicial para la distancia entre nodos hijo
    int offset = 20;    // Initial offset for child nodes

    // Llama a la función auxiliar con los valores iniciales
    printTreeHelper(root, initial_x, initial_y, offset);
}

// Función para buscar un valor en un árbol binario
bool searchGeneral(Node* root, int data){
    if(root == NULL) { // Si el nodo es NULL, el valor no está en el árbol
        return false;
    }else if(root->data == data) { // Si el nodo actual contiene el valor buscado, retorna true
        return true;
    }else if(data <= root->data) { // Si es menor o igual al valor del nodo actual, busca en el subárbol izquierdo
        return searchGeneral(root->left, data);
    }else { // Si es mayor que el valor del nodo actual, busca en el subárbol derecho
        return searchGeneral(root->right, data);
    }
}
