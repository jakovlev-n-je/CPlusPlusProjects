#include <iostream>
#include <clocale>

using namespace std;

struct Node
{
	int value;
	Node* ptr;

	Node(int value)
	{
		ptr = nullptr;
		this->value = value;
	}
};

Node* add(Node* root, int value);

void clear(Node* root);

Node* combine(Node* negativeRoot, Node* positiveRoot);

void print(Node* root);

Node* remove(Node* root, Node* node);

Node* removeRoot(Node* root);

Node* removeLargest(Node* root);

Node* shiftNegativeNodes(Node* root);

Node* sort(Node* root);

Node* add(Node* root, int value)
{
	if (root == NULL)
	{
		return new Node(value);
	}
	Node* current = root;
	while (current->ptr != nullptr)
	{
		current = current->ptr;
	}
	current->ptr = new Node(value);
	return root;
}

Node* combine(Node* firstRoot, Node* secondRoot)
{
	if (firstRoot == NULL && secondRoot != NULL) {
		return secondRoot;
	}
	else if (firstRoot != NULL && secondRoot == NULL)
	{
		return firstRoot;
	}
	else if (firstRoot == NULL && secondRoot == NULL)
	{
		return NULL;
	}
	Node* current = firstRoot;
	while (current->ptr != nullptr)
	{
		current = current->ptr;
	}
	current->ptr = secondRoot;
	return firstRoot;
}

void clear(Node* root)
{
	if (root == NULL)
	{
		return;
	}
	Node* current = root;
	do
	{
		Node* temp = current;
		current = current->ptr;
		delete temp;
		temp = nullptr;
	} while (current != NULL);
}

void print(Node* root)
{
	if (root == NULL) {
		cout << "Список пуст";
		return;
	}
	Node* current = root;
	do
	{
		cout << current->value << " ";
		current = current->ptr;
	} while (current != NULL);
}

Node* remove(Node* root, Node* node)
{
	if (node == NULL || root == NULL)
	{
		return NULL;
	}
	if (root == node)
	{
		return removeRoot(root);
	}
	Node* current = root;
	while (current->ptr != node)
	{
		current = current->ptr;
	}
	Node* temp = current->ptr;
	current->ptr = temp->ptr == nullptr ? nullptr : temp->ptr;
	delete temp;
	temp = nullptr;
	return root;
}

Node* removeRoot(Node* root)
{
	if (root == NULL)
	{
		return root;
	}
	if (root->ptr == nullptr)
	{
		delete root;
		root = nullptr;
		return NULL;
	}
	else
	{
		Node* temp = root->ptr;
		delete root;
		root = nullptr;
		return temp;
	}
}

Node* removeLargest(Node* root)
{
	if (root == NULL)
	{
		return root;
	}
	Node* current = root;
	Node* maxPositive = NULL;
	Node* maxNegative = NULL;
	do
	{
		if (current->value >= 0 && (maxPositive == NULL || current->value > maxPositive->value))
		{
			maxPositive = current;
		}
		if (current->value < 0 && (maxNegative == NULL || current->value > maxNegative->value))
		{
			maxNegative = current;
		}
		current = current->ptr;
	} while (current != NULL);
	if (maxPositive != NULL) {
		root = remove(root, maxPositive);
	}
	if (maxNegative != NULL)
	{
		root = remove(root, maxNegative);
	}
	return root;
}

Node* shiftNegativeNodes(Node* root)
{
	if (root == NULL)
	{
		return root;
	}
	Node* current = root;
	Node* positives = NULL;
	Node* negatives = NULL;
	do
	{
		if (current->value >= 0) {
			positives = positives == NULL ? new Node(current->value) : add(positives, current->value);
		}
		else
		{
			negatives = negatives == NULL ? new Node(current->value) : add(negatives, current->value);
		}
		current = current->ptr;
	} while (current != NULL);
	negatives = sort(negatives);
	return combine(negatives, positives);
}

Node* sort(Node* root)
{
	if (root == NULL || root->ptr == nullptr)
	{
		return root;
	}
	Node* newRoot = NULL;
	while (root != NULL)
	{
		Node* temp = root;
		root = root->ptr;
		if (newRoot == NULL || temp->value < newRoot->value)
		{
			temp->ptr = newRoot;
			newRoot = temp;
		}
		else
		{
			Node* current = newRoot;
			while (current->ptr != nullptr && temp->value >= current->ptr->value)
				current = current->ptr;
			temp->ptr = current->ptr;
			current->ptr = temp;
		}
	}
	return newRoot;
}

int main()
{
	setlocale(LC_ALL, "RUS");
	cout << "Введите размер списка: ";
	int size;
	cin >> size;
	if (size <= 0)
	{
		return 0;
	}
	Node* list = NULL;
	int i = 0;
	int value;
	cout << "Введите элементы списка: " << endl;
	do
	{
		i++;
		cin >> value;
		list = list == NULL ? new Node(value) : add(list, value);
	} while (i != size);
	cout << "\nСписок после создания: ";
	print(list);
	list = removeLargest(list);
	cout << "\n\nСписок после удаления узлов, содержащих наибольшие отрицательные и неотрицательные значения: ";
	print(list);
	cout << "\n\nСписок после сортировки (в порядке возрастания) элементов, содержащих отрицательные значения: ";
	list = shiftNegativeNodes(list);
	print(list);
	cout << "\n\nВведите новый узел списка: ";
	cin >> value;
	list = add(list, value);
	cout << "\nСписок после добавления конечного элемента: ";
	print(list);
	clear(list);
}
