#include "Player.h"

#include <cmath>

#include "PVZDoc.h"
#include "Plant.h"
#include "Seed.h"
#include "SeedBank.h"
#include "Sun.h"
#include "Yard.h"
#include "Chomper.h"
#include "Squash.h"

CPoint& Player::getPos() { return pos; }

void Player::setPos(CPoint point) { pos = point; }

std::shared_ptr<Plant> Player::getCurrentPlant() { return currentPlant; }

void Player::selectPlant(Yard& yard, SeedBank& sbank, CPoint& point) {
  // ����SeedBank����
  for (auto& seed : sbank.getSeedElements()) {
    if (seed.onClick(point.x, point.y) && !getCurrentPlant() &&
      sbank.getSunlight() >= seed.getPrice() && seed.getWaitingTime() == 0 &&
      seed.isOnlyState(Seed::READY)) {
      CRuntimeClass* factory = seed.getPlantClass();
      // ���ö�̬�������ƴ�������
      this->setCurrentPlant(
        std::shared_ptr<Plant>((Plant*)factory->CreateObject()));
      seed.addState(Seed::SELECTED);
      return;
    }
  }

  // ѡ������ɵ���ʱ����
  auto plant = this->getCurrentPlant();

  // û��ѡ��ֲ��ֱ���˳�
  if (!currentPlant) return;

  if (yard.onClick(point.x, point.y)) {
    // �ڷ�ֲ��
    POINT pos = yard.getPlantPos(point.x, point.y);
    if (pos.x > -1 && pos.y > -1) {
      this->placementPlant(yard, sbank, pos.x, pos.y);
    }
    return;
  }
  // ȡ����ֲ
  sbank.foreachAllSeed(
    [&](Seed& seed) {
      seed.cleanState(Seed::SELECTED);
  currentPlant.reset();
    },
    plant->GetRuntimeClass());
}

void Player::placementPlant(Yard& yard, SeedBank& sbank, int row, int col) {
  auto& plantMatrix = yard.getPlantMatrix();
  if (plantMatrix[row][col]) {
    AfxMessageBox("�����Ѿ���ֲ����");
    // ȡ����Ӧseed��ѡ��״̬
    sbank.foreachAllSeed([](Seed& seed) { seed.cleanState(Seed::SELECTED); },
      getCurrentPlant()->GetRuntimeClass());
    setCurrentPlant(nullptr);
    return;
  }
  // ������ֲ��
  auto& plant = plantMatrix[row][col] = getCurrentPlant();
  // �۳����� ������Ҫ��̬�ж�ֲ������
  theDoc->getSeedBank().foreachAllSeed(
    [&](Seed& s) { sbank.setSunlight(sbank.getSunlight() - s.getPrice()); },
    plant->GetRuntimeClass());
  plant->setPlantPos({ row, col });
  plant->setLeftX(yard.getPlantLeftX() + col * yard.getPlantWidth() +
    yard.getPlantWidth() * 0.2);
  plant->setTopY(yard.getPlantTopY() + row * yard.getPlantHeight() +
    yard.getPlantHeight() * (row < 3 ? 0.1 : 0));
  plant->setMapState(Plant::DefaultDynamic);
  // ������ֲ
  sbank.foreachAllSeed(
    [](Seed& seed) {
      seed.wait();
  seed.cleanState(Seed::SELECTED);
    },
    plant->GetRuntimeClass());
  // ���ѡ�е�ֲ��
  currentPlant.reset();
}

void Player::collectSun(Yard& yard, SeedBank& sbank,
  std::list<std::shared_ptr<Sun>>& sunList,
  CPoint& point) {
  for (auto iter = sunList.begin(); iter != sunList.end(); ++iter) {
    auto& sun = *iter;
    if (sun->onClick(point.x, point.y)) {
      sbank.setSunlight(sbank.getSunlight() + sun->getSunValue());
      if (!sun->isState(Sun::COLLECTED)) {
        (*iter)->setState(Sun::COLLECTED);
        int leftX = (int)((*iter)->getLeftX());
        int topY = (int)((*iter)->getTopY());
        // ����ƫ�Ʋ���
        // yard.getWidth() / 6 ��seedbank������λ��
        auto& currSun = *iter;
        currSun->moveSpeed = 20;  // (yard.getWidth() * 0.6) * 0.01;
        currSun->distance = (int)(sqrt(
          (topY * topY) + pow(yard.getWidth() / 7 - currSun->getLeftX(), 2)));
        currSun->xStep = (currSun->getLeftX() - yard.getWidth() / 7) /
          (currSun->distance / currSun->moveSpeed);
        currSun->yStep = (currSun->getTopY() + 100) /
          (currSun->distance / currSun->moveSpeed);
        // if (leftX < topY) (*iter)->moveFlg = false;
        break;
      }
    }
    if (sun->isState(Sun::FLASH)) {
      iter = sunList.erase(decltype(iter)(iter));
      break;
    }
  }
}

void Player::drawCurrentPlant(HDC hDC, Yard& yard) {
  std::shared_ptr<Plant> curr = getCurrentPlant();
  // û��ѡ��ֲ�������ֲ��������ʾ
  if (!curr) return;
  CPoint currPos = getPos();
  // ����ѡ�е�ֲ��
  static CPoint pos;
  // ��������
  CPoint newPos = yard.getPlantPos(currPos.x, currPos.y);
  if (pos != newPos) pos = newPos;
  for (;;) {
    // ����ʾ������
    if (!yard.isMovePlantArea(currPos.x, currPos.y)) break;
    if (yard.getPlantMatrix()[newPos.x][newPos.y]) break;
    curr->setState(Plant::VIRTUAL);
    curr->setLeftX(yard.getPlantLeftX() + pos.y * yard.getPlantWidth() +
      yard.getPlantWidth() * 0.2);
    curr->setTopY(yard.getPlantTopY() + pos.x * yard.getPlantHeight() +
      yard.getPlantHeight() * (pos.x < 3 ? 0.1 : 0));
    curr->draw(hDC);
    curr->cleanState(Plant::VIRTUAL);
    break;
  }

  if (curr->GetRuntimeClass() == RUNTIME_CLASS(Chomper)) {
    curr->setLeftX(currPos.x - curr->getWidth() * 0.25);
    curr->setTopY(currPos.y - curr->getHeight() * 0.4);
  }
  else {
    curr->setLeftX(currPos.x - curr->getWidth() * 0.5);
    curr->setTopY(currPos.y - curr->getHeight() * 0.8);
  }
  curr->draw(hDC);
}

void Player::setCurrentPlant(std::shared_ptr<Plant> plant) {
  currentPlant = plant;
}