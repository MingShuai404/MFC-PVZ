#pragma once
#include <afxwin.h>
#include <memory>
#include <list>
#include <string>

class Yard;

class SeedBank;

class Sun;

class Plant;

class Player {
private:
    CPoint pos;
    int sun;
    std::shared_ptr<Plant> currentPlant;

public:

    // ��ǵ��λ��
    CPoint& getPos();
    void setPos(CPoint);

    // ��ǰѡ���ֲ��
    void setCurrentPlant(std::shared_ptr<Plant>);
    std::shared_ptr<Plant> getCurrentPlant();
    
    // ѡ��ֲ�� ����ֲ��
    void selectPlant(Yard&, SeedBank&, CPoint&);
    void placementPlant(Yard&, SeedBank& ,int, int);
    void plantOver(SeedBank& sbank, CRuntimeClass* theClass, size_t state);
    void collectSun(Yard&, SeedBank&, std::list<std::shared_ptr<Sun>>&, CPoint&);
    void drawCurrentPlant(HDC hDC, Yard&);
};

