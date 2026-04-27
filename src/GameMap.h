#pragma once
#include "TextureRect.h"

class GameMap : public ReyEngine::TextureRect
{
	template <typename T>
	using UniformPair = ReyEngine::ReyShader::UniformPair<T>;

protected:
	const ReyEngine::FileSystem::Directory _resourceDirectory;

private:

	UniformPair<ReyEngine::Vec2<float>>_iResolution;

public:
	GameMap();
	void _init() override;
	void setResolution(const ReyEngine::Size<float>& res);
};
