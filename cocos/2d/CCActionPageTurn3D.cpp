/****************************************************************************
Copyright (c) 2009      Sindesso Pty Ltd http://www.sindesso.com/
Copyright (c) 2010-2012 cocos2d-x.org
CopyRight (c) 2013-2016 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "2d/CCActionPageTurn3D.h"
#include "2d/CCGrid.h"
#include "2d/CCNodeGrid.h"

NS_CC_BEGIN

const bool yOldVersion = false;

PageTurn3D* PageTurn3D::create(float duration, const Size& gridSize)
{
    PageTurn3D *action = new (std::nothrow) PageTurn3D();

    if (action && action->initWithDuration(duration, gridSize))
    {
        action->autorelease();
        return action;
    }

    delete action;
    return nullptr;
}

PageTurn3D *PageTurn3D::clone() const
{
    // no copy constructor
    return PageTurn3D::create(_duration, _gridSize);
}

GridBase* PageTurn3D::getGrid()
{
    auto result = Grid3D::create(_gridSize, _gridNodeTarget->getGridRect());
    if (result)
    {
        result->setNeedDepthTestForBlit(true);
    }
    
    return result;
}

/*
 * Update each tick
 * Time is the percentage of the way through the duration
 */
// old version vertical from bottom left - from http://discuss.cocos2d-x.org/t/i-would-like-to-know-how-to-flip-a-vertical-pageturn3d/17389 
void PageTurn3D::update(float time)
{
    float tt = MAX(0, time - 0.25f);
    float deltaAy = (tt * tt * 500);
    float ay = -100 - deltaAy;
    
    float deltaTheta = sqrtf(time);
    float theta = deltaTheta > 0.5f ? (float)M_PI_2*deltaTheta : (float)M_PI_2*(1-deltaTheta);
    
    float rotateByYAxis = (2-time)* M_PI;
    
    float sinTheta = sinf(theta);
    float cosTheta = cosf(theta);
    
    for (int i = 0; i <= _gridSize.width; ++i)
    {
        for (int j = 0; j <= _gridSize.height; ++j)
        {
            // Get original vertex
            Vec3 p = getOriginalVertex(Vec2(i ,j));
            
            p.x -= getGridRect().origin.x;
            float R = sqrtf((p.x * p.x) + ((p.y - ay) * (p.y - ay)));
            float r = R * sinTheta;
            float alpha = asinf( p.x / R );
            float beta = alpha / sinTheta;
            float cosBeta = cosf( beta );
            
            // If beta > PI then we've wrapped around the cone
            // Reduce the radius to stop these points interfering with others
            if (beta <= M_PI)
            {
                p.x = ( r * sinf(beta));
            }
            else
            {
                // Force X = 0 to stop wrapped
                // points
                p.x = 0;
            }

            p.y = ( R + ay - ( r * (1 - cosBeta) * sinTheta));

            // We scale z here to avoid the animation being
            // too much bigger than the screen due to perspective transform

            p.z = (r * ( 1 - cosBeta ) * cosTheta);// "100" didn't work for
            p.x = p.z * sinf(rotateByYAxis) + p.x * cosf(rotateByYAxis);
            p.z = p.z * cosf(rotateByYAxis) - p.x * sinf(rotateByYAxis);
            p.z/=7;
            //    Stop z coord from dropping beneath underlying page in a transition
            // issue #751
            if( p.z < 0.5f )
            {
                p.z = 0.5f;
            }
            
            // Set new coords
            p.x += getGridRect().origin.x;
            setVertex(Vec2(i, j), p);
            
        }
    }
}
// old version from  http://discuss.cocos2d-x.org/t/i-would-like-to-know-how-to-flip-a-vertical-pageturn3d/17389 
/*void PageTurn3D::update(float time)
{
	float tt = MAX(0, time - 0.25f);
	float deltaAy = (tt * tt * 500);
	float ay = -100 - deltaAy;
	float deltaTheta = -(float)M_PI_2 * sqrtf(time);
	float theta =  +(float)M_PI_2 + deltaTheta;

	float sinTheta = sinf(theta);
	float cosTheta = cosf(theta);

	for (int i = 0; i <= _gridSize.width; ++i)
	{
		for (int j = 0; j <= _gridSize.height; ++j)
		{
			// Get original vertex
			Vec3 p = getOriginalVertex(Vec2(i, j));

			float R = sqrtf((p.x * p.x) + ((p.y - ay) * (p.y - ay)));
			float r = R * sinTheta;
			float alpha = asinf(p.x / R);
			float beta = alpha / sinTheta;
			float cosBeta = cosf(beta);

			// If beta > PI then we've wrapped around the cone
			// Reduce the radius to stop these points interfering with others
			if (beta <= M_PI)
			{
				p.x = (r * sinf(beta));
			}
			else
			{
				// Force X = 0 to stop wrapped
				// points
				p.x = 0;
			}

			p.y = (R + ay - (r * (1 - cosBeta) * sinTheta));

			// We scale z here to avoid the animation being
			// too much bigger than the screen due to perspective transform
			p.z = (r * (1 - cosBeta) * cosTheta) / 7;// "100" didn't work for

													 //    Stop z coord from dropping beneath underlying page in a transition
													 // issue #751
			if (p.z < 0.5f)
			{
				p.z = 0.5f;
			}

			// Set new coords
			setVertex(Vec2(i, j), p);
		}
	}
}
*/
// orig - from bottom right
/*void PageTurn3D::update(float time)
{
	float tt = MAX(0, time - 0.25f);
	float deltaAy = (tt * tt * 500);
	float ay = -100 - deltaAy;

	float deltaTheta = sqrtf(time);
	float theta = deltaTheta > 0.5 ? (float)M_PI_2*deltaTheta : (float)M_PI_2*(1 - deltaTheta);

	float rotateByYAxis = (2 - time)* M_PI;

	float sinTheta = sinf(theta);
	float cosTheta = cosf(theta);

	for (int i = 0; i <= _gridSize.width; ++i)
	{
		for (int j = 0; j <= _gridSize.height; ++j)
		{
			// Get original vertex
			Vec3 p = getOriginalVertex(Vec2(i, j));

			p.x -= getGridRect().origin.x;
			float R = sqrtf((p.x * p.x) + ((p.y - ay) * (p.y - ay)));
			float r = R * sinTheta;
			float alpha = asinf(p.x / R);
			float beta = alpha / sinTheta;
			float cosBeta = cosf(beta);

			// If beta > PI then we've wrapped around the cone
			// Reduce the radius to stop these points interfering with others
			if (beta <= M_PI)
			{
				p.x = (r * sinf(beta));
			}
			else
			{
				// Force X = 0 to stop wrapped
				// points
				p.x = 0;
			}

			p.y = (R + ay - (r * (1 - cosBeta) * sinTheta));

			// We scale z here to avoid the animation being
			// too much bigger than the screen due to perspective transform

			p.z = (r * (1 - cosBeta) * cosTheta);// "100" didn't work for
			p.x = p.z * sinf(rotateByYAxis) + p.x * cosf(rotateByYAxis);
			p.z = p.z * cosf(rotateByYAxis) - p.x * sinf(rotateByYAxis);
			p.z /= 7;
			//    Stop z coord from dropping beneath underlying page in a transition
			// issue #751
			if (p.z < 0.5f)
			{
				p.z = 0.5f;
			}

			// Set new coords
			p.x += getGridRect().origin.x;
			setVertex(Vec2(i, j), p);

		}
	}
}
*/
/*
// older version from bottomleft works
void PageTurn3D::update(float time)
{
	float tt = MAX(0, time - 0.25f);
	float deltaAy = (tt * tt * 500);
	float ay = -100 - deltaAy;

	float deltaTheta = -(float)M_PI_2 * sqrtf(time);
	float theta =  +(float)M_PI_2 + deltaTheta;

	float sinTheta = sinf(theta);
	float cosTheta = cosf(theta);

	for (int i = 0; i <= _gridSize.width; ++i)
	{
		for (int j = 0; j <= _gridSize.height; ++j)
		{
			// Get original vertex
			Vec3 p = getOriginalVertex(Vec2(i, j));

			float R = sqrtf(((1024 - p.x) * (1024 - p.x)) + ((p.y - ay) * (p.y - ay)));
			float r = R * sinTheta;
			float alpha = asinf((1024 - p.x) / R);
			float beta = alpha / sinTheta;
			float cosBeta = cosf(beta);

			// If beta > PI then we've wrapped around the cone
			// Reduce the radius to stop these points interfering with others
			if (beta <= M_PI)
			{
				p.x = 1024 - (r * sinf(beta));
			}
			else
			{
				// Force X = 0 to stop wrapped
				// points
				p.x = 1024 - 0;
			}

			p.y = (R + ay - (r * (1 - cosBeta) * sinTheta));

			// We scale z here to avoid the animation being
			// too much bigger than the screen due to perspective transform
			p.z = (r * (1 - cosBeta) * cosTheta) / 7;// "100" didn't work for

													 //    Stop z coord from dropping beneath underlying page in a transition
													 // issue #751
			if (p.z < 0.5f)
			{
				p.z = 0.5f;
			}

			// Set new coords
			setVertex(Vec2(i, j), p);
		}
	}
}
*/
/*
// new version from bottomleft works
void PageTurn3D::update(float time)
{
	float tt = MAX(0, time - 0.25f);
	float deltaAy = (tt * tt * 500);
	float ay = -100 - deltaAy;

	float deltaTheta = -(float)M_PI_2 * sqrtf(time);
	float theta =  +(float)M_PI_2 + deltaTheta;

	float rotateByYAxis = (2 - time)* M_PI;

	float sinTheta = sinf(theta);
	float cosTheta = cosf(theta);

	for (int i = 0; i <= _gridSize.width; ++i)
	{
		for (int j = 0; j <= _gridSize.height; ++j)
		{
			// Get original vertex
			Vec3 p = getOriginalVertex(Vec2(i, j));

			p.x -= getGridRect().origin.x;  // latest version
			float R = sqrtf(((1024 - p.x) * (1024 - p.x)) + ((p.y - ay) * (p.y - ay)));
			float r = R * sinTheta;
			float alpha = asinf((1024 - p.x) / R);
			float beta = alpha / sinTheta;
			float cosBeta = cosf(beta);

			// If beta > PI then we've wrapped around the cone
			// Reduce the radius to stop these points interfering with others
			if (beta <= M_PI)
			{
				p.x = 1024 - (r * sinf(beta));
			}
			else
			{
				// Force X = 0 to stop wrapped
				// points
				p.x = 1024 - 0;
			}

			p.y = (R + ay - (r * (1 - cosBeta) * sinTheta));

			// We scale z here to avoid the animation being
			// too much bigger than the screen due to perspective transform
			if (yOldVersion) {
				p.z = (r * (1 - cosBeta) * cosTheta) / 7;// "100" didn't work for
			}
			else {
				p.z = (r * (1 - cosBeta) * cosTheta);// "100" didn't work for
				p.x = 1024 - (p.z * sinf(rotateByYAxis) + (1024 - p.x) * cosf(rotateByYAxis));
				p.z = p.z * cosf(rotateByYAxis) - (1024 - p.x) * sinf(rotateByYAxis);
				p.z /= 7;
			}

			//    Stop z coord from dropping beneath underlying page in a transition
			// issue #751
			if (p.z < 0.5f)
			{
				p.z = 0.5f;
			}

			// Set new coords
			p.x += getGridRect().origin.x; // latest version
			setVertex(Vec2(i, j), p);
		}
	}
}
*/
/*
// new version from topleft works
void PageTurn3D::update(float time)
{
	float tt = MAX(0, time - 0.25f);
	float deltaAy = (tt * tt * 500);
	float ay = -100 - deltaAy;

	float deltaTheta = -(float)M_PI_2 * sqrtf(time);
	float theta =  +(float)M_PI_2 + deltaTheta;

	float rotateByYAxis = (2 - time)* M_PI;

	float sinTheta = sinf(theta);
	float cosTheta = cosf(theta);

	for (int i = 0; i <= _gridSize.width; ++i)
	{
		for (int j = 0; j <= _gridSize.height; ++j)
		{
			// Get original vertex
			Vec3 p = getOriginalVertex(Vec2(i, j));

			p.x -= getGridRect().origin.x;  // latest version
			float R = sqrtf(((1024 - p.x) * (1024 - p.x)) + (((640 - p.y) - ay) * ((640 - p.y) - ay)));
			float r = R * sinTheta;
			float alpha = asinf((1024 - p.x) / R);
			float beta = alpha / sinTheta;
			float cosBeta = cosf(beta);

			// If beta > PI then we've wrapped around the cone
			// Reduce the radius to stop these points interfering with others
			if (beta <= M_PI)
			{
				p.x = 1024 - (r * sinf(beta));
			}
			else
			{
				// Force X = 0 to stop wrapped
				// points
				p.x = 1024 - 0;
			}

			p.y = 640 - (R + ay - (r * (1 - cosBeta) * sinTheta));

			// We scale z here to avoid the animation being
			// too much bigger than the screen due to perspective transform
			if (yOldVersion) {
				p.z = (r * (1 - cosBeta) * cosTheta) / 7;// "100" didn't work for
			}
			else {
				p.z = (r * (1 - cosBeta) * cosTheta);// "100" didn't work for
				p.x = 1024 - (p.z * sinf(rotateByYAxis) + (1024 - p.x) * cosf(rotateByYAxis));
				p.z = p.z * cosf(rotateByYAxis) - (1024 - p.x) * sinf(rotateByYAxis);
				p.z /= 14;// 7;
			}

			//    Stop z coord from dropping beneath underlying page in a transition
			// issue #751
			if (p.z < 0.5f)
			{
				p.z = 0.5f;
			}

			// Set new coords
			p.x += getGridRect().origin.x; // latest version
			//if (i < _gridSize.width / 2) {
				setVertex(Vec2(i, j), p);
			//}
		}
	}

}
*/
NS_CC_END
