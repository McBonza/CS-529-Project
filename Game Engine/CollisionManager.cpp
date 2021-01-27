#include "CollisionManager.h"
#include "Components/Body.h"
#include <algorithm>



CollideEvent::CollideEvent() : Event(EventType::COLLIDE) {
	hitTop = false;
	hitBot = false;
	hitLeft = false;
	hitRight = false;
	//withBullet = false;
}

CollideEvent::~CollideEvent() {

}

//-----------------------------------------------------------


Shape::Shape(ShapeType Type) {

	mpOwnerBody = nullptr;

	mType = Type;
}


//--------------------------------------------------

ShapeCircle::ShapeCircle(float Radius) : Shape(Shape::ShapeType::CIRCLE) {
	mRadius = Radius;
}

bool ShapeCircle::TestPoint(float ptX, float ptY) {
	// center point squared dist
	float sqDist = (ptX - mpOwnerBody->mPositionX) * (ptX - mpOwnerBody->mPositionX) + (ptY - mpOwnerBody->mPositionY) * (ptY - mpOwnerBody->mPositionY);

	//compared to squared radius
	if (sqDist > (mRadius * mRadius))
		return false;

	return true;
}


//--------------------------------------------------

ShapeAABB::ShapeAABB(float Left, float Right, float Top, float Bottom) : Shape(Shape::ShapeType::AABB) {

	mLeft = Left;
	mRight = Right;
	mTop = Top;
	mBottom = Bottom;
}

bool ShapeAABB::TestPoint(float ptX, float ptY) {
	float left, right, top, bottom;
	left = mpOwnerBody->mPositionX - mLeft;
	right = mpOwnerBody->mPositionX - mRight;
	top = mpOwnerBody->mPositionY - mTop;
	bottom = mpOwnerBody->mPositionY + mBottom;

	if (ptX < left ||
		ptX > right ||
		ptY < top ||
		ptY > bottom)
		return false;

	return true;
}

//-----------------------------------------------------------

//these 4 funtions are hidden here on purepose since they manipulate the collision managers contacts array
bool CheckCollisionCircleCircle(Shape* pCircleShape1, float Pos1X, float Pos1Y, Shape* pCircleShape2, float Pos2X, float Pos2Y, std::list<Contact*>& mContacts) {

	float c1c2DistSq;
	float r1, r2;

	c1c2DistSq = (Pos1X - Pos2X) * (Pos1X - Pos2X) + (Pos1Y - Pos2Y) * (Pos1Y - Pos2Y);
	r1 = ((ShapeCircle*)pCircleShape1)->mRadius;
	r2 = ((ShapeCircle*)pCircleShape2)->mRadius;

	if (c1c2DistSq > ((r1 + r2) * (r1 + r2)))
		return false;

	//Add new contact
	Contact* pNewContact = new Contact();
	pNewContact->mBodies[0] = pCircleShape1->mpOwnerBody;
	pNewContact->mBodies[1] = pCircleShape2->mpOwnerBody;

	pNewContact->mCollisionInfo[0]->otherObject = pNewContact->mBodies[1]->mpOwner;
	pNewContact->mCollisionInfo[1]->otherObject = pNewContact->mBodies[0]->mpOwner;

	mContacts.push_back(pNewContact);

	return true;
}

bool CheckCollisionAABBAABB(Shape* pAABBShape1, float Pos1X, float Pos1Y, Shape* pAABBShape2, float Pos2X, float Pos2Y, std::list<Contact*>& mContacts) {
	float left1, right1, top1, bottom1;
	float left2, right2, top2, bottom2;

	ShapeAABB* pAABB1 = (ShapeAABB*)pAABBShape1;
	ShapeAABB* pAABB2 = (ShapeAABB*)pAABBShape2;

	left1 = Pos1X + pAABB1->mLeft;
	right1 = Pos1X + pAABB1->mRight;
	top1 = Pos1Y + pAABB1->mTop;
	bottom1 = Pos1Y + pAABB1->mBottom;

	left2 = Pos2X + pAABB2->mLeft;
	right2 = Pos2X + pAABB2->mRight;
	top2 = Pos2Y + pAABB2->mTop;
	bottom2 = Pos2Y + pAABB2->mBottom;

	if (left1 > right2 ||
		left2 > right1 ||
		top1 > bottom2 ||
		top2 > bottom1)
		return false;

	//collision confirmed
	//Add new contact
	Contact* pNewContact = new Contact();

	//see which value smallest
	float topTest = abs(top1 - bottom2);
	float botTest = abs(bottom1 - top2);
	float rightTest = abs(right1 - left2);
	float leftTest = abs(left1 - right2);
	

	if (topTest < 20.0) {//top of block
		//printf("top\n");
		pNewContact->mCollisionInfo[0]->hitTop = true;
		pNewContact->mCollisionInfo[1]->hitBot = true;
	}
	if (botTest < 20.0) {//bottom of block
		//printf("bottom\n");
		pNewContact->mCollisionInfo[0]->hitBot = true;
		pNewContact->mCollisionInfo[1]->hitTop = true;
	}
	if (rightTest < 20.0) {//right of block
		//printf("right\n");
		pNewContact->mCollisionInfo[0]->hitRight = true;
		pNewContact->mCollisionInfo[1]->hitLeft = true;
	}
	if (leftTest < 20.0) {//left of block
		//printf("left\n");
		pNewContact->mCollisionInfo[0]->hitLeft = true;
		pNewContact->mCollisionInfo[1]->hitRight = true;
	}
	

	//make further checks to see which side
	/*double w = 0.5 * (pAABB1->mRight - pAABB1->mLeft + pAABB2->mRight - pAABB2->mLeft);
	double h = 0.5 * (pAABB1->mBottom - pAABB1->mTop + pAABB2->mBottom - pAABB2->mTop);
	double dx = Pos1X - Pos2X;
	double dy = Pos1Y - Pos2Y;

	if (abs(dx) < w && abs(dy) < h)//collision
	{
 		double wy = w * dy;
		double hx = h * dx;
		if (wy >= hx)
			if (wy >= -hx) {//top of block
				printf("top\n");//player.y = re.y - player.height;//align edges
				pNewContact->mCollisionInfo[0]->hitTop = true;
				pNewContact->mCollisionInfo[1]->hitBot = true;
			}
			else {//right of block
				printf("right\n");//player.x = re.x + re.width;//align edges
				pNewContact->mCollisionInfo[0]->hitRight = true;
				pNewContact->mCollisionInfo[1]->hitLeft = true;
			}
		else {
			if (wy >= -hx) {//left of block
				printf("left\n");//player.x = re.x - player.width;//align edges
				pNewContact->mCollisionInfo[0]->hitLeft = true;
				pNewContact->mCollisionInfo[1]->hitRight = true;
			}
			else {//bottom of block
				printf("bottom\n");//player.y = re.y + re.height;//align edges
				pNewContact->mCollisionInfo[0]->hitBot = true;
				pNewContact->mCollisionInfo[1]->hitTop = true;
			}
		}
	}*/

	pNewContact->mBodies[0] = pAABBShape1->mpOwnerBody;
	pNewContact->mBodies[1] = pAABBShape2->mpOwnerBody;

	pNewContact->mCollisionInfo[0]->otherObject = pNewContact->mBodies[1]->mpOwner;
	pNewContact->mCollisionInfo[1]->otherObject = pNewContact->mBodies[0]->mpOwner;

	mContacts.push_back(pNewContact);

	return true;
}
 
bool CheckCollisionCircleAABB(Shape* pCircleShape1, float Pos1X, float Pos1Y, Shape* pAABBShape2, float Pos2X, float Pos2Y, std::list<Contact*>& mContacts) {

	ShapeCircle* pCircle1 = (ShapeCircle*)pCircleShape1;
	ShapeAABB* pAABB2 = (ShapeAABB*)pAABBShape2;
	float left2, right2, top2, bottom2;

	left2 = Pos2X + pAABB2->mLeft;
	right2 = Pos2X + pAABB2->mRight;
	top2 = Pos2Y + pAABB2->mTop;
	bottom2 = Pos2Y + pAABB2->mBottom;

	float snappedX, snappedY;
	
	if (Pos1X < left2)
		snappedX = left2;
	else
		if (Pos1X > right2)
			snappedX = right2;
		else
			snappedX = Pos2X;

	if (Pos1Y < top2)
		snappedY = top2;
	else
		if (Pos1Y > bottom2)
			snappedY = bottom2;
		else
			snappedY = Pos2Y;

	if (!pCircle1->TestPoint(snappedX, snappedY))
		return false;

	//Add new contact
	Contact* pNewContact = new Contact();
	pNewContact->mBodies[0] = pCircleShape1->mpOwnerBody;
	pNewContact->mBodies[1] = pAABBShape2->mpOwnerBody;

	pNewContact->mCollisionInfo[0]->otherObject = pNewContact->mBodies[1]->mpOwner;
	pNewContact->mCollisionInfo[1]->otherObject = pNewContact->mBodies[0]->mpOwner;

	mContacts.push_back(pNewContact);

	return true;
}

bool CheckCollisionAABBCircle(Shape* pAABBShape1, float Pos1X, float Pos1Y, Shape* pCircleShape2, float Pos2X, float Pos2Y, std::list<Contact*>& mContacts) {
	return CheckCollisionCircleAABB(pCircleShape2, Pos1X, Pos1Y, pAABBShape1, Pos2X, Pos2Y, mContacts);
}


CollisionManager::CollisionManager() {
	CollisionFunctions[Shape::ShapeType::CIRCLE][Shape::ShapeType::CIRCLE] = CheckCollisionCircleCircle;
	CollisionFunctions[Shape::ShapeType::AABB][Shape::ShapeType::AABB] = CheckCollisionAABBAABB;
	CollisionFunctions[Shape::ShapeType::CIRCLE][Shape::ShapeType::AABB] = CheckCollisionCircleAABB;
	CollisionFunctions[Shape::ShapeType::AABB][Shape::ShapeType::CIRCLE] = CheckCollisionAABBCircle;
}

CollisionManager::~CollisionManager() {
	Reset();
}

void CollisionManager::Reset() {
	for (auto c : mContacts)
		delete c;
	mContacts.clear();
}


bool CollisionManager::CheckCollisionAndGenerateContact(Shape* pShape1, float Pos1X, float Pos1Y, Shape* pShape2, float Pos2X, float Pos2Y) {
	
	return CollisionFunctions[pShape1->mType][pShape2->mType](pShape1, Pos1X, Pos1Y, pShape2, Pos2X, Pos2Y, mContacts);
}

