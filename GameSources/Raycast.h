#pragma once
#include "stdafx.h"

// ���C�L���X�g�̌��ʂ�ێ�����\����
struct RaycastHit3D 
{
    Vec3 point;  // �Փ˒n�_
    bool hit;    // �Փ˂������������ǂ���
};

// ���C�L���X�g�̊֐��F���̂����C�̌o�H��ɂ��邩�ǂ����𔻒�
RaycastHit3D Raycast3D(const Vec3& origin, const Vec3& direction,
    float maxDistance, const Vec3& groundPos)
{
    // ���C�̍ŏI�n�_�i�n�_��������x�N�g�� * ���������Z�j
    Vec3 rayEnd = { origin.x + direction.x * maxDistance,
                       origin.y + direction.y * maxDistance,
                       origin.z + direction.z * maxDistance };

    // �n�ʁigroundPos.y�j�����C�̌o�H��ɂ��邩�ǂ����𔻒�
    if (groundPos.y <= origin.y && groundPos.y >= rayEnd.y)
    {
        // �Փ˂����������ꍇ�A�Փ˒n�_��Ԃ�
        return { { origin.x, groundPos.y, origin.z }, true };
    }

    // �Փ˂��������Ȃ������ꍇ�Ahit=false�̌��ʂ�Ԃ�
    return { { 0, 0, 0 }, false };
}