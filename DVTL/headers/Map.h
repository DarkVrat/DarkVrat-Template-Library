#ifndef DVTL_MAP_H
#define DVTL_MAP_H

#include "Utility.h"
#include "Initializer_list.h"

namespace DVTL {
template<typename T_Key, typename T_Value>
class Map {
public:
	//declaring iterators
	struct Node;
	class iterator;
	class const_iterator;

	//constructors, operators= and destructor
	Map();
	Map(const Map& right);
	Map(Map&& right);
	Map(Initializer_list<Pair<T_Key, T_Value>> init_list);

	Map& operator=(const Map& right);
	Map& operator=(Map&& right);

	~Map();

	//references to Map elements
	T_Value& At(const T_Key& key);
	T_Value& operator[](const T_Key& key);
	const T_Value& At(const T_Key& key) const;
	const T_Value& operator[](const T_Key& key) const;
	Node* getroot() { return m_root; }
	
	iterator Find(const T_Key& key);
	const_iterator Find(const T_Key& key) const;

	//working with data
	void Clear();
	bool Empty() const;
	bool Contains(const T_Key& key) const;
	size_t Size() const;
	void Swap(Map<T_Key, T_Value>& right);

	//adding and removing elements to a Map
	iterator Erase(const T_Key& key);
	iterator Insert(Pair<T_Key, T_Value>&& pair);
	iterator Insert(const Pair<T_Key, T_Value>& pair); 
	iterator Insert(const T_Key& key, const T_Value& val);

	//getting iterators begin and end
//	iterator Begin();
	iterator End() { return iterator(nullptr); }
//	const_iterator Begin() const;
	const_iterator End() const { return const_iterator(nullptr); }
//	const_iterator CBegin() const;
	const_iterator CEnd() const { return const_iterator(nullptr); }
private:
	Node* m_root;

	void deleteNodeWithChild(Node* ptr);
	void updateHeightAndSize(Node* node);
	Node* insertInTree(Node* node, Pair<T_Key, T_Value>&& pair);
	Node* balanceTree(Node* node);
	Node* rotateLeft(Node* node);
	Node* rotateRight(Node* node);
	int getHeight(Node* node);
	int getBalanceFactor(Node* node);
	size_t getSize(Node* node);
};

template<typename T_Key, typename T_Value>
struct Map<T_Key, T_Value>::Node {
	Pair<T_Key, T_Value> data;
	Node* parent;
	Node* left;
	Node* right;
	int height;
	size_t size;

	Node(const Pair<T_Key, T_Value>& value) : data(value), parent(nullptr), left(nullptr), right(nullptr), height(1), size(1) {}
	Node(Pair<T_Key, T_Value>&& value) : data(Move(value)), parent(nullptr), left(nullptr), right(nullptr), height(1), size(1) {}

	Node(const Node& right, Node* parentNode) : data(right.data), parent(parentNode), left(new Node(*right.left, this)), right(new Node(*right.right, this)), height(right.height), size(right.size) {}
	~Node() {};
};

//defining an iterator interface
template<typename T_Key, typename T_Value>
class Map<T_Key, T_Value>::iterator
{
public:
	//constructors, operators= and destructor
	iterator(typename Map<T_Key, T_Value>::Node* ptr) :ptr(ptr) {}
	iterator(const iterator& right) :ptr(right.ptr) {}
	iterator(iterator&& right) noexcept :ptr(right.ptr) { right.ptr = nullptr; }
	iterator& operator=(const iterator& right) { ptr = right.ptr; return *this; }
	iterator& operator=(iterator&& right) noexcept { ptr = right.ptr; right.ptr = nullptr; return *this; }
	~iterator() {}

	//logical operators
	bool operator==(const iterator& other) const { return ptr == other.ptr; }
	bool operator!=(const iterator& other) const { return ptr != other.ptr; }

	//data access
	Pair<T_Key, T_Value>& operator*() const { return ptr->data; }
	Pair<T_Key, T_Value>* operator->() const { return &(ptr->data); }

	//mathematical operators
	iterator& operator++();
	iterator& operator--();
	const iterator operator++(int);
	const iterator operator--(int);

	//transformation
	typename Map<T_Key, T_Value>::const_iterator get_const() const { return  typename Map<T_Key, T_Value>::const_iterator(*this); }

	friend class  Map<T_Key, T_Value>;
private:
	typename Map<T_Key, T_Value>::Node* get() const { return ptr; }
	typename Map<T_Key, T_Value>::Node* ptr;
};

template<typename T_Key, typename T_Value>
class Map<T_Key, T_Value>::const_iterator
{
public:
	//constructors, operators= and destructor
	const_iterator(const typename Map<T_Key, T_Value>::Node* ptr) :ptr(ptr) {}
	const_iterator(const typename Map<T_Key, T_Value>::iterator& it) :ptr(it.ptr) {}
	const_iterator(const const_iterator& right) :ptr(right.ptr) {}
	const_iterator(const_iterator&& right) noexcept :ptr(right.ptr) { right.ptr = nullptr; }
	const_iterator& operator=(const const_iterator& right) { ptr = right.ptr; return *this; }
	const_iterator& operator=(const_iterator&& right) noexcept { ptr = right.ptr; right.ptr = nullptr; return *this; }
	~const_iterator() {}

	//logical operators
	bool operator==(const const_iterator& other) const { return ptr == other.ptr; }
	bool operator!=(const const_iterator& other) const { return ptr != other.ptr; }

	//data access
	const Pair<T_Key, T_Value>& operator*() const { return ptr->data; }
	const Pair<T_Key, T_Value>* operator->() const { return &(ptr->data); }

	//mathematical operators
	const_iterator& operator++();
	const_iterator& operator--();
	const const_iterator operator++(int);
	const const_iterator operator--(int);

	friend class Map<T_Key, T_Value>;
private:
	typename Map<T_Key, T_Value>::Node* get() const { return const_cast<typename Map<T_Key, T_Value>::Node*>(ptr); }
	const typename Map<T_Key, T_Value>::Node* ptr;
};

template<typename T_Key, typename T_Value>
inline Map<T_Key, T_Value>::Map():m_root(nullptr){}

template<typename T_Key, typename T_Value>
inline Map<T_Key, T_Value>::Map(const Map& right):m_root(new Node(*right.m_root, nullptr)){}

template<typename T_Key, typename T_Value>
inline Map<T_Key, T_Value>::Map(Map&& right):m_root(right.m_root)
{
	right.m_root = nullptr;
}

template<typename T_Key, typename T_Value>
inline Map<T_Key, T_Value>::Map(Initializer_list<Pair<T_Key, T_Value>> init_list)
{
	for (int i = 0; i < init_list.Size(); i++)
		this->Insert(*(init_list.Begin() + i));
}

template<typename T_Key, typename T_Value>
inline Map<T_Key, T_Value>& Map<T_Key, T_Value>::operator=(const Map& right)
{
	if (m_root == right.m_root)return *this;

	deleteNodeWithChild(m_root);
	m_root = new Node(*right.m_root, nullptr);

	return *this;
}

template<typename T_Key, typename T_Value>
inline Map<T_Key, T_Value>& Map<T_Key, T_Value>::operator=(Map&& right)
{
	if (m_root == right.m_root)return *this;

	deleteNodeWithChild(m_root);
	m_root = right.m_root;
	right.m_root = nullptr;

	return *this;
}

template<typename T_Key, typename T_Value>
inline Map<T_Key, T_Value>::~Map()
{
	deleteNodeWithChild(m_root);
}

template<typename T_Key, typename T_Value>
inline T_Value& Map<T_Key, T_Value>::At(const T_Key& key)
{
	Node* currentNode = m_root;

	while (currentNode != nullptr) {
		if (Less(currentNode->data.First, key))
			currentNode = currentNode->right;
		else if (Less(key, currentNode->data.First))
			currentNode = currentNode->left;
		else
			return currentNode->data.Second;
	}
	
	throw "out of range map";
	return T_Value();
}

template<typename T_Key, typename T_Value>
inline T_Value& Map<T_Key, T_Value>::operator[](const T_Key& key)
{
	return At(key);
}

template<typename T_Key, typename T_Value>
inline const T_Value& Map<T_Key, T_Value>::At(const T_Key& key) const
{
	Node* currentNode = m_root;

	while (currentNode != nullptr) {
		if (Less(currentNode->data.First, key))
			currentNode = currentNode->right;
		else if (Less(key, currentNode->data.First))
			currentNode = currentNode->left;
		else
			return currentNode->data.Second;
	}

	throw "out of range map";
	return T_Value();
}

template<typename T_Key, typename T_Value>
inline const T_Value& Map<T_Key, T_Value>::operator[](const T_Key& key) const
{
	return At(key);
}

template<typename T_Key, typename T_Value>
inline typename Map<T_Key, T_Value>::iterator Map<T_Key, T_Value>::Find(const T_Key& key)
{
	Node* node = m_root;
	while (node!=nullptr)
	{
		if (Less(node->data.First, key))
			node = node->right;
		else if (Less(key, node->data.First))
			node = node->left;
		else break;
	}
	return iterator(node);
}

template<typename T_Key, typename T_Value>
inline typename Map<T_Key, T_Value>::const_iterator Map<T_Key, T_Value>::Find(const T_Key& key) const
{
	Node* node = m_root;
	while (node != nullptr)
	{
		if (Less(node->data.First, key))
			node = node->right;
		else if (Less(key, node->data.First))
			node = node->left;
		else break;
	}
	return const_iterator(node);
}

template<typename T_Key, typename T_Value>
inline void Map<T_Key, T_Value>::Clear()
{
	deleteNodeWithChild(m_root);
	m_root = nullptr;
}

template<typename T_Key, typename T_Value>
inline bool Map<T_Key, T_Value>::Empty() const
{
	return m_root==nullptr;
}

template<typename T_Key, typename T_Value>
inline bool Map<T_Key, T_Value>::Contains(const T_Key& key) const
{
	Node* currentNode = m_root;

	while (currentNode != nullptr) {
		if (Less(currentNode->data.First, key))
			currentNode = currentNode->right;
		else if (Less(key, currentNode->data.First))
			currentNode = currentNode->left;
		else
			return true;
	}

	return false;
}

template<typename T_Key, typename T_Value>
inline size_t Map<T_Key, T_Value>::Size() const
{
	return m_root == nullptr ? 0 : m_root->size;
}

template<typename T_Key, typename T_Value>
inline void Map<T_Key, T_Value>::Swap(Map<T_Key, T_Value>& right)
{
	Node* tempNode = right.m_root;
	right.m_root = m_root;
	m_root = tempNode;
}

template<typename T_Key, typename T_Value>
inline typename Map<T_Key, T_Value>::iterator Map<T_Key, T_Value>::Erase(const T_Key& key)
{
	//make erase
	return iterator();
}

template<typename T_Key, typename T_Value>
inline typename Map<T_Key, T_Value>::iterator Map<T_Key, T_Value>::Insert(Pair<T_Key, T_Value>&& pair)
{
	T_Key copyForFind = pair.First;
	m_root = insertInTree(m_root, Move(pair));
	return Find(copyForFind);
}

template<typename T_Key, typename T_Value>
inline typename Map<T_Key, T_Value>::iterator Map<T_Key, T_Value>::Insert(const Pair<T_Key, T_Value>& pair)
{
	return Insert(Pair<T_Key, T_Value>(pair));
}

template<typename T_Key, typename T_Value>
inline typename Map<T_Key, T_Value>::iterator Map<T_Key, T_Value>::Insert(const T_Key& key, const T_Value& val)
{
	return Insert(Pair<T_Key, T_Value>(key, val));
}

template<typename T_Key, typename T_Value>
inline void Map<T_Key, T_Value>::deleteNodeWithChild(Node* ptr)
{
	if (ptr == nullptr) return;

	deleteNodeWithChild(ptr->left);
	deleteNodeWithChild(ptr->right);
	delete ptr;
}

template<typename T_Key, typename T_Value>
inline typename Map<T_Key, T_Value>::Node* Map<T_Key, T_Value>::insertInTree(Node* node, Pair<T_Key, T_Value>&& pair)
{
	if (node == nullptr)
		return new Node(Move(pair));

	if (pair.First < node->data.First) {
		node->left = insertInTree(node->left, Move(pair));
		node->left->parent = node;
	}
	else if (pair.First > node->data.First) {
		node->right = insertInTree(node->right, Move(pair));
		node->right->parent = node;
	}
	else {
		node->data.Second = pair.Second;
		return node;
	}

	return balanceTree(node);
}

template<typename T_Key, typename T_Value>
inline typename Map<T_Key, T_Value>::Node* Map<T_Key, T_Value>::balanceTree(Node* node)
{
	updateHeightAndSize(node);

	if (getBalanceFactor(node) > 1) {
		if (getBalanceFactor(node->left) < 0)
			node->left = rotateLeft(node->left);
		return rotateRight(node);
	}

	if (getBalanceFactor(node) < -1) {
		if (getBalanceFactor(node->right) > 0)
			node->right = rotateRight(node->right);
		return rotateLeft(node);
	}

	return node;
}

template<typename T_Key, typename T_Value>
inline typename Map<T_Key, T_Value>::Node* Map<T_Key, T_Value>::rotateLeft(Node* node)
{
	Node* newRoot = node->right;

	newRoot->parent = node->parent;
	if (newRoot->parent != nullptr) {
		if (newRoot->parent->left == node) 
			newRoot->parent->left = newRoot;
		else
			newRoot->parent->right = newRoot;
	}

	node->right = newRoot->left;
	newRoot->left = node;

	node->parent = newRoot;
	if (node->right != nullptr) node->right->parent = node;

	updateHeightAndSize(node);
	updateHeightAndSize(newRoot);
	return newRoot;
}

template<typename T_Key, typename T_Value>
inline typename Map<T_Key, T_Value>::Node* Map<T_Key, T_Value>::rotateRight(Node* node)
{
	Node* newRoot = node->left;

	newRoot->parent = node->parent;
	if (newRoot->parent != nullptr) {
		if (newRoot->parent->left == node)
			newRoot->parent->left = newRoot;
		else
			newRoot->parent->right = newRoot;
	}

	node->left = newRoot->right;
	newRoot->right = node;

	node->parent = newRoot;
	if (node->left != nullptr) node->left->parent = node;

	updateHeightAndSize(node);
	updateHeightAndSize(newRoot);
	return newRoot;
}

template<typename T_Key, typename T_Value>
inline void Map<T_Key, T_Value>::updateHeightAndSize(Node* node)
{
	if (node != nullptr) {
		node->height = 1 + Max(getHeight(node->left), getHeight(node->right));
		node->size = 1 + getSize(node->left) + getSize(node->right);
	}
}

template<typename T_Key, typename T_Value>
inline int Map<T_Key, T_Value>::getHeight(Node* node)
{
	if (node == nullptr)
		return 0;
	return node->height;
}

template<typename T_Key, typename T_Value>
inline size_t Map<T_Key, T_Value>::getSize(Node* node)
{
	if (node == nullptr)
		return 0;
	return node->size;
}

template<typename T_Key, typename T_Value>
inline int Map<T_Key, T_Value>::getBalanceFactor(Node* node)
{
	if (node == nullptr)
		return 0;
	return (getHeight(node->left) / (getHeight(node->right)+1)) - (getHeight(node->right) / (getHeight(node->left)+1));
}



}

#endif // !DVTL_MAP_H
