// SimpleLinkedList.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <memory>
#include <stdexcept>
#include <ostream>

namespace custom_linked_list
{
	template<typename data_type>
	struct link
	{
		typedef std::shared_ptr<link<data_type>> link_type;

		link_type next;
		link_type previous;
		data_type my_data;

		explicit link(const data_type& data) : my_data(data)
		{}

		static void insert_front(link_type& lhs, link_type& new_link)
		{
			if(lhs->next)
			{
				link::insert_front(new_link, lhs->next);
			}

			lhs->next = new_link;
			lhs->next->previous = lhs;
		}

		static void insert_back(link_type& lhs, link_type& new_link)
		{
			if (lhs->previous)
			{
				link::insert_back(new_link, lhs->previous);
			}

			lhs->previous = new_link;
			lhs->previous->next = lhs;
		}

		static link_type append(link_type& lhs, const data_type& data)
		{
			if(!lhs->next)
			{
				lhs->next = std::make_shared<link>(data);
				lhs->next->previous = lhs;
				return lhs->next;
			}
			return link::append(lhs->next, data);
		}

		static link_type prepend(link_type& lhs, const data_type& data)
		{
			if (!lhs->previous)
			{
				lhs->previous = std::make_shared<link>(data);
				lhs->previous->next = lhs->lhs;
				return lhs->previous;
			}
			return link::prepend(lhs->previous, data);
		}

		link& operator=(const data_type& data)
		{
			my_data = data;
			return *this;
		}

		link& operator=(const link& other)
		{
			next = other.next;
			previous = other.previous;
			my_data = other.my_data;
			return &this;
		}

		link operator+(int increment)const
		{
			if (increment > 0)
			{
				if (!next)
					throw std::out_of_range("increment is larger then the list");
				if (increment > 1)
					return *next + --increment;
				if (increment == 1)
					return *next;
			}
			if (increment < 0)
			{
				if (!previous)
					throw std::out_of_range("increment is larger then the list");
				if (increment < -1)
					return *previous + ++increment;
				if (increment == -1)
					return *previous;
			}

			return *this;
		}

		link operator-(int decrement)const
		{
			return *this + -decrement;
		}

		// prefix operators
		link_type operator++()const
		{
			return next;
		}

		link_type operator--()const
		{
			return previous;
		}

		// postfix operators
		link_type operator++(int increment)
		{
			link result(*this);
			++(*this);
			return result;
		}

		link_type operator--(int increment)
		{
			link result(*this);
			--(*this);
			return result;
		}
	};

	template<typename data_type>
	class double_linked_list
	{
		typedef link<data_type> list_type;

		typename list_type::link_type end_;
		typename list_type::link_type begin_;
		size_t size_ = 0;

	public:
		double_linked_list()
		{}

		data_type operator[](size_t index)
		{
			if (index < size_ / 2)
				return ((*begin_) + index).my_data;
			else if (index < size_)
				return ((*end_) - (size_ - index - 1)).my_data;
			else
				throw std::out_of_range("index is larger then list size");
		}

		void push_back(data_type data)
		{
			if(!size_)
			{
				end_ = std::make_shared<list_type>(data);
				begin_ = end_;
			}
			else
			{
				end_ = list_type::append(end_,data);
			}
			++size_;
		}
		data_type pop_back()
		{
			if (!size_)
			{
				throw std::out_of_range("attempting to pop from empty list");
			}

			auto value = end_->my_data;

			--size_;
			if(!size_)
			{
				begin_.reset();
				end_.reset();
			}
			else
			{
				end_ = end_->previous;
				if (!end_)
					end_ = begin_;
				end_->next.reset();
			}

			return value;
		}

		void push_front(data_type data)
		{
			if (!size_)
			{
				end_ = std::make_shared<list_type>(data);
				begin_ = end_;
			}
			else
			{
				auto previous_begin = begin_;
				begin_ = std::make_shared<list_type>(data);
				list_type::insert_front(begin_, previous_begin);
			}
			++size_;
		}

		data_type pop_front()
		{
			if (!size_)
			{
				throw std::out_of_range("attempting to pop from empty list");
			}

			auto value = begin_->my_data;

			--size_;
			if (!size_)
			{
				begin_.reset();
				end_.reset();
			}
			else 
			{
				begin_ = begin_->next;
				if (!begin_)
					begin_ = end_;
				begin_->previous.reset();
			}

			return value;
		}

		_NODISCARD size_t size()const { return size_; }

		friend std::ostream& operator<<(std::ostream& os, const double_linked_list<data_type>& obj)
		{
			os << "{";
			auto current = obj.begin_;
			while(current)
			{
				os << static_cast<data_type>(current->my_data);
				os << ",";
				current = ++(*current);
			}
			os << "}";

			return os;
		}
	};
};