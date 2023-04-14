int scan(struct Token *t);

struct ASTNode * make_ast_node(int op, struct ASTNode * left, struct ASTNode* right, int value);
struct ASTNode * make_leaf_node(int op, int value);
struct ASTNode * make_unary_node(int op, struct ASTNode * node, int value);

struct ASTNode * r_create_tree(struct ASTNode *n, struct ASTNode * left, struct ASTNode * right, struct ASTNode *root);
struct ASTNode * pratt_create_tree(int ptp, struct ASTNode *left);
int interpretAST(struct ASTNode * node);


