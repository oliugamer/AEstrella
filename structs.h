#define MAXARST 25

typedef struct
{
    char carrer[12];
    unsigned numnodes;
} infoaresta;

typedef struct Node
{
    long int id;
    double latitud, longitud;
    int narst;
    double heuristica, distancia, cost;
    infoaresta arestes[MAXARST];
    struct Node *anterior;
} node;

typedef struct element
{
    unsigned indexNode;
    struct element *seguent;
} ElementCua;

typedef struct
{
    ElementCua *inici, *final;
} cues;