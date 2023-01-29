
#include <assert.h>
#include <stdlib.h> /* malloc free */
#include <stddef.h> /* size_t */

#include "hash_table.h"
#include "slist.h"

/*
Reviewer: Yahav
*/

typedef struct hash_entry hash_entry_t;

/*
static global compare function for keys, used to compare keys
*/
static compare_func_t gloabl_cmp_func = NULL;
static action_func_t global_action_func = NULL;

/*
hash table struct consisting of the hash function, size of s_lists array, and pointer to the array itself
*/
struct hash_table
{
	hash_func_t hash_func;
	size_t array_size;
	void *index_array;
};

/*
the entry holding key and data pair, will be held as data in s_list node
*/
struct hash_entry
{
	void *plain_key;
	void *value;
};

/*
create a hash entry, return NULL if failed, otherwise the entry
*/
static hash_entry_t *HashEntryCreate(const void *key,const void *value)
{
	hash_entry_t *new_entry = NULL;
	
	assert(key);
	assert(value);
	
	new_entry = (hash_entry_t *)malloc(sizeof(hash_entry_t));
	if(NULL == new_entry)
	{
		return NULL;
	}
	
	new_entry->plain_key = (void*)key;
	new_entry->value = (void*)value;
	
	return new_entry;
}

/*
destroy a hash entry
*/
static void HashEntryDestroy(hash_entry_t *entry)
{
	assert(entry);
	free(entry);
}

/*
get the entry value
*/
static void *HashEntryGetValue(hash_entry_t *entry)
{
	assert(entry);
	return entry->value;
}

/*
get the entry plaintext key
*/
static void *HashEntryGetKey(hash_entry_t *entry)
{
	assert(entry);
	return entry->plain_key;
}

/*
function that frees entries, used for freeing entire lists worth of entries when destroying a list in ForEach function
*/
static int FreeHashEntry(void *entry, void *parameter)
{
	assert(entry);
	HashEntryDestroy(entry);
	return 0;
	
	(void)parameter;
}

/*
used as matching function in SListFind, uses the global cmp_func to match an entry to a distinct key
*/
static int HashEntryCmp(const void *entry, void *key)
{
	assert(entry);
	assert(key);
	
	return gloabl_cmp_func(HashEntryGetKey((hash_entry_t *)entry), key);
}

/*
returns a pointer to a list by key and hash function
*/
static s_list_t *HashFindList(const hash_table_t *hash_table, const void *key)
{
	size_t index = 0;
	s_list_t *found_list = NULL;
	
	index = hash_table->hash_func(key);
	
	found_list = ((s_list_t*)*((size_t*)((char*)hash_table->index_array + sizeof(s_list_t*) * index)));
	
	return found_list;
}

/*
create the hash table struct and allocate memory for the index array, also create and set empty lists for each array entry
*/
hash_table_t *HashCreate(hash_func_t hash_func, size_t table_size, compare_func_t compare_func)
{
	size_t i = 0;
	hash_table_t *new_table = NULL;
	
	assert(hash_func);
	assert(compare_func);
	assert(table_size);
	
	gloabl_cmp_func = compare_func;
	
	new_table = (hash_table_t*)malloc(sizeof(hash_table_t) + (table_size * sizeof(s_list_t*)));
	if(NULL == new_table)
	{
		return NULL;
	}
	
	new_table->hash_func = hash_func;
	new_table->array_size = table_size;
	
	/* set the member to point to start of the index array itself */
	new_table->index_array = (void*)((char*)&new_table->index_array + sizeof(new_table->index_array));
	
	
	/* create empty s_lists and set a pointer to each one in each array entry */
	for(; i < new_table->array_size; ++i)
	{
		/* calculate list pointer poistion in array using pointer arith */
		*((size_t*)((char*)new_table->index_array + sizeof(s_list_t*) * i)) = (size_t) SListCreate();
	}
	
	return new_table;
}

/*
iterate over the entire table, deleting hash entries from each node in each list, then deleting the list. after finishing with all the lists free the table struct itself
*/
void HashDestroy(hash_table_t *hash_table)
{
	size_t i = 0;
	size_t array_size = 0;
	s_list_t *list = NULL;
	
	assert(hash_table);
	
	array_size = hash_table->array_size;
	
	for(; i < array_size; ++i)
	{
		/* calculate list pointer poistion in array using pointer arith */
		list = ((s_list_t*)*((size_t*)((char*)hash_table->index_array + sizeof(s_list_t*) * i)));
		
		SListForEach(list, SListBegin(list), SListEnd(list), FreeHashEntry, NULL);
		
		SListDestroy(list);
	}
	
	free(hash_table);
}

/*
find a single node matching the key, remove its hash entry and then remove it from the list.
return 1 if the entry doesnt exist, 0 for success
*/
int HashRemove(hash_table_t *hash_table, const void *key)
{
	s_list_iterator_t found_node = NULL;
	s_list_t *list = NULL;
	
	assert(hash_table);
	assert(key);
	
	list = HashFindList(hash_table, key);
	
	found_node = SListFind(SListBegin(list), SListEnd(list), HashEntryCmp, (void*)key);
	
	if(NULL == found_node)
	{
		return 1;
	}
	
	HashEntryDestroy(SListGet(list, found_node));
	
	SListRemove(list, found_node);
	
	return 0;
}

/*
enter new hash entry, checking if it doesnt exist before doing so.
return 1 if an error occured, 0 if successful
*/
int HashInsert(hash_table_t *hash_table, const void *key,const void *value)
{
	s_list_iterator_t found_node = NULL;
	s_list_t *list = NULL;
	hash_entry_t *new_entry = NULL;
	
	assert(hash_table);
	assert(key);
	assert(value);
	
	list = HashFindList(hash_table, key);
	
	found_node = SListFind(SListBegin(list), SListEnd(list), HashEntryCmp, (void*)key);
	
	if(NULL != found_node)
	{
		return 1;
	}
	
	new_entry = HashEntryCreate(key, value);
	
	if(NULL == new_entry)
	{
		return 1;
	}
	
	SListAdd(list, SListBegin(list), new_entry);
	
	return 0;
}

/*
iterate over the table counting number of nodes in each list and summing it all
*/
size_t HashSize(const hash_table_t *hash_table)
{
	size_t sum = 0;
	size_t i = 0;
	size_t array_size = 0;
	s_list_t *list = NULL;
	
	assert(hash_table);
	
	array_size = hash_table->array_size;
	
	for(; i < array_size; ++i)
	{
		/* calculate list pointer poistion in array using pointer arith */
		list = ((s_list_t*)*((size_t*)((char*)hash_table->index_array + sizeof(s_list_t*) * i)));
		sum += SListSize(list);
	}
	
	return sum;
}

/*
iterate over the table, if at least one list isnt empty return 0, if all lists are empty return 1
*/
int HashIsEmpty(const hash_table_t *hash_table)
{
	size_t i = 0;
	size_t array_size = 0;
	s_list_t *list = NULL;
	
	assert(hash_table);
	
	array_size = hash_table->array_size;
	
	for(; i < array_size; ++i)
	{
		/* calculate list pointer poistion in array using pointer arith */
		list = ((s_list_t*)*((size_t*)((char*)hash_table->index_array + sizeof(s_list_t*) * i)));
		if(0 != SListSize(list))
		{
			return 0;
		}
	}
	
	return 1;
}

/*
find and return a value corresponding to a distinct key, if no such entry exists return NULL
*/
void *HashFind(const hash_table_t *hash_table, const void *key)
{
	s_list_iterator_t found_node = NULL;
	s_list_t *search_list = NULL;
	
	assert(hash_table);
	assert(key);
	
	search_list = HashFindList(hash_table, key);
	
	found_node = SListFind(SListBegin(search_list), SListEnd(search_list), HashEntryCmp, (void*)key);
	
	if(NULL == found_node)
	{
		return NULL;
	}
	
	return HashEntryGetValue(SListGet(search_list, found_node));
}

/* 
wrap action function to work on entry values
*/
static int HashValueForeach(void *data, void* parameter)
{
	return global_action_func(HashEntryGetValue(data), parameter);
}

/*
iterate over all the lists in the table, performing action func on each.
*/
int HashForEach(hash_table_t *hash_table, action_func_t action_func, void *param)
{
	int action_retval = 0;
	size_t i = 0;
	size_t array_size = 0;
	s_list_t *list = NULL;
	
	
	assert(hash_table);
	assert(action_func);
	
	global_action_func = action_func;
	
	array_size = hash_table->array_size;
	
	for(; i < array_size; ++i)
	{
		/* calculate list pointer poistion in array using pointer arith */
		list = ((s_list_t*)*((size_t*)((char*)hash_table->index_array + sizeof(s_list_t*) * i)));
		
		action_retval = SListForEach(list, SListBegin(list), SListEnd(list), HashValueForeach, param);
		
		if(action_retval)
		{
			return action_retval;
		}
	}
	
	/* reset the global action function */
	global_action_func = NULL;
	
	return 0;
}





