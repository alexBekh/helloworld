#pragma once
#include"stdafx.h"


class FindFixtureByPosQuery : public b2QueryCallback
{

public:
	FindFixtureByPosQuery(const b2Vec2& _p)
	{
		p = _p;

		b2Vec2 d(0.001, 0.001);
		aabb.lowerBound = p - d;
		aabb.upperBound = p + d;
	}

	virtual bool ReportFixture(b2Fixture* _fixture) override
	{
		b2Body* b = _fixture->GetBody();
		if (b->GetType() == b2_dynamicBody && _fixture->TestPoint(p))
		{
			f = _fixture;
			return false;
		}
		return true;
	}

	const b2AABB& getAABB() const
	{
		return aabb;
	}

	bool isFound() const
	{
		return f != nullptr;
	}

	b2Fixture* getFixture()
	{
		return f;
	}

private:
	b2Vec2 p;
	b2Fixture* f = nullptr;
	b2AABB aabb;
};