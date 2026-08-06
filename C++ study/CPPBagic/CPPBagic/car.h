#pragma once

#include <string>
#include <iostream>

using namespace std;

enum EGEAR { P, N, D, R, ONE, TOW };

class CCar
{
	string m_strColor;
	EGEAR m_eGear;
	float m_fSpeedf;

public:
	CCar(string color)
	{
		m_strColor = color;
		m_eGear = EGEAR::P;
		m_fSpeedf = 0.0f;
	}

	void SetColor(string color)
	{
		m_strColor = color;
	}

	void SetGear(EGEAR gear)
	{
		m_eGear = gear;
	}

	float GetSpeed()
	{
		return m_fSpeedf;
	}

	void Accelerator()
	{
		// 1. 클래스 내부이기 때문에 m_eGear를 자유롭게 꺼내 쓸 수 있습니다!
		if (m_eGear == EGEAR::D)
		{
			m_fSpeedf++;
		}
		else
		{
			cout << "기어를 D로 변경해야 엑셀을 밟을 수 있습니다." << endl;
		}
	}

	void Break()
	{
		m_fSpeedf--;
	}

	void Display()
	{
		cout << "Color:" << m_strColor << endl;
		cout << "Speed:" << m_fSpeedf << endl;
		cout << "Gear:" << m_eGear << endl;
	}
};
/*
	구매한 자동차의 색상을 지정하고 공장에서 주문한다.
	1에서 정한 색상으로 공장에서 자동차를 제조한다.
	3에서 생산된 자동차를 인수 받는다.
	자동차는 기어를 D에 넣어야 엑셀을 밟으면 속도가 증가한다.
	자동차는 엑셀을 밟으면 속도가 증가한다.
	자동차의 브레이크를 밟으면 속도가 감소한다.
	속도가 0이 되면 자동차는 멈춘다.
	자동차의 조작을 입력을 받아 선택하도록 한다.
	자동차의 기어를 P에 위치에 넣고 주행을 마친다.

*/
void CarMain()
{
	CCar cCar("Black");

	cCar.SetGear(EGEAR::N);

	int switch_on = 0;
	while (true)
	{
		cout << "자동차 조작을 선택하세요." << endl;
		cout << "1. 엑셀, 2. 브레이크, 3. 기어N, 4. 기어D, 5. 기어R, 6. 기어ONE, 7. 기어TOW, 8. 주행종료" << endl;

		cin >> switch_on;

		switch (switch_on)
		{
		case 1:
			cCar.Accelerator();
			break;
		case 2:
			cCar.Break();
			break;
		case 3:
			cCar.SetGear(EGEAR::N);
			break;
		case 4:
			cCar.SetGear(EGEAR::D);
			break;
		case 5:
			cCar.SetGear(EGEAR::R);
			break;
		case 6:
			cCar.SetGear(EGEAR::ONE);
			break;
		case 7:
			cCar.SetGear(EGEAR::TOW);
			break;
		case 8:
			cCar.SetGear(EGEAR::P);
			break;
		default:
			break;
		}



		cCar.Display();

		if (cCar.GetSpeed() == 0)
		{
			cout << "자동차가 멈췄습니다." << endl;
		}

		if (switch_on == 8)
		{
			cout << "주행을 종료합니다." << endl;
			break;
		}

	}
	//cCar.Display();

}