#include<iostream>
#include<stdlib.h>
using namespace std;

int counter = 0;

typedef struct Node {
	int key;
	Node* Left;
	Node* Right;
	Node* Parent;
};

Node* makeNode(int key) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->key = key;
	node->Left = node->Right = node->Parent = NULL;
	return node;
}

Node* Search(Node *node, int key) {
	if (node == NULL || node->key == key) {
		return node;
	}// 빈 집합이거나 루트의 key값이 찾는 값일 때
	else if (node->key > key) {
		return Search(node->Left, key);
	}// 찾는 key값이 현재 노드의 값보다 작거나 경우
	else {
		return Search(node->Right, key);
	}// 찾는 key값이 현재 노드의 값보다 큰 경우
}

Node* Minimum(Node* node) {
	while (node->Left != NULL) {
		node = node->Left;
	}
	return node;
}

Node* Maximum(Node* node) {
	while (node->Right != NULL) {
		node = node->Right;
	}
	return node;
}

Node* Successor(Node* node, int key) {
	if (node->Right != NULL) {
		return Minimum(node->Right);
	}
	
	while (node->Parent != NULL && node->Parent->Left != node) {
		node = node->Parent;
	}// 노드의 부모노드가 존재하면서, 현재 노드가 부모노드의 왼쪽 서브트리의 노드일 때까지 반복 

	return node;
}

Node* Predecessor(Node* node, int key) {
	if (node->Left != NULL) {
		return Maximum(node->Left);
	}

	while (node->Parent != NULL && node->Parent->Right != node) {
		node = node->Parent;
	}
	return node;
}

void insert(Node* node, int key) {
	while (node->key < key && node->Right != NULL) {
		node = node->Right;
	}

	while (node->key > key && node->Left != NULL) {
		node = node->Left;
	}

	Node* E = makeNode(key);
	E->Parent = node;

	if (node->key > key) {
		node->Left = E;
	}
	else {
		node->Right = E;
	}
}


void Delete(Node* node, int key) {

	while (node->key != key) {
		if (node->key > key) {
			node = node->Left;
		}
		else {
			node = node->Right;
		}
	}

	if (node->Left == NULL && node->Right == NULL) {
		if (node->Parent->key > node->key) {
			node->Parent->Left = NULL;
		}
		else {
			node->Parent->Right = NULL;
		}
		free(node);
	}
	else if (node->Right != NULL) {
		
		//삭제할 노드보다 크면서 제일 작은 키값의 노드 얻기
		Node* next = Minimum(node->Right);
		
		// 삭제할 노드보다 크면서 제일 작은 노드의 부모노드와의 관계를 끊음
		if (next->Parent->key > next->key) {
			next->Parent->Left = next->Right;
		}
		else {
			next->Parent->Right = next->Right;
		}

		next->Right = node->Right;
		next->Left = node->Left;
		

		//삭제된 노드의 자리를 새로 올라온 노드로 변경
		if (node->Parent->key > node->key) {
			node->Parent->Left = next;
		}
		else {
			node->Parent->Right = next;
		}

		free(node);
	}
	else if(node->Left != NULL) {
		//삭제할 노드보다 작으면서 제일 큰 키값의 노드 얻기
		Node* next = Maximum(node->Left);

		// 삭제할 노드보다 작으면서 제일 큰 노드의 부모노드와의 관계를 끊음
		if (next->Parent->key > next->key) {
			next->Parent->Left = next-> Left;
		}
		else {
			next->Parent->Right = next->Left;
		}

		next->Right = node->Right;
		next->Left = node->Left;

		//삭제된 노드의 자리를 새로 올라온 노드로 변경
		if (node->Parent->key > node->key) {
			node->Parent->Left = next;
		}
		else {
			node->Parent->Right = next;
		}

		free(node);
	}
}


void inorder(Node* node) {
	if (node->Left != NULL) {
		inorder(node->Left);
	}

	cout << node->key << '\n';

	if (node->Right != NULL) {
		inorder(node->Right);
	}
}

int main() {
	Node* root = makeNode(3);


	insert(root, 5);
	insert(root, 1);
	insert(root, 6);
	insert(root, 8);
	insert(root, 7);
	insert(root, 2);
	insert(root, 4);



	inorder(root);

	Delete(root, 6);


	
	return 0;
}