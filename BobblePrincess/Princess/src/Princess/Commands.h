//2DAE07 - Vanden Heede, Pauline - 2019/2020
#pragma once

//Standard Includes
#include <cstdint>

namespace Princess
{
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute(uint16_t){};
	private:
	};

	class DuckCommand final : public Command
	{
	public:
		virtual void Execute(uint16_t);
	private:

	};

	class FartCommand final : public Command
	{
	public:
		virtual void Execute(uint16_t);
	private:
	};

	class FireCommand final : public Command
	{
	public:
		virtual void Execute(uint16_t);
	private:

	};

	class JumpCommand final : public Command
	{
	public:
		virtual void Execute(uint16_t);
	private:

	};
}



