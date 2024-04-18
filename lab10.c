#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie node structure
struct TrieNode {
    struct TrieNode *children[26];
    int count;
};

// Trie structure
struct Trie {
    struct TrieNode *root;
};

// Creates a new Trie node
struct TrieNode *createNode() {
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (node) {
        node->count = 0;
        for (int i = 0; i < 26; i++) {
            node->children[i] = NULL;
        }
    }
    return node;
}

// Inserts the word into the Trie structure
void insert(struct Trie *pTrie, char *word) {
    struct TrieNode *curr = pTrie->root;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (!curr->children[index]) {
            curr->children[index] = createNode();
        }
        curr = curr->children[index];
    }
    curr->count++;
}

// Computes the number of occurrences of the word
int numberOfOccurrences(struct Trie *pTrie, char *word) {
    struct TrieNode *curr = pTrie->root;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (!curr->children[index]) {
            return 0; // Word not found
        }
        curr = curr->children[index];
    }
    return curr->count;
}

// Deallocates the Trie structure
void deallocateTrie(struct TrieNode *root) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < 26; i++) {
        if (root->children[i] != NULL) {
            deallocateTrie(root->children[i]);
        }
    }
    free(root);
}

// Initializes a Trie structure
struct Trie *createTrie() {
    struct Trie *trie = (struct Trie *)malloc(sizeof(struct Trie));
    trie->root = createNode();
    return trie;
}

// Reads the dictionary file and stores the words in the array
int readDictionary(char *filename, char **pInWords) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file.\n");
        exit(1);
    }
    int count = 0;
    char word[100]; // Assuming maximum word length of 100 characters
    while (fscanf(file, "%s", word) != EOF) {
        pInWords[count] = strdup(word);
        count++;
    }
    fclose(file);
    return count;
}

int main(void) {
    char *inWords[256];

    // Read the number of words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i) {
        printf("%s\n", inWords[i]);
    }

    // Create and populate the Trie
    struct Trie *pTrie = createTrie();
    for (int i = 0; i < numWords; i++) {
        insert(pTrie, inWords[i]);
    }

    // Test the Trie with some sample words
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));
    }

    // Deallocate memory used by the Trie
    deallocateTrie(pTrie->root);
    free(pTrie);

    return 0;
}
