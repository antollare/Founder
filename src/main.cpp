#include "Logger.h"
//#include "GameMap.h"
#include "Window.h"
#include "TextureRect.h"

#include "Label.h"

using namespace std;
using namespace ReyEngine;
auto resDir = FileSystem::Directory(CrossPlatform::getProjectResourceDir());

int main(int argc, char** argv){
	Logger::info() << "Hello from main!" << endl;

	std::stringstream ss;
	{
		auto gameMessages = CustomLogger("gameLogger", ss);
		gameMessages.log("FOUNDER") << "This is a message from the game" << endl;
		cout << ss.str();
	}

	const int screenWidth = 1920;
	const int screenHeight = 1080;

	auto& window = Application::createWindowPrototype("Founder", screenWidth, screenHeight, {WindowFlags::RESIZE}, 60)->createWindow();
	window.setInternalLogLevel(LOG_ALL);
	auto root = window.getCanvas();

	window.exec();
	return 0;
}
