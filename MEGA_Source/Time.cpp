#include "Time.h"
#include "MEGA_InClude.h"

#define QUADPART(a)			(a.QuadPart)

namespace MEGA
{
	float Time::deltaTime = 0.0f;
	int Time::_fps = 0;

	LARGE_INTEGER Time::cpuFrequency = {};
	LARGE_INTEGER Time::startFrequency = {};
	LARGE_INTEGER Time::endFrequency = {};

	void Time::Init()
	{
		// CPU�� ���� ���ļ� �� ī��Ʈ ����
		QueryPerformanceFrequency(&cpuFrequency);
		QueryPerformanceCounter(&startFrequency);
	}
	void Time::Update()
	{
		QueryPerformanceCounter(&endFrequency);

		// ���ۿ� �ҿ�� �ð�(���ļ�)
		// �ҿ�� �ð��� ������ ���ļ��� ���� �� = deltaTime
		float calculationFrequency = static_cast<float>(QUADPART(endFrequency) - QUADPART(startFrequency));
		deltaTime = calculationFrequency / static_cast<float>(QUADPART(cpuFrequency));

		// �� ���۰� ��Ȯ�� ����� ���� �ʱ�ȭ.
		startFrequency.QuadPart = endFrequency.QuadPart; 
	}

	void Time::Render(HDC hdc)
	{
		// FPS ǥ��
		static float time = 0.0f;
		time += deltaTime;

		if (time >= 0.1f)
		{
			float fps = 1.0f / deltaTime;
			time = 0.0f;

			_fps = static_cast<int>(fps);
		}
	
		wchar_t str[256] = L"";
		swprintf_s(str, 256, L"FPS : %d", static_cast<int>(_fps));

		int len = wcsnlen_s(str, 256);
		TextOut(hdc, 50, 50, str, len);
		
	}
}
