#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free */
#include "avl_ntudsa.h"
long long int max_game_numbers;
//int sss=0;

struct data
{
	int* parent; //紀錄每個遊戲的parent遊戲，其API為輸入假的遊戲ID，輸出也是假的遊戲ID
	int* owner;  //紀錄每個遊戲的主人，其API為輸入假的遊戲ID，輸出也是假的OWNER
	int* h;      //紀錄owner所擁有tree的高度，其API為輸入假的OWNER，輸出為tree的高度
}record;

int int_compare(const void *pa, const void *pb, void *param)
{
	int a = *(const int*)pa;
	int b = *(const int*)pb;
	if(a < b)
		return -1;
	else if(a > b)	
		return +1;
	else 
		return 0;
}

int find(int i, const struct data record)
{
	int id=i;
	while(id != record.parent[id])
		id = record.parent[id];
	return id; //輸出真正的遊戲id
}


void merge_tree(struct avl_node *node, struct avl_table *avl_tree)
{
	if(node == NULL)
	{
		return;
	}	
	//	printf("%d ", (node->avl_data));
	if(node->avl_link[0] != NULL || node->avl_link[1] != NULL)
	{
		merge_tree(node->avl_link[0], avl_tree);
		merge_tree(node->avl_link[1], avl_tree);
	}
	for(int i=0; i<node->avl_cnt; i++)
	{
		avl_probe(avl_tree, node->avl_data); //放進比較高的那顆樹裡
	}	
	free(node); //free掉記憶體
}

void traverse(struct avl_node* node)
{
	if(node == NULL)
		return;
	//printf("%d ", (node->avl_data));
	if(node->avl_link[0] != NULL || node->avl_link[1] != NULL)
	{
		traverse(node->avl_link[0]);
		traverse(node->avl_link[1]);
	}
}

void unify_set(int owner_i, int owner_j, int root_i, int  root_j, struct avl_table *avl_tree[], struct data record)
{
	if( record.h[owner_i] >= record.h[owner_j] )
	{
		record.parent[root_j] = root_i;     //將root_j的parent換成root_i
		record.owner[root_j] = owner_i;     //將root_j的主人換成owner_i
		if(record.h[owner_i] == record.h[owner_j])
			record.h[owner_i]++;
		//printf("~~~~~merge_tree() function~~~~~~~~~~~~~\n");
		merge_tree(avl_tree[owner_j]->avl_root, avl_tree[owner_i]);
		//printf("~~~~~merge_tree() close~~~~~~~~~~~~~\n");
		//printf("~~~~~traverse() function~~~~~~~~~~~~~\n");
		//traverse(avl_tree[owner_i]->avl_root);
		//printf("~~~~~traverse() function~~~~~~~~~~~~~\n");
	}
	else
	{
		//printf("yeahhh~~\n");
		record.parent[root_j] = root_i;     //將root_j的parent換成root_i
		record.owner[root_j] = owner_i;     //將root_j的parent換成root_i
		//printf("~~~~~merge_tree() function~~~~~~~~~~~~~\n");
		merge_tree(avl_tree[owner_i]->avl_root, avl_tree[owner_j]);
		//printf("~~~~~merge_tree() close~~~~~~~~~~~~~\n");
		//交換avl_tree[owner_j]與avl_tree[owner_i]指向的位置，因為真正是要將j併入i
		avl_tree[owner_i] = avl_tree[owner_j];
		//printf("~~~~~traverse() function~~~~~~~~~~~~~\n");
		//traverse(avl_tree[owner_i]->avl_root);
		//printf("~~~~~traverse() function~~~~~~~~~~~~~\n");
	}
}

void count_max(const struct avl_node* node, long long int money)
{
	if(node==NULL)
	{
		//printf("~~~~~沒東西買了！~~~~~~~~~~~~~\n");
		return;
	}	
	if(money > (long long int)node->avl_sum[0] ) //可以一次買下全部
	{
		//printf("~~第%d次購買~~~~土豪，買了left subtree~~~~~~~~~~~~~\n", sss++ );
		money -= (long long int)node->avl_sum[0]; //扣掉錢
		max_game_numbers += (long long int)node->avl_cnode[0]; //把左側全部node數全部算進去
		//開始算node本身，分2個部分
		//1. 可以購買
		if(money >= (long long int)node->avl_data * 1ll)
		{
			//printf("~~第%d次購買~~~~買node~~~~~~~~~~~~~\n", sss++ );
			long long int numbers_can_buy = money / (long long int)node->avl_data;
			if(numbers_can_buy > (long long int)node->avl_cnt)      
				numbers_can_buy = (long long int)node->avl_cnt;
			money -= (long long int)node->avl_data * numbers_can_buy;
			max_game_numbers += (long long int)numbers_can_buy;
			//仍然有錢繼續買
			if(money > 0)
			{
				//printf("~~都可以買哩，往右邊走~~~~~~~~~~~~~\n");
				count_max(node->avl_link[1], money);
			}
		}
		else //2. 不能購買
		{
			//printf("~~~~~~~什麼屁都買不了~~~~~~~~~~~\n");
			return;
		}
	}
	else //沒辦法一次買下left subtree全部，只好往下avl_node[0]看看
	{
		//printf("~~~~~無法一次買下左邊~~~~~~~~~~~~~\n");
		count_max(node->avl_link[0], money);  
	}
		
}


int main()
{
	int n, m;
	int cmd, a;      //a為cmd第一個數字
	long long int b; //b為cmd第二個數字
	scanf("%d %d", &n, &m);
	struct avl_table *avl_tree[n]; //n個樹
	record.parent = (int*)malloc(sizeof(int)*n);
	record.owner  = (int*)malloc(sizeof(int)*n);
	record.h      = (int*)malloc(sizeof(int)*n);

	//建樹囉
	for(int i=0; i<n; i++)
	{
		int price = 0;
		scanf("%d", &price);
		avl_tree[i] = avl_create(int_compare, NULL, NULL);
		avl_probe(avl_tree[i], price); //放進對應樹裡
		record.parent[i] = i;
		record.owner[i] = i;
		record.h[i]=0;
	}


	//跑cmd
	for(int i=0; i<m; i++)
	{
		max_game_numbers = 0;
		scanf("%d %d %lld", &cmd, &a, &b);
		if(cmd==1) //找i遊戲的主人，把遊戲搶過來
		{
			//找假的根遊戲ID
			//root_i, root_j為假的遊戲ID，
			int root_i = find(a-1, record); 
			int tmp = (int)b;    int root_j = find(tmp-1, record);
			
			if(root_i != root_j)
				unify_set(record.owner[root_i], record.owner[root_j] , root_i, root_j, avl_tree , record); //record.owner[a-1]為假的OWNER ID
		}
		else if(cmd==2) //找i遊戲的主人，看看自己有多盤那，可以買他多少遊戲
		{
			int root_i = find(a-1, record);
			long long int money = b;
			//printf("~~~~~~~~count_max() function~~~~~~~~~~~~~\n");
			count_max(avl_tree[root_i]->avl_root, money);
			//printf("~~~~~~~~count_max() function~~~~~~~~~~~~~\n");
			printf("%d %lld\n", record.owner[root_i]+1 , max_game_numbers);
		}
	}

	return 0;
}