#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100
#define MAX_CHILDREN 10
#define NO_DISCOUNT -1.0f

typedef enum {
    CATEGORY,
    PRODUCT
} NodeType;

typedef struct Node {
    char name[MAX_NAME];
    NodeType type;
    float discount;              // NO_DISCOUNT se non definito
    float base_price;            // usato solo per i prodotti
    struct Node* children[MAX_CHILDREN];
    int num_children;
} Node;

/* Crea un nodo categoria */
Node* create_category(const char* name, float discount) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "Errore di allocazione memoria\n");
        exit(EXIT_FAILURE);
    }

    strncpy(node->name, name, MAX_NAME - 1);
    node->name[MAX_NAME - 1] = '\0';
    node->type = CATEGORY;
    node->discount = discount;
    node->base_price = 0.0f;
    node->num_children = 0;

    for (int i = 0; i < MAX_CHILDREN; i++) {
        node->children[i] = NULL;
    }

    return node;
}

/* Crea un nodo prodotto */
Node* create_product(const char* name, float base_price, float discount) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "Errore di allocazione memoria\n");
        exit(EXIT_FAILURE);
    }

    strncpy(node->name, name, MAX_NAME - 1);
    node->name[MAX_NAME - 1] = '\0';
    node->type = PRODUCT;
    node->discount = discount;
    node->base_price = base_price;
    node->num_children = 0;

    for (int i = 0; i < MAX_CHILDREN; i++) {
        node->children[i] = NULL;
    }

    return node;
}

/* Aggiunge un figlio a un nodo */
void add_child(Node* parent, Node* child) {
    if (parent == NULL || child == NULL) {
        fprintf(stderr, "Nodo nullo in add_child\n");
        exit(EXIT_FAILURE);
    }

    if (parent->num_children >= MAX_CHILDREN) {
        fprintf(stderr, "Troppi figli per il nodo %s\n", parent->name);
        exit(EXIT_FAILURE);
    }

    parent->children[parent->num_children++] = child;
}

/* Visita preorder: propaga lo sconto dall'alto verso il basso */
void calcola_prezzi(Node* node, float current_discount) {
    if (node == NULL) {
        return;
    }

    float effective_discount;

    if (node->discount != NO_DISCOUNT) {
        effective_discount = node->discount;
    } else {
        effective_discount = current_discount;
    }

    if (node->type == PRODUCT) {
        float final_price = node->base_price * (1.0f - effective_discount / 100.0f);
        printf("%s -> prezzo finale: %.2f\n", node->name, final_price);
    }

    for (int i = 0; i < node->num_children; i++) {
        calcola_prezzi(node->children[i], effective_discount);
    }
}

/* Libera tutta la memoria dell'albero */
void free_tree(Node* node) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < node->num_children; i++) {
        free_tree(node->children[i]);
    }

    free(node);
}

int main(void) {
    /*
        Istanza di esempio:

        E-commerce (sconto = 10%)
        |-- Abbigliamento (sconto = 20%)
        |   |-- Donna
        |   |   |-- Vestito estivo (prezzo = 50)
        |   |   \-- Borsa elegante (prezzo = 80, sconto = 30%)
        |   \-- Uomo
        |       \-- Camicia (prezzo = 40)
        |-- Cosmetici
        |   |-- Skincare (sconto = 15%)
        |   |   \-- Crema viso (prezzo = 30)
        |   \-- Make-up
        |       \-- Rossetto (prezzo = 20)
        \-- Tecnologia
            \-- Smartphone (prezzo = 500, sconto = 5%)
    */

    Node* ecommerce = create_category("E-commerce", 10.0f);

    Node* abbigliamento = create_category("Abbigliamento", 20.0f);
    Node* donna = create_category("Donna", NO_DISCOUNT);
    Node* uomo = create_category("Uomo", NO_DISCOUNT);

    Node* vestito = create_product("Vestito estivo", 50.0f, NO_DISCOUNT);
    Node* borsa = create_product("Borsa elegante", 80.0f, 30.0f);
    Node* camicia = create_product("Camicia", 40.0f, NO_DISCOUNT);

    Node* cosmetici = create_category("Cosmetici", NO_DISCOUNT);
    Node* skincare = create_category("Skincare", 15.0f);
    Node* makeup = create_category("Make-up", NO_DISCOUNT);

    Node* crema = create_product("Crema viso", 30.0f, NO_DISCOUNT);
    Node* rossetto = create_product("Rossetto", 20.0f, NO_DISCOUNT);

    Node* tecnologia = create_category("Tecnologia", NO_DISCOUNT);
    Node* smartphone = create_product("Smartphone", 500.0f, 5.0f);

    add_child(ecommerce, abbigliamento);
    add_child(ecommerce, cosmetici);
    add_child(ecommerce, tecnologia);

    add_child(abbigliamento, donna);
    add_child(abbigliamento, uomo);

    add_child(donna, vestito);
    add_child(donna, borsa);
    add_child(uomo, camicia);

    add_child(cosmetici, skincare);
    add_child(cosmetici, makeup);

    add_child(skincare, crema);
    add_child(makeup, rossetto);

    add_child(tecnologia, smartphone);

    printf("Risultati del test:\n\n");
    calcola_prezzi(ecommerce, 0.0f);

    /*
        Output atteso:

        Vestito estivo -> prezzo finale: 40.00
        Borsa elegante -> prezzo finale: 56.00
        Camicia -> prezzo finale: 32.00
        Crema viso -> prezzo finale: 25.50
        Rossetto -> prezzo finale: 18.00
        Smartphone -> prezzo finale: 475.00
    */

    free_tree(ecommerce);

    return 0;
}