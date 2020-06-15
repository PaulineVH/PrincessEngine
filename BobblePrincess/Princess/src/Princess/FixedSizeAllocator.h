#pragma once

//Standard includes
#include <cstdint>

namespace Princess
{
	template<typename T>
	class FixedSizeAllocator
	{
	public:
		//------ Public Templated Functions ------
		//---- Constructors ----
		FixedSizeAllocator() noexcept;
		FixedSizeAllocator(const uint16_t capacity) noexcept;
		FixedSizeAllocator(const FixedSizeAllocator&) = delete;
		FixedSizeAllocator(FixedSizeAllocator&&) noexcept;

		//---- Destructor ----
		~FixedSizeAllocator();

		//---- Operators ----
		//-- Access Operators --
		T& operator[](uint16_t index) noexcept;
		const T& operator[](uint16_t index) const noexcept;
		//-- Assignment Operators --
		FixedSizeAllocator& operator=(const FixedSizeAllocator&) = delete;
		FixedSizeAllocator& operator=(FixedSizeAllocator&&) noexcept;

		//---- Functionality ----
		void Initialise(uint16_t nrOfBlocks) noexcept;
		void Add(T&& value);

		//-- Getters --
		uint16_t GetSize() const noexcept;

	private:
		T* m_pHead;
		uint16_t m_Capacity;
		uint16_t m_Size;
	};


}

//------ Public Templated Functions ------
//---- Constructors ----
template<typename T>
Princess::FixedSizeAllocator<T>::FixedSizeAllocator() noexcept
	: m_pHead{ nullptr }
	, m_Capacity{ 0 }
	, m_Size{ 0 }
{
}

template<typename T>
Princess::FixedSizeAllocator<T>::FixedSizeAllocator(uint16_t capacity) noexcept
	: m_pHead{ new T[capacity] }
	, m_Capacity{ capacity }
	, m_Size{ 0 }
{
	//TODO: should come into log
	std::cout << "Component Allocator constructor with number " << capacity << " and size " << sizeof(T) << " called!\n";
}
//DELETED copy constructor
template<typename T>
Princess::FixedSizeAllocator<T>::FixedSizeAllocator(FixedSizeAllocator&& o) noexcept
	: m_pHead{ o.m_pHead }
	, m_Capacity{ o.m_Capacity }
	, m_Size{ o.m_Size }
{
	o.m_pHead = nullptr;
	o.m_Capacity = 0;
	o.m_Size = 0;
}

//---- Destructor ----
template<typename T>
Princess::FixedSizeAllocator<T>::~FixedSizeAllocator()
{
	if (m_pHead)
	{
		delete[] m_pHead;
		m_pHead = nullptr;
	}
}

//---- Operators ----
//-- Access Operators --
template<typename T>
T& Princess::FixedSizeAllocator<T>::operator[](uint16_t index) noexcept
{
	return m_pHead[index];
}
template<typename T>
const T& Princess::FixedSizeAllocator<T>::operator[](uint16_t index) const noexcept
{
	return m_pHead[index];
}
//-- Assignment Operators --
//DELETED copy assignment operator
template<typename T>
Princess::FixedSizeAllocator<T>& Princess::FixedSizeAllocator<T>::operator=(FixedSizeAllocator<T>&& o) noexcept
{
	this->m_pHead = o.m_pHead;
	this->m_Capacity = o.m_Capacity;
	this->m_Size = o.m_Size;

	o.m_pHead = nullptr;
	o.m_Capacity = 0;
	o.m_Size = 0;
	
	return *this;
}

//---- Functionality ----
template<typename T>
void Princess::FixedSizeAllocator<T>::Initialise(uint16_t capacity) noexcept
{
	if (m_pHead)
		return;

	m_Capacity = capacity;
	std::cout << "Component Allocator inialising with number " << m_Capacity << " and size " << sizeof(T) << " !\n";
	m_pHead = new T[m_Capacity];
}
template<typename T>
void Princess::FixedSizeAllocator<T>::Add(T&& value)
{
	if (m_Size + 1 > m_Capacity)
		return;


	*(m_pHead + m_Size) = std::move(value);
	++m_Size;
}

//-- Getters --
template<typename T>
uint16_t Princess::FixedSizeAllocator<T>::GetSize() const noexcept
{
	return m_Size;
}
