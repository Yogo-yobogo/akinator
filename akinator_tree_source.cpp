#include "akinator_tree.h"


void akinator (node* root) {

    node* pass_root = root;

    printf ("Begin akinator\n");
    printf ("pass_root->left = %p, pass_root->right = %p\n", pass_root->left, pass_root->right);

    while (pass_root != NULL && (pass_root->left != NULL || pass_root->right != NULL)){
        
        printf ("Come in loop\n");

        pass_root = ask_quest (pass_root);
    }

    printf ("Came out from loop\n");

    ask_ans (pass_root, root);

    printf ("End_akinator\n");
}

node* ask_quest (node* root) {

    if (root == NULL) {
        printf ("ask_quest: get NULL as node*\n");
        return 0;
    }

    char* answer = (char*) calloc (MAXLINE, sizeof(char));

    printf ("This object %s?(print \"YES\" or \"NO\")\n", root->data);

    scanf ("%s", answer);

    make_string_upper(answer, MAXLINE);

    printf ("answer = %s\n", answer);

    if (!(strcmp(answer, right_answer)))
    {
        return root->right;
    }
    else if (!(strcmp(answer, left_answer))) {
        return root->left;
    }
    else {
        printf ("Wrong answer\n");
        return NULL;
    }
}

void ask_ans(node* pass_root, node* root) {

    char* answer = (char*) calloc (MAXLINE, 1);

    printf ("You made a wish %s (print \"YES\" or \"NO\")\n", pass_root->data);

    scanf ("%s", answer);
    make_string_upper(answer, MAXLINE);

    printf ("answer = %s\n", answer);

    if (!(strcmp(answer, right_answer)))
    {
        printf ("I win again\n");
    }
    else if (!(strcmp(answer, left_answer))) {

        printf ("Who did you wish for?\n");
        getline (answer, MAXLINE);
        
        if (tree_search(root, answer) == NULL){
            insert_quest (pass_root, answer);
        }
        else {
            printf ("That object in tree yet!\n");
            //print_way(pass_root->data, root);
        }
    }
    else {
        printf ("You enter wrong answer\n");
    }

}

void insert_quest (node* p_node, char* answer) {

    char* quest = (char*) calloc (MAXLINE, 1);

    printf ("How is different %s from %s?\n", answer, p_node->data);
    getline (quest, MAXLINE);//scanf ("%s", quest);

    node *ans_node = creat_bin_node (answer, p_node, 'r', NULL, NULL);

    printf ("Creat new_ans %s\n", ans_node->data);

    node *old_node = creat_bin_node (p_node->data, p_node, 'l', NULL, NULL);

    printf ("Creat old_ans %s\n", old_node->data);

    p_node->data = quest;

    printf ("Creat new quest %s\n", p_node->data);
}

void tree_print(node* p_node) {
    printf ("(%s ", p_node->data);
    if (p_node->left != nullptr)
        tree_print(p_node->left);
    if (p_node->right != nullptr)
        tree_print(p_node->right);
    
    if (p_node->left == NULL && p_node->right == NULL) {
        printf ("(nil) (nil)");
    }

    printf (") ");
}

void tree_fprint(node* p_node, FILE *output) {
    fprintf (output,"(\"%s\" ", p_node->data);
    if (p_node->left != nullptr)
        tree_fprint(p_node->left, output);
    if (p_node->right != nullptr)
        tree_fprint(p_node->right, output);
    
    if (p_node->left == NULL && p_node->right == NULL) {
        fprintf (output,"nil nil");
    }

    fprintf (output,") ");
}

void tree_detor (node* tree) {
    if (tree->left != nullptr)
        tree_detor (tree->left);

    if (tree->right != nullptr)
        tree_detor(tree->right);

    free (tree);
}

node* tree_search (node* p_node, const char* str) {
    node* left_answer = 0, *right_answer = 0;
    if (strcmp(p_node->data, str) == 0) {
        printf ("Find answer %s\n", p_node->data);
        return p_node;
    }

    if (p_node->left != NULL) {
        printf ("Come in left\n");
        left_answer = tree_search (p_node->left, str);
    }
    if (p_node->right != NULL) {
        printf ("Come in right\n");
        right_answer = tree_search (p_node->right, str);
    }
    
    if (left_answer != NULL && strcmp(left_answer->data, str) == 0) {
        printf ("Find answer %s\n", left_answer->data);
        return left_answer;
    }

    if (right_answer != NULL && strcmp(right_answer->data, str) == 0) {
        printf ("Find answer %s\n", p_node->data);
        return right_answer;
    }
    return NULL;
}


node* creat_bin_node (const char* data, node* parent, const char descent, node* left_child, node* right_child) {
    
    node* new_node = (node*) calloc (MAXLINE, sizeof(char));
    new_node->data = data;

    if (parent != NULL && (tolower(descent) == 'l'|| tolower(descent) == 'r')) {
        if  (tolower(descent) == 'l') {
            parent->left = new_node;
        }
        else {
            parent->right = new_node;
        } 
    }

    new_node->left = left_child;
    new_node->right = right_child;

    return new_node;
}

int getline (char* str, int limit) {
    int i = 0;
    char ch = fisrt_no_space_simbol();
    printf ("ch = %c\n", ch);
    str[i] = ch;
    i++;

    while ( ch != 0 && ch != '\n' && ch != EOF && i < limit - 1) {
        ch = getchar();
        printf ("ch = %c\n", ch);
        str[i] = ch;
        i++;
    }

    str[i - 1] = '\0';
    return i;
}

int putline (char* str, int limit) {
    int i = 0;
    char ch = 1;
    do {
        ch = str[i];
        putchar(ch);
        str[i] = ch;
        i++;
    }
    while ( ch != 0 && ch != '\n' && ch != EOF && i < limit - 1);

    return i;
}

char fisrt_no_space_simbol () {
    char ch = '\n';
    while (isspace(ch)) {
        ch = getchar ();
    }
    return ch;
}

void make_string_upper (char *str, int limit) {
    for (int i = 0; i < limit - 1 && str[i] != 0; i++) {
        str[i] = toupper (str[i]);
    }
}

/*int get_data (char * data, char* str) {
    int i = 1;
    while (data[i - 1] != '"') {
        data[i] = getchar();
        i++;
    }
    return i;
}*/