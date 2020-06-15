
#ifdef PE_PLATFORM_WINDOWS
#include "Princess.h"

#ifdef _DEBUG
#include <vld.h>
#endif


class Demo final : public Princess::Engine
{
private:
	virtual void LoadGame() override
	{
		std::cout << "Demo: LoadGame() called!" << std::endl;

		std::cout << "Initialising componentManagers!\n";
		Princess::EntitySystem::GetInstance().InitialiseComponentManager<Princess::InputComponent>(10);


		uint16_t player1 = Princess::EntitySystem::GetInstance().CreateEntity();
		std::cout << player1 << std::endl;
		std::cout << "Adding InputComponent!\n";
		//Create InputComponent
		Princess::EntitySystem::GetInstance().AddComponent<Princess::InputComponent>(Princess::InputComponent{ player1, 0, 4 });

		Princess::InputComponent* inputPlayerOne = Princess::EntitySystem::GetInstance().GetComponent<Princess::InputComponent>(player1);
		
		inputPlayerOne->controllerUsed = true;
		inputPlayerOne->input.Add(Princess::Button{ XINPUT_GAMEPAD_B , new Princess::DuckCommand() });

		inputPlayerOne->input.Add(Princess::Button{ XINPUT_GAMEPAD_A , new Princess::DuckCommand() });

		inputPlayerOne->input.Add(Princess::Button{ XINPUT_GAMEPAD_Y , new Princess::DuckCommand() });

		inputPlayerOne->input.Add(Princess::Button{ XINPUT_GAMEPAD_X , new Princess::DuckCommand() });

		std::cout << "Component added!\n";


		uint16_t player2 = Princess::EntitySystem::GetInstance().CreateEntity();
		std::cout << player2 << std::endl;
		std::cout << "Adding InputComponent!\n";
		//Create InputComponent
		Princess::EntitySystem::GetInstance().AddComponent<Princess::InputComponent>(Princess::InputComponent{ player2, 1, 4, true });

		std::cout << "Component added!\n";

		Princess::InputComponent* inputPlayerTwo = Princess::EntitySystem::GetInstance().GetComponent<Princess::InputComponent>(player2);

		inputPlayerTwo->input.Add(Princess::Button{ XINPUT_GAMEPAD_B , new Princess::FireCommand() });

		inputPlayerTwo->input.Add(Princess::Button{ XINPUT_GAMEPAD_A , new Princess::FireCommand() });

		inputPlayerTwo->input.Add(Princess::Button{ XINPUT_GAMEPAD_Y , new Princess::FireCommand() });

		inputPlayerTwo->input.Add(Princess::Button{ XINPUT_GAMEPAD_X , new Princess::FireCommand() });

		//m_Head was nullptr because inputcomponent destructor is called here
	}
};


int main(int, char* [])
{
	/*Demo game{};
	game.Run();*/
	std::cout << "Main function Bubble Bobble is running!" << std::endl;
	//Princess::ComponentAllocator<Princess::TransformComponent> allocator{};
	//allocator.Initialise(10);
	/*Princess::ComponentManager<Princess::TransformComponent>::GetInstance().Initialise(10);

	std::cout << "Adding components!\n";
	Princess::ComponentManager<Princess::TransformComponent>::GetInstance().AddComponent(Princess::TransformComponent{ 1, Princess::Float2{ 7.f, 7.f } });
	Princess::ComponentManager<Princess::TransformComponent>::GetInstance().AddComponent(Princess::TransformComponent{ 2, Princess::Float2{ 5.f, 5.f } });

	std::cout << "Finding components!\n";
	Princess::TransformComponent* pComponent = Princess::ComponentManager<Princess::TransformComponent>::GetInstance().GetComponent(2);
	if (pComponent)
	{
		std::cout << "Entity ID found base component: " << pComponent->IDentity << ".\n";
		std::cout << *pComponent << '\n';
	}
	else
	{
		std::cout << "No entity found with this base component.\n";
	}

	pComponent = Princess::ComponentManager<Princess::TransformComponent>::GetInstance().GetComponent(3);
	if (pComponent)
	{
		std::cout << "Entity ID found base component: " << pComponent->IDentity << ".\n";
		std::cout << *pComponent << '\n';
	}
	else
	{
		std::cout << "No entity found with this base component.\n";
	}

	pComponent = Princess::ComponentManager<Princess::TransformComponent>::GetInstance().GetComponent(1);
	if (pComponent)
	{
		std::cout << "Entity ID found base component: " << pComponent->IDentity << ".\n";
		std::cout << *pComponent << '\n';
	}
	else
	{
		std::cout << "No entity found with this base component.\n";
	}

	std::cout << "Removing components!\n";
	Princess::ComponentManager<Princess::TransformComponent>::GetInstance().RemoveComponent(1);
	pComponent = Princess::ComponentManager<Princess::TransformComponent>::GetInstance().GetComponent(1);
	if (pComponent)
	{
		std::cout << "Entity ID found base component: " << pComponent->IDentity << ".\n";
		std::cout << *pComponent << '\n';
	}
	else
	{
		std::cout << "No entity found with this base component.\n";
	}*/

	/*std::cout << "Creating EntitySystem!\n";
	uint16_t player1 = Princess::EntitySystem::GetInstance().CreateEntity();
	std::cout << "Player1 ID: " << player1 << ".\n";
	uint16_t player2 = Princess::EntitySystem::GetInstance().CreateEntity();
	std::cout << "Player2 ID: " << player2 << ".\n";
	std::cout << std::endl;

	std::cout << "Initialising componentManagers!\n";
	Princess::EntitySystem::GetInstance().InitialiseComponentManager<Princess::TransformComponent>(10);
	Princess::EntitySystem::GetInstance().InitialiseComponentManager<Princess::HealthComponent>(10);
	std::cout << std::endl;

	std::cout << "Adding components!\n";
	Princess::EntitySystem::GetInstance().AddComponent<Princess::TransformComponent>(Princess::TransformComponent{ player1, Princess::Float2{ 7.f, 7.f } });
	
	Princess::EntitySystem::GetInstance().AddComponent<Princess::HealthComponent, Princess::TransformComponent>(Princess::HealthComponent{ player2, 6 }, 
		Princess::TransformComponent{ player2, Princess::Float2{ 5.f, 5.f } });

	Princess::EntitySystem::GetInstance().AddComponent<Princess::TransformComponent>(Princess::TransformComponent{ player1, Princess::Float2{ 5.f, 5.f } });

	std::cout << std::endl;

	std::cout << "Getting components!\n";
	Princess::TransformComponent* pTransform1 = Princess::EntitySystem::GetInstance().GetComponent<Princess::TransformComponent>(player1);
	if (pTransform1)
	{
		std::cout << "Entity with ID " << player1 << " has a transform component with values: \n";
		std::cout << *pTransform1 << ".\n";
	}
	else
	{
		std::cout << "Didn't find Transform for " << player1 << ".\n";
	}
	Princess::TransformComponent* pTransform2 = Princess::EntitySystem::GetInstance().GetComponent<Princess::TransformComponent>(player2);
	if (pTransform2)
	{
		std::cout << "Entity with ID " << player2 << " has a transform component with values: \n";
		std::cout << *pTransform2 << ".\n";
	}
	else
	{
		
		std::cout << "Didn't find Transform for " << player2 << ".\n";
	}
	Princess::HealthComponent* pHealth1 = Princess::EntitySystem::GetInstance().GetComponent<Princess::HealthComponent>(player1);
	if (pHealth1)
	{
		std::cout << "Entity with ID " << player1 << " has a health component with values: \n";
		std::cout << *pHealth1 << ".\n";
	}
	else
	{
		std::cout << "Didn't find health for " << player1 << ".\n";
	}
	Princess::HealthComponent* pHealth2 = Princess::EntitySystem::GetInstance().GetComponent<Princess::HealthComponent>(player2);
	if (pHealth2)
	{
		std::cout << "Entity with ID " << player2 << " has a health component with values: \n";
		std::cout << *pHealth2 << ".\n";
	}
	else
	{
		std::cout << "Didn't find health for " << player2 << ".\n";
	}
*/

	Demo demo{};
	demo.Run();



	std::cout << "Exiting main function Bubble Bobble!" << std::endl;

	return 0;
}

#endif

