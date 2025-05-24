#ifndef __ILRD__OL13940_TRIE__
#define __ILRD__OL13940_TRIE__

typedef struct trie trie_t;

/*
* TrieCreateNode description:
*	Create Node and initialize its children to NULL
*
* @param:
*   void
* 
* @return:
*   Returns - A trie_t pointer, in failure returns NULL
*
* complexity
*	Time: O(1).
*	Space O(1)
*/
trie_t *TrieCreate(unsigned int mask);

unsigned int TrieInsert(trie_t *trie, unsigned int key);

unsigned int TrieInsertNext(trie_t *trie);

unsigned int TrieRemove(trie_t *trie, unsigned int key);

void TrieDestroy(trie_t *trie);

size_t TrieCount(trie_t *trie);

unsigned int TrieSearch(trie_t *trie, unsigned int key);
#endif