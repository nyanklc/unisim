#pragma once

namespace vuniverse
{
	class VuniverseEngine
	{
	public:
		VuniverseEngine();

		void start();

		bool isRunning();

		void stop();

	private:
		bool _isRunning;
	};
}