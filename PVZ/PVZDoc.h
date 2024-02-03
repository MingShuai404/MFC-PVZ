#pragma once
#include "stdafx.h"
#include <afxwin.h>

#include <list>

#include "Player.h"
#include "ResourceManage.h"
#include "SeedBank.h"
#include "Yard.h"

class PVZDoc : public CDocument {
  DECLARE_DYNCREATE(PVZDoc)

public:
  using SunlightList = std::list<std::shared_ptr<Sun>>;

private:
  // �ĵ��ౣ��Ժ����Ϣ�������Ϣ
  Yard yard;
  Player player;
  SeedBank sbank;
  SunlightList sunList;

public:
  PVZDoc();

public:
  Yard& getYard();
  Player& getPlayer();
  SeedBank& getSeedBank();
  SunlightList& getSunList();
};
