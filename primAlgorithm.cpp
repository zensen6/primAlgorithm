#include <stdio.h>
#include <stdlib.h>
#define NODE_MAX 10001
#define EDGE_MAX 200001
#define INT_MAX 10000

typedef struct edge {

	int node;
	int cost;

}Edge;

typedef struct pri {

	Edge* heap[EDGE_MAX];
	int count;

}priorityQueue;


typedef priorityQueue PQ;


void init(PQ* pq) {

	for (int i = 0; i < EDGE_MAX; i++) pq->heap[i] = NULL;
	pq->count = 0;

}

int max(int a, int b) {
	return a >= b ? a : b;
}

void swap(Edge* ed1, Edge* ed2) {

	int tmp1 = ed1->node;
	int tmp2 = ed1->cost;
	ed1->node = ed2->node;
	ed1->cost = ed2->cost;
	ed2->node = tmp1;
	ed2->cost = tmp2;
}

void push(PQ* pq, Edge* ed) {

	pq->heap[pq->count] = ed;
	int now = pq->count;
	int parent = (now - 1) / 2;
	while (now >0 && pq->heap[now]->cost < pq->heap[parent]->cost) {
		
		swap(pq->heap[now], pq->heap[parent]);
		now = parent;
		parent = (parent - 1) / 2;

	}
	pq->count++;

}


Edge* pop(priorityQueue *pq) {
	if (pq->count <= 0) return NULL; 
	Edge *res = pq->heap[0];
	pq->count--;
	pq->heap[0] = pq->heap[pq->count];
	int now = 0, leftChild = 1, rightChild = 2;
	int target = now; // 새 원소를 추출한 이후에 하향식으로 힙을 구성합니다. 
	while (leftChild < pq->count) {
		if (pq->heap[target]->cost > pq->heap[leftChild]->cost) target = leftChild; 
		if (pq->heap[target]->cost > pq->heap[rightChild]->cost && rightChild < pq->count) target = rightChild;
		if (target == now) break; // 더 이상 내려가지 않아도 될 때 종료 
		else {
			swap(pq->heap[now], pq->heap[target]);
			now = target;
			leftChild = now * 2 + 1;
			rightChild = now * 2 + 2; 
		}
	}
	return res;
}

typedef struct node {

	node* next;
	Edge* data;

}Node;

int d[NODE_MAX];

void addNode(Node** target, int index, Edge* edge) {               //index 노드에서 (시작)하는 edge넣기이다.
	if (target[index] == NULL) {
		target[index] = (Node*)malloc(sizeof(Node)); 
		target[index]->data = edge; 
		target[index]->next = NULL;
	} 

	else { 
		Node* node = (Node*)malloc(sizeof(Node)); 
		node->data = edge; 
		node->next = target[index];
		target[index] = node; 
	} 
}

int main() {

	Node** adj;
	PQ* pq = (PQ*)malloc(sizeof(PQ));
	init(pq);

	int V, E;
	scanf("%d %d", &V, &E);
	adj = (Node**)malloc(sizeof(Node*) * (V+1)); 
	for (int i = 1; i <= V; i++) {
		adj[i] = NULL;
	}

	
	for (int i = 0; i < E; i++) {

		Edge* ed1 = (Edge*)malloc(sizeof(Edge));
		Edge* ed2 = (Edge*)malloc(sizeof(Edge));
		int a, b, c;   //a에서시작 b에서 종결 c=cost
		scanf("%d %d %d", &a, &b, &c);
		ed1->node = b;
		ed1->cost = c;
		addNode(adj, a, ed1);
		ed2->node = a;
		ed2->cost = c;
		addNode(adj, b, ed2);

	}
	long long res = 0; 
	Edge *start = (Edge*)malloc(sizeof(Edge));
	start->cost = 0; 
	start->node = 1; 
	push(pq, start);
	for (int i = 1; i <= V; i++) {

		int nextnode = -1;
		int nextcost = INT_MAX;
		while (1) {
			Edge* ed = pop(pq);
			if (ed == NULL) break;
			nextnode = ed->node;
			if (!d[nextnode]) {
				d[nextnode] = 1;
				nextcost = ed->cost; break;
				
			}

		}
		//if (nextcost == INT_MAX) printf("연결 그래프가 아닙니다.\n");
		res += nextcost;
		
		Node* cur = adj[nextnode];
		while (cur != NULL) { 
			push(pq, cur->data);
			cur = cur->next;
		}

	}
	printf("%lld\n", res);

}




