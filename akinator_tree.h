#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct nod{
    const char* data;
    struct nod* left;
    struct nod* right;
    struct nod* parent;
} node;

#define MAXLINE 100

const char right_answer [] = "YES";
const char left_answer [] = "NO";

void akinator (node* root);
node* ask_quest (node* root);
void ask_ans(node* pass_root, node* root);
void insert_quest (node* p_node, char* answer);
void tree_print(node* p_node);
void tree_fprint (node* p_node, FILE *output);
void tree_detor(node* p_node);
node* tree_search (node* p_node, const char* str);
node* creat_bin_node (const char* data, node* parent, const char descent, node* left_child, node* right_child);


int getline (char* str, int limit);
int putline (char* str, int limit);
char fisrt_no_space_simbol ();
void make_string_upper (char *str, int limit);