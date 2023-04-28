int scan(struct Token *t);

struct ASTNode * make_ast_node(int op, struct ASTNode * left, struct ASTNode* right, int value);
struct ASTNode * make_leaf_node(int op, int value);
struct ASTNode * make_unary_node(int op, struct ASTNode * node, int value);

struct ASTNode * r_create_tree(struct ASTNode *n, struct ASTNode * left, struct ASTNode * right, struct ASTNode *root);
struct ASTNode * pratt_create_tree(int ptp, struct ASTNode *left);
int interpretAST(struct ASTNode * node);

int q_add(int r1, int r2);
int measure_result(int reg);
int load_qregister(int val);
void q_load_preamble();

void genereate_code(struct ASTNode * node);

