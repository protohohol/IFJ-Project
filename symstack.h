



typedef struct item_stack {
    exp_stack_symbol symbol;
    exp_type etype;
    struct item_stack * next;
} item_stack_t;

typedef struct sstack {
    item_stack_t * top;
} sstack_t;




void stack_init (sstack_t * sstack);
bool stack_push (sstack_t * sstack, exp_stack_symbol symbol, exp_type type);
bool stack_pop(sstack_t * sstack);
item_stack_t* get_top ( sstack_t * sstack);


