#include "exercice9.h"
#include "exercice9.h"

// Q.9.1
void submit_vote(Protected *p)
{
    FILE *file = fopen(PENDING_VOTE_FILE_PATH, "a");
    char *tmp = protected_to_str(p);
    fprintf(file, "%s\n", tmp);
    free(tmp);
    fclose(file);
}

// Q.9.2
void create_block(CellTree *tree, Key *author, int d)
{

    CellTree *lastNode = last_node(tree);
    Block *newBlock = malloc(sizeof(Block));
    newBlock->author = author;

    // Premier block value du hash precedent par défault
    if (lastNode->block == NULL)
        newBlock->previous_hash = unsigned_strdup("476308207be73d246071f1e59ab2cfad5979031474cc8916c539eea8d3df4939");
    else
        newBlock->previous_hash = unsigned_strdup((char *)lastNode->block->hash);

    newBlock->hash = NULL;
    // cree un bloc valide contenant les votes en attente dans le fichier ”Pending votes.txt”

    newBlock->votes = read_protected_from_file(PENDING_VOTE_FILE_PATH);
    newBlock->nonce = d;
    compute_proof_of_work(newBlock, d);
    // supprime le fichier ”Pending votes.txt” apr`es avoir cr´e´e le bloc
    if (remove(PENDING_VOTE_FILE_PATH) == 0)
    {
        printf("The file is deleted successfully.\n");
    }
    else
    {
        printf("The file is not deleted.\n");
    };
    // ecrit le bloc obtenu dans un fichier appel´e ”Pending block”.
    write_block_to_file(newBlock, PENDING_BLOCK_FILE_PATH);
    // free(newBlock->author);
    delete_list_protected_from_node(newBlock->votes);

    delete_block(newBlock);
}

// Q.9.3
void add_block(int d, char *name)
{
    Block *blockFromFile = read_block_from_file(name);
    int boolean = verify_block(blockFromFile, d);
    if (boolean == 1)
    {
        char *author = key_to_str(blockFromFile->author);
        char *extension = ".txt";
        int len = (strlen(VALID_BLOCK_PATH) + strlen(author) + strlen(extension) + 1);
        char *filename = malloc(sizeof(char) * len);
        memset(filename, 0, len);
        // la ligne suivante sert pour le chemin vers le document.txt
        strcat(strcat(strcat(filename, VALID_BLOCK_PATH), author), extension);
        write_block_to_file(blockFromFile, filename);
        free(filename);
        free(author);
    }
    if (remove(PENDING_BLOCK_FILE_PATH) == 0)
    {
        printf("The file is deleted successfully.\n");
    }
    else
    {
        printf("The file is not deleted.\n");
    };
    free(blockFromFile->author);
    delete_list_protected_from_node(blockFromFile->votes);

    delete_block(blockFromFile);
}


// Q.9.4

int count_file_in_directory(char *directory)
{
    int i = 0;
    DIR *rep = opendir(directory);
    if (rep != NULL)
    {
        struct dirent *dir;
        while ((dir = readdir(rep)))
        {
            if (strncmp(dir->d_name, ".", 1) != 0 && strncmp(dir->d_name, "..", 2) != 0)
            {
                i++;
            }
        }
        closedir(rep);
    }
    return i;
}

CellTree *read_tree()
{
    char filePathBuffer[BUFFER_SIZE];
    int nbFileInDirectory = count_file_in_directory(VALID_BLOCK_PATH);
    CellTree **tabTree = malloc(sizeof(CellTree *) * nbFileInDirectory);
    int indexTabTree = 0;
    DIR *rep = opendir(VALID_BLOCK_PATH);
    if (rep != NULL)
    {
        struct dirent *dir;
        while ((dir = readdir(rep)))
        {
            if (strncmp(dir->d_name, ".", 1) != 0 && strncmp(dir->d_name, "..", 2) != 0)
            {
                snprintf(filePathBuffer, sizeof(VALID_BLOCK_PATH) + sizeof(dir->d_name), "%s%s", VALID_BLOCK_PATH, dir->d_name);
                printf("%s\n", filePathBuffer);
                Block *blockFromFile1 = read_block_from_file(filePathBuffer);
                tabTree[indexTabTree] = create_node(blockFromFile1);
                indexTabTree++;
            }
        }
        closedir(rep);
    }

    // On parcourt le tableau T de noeuds, et pour chaque noeud T[i], on recherche tous ses fils T[j];
    for (int i = 0; i < nbFileInDirectory; i++)
    {
        for (int j = 0; j < nbFileInDirectory; j++)
        {

            if (hash_compare(tabTree[i]->block->hash, tabTree[j]->block->previous_hash) == 1)
            {
                printf("uhk\n");
                add_child(tabTree[i], tabTree[j]);
            }
        }
    }
    // On parcourt une derni`ere fois le tableau T pour trouver la racine de l’arbre
    for (int i = 0; i < nbFileInDirectory; i++)
    {
        if (tabTree[i]->father == NULL)
        {
            CellTree *tmp = tabTree[i];
            free(tabTree);
            return tmp;
        }
    }
    printf("Racine non trouvé\n");
    return NULL;
}

// Q.9.5
Key *compute_winner_BT(CellTree *tree, CellKey *candidates, CellKey *voters, int sizeC, int sizeV)
{
    CellProtected *mergeDeclaration = fusion_cell_protected_from_all_node(tree);
    supprimer_fausse_signature(&mergeDeclaration);

    print_list_protected(mergeDeclaration);

    Key *vainqueur = compute_winner(mergeDeclaration, candidates, voters, sizeC, sizeV);

    delete_list_protected_from_node(mergeDeclaration);
    return vainqueur;
}
