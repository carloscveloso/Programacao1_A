/*
// Estrutura para armazenar informação sobre uma propriedade
struct Propriedade {
    char tipo[50]; 
    char endereco[100]; 
    double preco;
    struct Propriedade *prev;
    struct Propriedade *next;
} Propriedade;

typedef struct Node{
    struct Node *prev;
    struct Node *next;
    int data;
} Node;

Node *head = NULL;
Node *tail = NULL;

Node *createNode(int data){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void appendNode(Node** head, Node** tail, int data) {
    Node* newNode = createNode(data);
    if (*tail == NULL) {
        *head = newNode;
        *tail = newNode;
    } else {
        (*tail)->next = newNode;
        newNode->prev = *tail;
        *tail = newNode;
    }
}

void prependNode(Node** head, Node** tail, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        *tail = newNode;
    } else {
        (*head)->prev = newNode;
        newNode->next = *head;
        *head = newNode;
    }
}


void deleteNode(Node** head, Node** tail, Node* nodeToDelete) {
    if (nodeToDelete == NULL) return;

    if (nodeToDelete == *head) {
        *head = nodeToDelete->next;
    }
    if (nodeToDelete == *tail) {
        *tail = nodeToDelete->prev;
    }
    if (nodeToDelete->prev != NULL) {
        nodeToDelete->prev->next = nodeToDelete->next;
    }
    if (nodeToDelete->next != NULL) {
        nodeToDelete->next->prev = nodeToDelete->prev;
    }

    free(nodeToDelete);
}

void printListFromHead(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void printListFromTail(Node* tail) {
    Node* current = tail;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->prev;
    }
    printf("\n");
}


*/