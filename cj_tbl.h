#ifndef CJ_TBL_H
#define CJ_TBL_H

#define DEFAULT_LEN 100

typedef struct cj_tbl_ {
    int *arr;
    int *vals;
    int *key_indices;
    int current_key_idx;
    int next_key;
    int current_val_idx;
    char *keys;
} cj_tbl;

cj_tbl* cj_create_tbl() {
    cj_tbl *t = (cj_tbl*)malloc(sizeof(cj_tbl));
    t->arr = (int*)malloc(DEFAULT_LEN);
    t->keys = (char*)malloc(DEFAULT_LEN);
    t->vals = (int*)malloc(DEFAULT_LEN);
    t->key_indices = (int*)malloc(DEFAULT_LEN);
    t->current_key_idx = 0;
    t->next_key = 0;
    t->current_val_idx = 0;
    return t;
}

void cj_arr_assign_int(cj_tbl *t, int idx, int val) {
    t->arr[idx] = val;
}

void cj_arr_assign_str(cj_tbl *t, char* idx, int val) {
    t->key_indices[t->current_key_idx++] = t->next_key;
    size_t len = strlen(idx);
    memcpy(t->keys + t->next_key, idx, len);
    unsigned int *val_idx = (unsigned int*)(t->keys + t->next_key + len + 1);
    t->vals[t->current_val_idx] = val;
    *val_idx = t->current_val_idx++;
    t->next_key += len + 1 + sizeof(unsigned int);
}

int cj_arr_get_int(cj_tbl *t, int idx) {
    return t->arr[idx];
}

int cj_arr_get_str(cj_tbl *t, char* key) {
    int key_idx;
    for(int i = 0; i < t->current_key_idx; i++) {
        char* possible_match = t->keys + t->key_indices[i];
        if(strcmp(key, possible_match) == 0) {
            key_idx = i;
            break;
        }
    }
    // TODO: Error handling for non-existent key
    int len = strlen(t->keys + t->key_indices[key_idx]);
    char *val_idx_begin = t->keys + key_idx + len + 1;
    unsigned int *val_idx = (unsigned int*)val_idx_begin;
    return t->vals[*val_idx];
}

void cj_destroy_tbl(cj_tbl **t) {
    free((*t)->arr);
    (*t)->arr = NULL;
    free((*t)->keys);
    (*t)->keys = NULL;
    free((*t)->vals);
    (*t)->vals = NULL;
    free((*t)->key_indices);
    (*t)->key_indices = NULL;
    free(*t);
    *t = NULL;
}

#endif
