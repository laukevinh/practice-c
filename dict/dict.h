struct Node {
    char *key;
    int val;
    struct Node *next;
};

struct Dict {
    struct Node **head;
    int m;
};

struct Dict* new_dict(int m);
void delete_dict(struct Dict *dict);
struct Node* new_node(char *s, int i);
void print_items(struct Dict *dict);
double prehash(char *s);
int hash(double k, double m);
void add(struct Dict *dict, char *key, int value);
int get(struct Dict *dict, char *key);
void del(struct Dict *dict, char *key);

void test_new_dict(void);
void test_prehash(void);
void test_add(void);
void test_get(void);
void test_del(void);
