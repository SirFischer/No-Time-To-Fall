#pragma once

#include "Yuna.hpp"
#include <algorithm>

class Camera
{
private:
	sf::View mView;
	sf::Vector2f mPosition = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f mSize = sf::Vector2f(1920.0f, 1080.0f);
	float mZoomLevel = 0.85f;
	
	const sf::Vector2f REFERENCE_RESOLUTION = sf::Vector2f(1920.0f, 1080.0f);
	sf::Vector2f mWindowSize;
	float mScaleFactor = 1.5f;

public:
	Camera() : mWindowSize(1920.0f, 1080.0f)
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
		mWindowSize = size;
		CalculateScaling();
		UpdateView();
	}

	void SetZoom(float zoomLevel)
	{
		mZoomLevel = zoomLevel;
		UpdateView();
	}
	
	void CalculateScaling()
	{
		float scaleX = mWindowSize.x / REFERENCE_RESOLUTION.x;
		float scaleY = mWindowSize.y / REFERENCE_RESOLUTION.y;
		mScaleFactor = std::min(scaleX, scaleY);
		
		mSize.x = REFERENCE_RESOLUTION.x * mScaleFactor;
		mSize.y = REFERENCE_RESOLUTION.y * mScaleFactor;
	}
	
	void UpdateView()
	{
		mView.setCenter(mPosition);
		mView.setSize(mSize * mZoomLevel);
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

	float GetScaleFactor() const
	{
		return mScaleFactor;
	}

	void Reset()
	{
		mPosition = sf::Vector2f(0.0f, 0.0f);
		mZoomLevel = 1.0f;
		UpdateView();
	}
};