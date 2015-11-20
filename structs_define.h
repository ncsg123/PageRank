/*************************************************************
	Module Name: structs_define.h
	Module Date: 07/14/2015
	Module Auth: LiuDong

	Description: define structs of simulation
		Revision History:
		Date		Rel Ver.		Notes
		07/14/2015  1.0				Module created
 *************************************************************/

/* define block */
#ifndef data_length
#define data_length 1024
#endif
#ifndef block_length
#define block_length 64
#endif
#ifndef block_size
#define block_size data_length/block_length
#endif

typedef struct block{
	int length;
	int number;
}block;
struct block blocks[block_size];

/* define split */
#ifndef split_length
#define split_length block_length
#endif

#ifndef split_size
#define split_size block_size
#endif
typedef struct split{
	int length;
	int number; // the No.
//	int split_DN; // the reflection of splits and dataNode
//	int split_mapper; // the reflection of splits and mappers
}split;
struct split splits[split_size];
int splits_DN[split_size][2]; // the reflection of splits and dataNode
int splits_mappers[split_size][2]; // the reflection of splits and mappers  

/* define mapper */
#ifndef dataNode_size
#define dataNode_size 5
#endif
#ifndef mapper_perDN
#define mapper_perDN 2
#endif
#ifndef mapper_size
#define mapper_size dataNode_size*mapper_perDN
#endif

typedef struct mapperSplitsNode{
	int split_num;
	struct mapperSplitsNode *next;
}mapperSplitsNode;

typedef struct mapper{
	int DN_num; // the No. of DN
	int perDN_size; // the size of mapper in one DN
	int inDN_num; // the No. in one DN
	int total_num; // the No. of all 
	struct mapperSplitsNode cur_splits; // a linklist of reflection  between mapper and splits
}mapper;
struct mapper mappers[mapper_size];

/* define reducer */
#ifndef reducer_size
#define reducer_size 2
#endif

typedef struct reducer{
	int DN_num; // the No. of DN
	int perDN_size; // size of reducers on one DN
	int inDN_num; // the No. of the reducer on one DN
	int total_num;
}reducer;
struct reducer reducers[reducer_size];
