// Guillem Moles 1635000

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "structs.h"

#define CARRERS "Carrers.csv"
#define NODES "Nodes.csv"

unsigned buscapunt(long int ident, node l[], unsigned nnodes); 

node *llegirfitxers(int *nnodes)
{
    int ll, ll_fitxer_nodes = 0, i;
    node *nodes;

    FILE *fitxer_nodes;
    fitxer_nodes = fopen(NODES, "r");
    if (fitxer_nodes == NULL)
    {
        printf("\nNo s'ha accedit al fitxer de dades\n");
        exit(1);
    }

    while ((ll = fgetc(fitxer_nodes)) != EOF)
        if (ll == '\n')
            ll_fitxer_nodes++;

    rewind(fitxer_nodes);

    if ((nodes = (node *)malloc(sizeof(node) * ll_fitxer_nodes)) == NULL)
    {
        printf("No hi ha suficient espai de memòria");
        exit(-1);
    }

    for (i = 0; i < ll_fitxer_nodes; i++)
    {
        // inicialitzar els nodes
        fscanf(fitxer_nodes, "%ld;%lf;%lf\n", &nodes[i].id, &nodes[i].latitud, &nodes[i].longitud);
        nodes[i].heuristica = 0.;
        nodes[i].cost = DBL_MAX;
        nodes[i].anterior = NULL;
        nodes[i].distancia = 0;
        nodes[i].narst = 0;
    }

    FILE *fitxer_carrers;
    fitxer_carrers = fopen(CARRERS, "r");
    if (fitxer_carrers == NULL)
    {
        printf("\nNo s'ha accedit al fitxer de dades\n");
        exit(1);
    }
    for (i = 0; fgetc(fitxer_carrers) != EOF; i++)
    {
        char id[12];
        fscanf(fitxer_carrers, "d=%[0-9]", id);
        unsigned node_ant = 0;
        while (fgetc(fitxer_carrers) != '\n')
        {
            long int node_llegit;
            unsigned node_act;
            fscanf(fitxer_carrers, "%ld", &node_llegit);
            node_act = buscapunt(node_llegit, nodes, ll_fitxer_nodes);
            if (node_ant != 0)
            {
                // aresta del node actual al anterior
                for (int j = 0; j < 12; j++)
                    nodes[node_act].arestes[nodes[node_act].narst].carrer[j] = id[j];
                nodes[node_act].arestes[nodes[node_act].narst].numnodes = node_ant;
                nodes[node_act].narst++;

                // aresta del node anterior al actual
                for (int j = 0; j < 12; j++)
                    nodes[node_ant].arestes[nodes[node_ant].narst].carrer[j] = id[j];
                nodes[node_ant].arestes[nodes[node_ant].narst].numnodes = node_act;
                nodes[node_ant].narst++;
            }
            node_ant = node_act;
        }
    }
    *nnodes = ll_fitxer_nodes;
    return nodes;
}