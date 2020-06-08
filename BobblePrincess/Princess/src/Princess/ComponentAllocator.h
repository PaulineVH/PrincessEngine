#pragma once
#include "FixedSizeAllocator.h"
#include "Utils.h"


#include <memory>
#include <iostream>


namespace Princess
{
	/*
		The next pointer is stored in the component itself.
	*/
	template<typename T>
	class ComponentAllocator
	{
	public:
		//---- Constructors ----
		ComponentAllocator();
		ComponentAllocator(const uint16_t nrOfBlocks);
		ComponentAllocator(const ComponentAllocator&) = delete;
		ComponentAllocator(ComponentAllocator&&) = delete;
		//---- Destructor ----
		~ComponentAllocator();
		//---- Operators ----
		//-- Access Operators --
		T* operator[](uint16_t index);
		const T* operator[](uint16_t index) const;
		//-- Assignment Operators --
		ComponentAllocator& operator=(const ComponentAllocator&) = delete;
		ComponentAllocator& operator=(ComponentAllocator&&) = delete;

		//---- Functionality ----
		uint16_t Add(T&& value);
		//remove from the list and swap with the last one
		void Remove(uint16_t id);

	private:
		//---- Datamembers ----
		const uint16_t m_Capacity;

		T* m_pHead;
		uint16_t m_Size;
	};



	
}


//-------- Templated Functions --------
//---- Constructors ----
template<typename T>
inline Princess::ComponentAllocator<T>::ComponentAllocator()
	: ComponentAllocator( 10 )
{
}
template<typename T>
Princess::ComponentAllocator<T>::ComponentAllocator(const uint16_t nrOfBlocks)
	: m_Capacity{ nrOfBlocks }
	, m_Size{ 0 }
	, m_pHead{ reinterpret_cast<T*>(calloc(static_cast<size_t>(nrOfBlocks), sizeof(T))) }
{
	//TODO: should come into log
	std::cout << "Component Allocator constructor with number " << nrOfBlocks << " and size " << sizeof(T) << " called!\n";

}

//---- Destructor ----
template<typename T>
Princess::ComponentAllocator<T>::~ComponentAllocator()
{
	free(m_pHead);
	m_pHead = nullptr;
}

//---- Operators ----
//-- Access Operators --
template<typename T>
T* Princess::ComponentAllocator<T>::operator[](uint16_t index)
{
	if (index >= m_Size)
		throw(std::exception("Out of bounds."));

	return m_pHead + index;
}
template<typename T>
const T* Princess::ComponentAllocator<T>::operator[](uint16_t index) const
{
	if (index >= m_Size)
		throw(std::exception("Out of bounds."));

	return m_pHead + index;
}

//---- Functionality ----
template<typename T>
uint16_t Princess::ComponentAllocator<T>::Add(T&& value)
{
	if (m_Size + 1 > m_Capacity)
		return 0;

	*(m_pHead + m_Size) = std::move(value);
	++m_Size;
	return m_Size; //index that you return is from 1 - max 
}

template<typename T>
void Princess::ComponentAllocator<T>::Remove(uint16_t id)
{
	if (id > m_Size)
		return;
	/*
		not putting to zero memory makes it the case that you need to initilaise the value
	*/
	if (id == m_Size - 1)
	{
		--m_Size;
		return;
	}
	/*
		move last one to id space
	*/
	*(m_pHead + id - 1) = std::move(*(m_pHead + m_Size - 1));
	--m_Size;
}