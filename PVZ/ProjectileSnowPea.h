#pragma once
#include "ProjectilePea.h"
class ProjectileSnowPea : public ProjectilePea
{
    DECLARE_DYNCREATE(ProjectileSnowPea)

public:
    // �ƶ��ٶ�
    static constexpr int step = 3;

public:

    ProjectileSnowPea();
};

