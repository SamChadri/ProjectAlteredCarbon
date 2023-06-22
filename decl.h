int scan(struct Token *t);

struct ASTNode * make_ast_node(int op, struct ASTNode * left, struct ASTNode* right, int value);
struct ASTNode * make_leaf_node(int op, int value);
struct ASTNode * make_unary_node(int op, struct ASTNode * node, int value);

struct ASTNode * cmake_ast_node(int op, struct ASTNode * left, struct ASTNode* right, char * value);
struct ASTNode * cmake_leaf_node(int op, char * id);


struct ASTNode * r_create_tree(struct ASTNode *n, struct ASTNode * left, struct ASTNode * right, struct ASTNode *root);
struct ASTNode * pratt_create_tree(int ptp, struct ASTNode *left);
int interpretAST(struct ASTNode * node);

struct RegOp q_add(int r1, int r2);
struct RegOp q_subtract(int r1, int r2);
struct RegOp q_multiply(int r1, int r2);
int measure_result(int reg);
struct RegOp load_qregister(int val, int position);
void q_load_preamble();

void aspreamble();
void aspostamble();
void free_all_registers();

int asloadint(int val);
int asadd(int r1, int r2);
int assub(int r1, int r2);
int asmultiply(int r1, int r2);
int asdivide(int r1, int r2);
int asprint(int register);

int asloadsymbol(char *symbol);
int asstoresymbol(int r, char *symbol);


void generate_qasm(struct ASTNode * node);
void generate_asm(struct ASTNode * node);

int interpret_asm_AST(struct ASTNode * node );
int interpret_qasm_AST(struct ASTNode * node);

struct NESTNode * make_nest_node(struct ASTNode * root, struct NESTNode * next, int token,int priority);
struct NESTNode * insert_nest_node(struct NESTNode * node, struct NESTNode * head);



struct NESTNode * build_astat_nest();
struct NESTNode * build_qstat_nest();
void interpret_astat_nest(struct NESTNode * head);
void interpret_qstat_nest(struct NESTNode * head);

struct SYMNode * create_symbol(char * s, struct SYMNode * next, int priority);
struct SYMNode * find_symbol(char *s);
void add_symbol(struct SYMNode * node);









