#include <stdlib.h> // for use malloc()
#include "structs_define.h"
void initialize_blocks() {
	/* initialize the block */
	int i;
	for(i = 0; i <  block_size; i++) {
		blocks[i].length = block_length;
		blocks[i].number = i;
	}
}

void initialize_splits() {
	/* initialize the split */
	int i;
	for (i = 0; i < split_size; i++) {
		splits[i].length = split_size;
		splits[i].number = i;
	}
}

void initialize_splits_DN() {
	/* initialize the splits_DN table */
	int i = 0;
	for(i = 0; i < split_size; i++) {
		splits_DN[i][0] = i;
		splits_DN[i][1] = i % dataNode_size;
	}
	
}

void initialize_splits_mappers() {
	/* initialize the splits_mappers table */
	int i = 0;
	for(i = 0; i < split_size; i++) {
		splits_mappers[i][0] = i;
		splits_mappers[i][1] = i % mapper_size;
	}
}

void initialize_mappers() {
	/* initialize the mapper*/
	int i,j;
	for(i = 0; i < mapper_size; i++) {
		mappers[i].DN_num = i % dataNode_size;
		mappers[i].perDN_size = mapper_perDN;
		mappers[i].inDN_num = i % dataNode_size % mapper_perDN;
		mappers[i].total_num = i;
		
		/*initialize the mapper_splits linked list*/
		struct mapperSplitsNode *p = &mappers[i].cur_splits;
		p->next = NULL;
		p->split_num = -1; // when no splits, the value equals -1
		for(j = 0; j < split_size; j++) {
			if(splits_mappers[j][1] == i) {
				p->split_num = splits_mappers[j][0]; // refresh the value
				mapperSplitsNode *q = (mapperSplitsNode *)malloc(sizeof(mapperSplitsNode));
				q->split_num = -1;
				q->next = p->next;
				p->next = q;
				p = q;
			}
		}
	}
}

void initialize_reducers() {
	/* initialize the reducer*/
	int i = 0;
	for(i = 0; i < reducer_size; i++) {
		reducers[i].DN_num = i % dataNode_size;
		reducers[i].inDN_num = i % reducer_size;
		reducers[i].inDN_num = i % dataNode_size ;
		reducers[i].total_num = i;
	}
}

void initialize() {
	initialize_blocks(); // initialize the structs blocks[] 
	initialize_splits(); // initialize the structs splits[] 

	initialize_splits_DN(); // initialize the splits_DN table
	initialize_splits_mappers(); // initialize the splits_mappers table

	initialize_mappers() ; // initialize the structs mappers[], must be called after initialize_splits_mappers()
	initialize_reducers(); // initialize the structs reducers[]
}

/* for building
void main() {
	
}
*/