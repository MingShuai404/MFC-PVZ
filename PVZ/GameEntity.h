#include "GameElement.h"

/// <summary>
/// GameElement ����Ϸ�е�ʵ�� ������ֵ����ײ��� 
/// </summary>

class GameEntity : public GameElement {
public:
    DECLARE_DYNCREATE(GameEntity)

public:
    GameEntity(CRuntimeClass* msg = nullptr);

protected:
    int healthPoint;
    CRect collisioArea{ 0 };
    
};