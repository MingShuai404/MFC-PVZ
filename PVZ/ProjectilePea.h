#pragma once
#include "Ejects.h"
class ProjectilePea : public Ejects {

    DECLARE_DYNCREATE(ProjectilePea)

public:
    // �ƶ��ٶ�
    static constexpr int step = 5;
    static constexpr int hurt = 20;

public:

    ProjectilePea(CRuntimeClass* msg = RUNTIME_CLASS(ProjectilePea), int h = ProjectilePea::hurt);

    virtual void move();
};

