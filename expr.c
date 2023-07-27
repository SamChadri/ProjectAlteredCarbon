#include "defs.h"
#include "data.h"
#include "decl.h"
#include <stdio.h>

int token_op(int tok){
    switch(tok){
        case T_PLUS:
            return A_ADD;
        case T_MINUS:
            return A_SUBTRACT;
        case T_STAR:
            return A_MULTIPLY;
        case T_SLASH:
            return A_DIVIDE;
        case T_INTLIT:
            return A_INTLIT;
        case T_EQ:
            return A_EQ;
        case T_NE:
            return A_NE;
        case T_LT:
            return A_LT;
        case T_GT:
            return A_GT;
        case T_LE:
            return A_LE;
        case T_GE:
            return A_GE;
        default:
            fprintf(stderr, "Unknown token found in token_op() on line %d\n", Line);
            exit(1);
    }
}
static char *ASTop[] = { "+", "-", "*", "/", "=", "!=", "<", ">", "<=", ">="};
static int OpPrec[] = { 0, 0, 10, 10, 20, 20, 30, 30, 30, 30};

static int op_precedence(int tokentype) {

    int prec = OpPrec[tokentype];
    if (prec < 0 || prec > 30) {
        fprintf(stderr, "syntax error on line %d, token %d\n", Line, tokentype);
        exit(1);
    }
    return (prec);
}

struct ASTNode * scan_leaf(){
    struct ASTNode * n;
    scan(&token);
    switch (token.token) {
        case T_INTLIT:
            printf("expr::scan_leaf::Making Leaf node for integer %d \n", token.int_value);
            n = make_leaf_node(A_INTLIT, token.int_value);
            return (n);
        case T_IDENT:
            printf("expr::scan_leaf::Making Leaf node for identifier %s \n", Text);
            if(find_symbol(Text) == NULL){
                fprintf(stderr, "Unknown variable: %s \n", Text);
                exit(1);
            }
            n = cmake_leaf_node(A_IDENT, Text);
            return (n);
        default:
            fprintf(stderr, "expr::scan_leaf::syntax error on line %d, token %s\n", Line, ASTop[token.token]);
            exit(1);
    }
}


struct ASTNode * pratt_create_tree(int ptp, struct ASTNode *left)
{
    struct ASTNode * n, *root;
    int tokentype;

    printf("Starting creation \n");
    if(left == NULL){
        left = scan_leaf();
        printf("Initiating with leaf %d \n", left->value );

    }
    scan(&token);

    if(token.token == T_SEMI){
        printf("FOUND SEMICOLON... EXITING PRATT CREATE TREE \n");
        return left;
    }
    int op_token = token_op(token.token);
    printf("TOKEN PROCESSED \n");

    n = make_ast_node(op_token, NULL, NULL, 0);
    printf("Creating token node: %s \n", ASTop[op_token]);
    if(op_precedence(op_token) > ptp){
        printf("Previous token: '%s'. '%s' Takes precedence \n",ASTop[ptp],ASTop[op_token]);
        n->left = left->right;
        n->left->position = LEFT_REG;
        left->right = n;
        n->right = scan_leaf();
        n->right->position = RIGHT_REG;
        root = pratt_create_tree(ptp, left);
        if(root == NULL){
            return left;
        }else{
            return root;
        }
    }
    else{
        printf("No Precedence found \n",ASTop[op_token], ASTop[ptp]);

        n->left = left;
        n->left->position = LEFT_REG;
        n->right = scan_leaf();
        n->right->position = RIGHT_REG;

        root = pratt_create_tree(op_token, n);
        return root;
    }

    
}


struct ASTNode * r_create_tree(struct ASTNode *n, struct ASTNode * left, struct ASTNode * right, struct ASTNode *root)
{
    //struct ASTNode *temp_n, *temp_left, *temp_right;
    printf("Starting creation\n");
    int nodeType;
    scan(&token);
    switch(token.token){
        case T_INTLIT:
            if(n == NULL){
                if(left == NULL){
                    int op_token = token_op(token.token);
                    printf("Making Leaf node %d \n", token.int_value);
                    left = make_leaf_node(op_token, token.int_value);
                }
                n = r_create_tree( NULL, left, NULL, NULL);
                printf("Leaf node %d returned n with value %d \n ", token.int_value, n->value);
                right = r_create_tree(n,left, NULL, NULL);
                printf("Leaf node %d returned right with value %d \n ", token.int_value, right->value);
                n = make_ast_node(n->op, left, right, 0);
                printf("N-Left: %d, N-Right: %d, N %s \n ",left->value, right->value, ASTop[n->op]);
                root = r_create_tree(NULL, NULL, NULL, n);
                if(root != NULL){
                    return root;
                }else{
                    return n;
                }
            }
            else{
                int op_token = token_op(token.token);
                printf("Making Leaf node %d \n", token.int_value);
                return make_leaf_node(op_token, token.int_value);
            }

        case T_MINUS:{
            int op_token = token_op(token.token);
            printf("Making sign node %s\n", ASTop[op_token]);
            if(left != NULL){
                return make_ast_node(op_token, NULL, NULL, 0);
            }
            if(root != NULL){
                printf("Making sign node %s\n and making it the root \n", ASTop[op_token]);
                left = root;
                n = make_ast_node(op_token, NULL, NULL, 0);
                right = r_create_tree(n, left, NULL, NULL );
                n->right = right;
                n->left = left;
                root = r_create_tree(NULL, NULL, NULL, n);
                if(root != NULL){
                    return root;
                }else{
                    return n;
                }
            }

        }
        case T_PLUS: {
            int op_token = token_op(token.token);
            if(left != NULL){
                printf("Making Sign node %s\n", ASTop[op_token]);
                return make_ast_node(op_token, NULL, NULL, 0);
            }
            if(root != NULL){
                printf("Making sign node %s\n and making it the root \n", ASTop[op_token]);
                left = root;
                n = make_ast_node(op_token, NULL, NULL, 0);
                right = r_create_tree(n, left, NULL, NULL );
                n->right = right;
                n->left = left;
                root = r_create_tree(NULL, NULL, NULL, n);
                if(root != NULL){
                    return root;
                }else{
                    return n;
                }
            }
        }
        case T_STAR: {
            int op_token = token_op(token.token);
            if(left != NULL){
                printf("Making sign node %s\n", ASTop[op_token]);
                return make_ast_node(op_token, NULL, NULL, 0);
            }
            if(root != NULL){
                //CHECK ROOT to see if its not STAR or DIVIDER LATER
                printf("Making sign node %s as with priorty ordering\n", ASTop[op_token]);
                n = make_ast_node(op_token, NULL, NULL, 0);
                struct ASTNode * temp_right = root->right;
                root->right = n;
                n->left  = temp_right;
                right =  r_create_tree(n,left, NULL, NULL);
                n->right = right;
                root = r_create_tree(NULL, NULL, NULL, root);
                return root;
            }
        }
            break;
        case T_SLASH:{

            int op_token = token_op(token.token);
            printf("Making sign node %s\n", ASTop[op_token]);
            if(left != NULL){
                printf("Making sign node %s\n", ASTop[op_token]);
                return make_ast_node(op_token, NULL, NULL, 0);
            }
            if(root != NULL){
                printf("Making sign node %s as with priorty ordering\n", ASTop[op_token]);
                //CHECK ROOT to see if its not STAR or DIVIDER LATER
                n = make_ast_node(op_token, NULL, NULL, 0);
                struct ASTNode * temp_right = root->right;
                root->right = n;
                n->left  = temp_right;
                right =  r_create_tree(n,left, NULL, NULL);
                n->right = right;
                root = r_create_tree(NULL, NULL, NULL, root);
                return root;
            }
        }
        case T_EOF:
            printf("END OF FILE RETURNING \n");
            return root;
        

        default:
            fprintf(stderr, "unknown token in arithop() on line %d\n", Line);
            exit(1);
        
    }

}