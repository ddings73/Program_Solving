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

int Children(Node* node) {
	int ret = 0;
	if (node->Left != NULL) ret++;
	if (node->Right != NULL) ret += 2;
	return ret;
}

void Delete(Node* node, int key) {
	
	Node* root = node;

	// key값의 노드 찾기.
	while (node->key != key) {
		if (node->key > key) {
			node = node->Left;
		}
		else {
			node = node->Right;
		}
	}

	switch (Children(node)) {
	case 0:
		if (node->Parent->Left == node) {
			node->Parent->Left = NULL;
		}
		else {
			node->Parent->Right = NULL;
		}

		free(node);
		break;
	case 1: // 왼쪽 자식만 존재
		if (node->Parent->Left == node) {
			node->Parent->Left = node->Left;
			node->Left->Parent = node->Parent;
		}
		else {
			node->Parent->Right = node->Left;
			node->Left->Parent = node->Parent;
		}

		free(node);
		break;
	case 2: // 오른쪽 자식만 존재
		if (node->Parent->Left == node) {
			node->Parent->Left = node->Right;
			node->Right->Parent = node->Parent;
		}
		else {
			node->Parent->Right = node->Right;
			node->Right->Parent = node->Parent;
		}

		free(node);
		break;
	default: // 양쪽 자식 모두 존재
		Node* successor = Successor(node, node->key);
		int tmp = successor->key;
		successor->key = node->key;
		node->key = tmp;

		Delete(successor, successor->key);
		break;
	}

}


void inorder(Node* node, int tab) {
	if (node->Left != NULL) {
		inorder(node->Left, tab + 1);
	}

	int i = 0;
	while (i < tab) {
		cout << "\t";
		i++;
	}

	cout << node->key << '\n';

	if (node->Right != NULL) {
		inorder(node->Right, tab + 1);
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



	inorder(root, 0);

	Delete(root, 6);


	inorder(root, 0);
	
	return 0;
}