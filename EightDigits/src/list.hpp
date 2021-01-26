#pragma once

#include <memory>


template<typename T> class List;


template<typename T> class TNode
{
	friend class List<T>;

public:
	
	TNode(const T& dat) : data_(dat) {}

private:
	std::shared_ptr<TNode<T>> next_;

	T data_;
};


template<typename T>
class List
{

public:

	List() { last_ = first_ = nullptr; length_ = 0; }

	inline int Length() const { return length_; }

	void Append(const T&);

	T Pop(int index);

	int Find(T&);

	void Insert(const T& elem, int index);

private:

	std::shared_ptr<TNode<T>> first_, last_; 
	
	int length_;  

};


template<typename T>
void List<T>::Append(const T& elem)
{
	Insert(elem, length_);
}


template<typename T>
void List<T>::Insert(const T& elem, int index)
{
	auto ptr = std::make_shared<TNode<T>>(elem);

	if (first_)
	{
		// at start
		if (index <= 0)
		{
			ptr->next_ = first_;
			first_ = ptr;
		}
		// at end
		if (index > length_ - 1)
		{
			last_->next_ = ptr;
			last_ = last_->next_;
		}

		if (index > 0 && index < length_)
		{
			index--;
			auto q = first_;
			
			while (index-- > 0)
				q = q->next_;
			
			ptr->next_ = q->next_;
			q->next_ = ptr;
		}
	}
	else
	{
		first_ = last_ = ptr;
	}

	length_++;
}


template<typename T>
T List<T>::Pop(int index)
{
	std::shared_ptr<TNode<T>> p = first_;
	
	while (index-- > 0)
		p = p->next_;
	
	return p->data_;
}


template<typename T>
int List<T>::Find(T& elem)
{
	int index = 0;
	for (; index < length_; index++)
		if (Pop(index) == elem)
			break;
	
	return index;
}
