#pragma once
#include "../2DFrameWork/framework.h"
#pragma comment (lib,"../Build/2DFrameWork/2DFrameWork.lib")

#include "MonsterManager.h"
#include "DamageDisplayManager.h"
#include "BuildManager.h"

#define MONSTER MonsterManager::GetInstance()

#define DAMAGE DamageDisplayManager::GetInstance()

#define BUILD BuildManager::GetInstance()



inline Vector2 GetAdjustedPosition(const Vector2& pos)
{
    return Vector2(
        pos.x + app.GetHalfWidth() / CAM->scale.x - CAM->position.x,
        CAM->position.y - pos.y + app.GetHalfHeight() / CAM->scale.y
    ) *=  CAM->scale;;
}
inline Vector2 GetAdjustedPositionXY(const Vector2& pos, Vector2 offset)
{

	Vector2 adjustedPosition = Vector2(
		pos.x + app.GetHalfWidth() / CAM->scale.x - CAM->position.x,
		CAM->position.y - pos.y + app.GetHalfHeight() / CAM->scale.y
	) *= CAM->scale;
	// Apply the y-axis offset
	adjustedPosition -= offset;

	return adjustedPosition;
}

inline Vector2 GetAdjustedPositionX(const Vector2& pos, float offset_x)
{

	Vector2 adjustedPosition = Vector2(
		pos.x + app.GetHalfWidth() / CAM->scale.x - CAM->position.x,
		CAM->position.y - pos.y + app.GetHalfHeight() / CAM->scale.y
	) *= CAM->scale;
	// Apply the y-axis offset
	adjustedPosition.x -= offset_x;

	return adjustedPosition;
}
inline Vector2 GetAdjustedPositionY(const Vector2& pos, float offset_y)
{

    Vector2 adjustedPosition = Vector2(
        pos.x + app.GetHalfWidth() / CAM->scale.x - CAM->position.x,
        CAM->position.y - pos.y + app.GetHalfHeight() / CAM->scale.y
    ) *= CAM->scale;
    // Apply the y-axis offset
    adjustedPosition.y -= offset_y;

    return adjustedPosition;
}


namespace ImageUtils {
	inline void set(ObImage* img, Int2 maxF = Int2(), Vector2 pivot = OFFSET_N) {
		// 1. �̹����� �ִ� ������ ����
		if (maxF.x > Int2().x && maxF.y > Int2().y)
			img->maxFrame = maxF;

		// 2. �̹����� x ������ ����
		img->scale.x = img->imageSize.x / img->maxFrame.x;

		// 3. �̹����� y ������ ����
		img->scale.y = img->imageSize.y / img->maxFrame.y;

		// 6. �̹����� ȸ�� �߽��� ����
		img->pivot = pivot;
	}
	inline void setPT(ObImage* img, GameObject* P) {
		img->SetParentRT(*P);
	}
	inline void setPT(ObRect* img, GameObject* P) {
		img->SetParentRT(*P);
	}
	inline void setPT(GameObject* img, GameObject* P) {
		img->SetParentRT(*P);
	}
	inline void setScale(ObImage* img, Vector2 scale) {
		// 2. �̹����� x ������ ����
		img->scale.x = img->imageSize.x / img->maxFrame.x * scale.x;

		// 3. �̹����� y ������ ����
		img->scale.y = img->imageSize.y / img->maxFrame.y * scale.y;
	}
	inline void setScale(ObRect* rc, Vector2 scale) {
		// 2. �̹����� x ������ ����
		rc->scale.x = scale.x;

		// 3. �̹����� y ������ ����
		rc->scale.y = scale.y;
	}
	inline void setScale(GameObject* rc, Vector2 scale) {
		// 2. �̹����� x ������ ����
		rc->scale.x = scale.x;

		// 3. �̹����� y ������ ����
		rc->scale.y = scale.y;
	}
	inline void OffsetPos(ObImage* img, float Offset) {
		// 4. �̹����� x ��ġ ������ ����
		float offsetX = img->scale.x / 2 + Offset;
		img->SetLocalPosX(offsetX);

		// 5. �̹����� y ��ġ ������ ����
		float offsetY = img->scale.y / 2 + Offset;
		img->SetLocalPosY(offsetY);
	}
	inline void OffsetPosX(ObImage* img, float Offset) {
		// 4. �̹����� x ��ġ ������ ����
		float offsetX = img->scale.x / 2 + Offset;
		img->SetLocalPosX(offsetX);
	}
	inline void OffsetPosY(ObImage* img, float Offset) {
		// 5. �̹����� y ��ġ ������ ����
		float offsetY = img->scale.y / 2 + Offset;
		img->SetLocalPosY(offsetY);
	}
	inline void OffsetPos(ObImage* img, Vector2 Offset) {
		// 4. �̹����� x ��ġ ������ ����
		float offsetX = img->scale.x / 2 + Offset.x;
		img->SetLocalPosX(offsetX);

		// 5. �̹����� y ��ġ ������ ����
		float offsetY = img->scale.y / 2 + Offset.y;
		img->SetLocalPosY(offsetY);
	}
}