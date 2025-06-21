#pragma once

#include "Yuna.hpp"

class Camera
{
private:
	sf::View mView;
	sf::Vector2f mPosition = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f mSize = sf::Vector2f(1920.0f, 1080.0f);
	float mZoomLevel = 1.0f;

public:
	Camera()
	{
		mView.setCenter(mPosition);
		mView.setSize(mSize);
		mView.zoom(mZoomLevel);
	}

	void SetPosition(const sf::Vector2f& position)
	{
		mPosition = position;
		mView.setCenter(mPosition);
	}

	void SetSize(const sf::Vector2f& size)
	{
		mSize = size;
		mView.setSize(mSize);
	}

	void SetZoom(float zoomLevel)
	{
		mZoomLevel = zoomLevel;
		mView.zoom(mZoomLevel);
	}

	const sf::View& GetView() const
	{
		return mView;
	}
	sf::Vector2f GetPosition() const
	{
		return mPosition;
	}
	float GetZoomLevel() const
	{
		return mZoomLevel;
	}
	void Reset()
	{
		mPosition = sf::Vector2f(0.0f, 0.0f);
		mZoomLevel = 1.0f;
		mView.setCenter(mPosition);
		mView.setSize(mSize);
		mView.zoom(mZoomLevel);
	}
};