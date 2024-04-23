#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "akinator_tree.h"

int main()
{
    FILE *output = fopen ("akinator_data_write", "w");
    FILE *input = fopen ("akinator_data_read", "r");
    
    char *buf = (char*) calloc (MAXLINE, sizeof(char));

    fread (buf, MAXLINE, sizeof (char), output);

    node *root = (node*) calloc (1, sizeof(node));
    (*root).data = "Nothing";

    char start = '1';

    while (start == '1') {
    
    akinator (root);
    printf ("If you would like to continue enter 1\n");
    start = fisrt_no_space_simbol();
    }

    tree_fprint (root, output);

    tree_detor (root);

    free (output);
    free (input);
}

