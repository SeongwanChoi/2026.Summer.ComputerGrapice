#pragma once
#include <iostream>
#include <limits>
#include <string>

using namespace std;

enum Type_ScreenSize
{
	_32inch = 1,
	_43inch = 2,
	_50inch = 3,
	_55inch = 4,
	_65inch = 5
};

enum Type_Brand
{
	SAMSUNG = 1,
	LG = 2,
	SONY = 3,
	PHILIPS = 4
};

enum Type_Panel
{
	LED = 1,
	OLED = 2,
	QLED = 3,
	LCD = 4
};

enum Type_Resolution
{
	HD = 1,
	FULL_HD = 2,
	UHD = 3,
	_4K = 4,
	_8K = 5
};

class CTV
{
	Type_Panel m_ePanel;
	Type_Brand m_eBrand;
	Type_ScreenSize m_eScreenSize;
	Type_Resolution m_eResolution;

	unsigned int m_nChannel;
	unsigned int m_nVolume;

public:
	CTV(Type_Panel panel, Type_Brand brand, Type_ScreenSize screansize, Type_Resolution resolution)
	{
		m_ePanel = panel;
		m_eBrand = brand;
		m_eScreenSize = screansize;
		m_eResolution = resolution;

		m_nChannel = 1;
		m_nVolume = 30;
	}

	void Display()
	{
		cout << "Panel:" << m_ePanel << endl;
		cout << "Brand:" << m_eBrand << endl;
		cout << "ScreenSize:" << m_eScreenSize << endl;
		cout << "Resolution:" << m_eResolution << endl;
	}

	void ChannelUp()
	{
		m_nChannel++;
		cout << "Ch: " << m_nChannel << endl;
	}

	void VolumeUp()
	{
		m_nVolume++;
		cout << "Vol: " << m_nVolume << endl;
	}

	void ChannelDown()
	{
		m_nChannel--;
		cout << "Ch: " << m_nChannel << endl;
	}

	void VolumeDown()
	{
		m_nVolume--;
		cout << "Vol: " << m_nVolume << endl;
	}

	void setChannel(unsigned int channel)
	{
		m_nChannel = channel;
		cout << "Ch: " << m_nChannel << endl;
	}

	int GetChannel()
	{
		return m_nChannel;
	}

	void SetVolume(unsigned int volume)
	{
		m_nVolume = volume;
		cout << "Vol: " << m_nVolume << endl;
	}

	int GetVolume()
	{
		return m_nVolume;
	}
};

// 매장에서 TV를 여러 종류의 TV중에 1가지 TV를 모델을 고른다.
// 물건을 계산 이후 창고에서 집까지 배송한다.
// TV를 설치하고 전원을 켜고 채널을 바꾸면 다른 방송을 볼 수 있고, 
// 볼륨 조절 버튼을 이용하여 소리 작거나 크면 조작 가능하다.

void TvMain()
{
	cout << "=================================" << endl;
	cout << "TV 매장에 오신것을 환영합니다!" << endl;
	cout << "=================================" << endl;

	bool price;
	int panel;
	int brand;
	int screansize;
	int resolution;
	int input;

	cout << "원하는 패널을 골라주세요." << endl;
	cout << "1. LED, 2. OLED, 3. QLED, 4. LCD" << endl;
	cin >> panel;

	cout << "원하는 브렌드를 골라주세요." << endl;
	cout << "1. SAMSUNG, 2. LG, 3. SONY, 4. PHILIPS" << endl;
	cin >> brand;

	cout << "원하는 크기의 스크린을 골라주세요." << endl;
	cout << "1. 32inch, 2. 43inch, 3. 50inch, 4. 55inch, 5. 65inch" << endl;
	cin >> screansize;

	cout << "원하는 해상도를 골라주세요." << endl;
	cout << "1. HD, 2. FULL_HD, 3. UHD, 4. 4K, 5. 8K" << endl;
	cin >> resolution;

	CTV cTv{ Type_Panel(panel), Type_Brand(brand), Type_ScreenSize(screansize), Type_Resolution(resolution) };

	cTv.Display();

	cout << "해당 제품으로 구매하시겠습니까? (0. 예, 1. 아니오)" << endl;
	cin >> price;

	if (price)
	{
		cout << "구매를 취소하셨습니다." << endl;
		return;
	}
	else
	{
		string address;
		cout << "배송할 주소를 입력해 주세요" << endl;
		cin >> address;
		cout << address << "로 배송이 완료되었습니다." << endl;
	}

	cout << "TV 설치를 완료했습니다." << endl;

	while (true)
	{
		cout << "1. 채널 올리기, 2. 채널 내리기, 3. 채널 입력, 4. 볼륨 올리기, 5. 볼륨 내리기, 6. 끄기" << endl;

		cin >> input;

		switch (input)
		{
			case 1:
				if (cTv.GetChannel() == 100)
					cTv.setChannel(1);
				else
					cTv.ChannelUp();
				break;
			case 2:
				if (cTv.GetChannel() == 1)
					cTv.setChannel(100);
				else
					cTv.ChannelDown();
				break;
			case 3:
				int channel;
				cout << "채널을 입력해주세요." << endl;
				cin >> channel;
				if (channel <= 100)
					cTv.setChannel(channel);
				else
					cout << "없는 채널입니다." << endl;

				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				break;
			case 4:
				if (cTv.GetVolume() == 100)
					cTv.SetVolume(1);
				else
					cTv.VolumeUp();
				break;
			case 5:
				if (cTv.GetVolume() == 1)
					cTv.SetVolume(100);
				else
					cTv.VolumeDown();
				break;
			case 6:
				cout << "TV를 종료합니다." << endl;
				return;
		default:
			cout << "잘못된 입력입니다." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
	}

}