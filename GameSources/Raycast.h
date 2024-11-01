#pragma once
#include "stdafx.h"

// レイキャストの結果を保持する構造体
struct RaycastHit3D 
{
    Vec3 point;  // 衝突地点
    bool hit;    // 衝突が発生したかどうか
};

// レイキャストの関数：物体がレイの経路上にあるかどうかを判定
RaycastHit3D Raycast3D(const Vec3& origin, const Vec3& direction,
    float maxDistance, const Vec3& groundPos)
{
    // レイの最終地点（始点から方向ベクトル * 距離を加算）
    Vec3 rayEnd = { origin.x + direction.x * maxDistance,
                       origin.y + direction.y * maxDistance,
                       origin.z + direction.z * maxDistance };

    // 地面（groundPos.y）がレイの経路上にあるかどうかを判定
    if (groundPos.y <= origin.y && groundPos.y >= rayEnd.y)
    {
        // 衝突が発生した場合、衝突地点を返す
        return { { origin.x, groundPos.y, origin.z }, true };
    }

    // 衝突が発生しなかった場合、hit=falseの結果を返す
    return { { 0, 0, 0 }, false };
}