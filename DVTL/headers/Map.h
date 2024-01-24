#ifndef DVTL_MAP_H
#define DVTL_MAP_H

#include "Utility.h"
#include "Initializer_list.h"

namespace DVTL {
template<typename T_Key, typename T_Value>
class Map {
public:
	//declaring iterators
	class Node;
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
	iterator Begin();
	iterator End();
	const_iterator Begin();
	const_iterator End();
	const_iterator CBegin();
	const_iterator CEnd();
private:
	Node* m_root;

	void deleteNodeWithChild(Node* ptr);
};

template<typename T_Key, typename T_Value>
struct Map<T_Key, T_Value>::Node {
	Pair<T_Key, T_Value> data;
	Node* parent;
	Node* left;
	Node* right;
	size_t height;
	size_t size;

	Node(const Pair<T_Key, T_Value>& value) : data(value), parent(nullptr), left(nullptr), right(nullptr), height(1), size(1) {}
	Node(Pair<T_Key, T_Value>&& value) : data(Move(value)), parent(nullptr), left(nullptr), right(nullptr), height(1), size(1) {}

	Node(const Node& right, Node* parentNode) : data(right.data), parent(parentNode), left(new Node(*right.left, this)), right(new Node(*right.right, this)), height(right.height), size(right.size) {}

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
inline Map<T_Key, T_Value>::iterator Map<T_Key, T_Value>::Erase(const T_Key& key)
{
	//make erase
	return iterator();
}

template<typename T_Key, typename T_Value>
inline Map<T_Key, T_Value>::iterator Map<T_Key, T_Value>::Insert(Pair<T_Key, T_Value>&& pair)
{
	return Insert(Pair(pair));
}

template<typename T_Key, typename T_Value>
inline Map<T_Key, T_Value>::iterator Map<T_Key, T_Value>::Insert(const Pair<T_Key, T_Value>& pair)
{
	//make insert
	return iterator();
}

template<typename T_Key, typename T_Value>
inline Map<T_Key, T_Value>::iterator Map<T_Key, T_Value>::Insert(const T_Key& key, const T_Value& val)
{
	return Insert(Pair(key, val));
}

template<typename T_Key, typename T_Value>
inline void Map<T_Key, T_Value>::deleteNodeWithChild(Node* ptr)
{
	if (ptr == nullptr) return;

	deleteNodeWithChild(ptr->left);
	deleteNodeWithChild(ptr->right);
	delete ptr;
}



}

#endif // !DVTL_MAP_H
