#include "exercice9.h"
#include "exercice9.h"

void submit_vote(Protected *p)
{
    FILE *file = fopen(PENDING_VOTE_FILE_PATH, "a");
    char *tmp = protected_to_str(p);
    fprintf(file, "%s\n", tmp);
    free(tmp);
    fclose(file);
}

void create_block(CellTree *tree, Key *author, int d)
{
    // cr´ee un bloc valide contenant les votes en attente dans le fichier ”Pending votes.txt”
    CellProtected *pendingVote = read_protected_from_file(PENDING_VOTE_FILE_PATH);

    CellTree *lastNode = last_node(tree);

    Block *newBlock = malloc(sizeof(Block));
    newBlock->author = author;
    newBlock->previous_hash = lastNode->block->hash;
    newBlock->hash = NULL;
    newBlock->votes = pendingVote;

    compute_proof_of_work(newBlock, d);
    // supprime le fichier ”Pending votes.txt” apr`es avoir cr´e´e le bloc
    if (remove(PENDING_VOTE_FILE_PATH) == 0)
    {
        printf("The file is deleted successfully.");
    }
    else
    {
        printf("The file is not deleted.");
    };
    // ecrit le bloc obtenu dans un fichier appel´e ”Pending block”.

    write_block_to_file(newBlock);
}

void add_block(int d, char *name)
{
    Block *blockFromFile = read_block_from_file(name);
    int boolean = verify_block(blockFromFile, d);
    if (boolean == 1)
    {
        write_block_to_file(blockFromFile);
    }
    if (remove(PENDING_BLOCK_FILE_PATH) == 0)
    {
        printf("The file is deleted successfully.");
    }
    else
    {
        printf("The file is not deleted.");
    };
}
