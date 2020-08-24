#include <memory>
#include <iostream>

#define CTOR std::cout << __func__ << " In C'tor" << std::endl;
#define DTOR std::cout << __func__ << " In D'tor" << std::endl;

struct Player {
	Player() { CTOR; }
	~Player() { DTOR; }
	const char* name;
};

struct Csk {

	Csk (std::unique_ptr<Player> cap)
		: captain(std::move(cap)) { CTOR; }

	~Csk() { DTOR; }

	std::unique_ptr<Player> captain;
};

int main() {

	{
		std::unique_ptr<Player> msd { new Player{} };
		msd->name = "MSD";

		Csk theCaptain { std::move(msd) }; // lifetime of Player is tied to the lifetime of Csk
	}

	std::cout << "Tata...." << std::endl;
}
