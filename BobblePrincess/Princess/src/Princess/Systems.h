//2DAE07 - Vanden Heede, Pauline - 2019/2020
#pragma once
//Project Includes
#include "ComponentManager.h"
#include "Components.h"
#include "Renderer.h"

namespace Princess
{
	//Abstract class
	struct BaseComponentSystem
	{
		//Pure virtual functions
		virtual void OnUpdate(float) = 0;
		virtual void onCollison() = 0;
	};


	struct RenderSystem : BaseComponentSystem
	{
		void OnUpdate(float) override
		{
			ComponentAllocatorPair<TextureComponent> pair = ComponentManager<TextureComponent>::GetInstance().GetComponents();
			TextureComponent* pBegin{ pair.pArray };
			TextureComponent* pEnd{ pair.pArray + pair.size };
			for (; pBegin != pEnd; ++pBegin)
			{
				Renderer::GetInstance().RenderTexture(pBegin, ComponentManager<TransformComponent>::GetInstance().GetComponent(pBegin->IDentity)->position);
			}
		}
	};

}
