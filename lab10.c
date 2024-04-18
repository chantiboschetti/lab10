#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie node structure
struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int count;
};

// Trie structure
struct Trie {
    struct TrieNode *root;
};

// Create a new trie node
struct TrieNode *createTrieNode() {
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (node) {
        node->count = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            node->children[i] = NULL;
        }
    }
    return node;
}

// Inserts the word into the trie structure
void insert(struct Trie *pTrie, char *word) {
    struct TrieNode *current = pTrie->root;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (!current->children[index]) {
            current->children[index] = createTrieNode();
        }
        current = current->children[index];
    }
    current->count++;
}

// Computes the number of occurrences of the word
int numberOfOccurrences(struct Trie *pTrie, char *word) {
    struct TrieNode *current = pTrie->root;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (!current->children[index]) {
            return 0;
        }
        current = current->children[index];
    }
    return current->count;
}

// Deallocates the trie structure
void deallocateTrieNode(struct TrieNode *node) {
    if (node) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            deallocateTrieNode(node->children[i]);
        }
        free(node);
    }
}

// Initializes a trie structure
struct Trie *createTrie() {
    struct Trie *pTrie = (struct Trie *)malloc(sizeof(struct Trie));
    if (pTrie) {
        pTrie->root = createTrieNode();
    }
    return pTrie;
}

// Reads the dictionary file and returns the number of words
int readDictionary(char *filename, char **pInWords) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file.\n");
        exit(1);
    }
    int count = 0;
    char word[100]; // Assuming maximum word length is 100 characters
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
    
    struct Trie *pTrie = createTrie();
    for (int i = 0; i < numWords; i++) {
        insert(pTrie, inWords[i]);
    }
    
    // Test cases
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));
    }
    
    // Deallocate memory
    deallocateTrieNode(pTrie->root);
    free(pTrie);
    
    return 0;
}
