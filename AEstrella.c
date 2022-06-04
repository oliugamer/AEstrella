// Guillem Moles 1635000

#include <stdio.h>
#include <stdlib.h>
#include "llegirfitxers.h"
#include "cues.h"
#include "structs.h"

/* 
|---------------------------------------------------------
|
|   > Compilar amb: "$make AEstrella"
|   > Executar amb: "$./AEstrella {id_node} {id_node}"
|
|---------------------------------------------------------
*/

int main(int argc, char **argv)
{
    unsigned j, i;

    long int inici, desti;
    if (argc < 3 || sscanf(argv[1], "%ld", &inici) != 1 || sscanf(argv[2], "%ld", &desti) != 1)
    {
        printf("Format incorrecte.\nFormat correcte: ./AEstrella {Node_sortida} {Node_arribada}\n");
        return -1;
    }

    cues cua = {NULL, NULL};
    node *nodes;
    int nnodes;
    nodes = llegirfitxers(&nnodes);

    //La cua funciona amb els índexos del vector de nodes
    unsigned index_inicial = buscapunt(inici, nodes, nnodes);
    unsigned node_desti = buscapunt(desti, nodes, nnodes); 
    i = index_inicial;
    nodes[i].cost = 0;
    posarencua(i, nodes, &cua);
    while(nodes[i].id != desti){
        i = treucua(&cua);
        for(j=0;j<nodes[i].narst;j++){
            char ret = calcularcost(&nodes[nodes[i].arestes[j].numnodes], nodes[node_desti], &nodes[i]);
            if(ret == 1)
                posarencua(nodes[i].arestes[j].numnodes, nodes, &cua);
        }
    }

    printf("La distància entre %ld a %ld és de %lf metres\n", inici, desti, nodes[node_desti].distancia*1000);
    printnodes(&nodes[node_desti]);

    return 0;
}
