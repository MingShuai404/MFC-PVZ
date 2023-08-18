#pragma once
#include <afxwin.h>
#include "GameElement.h"
#include "Config.h"

class Plant;

class SeedBank;

class Seed : public GameElement {

    friend class SeedBank;

    DECLARE_DYNCREATE(Seed)

public:

    enum MapStatus { background = 0, mask };

    enum Status { READY = 0b10, FORBID = 0b100, SELECTED = 0b1000 };

private:

    CRuntimeClass* plantClass;
    int price;
    // ��ȴʱ��
    int waitingTime = 0;
    int maxWaitingTime;

public:

    Seed(CRuntimeClass* plant = nullptr, int seedPrice = 0, int maxWaitTime = 0);

    Seed(const Seed& seed);

    CRuntimeClass* getPlantClass();

    int getPrice();

    int getWaitingTime();

    void wait();

    void update(SeedBank&);

    virtual void draw(HDC);

    virtual bool onClick(int cx, int cy);
};

