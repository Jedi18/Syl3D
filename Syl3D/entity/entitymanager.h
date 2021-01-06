#pragma once

namespace entity
{
	/**
	* To do operations safely that require changing multiple class values
	*/
	class EntityManager
	{
	public:
		static EntityManager* entityManager();

		static void releaseInstance();

		void changeTexture() const;

	private:
		EntityManager();

	private:
		static EntityManager* _instance;
	};
}

