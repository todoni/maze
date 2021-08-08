#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int map[8][8] ={
	{0, 0, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 0, 1, 1, 1, 1},
	{1, 1, 1, 0, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0},
	{1, 1, 1, 1, 1, 1, 1, 0}
};

typedef struct s_node
{
	int				x;
	int				y;
	struct s_node *next;
}				t_node;


void	push(t_node **node, int x, int y)
{
	t_node 	*new;
	t_node	*temp;


	new = malloc(sizeof(t_node));
	if (!new)
		return ;
	new->x = x;
	new->y = y;
	if (node == NULL || *node == NULL)
		*node = new;
	else
	{
		temp = *node;
		*node = new;
		(*node)->next = temp;
	}
}

void	pop(t_node **node) // remove a head list
{
	t_node *temp;

	if (node == NULL || *node == NULL)
		return ;
	temp = *node;
	*node = (*node)->next;
	free(temp);
	temp = NULL;
}

void print_stack(t_node *node)
{
	while (node->next != NULL)
	{
		printf("(%d, %d) <-", node->x, node->y);
		node = node->next;
	}
	printf("(%d, %d)", node->x, node->y);
}

void print_result(t_node *node, int x, int y)
{
	printf("출구는 (%d, %d) 입니다.\n\n", x, y);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	print_stack(node);
	exit(0);
}

void	dfs(t_node **node, int x, int y)
{
	if (x == 0 && y == 0)
		push(node, x, y);
	else if ((*node)->x != x || (*node)->y != y)
		push(node, x, y);
	map[x][y] = 9;

	if (x == 7 && y == 7)
		print_result(*node, x, y);
	if (x > 0 && map[x - 1][y] == 0)
		dfs(node, x - 1, y);
	if (y < 8 && map[x][y + 1] == 0)
		dfs(node, x, y + 1);
	if (y > 0 && map[x][y - 1] == 0)
		dfs(node, x, y - 1);
	if (x < 8 && map[x + 1][y] == 0)
		dfs(node, x + 1, y);

	map[x][y] = 2;
	pop(node);
	dfs(node, (*node)->x, (*node)->y);
}

int main()
{
	t_node *stack = NULL;

	dfs(&stack, 0, 0);
}
