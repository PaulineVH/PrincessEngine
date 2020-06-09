#pragma once
//Project includes
#include "Utils.h"
#include "Components.h"
#include "Exception.h"
#include "Core.h"

//Standard includes
#include <memory>
#include <iostream>

namespace Princess
{
	template<typename T>
	class ComponentAllocator
	{
	public:
		//------ Public Templated Functions ------
		//---- Constructors ----
		ComponentAllocator();
		ComponentAllocator(const uint16_t nrOfBlocks);
		ComponentAllocator(const ComponentAllocator&) = delete;
		ComponentAllocator(ComponentAllocator&&) = delete;
		//---- Destructor ----
		~ComponentAllocator();
		//---- Operators ----
		//-- Access Operators --
		T& operator[](uint16_t index);
		const T& operator[](uint16_t index) const;
		//-- Assignment Operators --
		ComponentAllocator& operator=(const ComponentAllocator&) = delete;
		ComponentAllocator& operator=(ComponentAllocator&&) = delete;

		//---- Functionality ----
		void Initialise(uint16_t nrOfBlocks);
		uint16_t Add(T&& value);
		T* Find(uint16_t entityID) const;
		//remove from the list and swap with the last one
		void Remove(uint16_t id);

	private:
		//---- Datamembers ----
		T* m_pHead;
		
		uint16_t m_Capacity;
		uint16_t m_Size;
	};

}


//------ Public Templated Functions ------
//---- Constructors ----
template < typename T>
Princess::ComponentAllocator<T>::ComponentAllocator()
	: m_Capacity{ 0 }
	, m_Size{ 0 }
	, m_pHead{ nullptr }
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
inline T& Princess::ComponentAllocator<T>::operator[](uint16_t index)
{
	return *(m_pHead + index - 1);
}
template<typename T>
inline const T& Princess::ComponentAllocator<T>::operator[](uint16_t index) const
{
	return *(m_pHead + index - 1);
}
//-- Assignment Operators --
//DELETED

//---- Functionality ----
template<typename T>
void Princess::ComponentAllocator<T>::Initialise(uint16_t nrOfBlocks)
{
	std::cout << "Component Allocator inialising with number " << nrOfBlocks << " and size " << sizeof(T) << " !\n";
	m_pHead = reinterpret_cast<T*>(calloc(static_cast<size_t>(nrOfBlocks), sizeof(T)));
	m_Capacity = nrOfBlocks;
}
template<typename T>
uint16_t Princess::ComponentAllocator<T>::Add(T&& value)
{
	if (m_Size + 1 > m_Capacity)
		return 0;

	*(m_pHead + m_Size) = std::move(value);
	++m_Size;
	return m_Size; //index that you return is from 1 - max 
}
//Returns pointer because this function doesn't necessarily find a component with the entityID given as variable.
template<typename T>
T* Princess::ComponentAllocator<T>::Find(uint16_t entityID) const
{
	T* pBegin{ m_pHead };
	// if m_Size == 1 then space 0 is filled in.
	T* pEnd{ m_pHead + m_Size - 1 };

	for (; pBegin != pEnd; ++pBegin) {
		if (static_cast<Princess::BaseComponent>(pBegin).IDentity == entityID) {
			return *pBegin;
		}
	}

	return nullptr;
}
template<typename T>
void Princess::ComponentAllocator<T>::Remove(uint16_t entityID)
{
	T* pFound = Find(entityID);
	if (pFound) // if nullptr then this statement is false
	{
		//move last one to space that needs to be removed except if it's the last one in the array + decrement size
		if (pFound != m_pHead + m_Size - 1)
		{
			*(pFound) = std::move(*(m_pHead + m_Size - 1));
		}
		--m_Size;
	}
}