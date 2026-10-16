#include "Precompiled.h"
#include "TimeUtil.h"

using namespace VGP242Engine;
using namespace VGP242Engine::Core;

float TimeUtil::GetTime()
{
	static const auto startTime = std::chrono::high_resolution_clock::now();
	const auto currentTime = std::chrono::high_resolution_clock::now();
	const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
	return milliseconds / 1000.f;
}


float TimeUtil::GetDeltaTime()
{
	static auto lastCallTime = std::chrono::high_resolution_clock::now();
	const auto currentTime = std::chrono::high_resolution_clock::now();
	const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(lastCallTime - currentTime).count();
	return milliseconds / 1000.f;
}
