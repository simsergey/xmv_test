/* 	xmv test v1.2

	Приложение предназначено для сравнения производительности вычислений
	векторов в числах с плавающей запятой для одного потока, проводимых
	непосредственно (FLOAT) либо с помощью SSE (XMVECTOR) на ЦП разных
	производителей и поколений.

	Приложение получает разрешение высокоточного таймера в системе и проводит
	измерения для каждого этапа в тиках этого таймера, затем производится
	определение времени в наносекундах и определение производительности
	в мегафлопсах.

	Предполагается 3 этапа - 2D, 3D, 4D векторы.

	Исходный код может быть использован по лицензии MIT.
	
	Автор: Соломаха С.С. - sergey.solomakha@yahoo.com
*/

#include "stdafx.h"

#include <DirectXMath.h>
#include <Windows.h>
#include <locale>

using namespace DirectX;

int main()
{
	XMVECTOR		xmv_last,		// Векторы XMFLOAT	
					xmv_correct,
					xmv_new;
	float			lx, ly, lz, lw, // Векторы Float
					cx, cy, cz, cw,
					nx, ny, nz, nw;
	LARGE_INTEGER	resl,			// Разрешение высокоточного таймера
					atBegin,		// Значение высокоточного таймера в начале этапа
					atEnd;			// Хначение высокоточного таймера в конце этапа
	LONGLONG		lixmv,			// Результат в тиках для этапа
					lixmns,			// Результат в наносекундах для этапа
					flops;			// Результат в мегафлопсах для этапа
	unsigned long 	j;				// Индекс цикла

	// Установка русского языка для консоли и титул
	setlocale(LC_ALL, "Russian");
	wprintf(L"xmv test v1.2\n");
	wprintf(L"Измерение производительности:\n");

	// Получение разрешения высокоточного таймера
	if (!QueryPerformanceFrequency(&resl))
	{
		wprintf(L" Не удалось получить разрешение высокоточного таймера.\n");
		return 0;
	}
	wprintf(L" Разрешение высокоточного таймера: %lld тиков в секунду.\n \
1 тик = %lld наносекунд",
			resl.QuadPart,
			1000000000ll / resl.QuadPart
	);
	
	{ // Этап 1 - Сложение 3 млн. 2D векторов
		wprintf(L"\n\n 1. Сложение 3 млн. 2D векторов из чисел с плавающей запятой\n");

		// XMVECTOR
		nx = 0.0f; ny = 0.0f;
		cx = 30.0f; cy = 85.0f;
		lx = 10.0f + nx; ly = 15.0f + ny;

		xmv_last = XMLoadFloat2(&XMFLOAT2(lx, ly));
		xmv_correct = XMLoadFloat2(&XMFLOAT2(cx, cy));
		xmv_new = XMLoadFloat2(&XMFLOAT2(nx, ny));

		if (!QueryPerformanceCounter(&atBegin))
		{
			wprintf(L" \nНе удалось получить начальное значение высокоточного таймера.");
			return 0;
		}

		for (j = 0ul; j < 1000000ul; j++)
		{
			xmv_new = xmv_last + xmv_correct + xmv_new;
		}

		if (!QueryPerformanceCounter(&atEnd))
		{
			wprintf(L" \nНе удалось получить конечное значение высокоточного таймера.");
			return 0;
		}

		lixmv = atEnd.QuadPart - atBegin.QuadPart;
		lixmns = lixmv * 1000000000ll;
		lixmns /= resl.QuadPart;
		wprintf(L"   В формате XMVECTOR ");
		wprintf(L"заняло %6lld тиков или %6lld наносекунд", lixmv, lixmns);
		flops = 4000000000000000ll / lixmns;
		flops /= 1000000; // Mflops
		wprintf(L"\n   Производительность %6lld мегафлопс", flops);

		// FLOAT
		nx = 0.0f; ny = 0.0f;
		cx = 30.0f; cy = 85.0f;
		lx = 10.0f + nx; ly = 15.0f + ny;
		
		if (!QueryPerformanceCounter(&atBegin))
		{
			wprintf(L" \nНе удалось получить начальное значение высокоточного таймера.");
			return 0;
		}

		for (j = 0ul; j < 1000000ul; j++)
		{
			nx = lx + cx + nx;
			ny = ly + cy + ny;
		}

		if (!QueryPerformanceCounter(&atEnd))
		{
			wprintf(L" \nНе удалось узнать конечное значение высокоточного таймера.");
			return 0;
		}

		lixmv = atEnd.QuadPart - atBegin.QuadPart;
		lixmns = lixmv * 1000000000ll;
		lixmns /= resl.QuadPart;
		wprintf(L"\n   В формате FLOAT    ");
		wprintf(L"заняло %6lld тиков или %6lld наносекунд", lixmv, lixmns);
		flops = 4000000000000000ll / lixmns;
		flops /= 1000000; // Mflops
		wprintf(L"\n   Производительность %6lld мегафлопс", flops);

		if (nx != XMVectorGetX(xmv_new) || ny != XMVectorGetY(xmv_new))
			wprintf(L"\n   Ошибка! Расчеты для XMVECTOR и FLOAT не совпадают!");
	}

	{ // Этап 2 -  Сложение 3 млн. 3D векторов
		wprintf(L"\n\n 2. Сложение 3 млн. 3D векторов из чисел с плавающей запятой");

		// XMVECTOR
		nx = 0.0f;	ny = 0.0f;	nz = 0.0f;
		cx = 30.0f; cy = 85.0f; cz = 6.0f;
		lx = 10.0f; ly = 15.0f;	lz = 5.0f;

		xmv_last = XMLoadFloat3(&XMFLOAT3(lx, ly, lz));
		xmv_correct = XMLoadFloat3(&XMFLOAT3(cx, cy, cz));
		xmv_new = XMLoadFloat3(&XMFLOAT3(nx, ny, nz));

		if (!QueryPerformanceCounter(&atBegin))
		{
			wprintf(L" \nНе удалось получить начальное значение высокоточного таймера.");
			return 0;
		}

		for (j = 0ul; j < 1000000ul; j++)
		{
			xmv_new = xmv_last + xmv_correct + xmv_new;
		}

		if (!QueryPerformanceCounter(&atEnd))
		{
			wprintf(L" \nНе удалось получить конечное значение высокоточного таймера.");
			return 0;
		}

		lixmv = atEnd.QuadPart - atBegin.QuadPart;
		lixmns = lixmv * 1000000000ll;
		lixmns /= resl.QuadPart;
		wprintf(L"\n   В формате XMVECTOR ");
		wprintf(L"заняло %6lld тиков или %6lld наносекунд", lixmv, lixmns);
		flops = 6000000000000000ll / lixmns;
		flops /= 1000000; // Mflops
		wprintf(L"\n   Производительность %6lld мегафлопс", flops);

		// FLOAT
		nx = 0.0f;	ny = 0.0f;	nz = 0.0f;
		cx = 30.0f; cy = 85.0f; cz = 6.0f;
		lx = 10.0f; ly = 15.0f;	lz = 5.0f;

		if (!QueryPerformanceCounter(&atBegin))
		{
			wprintf(L" \nНе удалось получить начальное значение высокоточного таймера.");
			return 0;
		}

		for (j = 0ul; j < 1000000ul; j++)
		{
			nx = lx + cx + nx;
			ny = ly + cy + ny;
			nz = lz + cz + nz;
		}

		if (!QueryPerformanceCounter(&atEnd))
		{
			wprintf(L" \nНе удалось получить конечное значение высокоточного таймера.");
			return 0;
		}

		lixmv = atEnd.QuadPart - atBegin.QuadPart;
		lixmns = lixmv * 1000000000ll;
		lixmns /= resl.QuadPart;
		wprintf(L"\n   В формате FLOAT    ");
		wprintf(L"заняло %6lld тиков или %6lld наносекунд", lixmv, lixmns);
		flops = 6000000000000000ll / lixmns;
		flops /= 1000000; // Mflops
		wprintf(L"\n   Производительность %6lld мегафлопс", flops);
		
		if (nx != XMVectorGetX(xmv_new) || ny != XMVectorGetY(xmv_new) || nz != XMVectorGetZ(xmv_new))
			wprintf(L"\n   Ошибка! Расчеты для XMVECTOR и FLOAT не совпадают!");
	}

	{ // Этап 3 - Сложение 3 млн. 4D векторов
		wprintf(L"\n\n 3. Сложение 3 млн. 4D векторов из чисел с плавающей запятой");

		// XMVECTOR
		nx = 0.0f;	ny = 0.0f;	nz = 0.0f;	nw = 0.0f;
		cx = 30.0f; cy = 85.0f; cz = 6.0f;	cw = 32.0f;
		lx = 10.0f; ly = 15.0f;	lz = 5.0f;	lw = 9.0f;

		xmv_last = XMLoadFloat4(&XMFLOAT4(lx, ly, lz, lw));
		xmv_correct = XMLoadFloat4(&XMFLOAT4(cx, cy, cz, cw));
		xmv_new = XMLoadFloat4(&XMFLOAT4(nx, ny, nz, nw));

		if (!QueryPerformanceCounter(&atBegin))
		{
			wprintf(L" \nНе удалось получить начальное значение высокоточного таймера.");
			return 0;
		}

		for (j = 0ul; j < 1000000ul; j++)
		{
			xmv_new = xmv_last + xmv_correct + xmv_new;
		}

		if (!QueryPerformanceCounter(&atEnd))
		{
			wprintf(L" \nНе удалось получить конечное значение высокоточного таймера.");
			return 0;
		}

		lixmv = atEnd.QuadPart - atBegin.QuadPart;
		lixmns = lixmv * 1000000000ll;
		lixmns /= resl.QuadPart;
		wprintf(L"\n   В формате XMVECTOR ");
		wprintf(L"заняло %6lld тиков или %6lld наносекунд", lixmv, lixmns);
		flops = 8000000000000000ll / lixmns;
		flops /= 1000000; // Mflops
		wprintf(L"\n   Производительность %6lld мегафлопс", flops);

		// FLOAT
		nx = 0.0f;	ny = 0.0f;	nz = 0.0f;	nw = 0.0f;
		cx = 30.0f; cy = 85.0f; cz = 6.0f;	cw = 32.0f;
		lx = 10.0f; ly = 15.0f;	lz = 5.0f;	lw = 9.0f;

		if (!QueryPerformanceCounter(&atBegin))
		{
			wprintf(L" \nНе удалось получить начальное значение высокоточного таймера.");
			return 0;
		}

		for (j = 0ul; j < 1000000ul; j++)
		{
			nx = lx + cx + nx;
			ny = ly + cy + ny;
			nz = lz + cz + nz;
			nw = lw + cw + nw;
		}

		if (!QueryPerformanceCounter(&atEnd))
		{
			wprintf(L" \nНе удалось получить конечное значение высокоточного таймера.");
			return 0;
		}

		lixmv = atEnd.QuadPart - atBegin.QuadPart;
		lixmns = lixmv * 1000000000ll;
		lixmns /= resl.QuadPart;

		wprintf(L"\n   В формате FLOAT    ");
		wprintf(L"заняло %6lld тиков или %6lld наносекунд", lixmv, lixmns);
		flops = 8000000000000000ll / lixmns;
		flops /= 1000000; // Mflops
		wprintf(L"\n   Производительность %6lld мегафлопс", flops);

		if (nx != XMVectorGetX(xmv_new) || ny != XMVectorGetY(xmv_new) 
			|| nz != XMVectorGetZ(xmv_new) || nw != XMVectorGetW(xmv_new))
			wprintf(L"\n   Ошибка! Расчеты для XMVECTOR и FLOAT не совпадают!");
	}

	wprintf(L"\n\n Тест завершен.\n");
	flushall();
	char d = 0;
	scanf("%c", &d);

    return 0;
}

