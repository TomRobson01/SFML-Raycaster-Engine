#include <algorithm>

#include "RayParticle.h"
#include "VMath.h"

#pragma region Constructor
RayParticle::RayParticle(std::vector<Boundary*> _boundaries, sf::RenderWindow* _window2D, sf::RenderWindow* _window, TextureAtlas* _tAtlas)
{
	// Constructor
	position = sf::Vector2f(3, 240);

	boundaries = _boundaries;
	window = _window;
	window2D = _window2D;
	columnWidth = window->getSize().x / 60.f;

	textures = _tAtlas->getTextures();
}
#pragma endregion

#pragma region Transformation
void RayParticle::updatePos(sf::Vector2f _newPos)
{
	position = _newPos;
}

void RayParticle::updateRot(float _newRot)
{
	rotation = _newRot;
}
#pragma endregion

#pragma region Utilities
bool compareByDist(const RayData& a, const RayData& b)
{
	return a.hitDist > b.hitDist;
}
#pragma endregion

#pragma region Draw Functions
void RayParticle::emitRays()
{
	int raysCast = 0;

	// Sends rays out at an interval of 10 degrees per ray, in a 60 degrees vision cone
	for (int i = rotation; i < 60 + rotation; i++)
	{
		// Generate a new ray, and then rotate it the appropreate number of degrees
		Ray* currentRay = new Ray(position, sf::Vector2f(1.f, -1.f), window2D);
		currentRay->setRayDirection(VMath::rotateVector(currentRay->getRayDirection(), i));

		rays.push_back(currentRay);

		if (raysCast == 60 / 2)
		{
			direction = currentRay->getRayDirection();
		}

		// Draw the 2D representation of the ray - DEBUG
		currentRay->draw2D();
		
		raysCast++;
	}


	// Loop through all generated rays
	for (int i = 0; i < rays.size(); i++)
	{
		DrawData drawBuffer;

		sf::Color heldColour = sf::Color(255, 255, 255, 0);

		bool hit = false;								// Stores if any boundary results in a hit
		bool hasTravelledThroughTransparent = false;	// Stores if the ray has travelled through a transparent surface
		float closestHitDist = 9999.f;					// Stores the distance to the closest hit
		int closestHitTextureID = 4;					// Stores the texture ID of the current closest boundary hit
		float closestInersectionPoint = 2.f;			// Stores the point along the line the ray intersects with (0.f - 1.f)

		sf::Vector2f closestHitPoint;	// Stores the current closest hit

		// These vectors store all the essential data for the chosen hits of this ray (once the closest rays have been chosen)
		std::vector<bool> hits;
		std::vector<float> hitDists;
		std::vector<int> textureIDs;
		std::vector<float> intersectionPoints;
		std::vector<sf::Color> colours;


		// Loop through each boundary
		for (int ii = 0; ii < boundaries.size(); ii++)
		{
			// Cast the ray to the target bounadry - check for intersection
			if (rays[i]->cast(boundaries[ii]))
			{

				// Calculate the distance between this hit and the particle's position - if it's smaller than the previous record, that's our new closest
				float dist = sqrtf(powf(rays[i]->getHitPoint().x - position.x, 2) + powf(rays[i]->getHitPoint().y - position.y, 2) * 1.0f);
				float angle = atan2f(direction.y, direction.x) - VMath::getAngle(rays[i]->getRayDirection());

				dist *= cos(angle);	// Applies some fish-eye correction

				if (boundaries[ii]->getIsTransparent())
				{
					// If the ray intersects a transparent boundary, it stores that data for rendering, however it continues on to see if anything can be seen behind the transparent surface
					closestHitDist = dist;
					closestHitPoint = rays[i]->getHitPoint();
					closestInersectionPoint = rays[i]->getRayIntersectionValue();
					closestHitTextureID = boundaries[ii]->getTextureId();
					heldColour = boundaries[ii]->get3DColour();


					hits.push_back(hit);
					hitDists.push_back(closestHitDist);
					intersectionPoints.push_back(closestInersectionPoint);
					textureIDs.push_back(closestHitTextureID);
					colours.push_back(heldColour);

					closestHitDist = 9999.f;
				}
				else
				{
					hit = true;

					if (dist < closestHitDist)
					{
						closestHitDist = dist;
						closestHitPoint = rays[i]->getHitPoint();
						closestInersectionPoint = rays[i]->getRayIntersectionValue();
						closestHitTextureID = boundaries[ii]->getTextureId();
						heldColour = boundaries[ii]->get3DColour();
					}
				}


			}
		}

		// If any (opaque) boundaries have intersected the ray
		if (hit)
		{
			// Draw a line to the intersection point
			sf::Vertex line[] =
			{
				sf::Vertex(rays[i]->getRayOrigin()),
				sf::Vertex(closestHitPoint, sf::Color(255,255,255,15))
			};

			window2D->draw(line, 2, sf::Lines);

			hits.push_back(hit);
			hitDists.push_back(closestHitDist);
			intersectionPoints.push_back(closestInersectionPoint);
			textureIDs.push_back(closestHitTextureID);
			colours.push_back(heldColour);
		}

		// Adds all hit data this ray has gathered to the draw buffer
		for (int d = 0; d < hits.size(); d++)
		{
			RayData data;

			data.hit = true;
			data.angleOffset = atan2f(direction.y, direction.x) - atan2f(rays[i]->getRayDirection().y, rays[i]->getRayDirection().x);
			data.textureID = textureIDs[d];
			data.intersectionValue = intersectionPoints[d];
			data.boundaryColour = colours[d];
			data.hitDist = hitDists[d];

			drawBuffer.drawData.push_back(data);
		}

		drawData.push_back(drawBuffer);
	}

	// All rays have been checked, reset the vector
	rays.clear();
}


void RayParticle::drawScene3D()
{
	emitRays();	// Casts all nescessary rays, and gathers data for the draw buffer

	float screenWidth;
	float stepDist;
	screenWidth = window->getSize().x;
	stepDist =  screenWidth / 60;		// Divides the screen into 60 columns to check

	// Loop through all draw data gathered
	for (int i = 0; i < drawData.size(); i++)
	{
		
		std::vector<RayData> depthBuffer = drawData[i].drawData;			// Gets the default draw buffer data for this column
		std::sort(depthBuffer.begin(), depthBuffer.end(), compareByDist);	// Sorts the order so that the furthest visible walls are drawn first

		// Loops through all data in the depth buffer for this column
		for (int ii = 0; ii < depthBuffer.size(); ii++)
		{
			// Gets data for this column
			RayData data = depthBuffer[ii];

			// Generates sprite representing this column
			sf::Sprite column;

			float h = 0;

			if (data.intersectionValue <= 1 && data.intersectionValue >= 0)
			{
				// Sets height of the column to be relative to it's distance from the player
				h = window->getSize().y / (data.hitDist);
			}

			// Sets texture and texture rect for column
			column.setTexture(textures[data.textureID]);
			column.setTextureRect(sf::IntRect(textures[data.textureID].getSize().x * data.intersectionValue, 0, 1, textures[data.textureID].getSize().y));

			// Sets colour (mainly used for transparency)
			column.setColor(data.boundaryColour);

			// Centers the sprite's pivot point (SFML uses the top left by default, but I find the center easier to work with)
			column.setOrigin(sf::Vector2f(0, textures[data.textureID].getSize().y / 2));

			// Places the column in the correct position on the screen
			column.setPosition(sf::Vector2f(i * stepDist, window->getSize().y / 2));
			// Scales column to appropreate height
			column.setScale(sf::Vector2f(columnWidth, h / 2));

			// Draws column to 3D Window
			window->draw(column);

		}
	}

	// Clears draw buffer
	drawData.clear();
}
#pragma endregion

#pragma region Getters/Setters
sf::Vector2f RayParticle::getDirection()
{
	return direction;
}

void RayParticle::setDirection(sf::Vector2f _newDir)
{
	direction = _newDir;
}
#pragma endregion
