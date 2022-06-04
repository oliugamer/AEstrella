// Guillem Moles 1635000

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structs.h"

double distancia(node node_a, node node_b)
{
    int R = 6371;
    double pi = 3.1415926536;
    double xa = R * cos(node_a.longitud * pi / 180) * cos(node_a.latitud * pi / 180);
    double ya = R * sin(node_a.longitud * pi / 180) * cos(node_a.latitud * pi / 180);
    double za = R * sin(node_a.latitud * pi / 180);
    double xb = R * cos(node_b.longitud * pi / 180) * cos(node_b.latitud * pi / 180);
    double yb = R * sin(node_b.longitud * pi / 180) * cos(node_b.latitud * pi / 180);
    double zb = R * sin(node_b.latitud * pi / 180);
    double distx = xa - xb;
    double disty = ya - yb;
    double distz = za - zb;
    return sqrt((distx * distx) + (disty * disty) + (distz * distz));
}

void posarencua(unsigned index_node, node nodes[], cues* cua){
    ElementCua *actual;
    if((actual = (ElementCua *) malloc(sizeof(ElementCua))) == NULL){
        printf("No hi ha suficient espai de memòria\n");
        exit(-1);
    }
    actual->indexNode = index_node;
    actual->seguent = NULL;
    if(cua->inici == NULL){
        cua->inici = actual;
        cua->final = actual;
    } else {
        ElementCua *seguent = cua->inici, *anterior;
        while(seguent != NULL){
            if(nodes[index_node].cost < nodes[seguent->indexNode].cost){
                actual->seguent = seguent;
                if (seguent == cua->inici){
                    // ficar al inici de la cua
                    cua->inici = actual;
                } else {
                    // ficar al mitg de la cua
                    anterior->seguent = actual;
                }
                break;
            }
            anterior = seguent;
            seguent = seguent->seguent;
        }
        if(seguent == NULL){
            // ficar al final de la cua
            cua->final->seguent = actual;
            cua->final = actual;
        }
    }
}

unsigned treucua(cues* cua){
    if(cua->inici == NULL){
        printf("Error: no s'ha trobat cap ruta");
        exit(1);
    }
    unsigned index;
    index = cua->inici->indexNode;
    cua->inici = cua->inici->seguent;
    return index;
}

char calcularcost(node *n, node desti, node *anterior){
    // calcular la heurística
    if(n->heuristica == 0){
        n->heuristica = distancia(*n, desti);
    }

    // calcular el cost
    double cost=0, dist;
    dist = distancia(*n, *anterior);
    cost += n->heuristica;
    cost += anterior->cost;
    cost += dist;
    if(cost < n->cost){
        n->cost = cost;
        n->anterior = anterior;
        n->distancia = dist + n->anterior->distancia;
        return 1;
    }
    return 0;
}

unsigned buscapunt(long int ident, node l[], unsigned nnodes)
{
    int mid, min = 0, max = nnodes;
    while (min <= max)
    {
        mid = (min + ((max - min) / 2));
        if (l[mid].id == ident)
            break;
        if (l[mid].id < ident)
            min = mid + 1;
        else
            max = mid - 1;
    }
    return mid;
}

void printnodes(node *n){
    if(n->anterior != NULL){
        printnodes(n->anterior);
    }
    printf("Id=%-13li | %-13lf | %-13lf | Dist=%-13lf\n", n->id, n->latitud, n->longitud, n->distancia * 1000);
}