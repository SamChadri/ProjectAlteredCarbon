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
        default:
            fprintf(stderr, "Unknown token found in token_op() on line %d\n", Line);
            exit(1);
    }
}
static char *ASTop[] = { "+", "-", "*", "/" };


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