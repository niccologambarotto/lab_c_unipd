#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char nome[64];
    int sv_match;           // set vinti nel match contro il fratello
    int sv_tot;             // set vinti totali nel torneo
    int sp_tot;             // set persi totali nel torneo
    struct Node *left;
    struct Node *right;
} Node;

/* =========================================================
   Creazione nodi
   ========================================================= */

Node *create_leaf(const char *nome) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (n == NULL) {
        fprintf(stderr, "Errore: memoria insufficiente.\n");
        exit(EXIT_FAILURE);
    }

    strncpy(n->nome, nome, sizeof(n->nome) - 1);
    n->nome[sizeof(n->nome) - 1] = '\0';

    n->sv_match = 0;
    n->sv_tot = 0;
    n->sp_tot = 0;
    n->left = NULL;
    n->right = NULL;

    return n;
}

/*
 * Crea un nodo interno che rappresenta il vincitore del match tra left e right.
 * left_sets/right_sets = set vinti dai due figli nel match corrente.
 */
Node *create_match(Node *left, Node *right,
                   const char *winner_name,
                   int left_sets, int right_sets) {
    Node *parent = create_leaf(winner_name);
    parent->left = left;
    parent->right = right;

    left->sv_match = left_sets;
    right->sv_match = right_sets;

    return parent;
}

/* =========================================================
   Visita post-order
   ========================================================= */

/*
 * Calcola sv_tot/sp_tot con una sola visita post-order.
 * Stampa il perdente quando termina il suo torneo.
 */
void postorder_compute_and_print(Node *x) {
    if (x == NULL) {
        return;
    }

    /* foglia */
    if (x->left == NULL && x->right == NULL) {
        x->sv_tot = 0;
        x->sp_tot = 0;
        return;
    }

    postorder_compute_and_print(x->left);
    postorder_compute_and_print(x->right);

    Node *L = x->left;
    Node *R = x->right;

    /* aggiorna i due giocatori con il match corrente */
    L->sv_tot += L->sv_match;
    L->sp_tot += R->sv_match;

    R->sv_tot += R->sv_match;
    R->sp_tot += L->sv_match;

    Node *winner = NULL;
    Node *loser = NULL;

    if (strcmp(x->nome, L->nome) == 0) {
        winner = L;
        loser = R;
    } else if (strcmp(x->nome, R->nome) == 0) {
        winner = R;
        loser = L;
    } else {
        fprintf(stderr,
                "Errore strutturale: il padre '%s' non coincide con nessun figlio ('%s', '%s').\n",
                x->nome, L->nome, R->nome);
        exit(EXIT_FAILURE);
    }

    /* il nodo corrente eredita i totali del vincitore */
    x->sv_tot = winner->sv_tot;
    x->sp_tot = winner->sp_tot;

    /* il perdente esce dal torneo: stampa finale */
    printf("%-22s sv_tot=%2d sp_tot=%2d\n",
           loser->nome, loser->sv_tot, loser->sp_tot);
}

/* =========================================================
   Deallocazione
   ========================================================= */

void free_tree(Node *x) {
    if (x == NULL) {
        return;
    }
    free_tree(x->left);
    free_tree(x->right);
    free(x);
}

/* =========================================================
   Costruzione del tabellone Montecarlo 2026
   SENZA bye:
   - le teste di serie entrano direttamente al turno successivo
   - l'albero resta binario proprio
   ========================================================= */

Node *build_montecarlo_2026_tree(void) {
    /* ===================== SEZIONE 1 ===================== */
    Node *a1 = create_match(create_leaf("S. Baez"), create_leaf("S. Wawrinka"),
                            "S. Baez", 2, 0);
    Node *a2 = create_match(create_leaf("T. Etcheverry"), create_leaf("G. Dimitrov"),
                            "T. Etcheverry", 2, 1);
    Node *a3 = create_match(create_leaf("T. Atmane"), create_leaf("E. Quinn"),
                            "T. Atmane", 2, 0);
    Node *a4 = create_match(create_leaf("J. Lehecka"), create_leaf("E. Nava"),
                            "J. Lehecka", 2, 1);
    Node *a5 = create_match(create_leaf("M. Fucsovics"), create_leaf("A. Tabilo"),
                            "A. Tabilo", 0, 2);
    Node *a6 = create_match(create_leaf("G. Monfils"), create_leaf("T. Griekspoor"),
                            "G. Monfils", 2, 1);

    Node *a7 = create_match(create_leaf("C. Alcaraz"), a1,
                            "C. Alcaraz", 2, 0);
    Node *a8 = create_match(a2, a3,
                            "T. Etcheverry", 2, 1);
    Node *a9 = create_match(a4, a5,
                            "J. Lehecka", 2, 1);
    Node *a10 = create_match(a6, create_leaf("A. Bublik"),
                             "A. Bublik", 0, 2);

    Node *a11 = create_match(a7, a8,
                             "C. Alcaraz", 2, 1);
    Node *a12 = create_match(a9, a10,
                             "A. Bublik", 0, 2);

    Node *qf1 = create_match(a11, a12,
                             "C. Alcaraz", 2, 0);

    /* ===================== SEZIONE 2 ===================== */
    Node *b1 = create_match(create_leaf("V. Vacherot"), create_leaf("J. Cerundolo"),
                            "V. Vacherot", 2, 1);
    Node *b2 = create_match(create_leaf("D. Dzumhur"), create_leaf("F. Marozsan"),
                            "F. Marozsan", 0, 2);
    Node *b3 = create_match(create_leaf("H. Hurkacz"), create_leaf("L. Darderi"),
                            "H. Hurkacz", 2, 1);
    Node *b4 = create_match(create_leaf("F. Cobolli"), create_leaf("F. Comesana"),
                            "F. Cobolli", 2, 1);
    Node *b5 = create_match(create_leaf("D. Shapovalov"), create_leaf("A. Blockx"),
                            "A. Blockx", 1, 2);
    Node *b6 = create_match(create_leaf("C. Norrie"), create_leaf("M. Kecmanovic"),
                            "C. Norrie", 2, 1);

    Node *b7 = create_match(create_leaf("L. Musetti"), b1,
                            "V. Vacherot", 0, 2);
    Node *b8 = create_match(b2, b3,
                            "H. Hurkacz", 0, 2);
    Node *b9 = create_match(b4, b5,
                            "A. Blockx", 0, 2);
    Node *b10 = create_match(b6, create_leaf("A. de Minaur"),
                             "A. de Minaur", 1, 2);

    Node *b11 = create_match(b7, b8,
                             "V. Vacherot", 2, 1);
    Node *b12 = create_match(b9, b10,
                             "A. de Minaur", 0, 2);

    Node *qf2 = create_match(b11, b12,
                             "V. Vacherot", 2, 1);

    /* ===================== SEMIFINALE ALTA ===================== */
    Node *sf1 = create_match(qf1, qf2,
                             "C. Alcaraz", 2, 0);

    /* ===================== SEZIONE 3 ===================== */
    Node *c1 = create_match(create_leaf("R. Bautista Agut"), create_leaf("M. Berrettini"),
                            "M. Berrettini", 0, 0);   /* ritiro */
    Node *c2 = create_match(create_leaf("J. Fonseca"), create_leaf("G. Diallo"),
                            "J. Fonseca", 2, 0);
    Node *c3 = create_match(create_leaf("A. Rinderknech"), create_leaf("K. Khachanov"),
                            "A. Rinderknech", 2, 0);
    Node *c4 = create_match(create_leaf("A. Rublev"), create_leaf("N. Borges"),
                            "A. Rublev", 2, 1);
    Node *c5 = create_match(create_leaf("Z. Bergs"), create_leaf("A. Mannarino"),
                            "Z. Bergs", 2, 0);
    Node *c6 = create_match(create_leaf("C. Garin"), create_leaf("M. Arnaldi"),
                            "C. Garin", 2, 0);

    Node *c7 = create_match(create_leaf("D. Medvedev"), c1,
                            "M. Berrettini", 0, 2);
    Node *c8 = create_match(c2, c3,
                            "J. Fonseca", 2, 1);
    Node *c9 = create_match(c4, c5,
                            "Z. Bergs", 0, 2);
    Node *c10 = create_match(c6, create_leaf("A. Zverev"),
                             "A. Zverev", 0, 2);

    Node *c11 = create_match(c7, c8,
                             "J. Fonseca", 0, 2);
    Node *c12 = create_match(c9, c10,
                             "A. Zverev", 0, 2);

    Node *qf3 = create_match(c11, c12,
                             "A. Zverev", 1, 2);

    /* ===================== SEZIONE 4 ===================== */
    Node *d1 = create_match(create_leaf("M. Cilic"), create_leaf("A. Shevchenko"),
                            "M. Cilic", 2, 0);
    Node *d2 = create_match(create_leaf("C. Moutet"), create_leaf("A. Muller"),
                            "C. Moutet", 2, 0);
    Node *d3 = create_match(create_leaf("A. Popyrin"), create_leaf("C. Ruud"),
                            "C. Ruud", 0, 2);
    Node *d4 = create_match(create_leaf("F. Cerundolo"), create_leaf("S. Tsitsipas"),
                            "F. Cerundolo", 2, 0);
    Node *d5 = create_match(create_leaf("D. Altmaier"), create_leaf("T. Machac"),
                            "T. Machac", 1, 2);
    Node *d6 = create_match(create_leaf("M. Kouame"), create_leaf("U. Humbert"),
                            "U. Humbert", 0, 2);

    Node *d7 = create_match(create_leaf("F. Auger-Aliassime"), d1,
                            "F. Auger-Aliassime", 2, 0);
    Node *d8 = create_match(d2, d3,
                            "C. Ruud", 0, 2);
    Node *d9 = create_match(d4, d5,
                            "T. Machac", 0, 2);
    Node *d10 = create_match(d6, create_leaf("J. Sinner"),
                             "J. Sinner", 0, 2);

    Node *d11 = create_match(d7, d8,
                             "F. Auger-Aliassime", 1, 0);  /* ritiro Ruud */
    Node *d12 = create_match(d9, d10,
                             "J. Sinner", 1, 2);

    Node *qf4 = create_match(d11, d12,
                             "J. Sinner", 0, 2);

    /* ===================== SEMIFINALE BASSA ===================== */
    Node *sf2 = create_match(qf3, qf4,
                             "J. Sinner", 0, 2);

    /* ===================== FINALE ===================== */
    Node *finale = create_match(sf1, sf2,
                                "J. Sinner", 0, 2);

    return finale;
}

/* =========================================================
   Test
   ========================================================= */

void test_montecarlo_2026(void) {
    Node *radice = build_montecarlo_2026_tree();

    printf("ATP Monte-Carlo Masters 2026\n");
    printf("Calcolo set vinti/persi con visita post-order\n");
    printf("=============================================\n");

    postorder_compute_and_print(radice);

    /* manca solo il vincitore finale */
    printf("%-22s sv_tot=%2d sp_tot=%2d\n",
           radice->nome, radice->sv_tot, radice->sp_tot);

    free_tree(radice);
}

int main(void) {
    test_montecarlo_2026();
    return 0;
}