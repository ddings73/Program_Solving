#include<iostream>
using namespace std;
#pragma warning(disable:4996);

typedef struct Node {
	int key;
	char color;

	Node* Left;
	Node* Right;
	Node* Parent;
}Node;


Node* makeNode(int key) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->key = key;
	node->color = 'R';
	node->Left = node->Right = node->Parent = NULL;
	return node;
}

Node* Search(Node* node, int key) {
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

Node* Successor(Node* node, int key) {
	return Minimum(node->Right);
}

Node* insert(Node* node, int key) {

	while (1) {
		if(node->key < key && node->Right != NULL)
			node = node->Right;
		else if (node->key > key && node->Left != NULL) {
			node = node->Left;
		}
		else {
			break;
		}
	}


	Node* E = makeNode(key);
	E->Parent = node;

	if (node->key > key) {
		node->Left = E;
	}
	else {
		node->Right = E;
	}

	return E;
}

Node* LeftRotate(Node* now) {
	// 내 부모노드를 우측노드의 부모노드로 만듬
	now->Right->Parent = now->Parent;

	if (now->Parent != NULL) {
		if (now->Parent->Right == now) {
			now->Parent->Right = now->Right;
		}
		else {
			now->Parent->Left = now->Right;
		}
	}
	// 내 부모노드를 오른쪽에 있던 노드로 만듬
	now->Parent = now->Right;

	// 내 오른쪽 노드를 부모 노드의 왼쪽 노드로 만듬
	now->Right = now->Parent->Left;

	if (now->Right != NULL) {
		// 내 오른쪽 노드의 부모를 나로 갱신
		now->Right->Parent = now;
	}

	// 내 부모노드의 왼쪽 방향을 나로 갱신
	now->Parent->Left = now;

	return now;
}

Node* RightRotate(Node* now) {
	// 내 부모노드를 왼쪽노드의 부모노드로 바꿈
	now->Left->Parent = now->Parent;

	if (now->Parent != NULL) {
		if (now->Parent->Right == now) {
			now->Parent->Right = now->Left;
		}
		else {
			now->Parent->Left = now->Left;
		}
	}
	// 내 부모노드를 왼쪽에 있던 노드로 변경
	now->Parent = now->Left;

	// 내 왼쪽 노드를 부모노드의 오른쪽 노드로 만듬
	now->Left = now->Parent->Right;

	if (now->Left != NULL) {
		// 내 왼쪽 노드의 부모를 나로 갱신
		now->Left->Parent = now;
	}

	// 내 부모노드의 오른쪽 방향을 나로 갱신
	now->Parent->Right = now;

	return now;
}

Node* RBTinsert(Node* node, int key) {
	Node* now = insert(node, key);

	while (now->Parent != NULL && now->Parent->color == 'R') {
		Node* p = now->Parent;
		if (p->Parent->Left == p) { 
			// 부모노드 위치가 왼쪽인 경우
			Node* uncle = p->Parent->Right;
			if (uncle == NULL || uncle->color == 'B') {
				// 형제노드가 BLACK
				if(p->Right == now){
					now = LeftRotate(p);
				}

				now->Parent->color = 'B';
				now->color = 'R';
				now->Parent->Parent->color = 'R';
				now = RightRotate(now->Parent->Parent);

			}
			else {
				// 형제노드가 RED
				now = p->Parent;
				now->color = 'R';
				now->Left->color = now->Right->color = 'B';
			}
		}
		else { 
			// 부모노드 위치가 오른쪽인 경우
			Node* uncle = p->Parent->Left;
			if (uncle == NULL || uncle->color == 'B') {
				if (p->Left == now) {
					now = RightRotate(p);
				}

				now->Parent->color = 'B';
				now->color = 'R';
				now->Parent->Parent->color = 'R';
				now = LeftRotate(now->Parent->Parent);
			}
			else {
				now = p->Parent;
				now->color = 'R';
				now->Left->color = now->Right->color = 'B';
			}
		}
	}

	if (node->Parent != NULL) {
		node = node->Parent;
	}
	node->color = 'B';
	return node;
}

Node* RBTDeletefix(Node* node, Node* check) {
	if (check->color == 'R') {
		check->color = 'B';
		return node;
	}

	while (check->Parent != NULL && check->color == 'B') {
		Node* p = check->Parent;
		if (p->Left == check) {
			Node* uncle = p->Right;
			if (uncle->color == 'R') {
				p->color = 'R';
				uncle->color = 'B';
				p = LeftRotate(p);
				uncle = p->Right;
			}

			if ( (uncle->Left == NULL || uncle->Left->color == 'B') && (uncle->Right == NULL || uncle->Right->color == 'B') ) {
				uncle->color = 'R';

				if (check->key == -1) {
					p->Left = NULL;
				}
				if (p->color == 'R') {
					p->color = 'B';
					break;
				}
				else {
					check = p;
				}
			}
			else if (uncle->Right == NULL || uncle->Right->color == 'B') {
				uncle->color = 'R';
				uncle->Left->color = 'B';
				RightRotate(uncle);
			}
			else if (uncle->Right->color == 'R') {
				uncle->color = p->color;
				p->color = 'B';
				uncle->Right->color = 'B';

				if (check->key == -1) {
					p->Left = NULL;
				}

				LeftRotate(p);

				break;
			}
		}
		else {
			Node* uncle = p->Left;
			if (uncle->color == 'R') {
				p->color = 'R';
				uncle->color = 'B';
				p = RightRotate(p);
				uncle = p->Left;
			}

			if (uncle == NULL) {
				p->color = 'R';

			}
			else if ((uncle->Left == NULL || uncle->Left->color == 'B') && (uncle->Right == NULL || uncle->Right->color == 'B')) {
				uncle->color = 'R';

				if (check->key == -1) {
					p->Right = NULL;
				}
				if (p->color == 'R') {
					p->color = 'B';
					break;
				}
				else {
					check = p;
				}
			}
			else if (uncle->Left == NULL || uncle->Left->color == 'B') {
				uncle->color = 'R';
				uncle->Right->color = 'B';
				LeftRotate(uncle);
			}
			else if (uncle->Left->color == 'R') {
				uncle->color = p->color;
				p->color = 'B';
				uncle->Left->color = 'B';

				if (check->key == -1) {
					p->Right = NULL;
				}

				RightRotate(p);

				break;
			}
		}
	}
	while (node->Parent != NULL) {
		node = node->Parent;
	}
	return node;
}

Node* Delete(Node* node, int key) {

	Node* ret = node;

	// key값의 노드 찾기.
	while (node->key != key) {
		if (node->key > key) {
			node = node->Left;
		}
		else {
			node = node->Right;
		}
	}

	Node* deleted;

	if (node->Left == NULL || node->Right == NULL) {
		deleted = node;
	}
	else {
		deleted = Successor(node, node->key);
	}

	Node* focus = (Node*)malloc(sizeof(Node));
	if (deleted->Left != NULL) {
		focus = deleted->Left;
	}
	else {
		if (deleted->Right == NULL) {
			focus->key = -1;
			focus->color = 'B';
		}
		else {
			focus = deleted->Right;
		}
	}

	if (focus != NULL) {
		focus->Parent = deleted->Parent;
	}


	// 삭제할게 루트이면
	if (deleted->Parent == NULL) {
		if (focus->key != -1) {
			deleted = focus;
			return focus;
		}
		else
			return NULL;
	}
	else if (deleted->Parent->Left == deleted) {
		deleted->Parent->Left = focus;
	}
	else {
		deleted->Parent->Right = focus;
	}

	if (deleted != node) {
		node->key = deleted->key;
	}

	if (deleted->color != 'R') {
		ret = RBTDeletefix(ret, focus);
	}
	else {
		if (focus->key == -1) {
			if (focus->Parent->Right == focus) {
				focus->Parent->Right = NULL;
			}
			else {
				focus->Parent->Left = NULL;
			}
			focus = NULL;
		}
	}

	return ret;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	freopen("rbt.inp", "r", stdin);
	freopen("rbt.out", "w", stdout);
	
	char op;
	int key;

	Node* root = NULL;
	while (1) {
		cin >> op >> key;
		if (key == -1) break;

		switch (op) {
		case 'i':
			if (root == NULL) {
				root = makeNode(key);
				root->color = 'B';
			}
			else {
				root = RBTinsert(root, key);
			}
			break;
		case 'd':
			root = Delete(root, key);
			break;
		default:
			Node* node = Search(root, key);
			cout << "color(" << key << "): ";
			
			if (node->color == 'R')
				cout << "RED\n";
			else
				cout << "BLACK\n";

			break;
		}
;	}
	return 0;
}