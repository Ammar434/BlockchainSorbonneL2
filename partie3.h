#ifndef PARTIE3_H
#define PARTIE3_H
typedef struct cellKey
{
    Key *data;
    struct cellKey *next;
} CellKey;
CellKey *create_cell_key(Key *key);

#endif // PARTIE3_H