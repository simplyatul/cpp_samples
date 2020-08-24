#include <memory>
#include <iostream>

struct Player {
	Player() {
		std::cout << "In C'tor" << std::endl;
	}

	~Player() {
		std::cout << "In D'tor" << std::endl;
	}
	const char* name;
};

int main() {

	{
		std::unique_ptr<Player> msd { new Player{} };
		msd->name = "MSD";
	}

	std::cout << "Tata...." << std::endl;
}
