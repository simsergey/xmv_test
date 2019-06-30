/* 	xmv test v1.2

	���������� ������������� ��� ��������� ������������������ ����������
	�������� � ������ � ��������� ������� ��� ������ ������, ����������
	��������������� (FLOAT) ���� � ������� SSE (XMVECTOR) �� �� ������
	�������������� � ���������.

	���������� �������� ���������� ������������� ������� � ������� � ��������
	��������� ��� ������� ����� � ����� ����� �������, ����� ������������
	����������� ������� � ������������ � ����������� ������������������
	� �����������.

	�������������� 3 ����� - 2D, 3D, 4D �������.

	�������� ��� ����� ���� ����������� �� �������� MIT.
	
	�����: �������� �.�. - sergey.solomakha@yahoo.com
*/

#include "stdafx.h"

#include <DirectXMath.h>
#include <Windows.h>
#include <locale>

using namespace DirectX;

int main()
{
	XMVECTOR		xmv_last,		// ������� XMFLOAT	
					xmv_correct,
					xmv_new;
	float			lx, ly, lz, lw, // ������� Float
					cx, cy, cz, cw,
					nx, ny, nz, nw;
	LARGE_INTEGER	resl,			// ���������� ������������� �������
					atBegin,		// �������� ������������� ������� � ������ �����
					atEnd;			// �������� ������������� ������� � ����� �����
	LONGLONG		lixmv,			// ��������� � ����� ��� �����
					lixmns,			// ��������� � ������������ ��� �����
					flops;			// ��������� � ����������� ��� �����
	unsigned long 	j;				// ������ �����

	// ��������� �������� ����� ��� ������� � �����
	setlocale(LC_ALL, "Russian");
	wprintf(L"xmv test v1.2\n");
	wprintf(L"��������� ������������������:\n");

	// ��������� ���������� ������������� �������
	if (!QueryPerformanceFrequency(&resl))
	{
		wprintf(L" �� ������� �������� ���������� ������������� �������.\n");
		return 0;
	}
	wprintf(L" ���������� ������������� �������: %lld ����� � �������.\n \
1 ��� = %lld ����������",
			resl.QuadPart,
			1000000000ll / resl.QuadPart
	);
	
	{ // ���� 1 - �������� 3 ���. 2D ��������
		wprintf(L"\n\n 1. �������� 3 ���. 2D �������� �� ����� � ��������� �������\n");

		// XMVECTOR
		nx = 0.0f; ny = 0.0f;
		cx = 30.0f; cy = 85.0f;
		lx = 10.0f + nx; ly = 15.0f + ny;

		xmv_last = XMLoadFloat2(&XMFLOAT2(lx, ly));
		xmv_correct = XMLoadFloat2(&XMFLOAT2(cx, cy));
		xmv_new = XMLoadFloat2(&XMFLOAT2(nx, ny));

		if (!QueryPerformanceCounter(&atBegin))
		{
			wprintf(L" \n�� ������� �������� ��������� �������� ������������� �������.");
			return 0;
		}

		for (j = 0ul; j < 1000000ul; j++)
		{
			xmv_new = xmv_last + xmv_correct + xmv_new;
		}

		if (!QueryPerformanceCounter(&atEnd))
		{
			wprintf(L" \n�� ������� �������� �������� �������� ������������� �������.");
			return 0;
		}

		lixmv = atEnd.QuadPart - atBegin.QuadPart;
		lixmns = lixmv * 1000000000ll;
		lixmns /= resl.QuadPart;
		wprintf(L"   � ������� XMVECTOR ");
		wprintf(L"������ %6lld ����� ��� %6lld ����������", lixmv, lixmns);
		flops = 4000000000000000ll / lixmns;
		flops /= 1000000; // Mflops
		wprintf(L"\n   ������������������ %6lld ���������", flops);

		// FLOAT
		nx = 0.0f; ny = 0.0f;
		cx = 30.0f; cy = 85.0f;
		lx = 10.0f + nx; ly = 15.0f + ny;
		
		if (!QueryPerformanceCounter(&atBegin))
		{
			wprintf(L" \n�� ������� �������� ��������� �������� ������������� �������.");
			return 0;
		}

		for (j = 0ul; j < 1000000ul; j++)
		{
			nx = lx + cx + nx;
			ny = ly + cy + ny;
		}

		if (!QueryPerformanceCounter(&atEnd))
		{
			wprintf(L" \n�� ������� ������ �������� �������� ������������� �������.");
			return 0;
		}

		lixmv = atEnd.QuadPart - atBegin.QuadPart;
		lixmns = lixmv * 1000000000ll;
		lixmns /= resl.QuadPart;
		wprintf(L"\n   � ������� FLOAT    ");
		wprintf(L"������ %6lld ����� ��� %6lld ����������", lixmv, lixmns);
		flops = 4000000000000000ll / lixmns;
		flops /= 1000000; // Mflops
		wprintf(L"\n   ������������������ %6lld ���������", flops);

		if (nx != XMVectorGetX(xmv_new) || ny != XMVectorGetY(xmv_new))
			wprintf(L"\n   ������! ������� ��� XMVECTOR � FLOAT �� ���������!");
	}

	{ // ���� 2 -  �������� 3 ���. 3D ��������
		wprintf(L"\n\n 2. �������� 3 ���. 3D �������� �� ����� � ��������� �������");

		// XMVECTOR
		nx = 0.0f;	ny = 0.0f;	nz = 0.0f;
		cx = 30.0f; cy = 85.0f; cz = 6.0f;
		lx = 10.0f; ly = 15.0f;	lz = 5.0f;

		xmv_last = XMLoadFloat3(&XMFLOAT3(lx, ly, lz));
		xmv_correct = XMLoadFloat3(&XMFLOAT3(cx, cy, cz));
		xmv_new = XMLoadFloat3(&XMFLOAT3(nx, ny, nz));

		if (!QueryPerformanceCounter(&atBegin))
		{
			wprintf(L" \n�� ������� �������� ��������� �������� ������������� �������.");
			return 0;
		}

		for (j = 0ul; j < 1000000ul; j++)
		{
			xmv_new = xmv_last + xmv_correct + xmv_new;
		}

		if (!QueryPerformanceCounter(&atEnd))
		{
			wprintf(L" \n�� ������� �������� �������� �������� ������������� �������.");
			return 0;
		}

		lixmv = atEnd.QuadPart - atBegin.QuadPart;
		lixmns = lixmv * 1000000000ll;
		lixmns /= resl.QuadPart;
		wprintf(L"\n   � ������� XMVECTOR ");
		wprintf(L"������ %6lld ����� ��� %6lld ����������", lixmv, lixmns);
		flops = 6000000000000000ll / lixmns;
		flops /= 1000000; // Mflops
		wprintf(L"\n   ������������������ %6lld ���������", flops);

		// FLOAT
		nx = 0.0f;	ny = 0.0f;	nz = 0.0f;
		cx = 30.0f; cy = 85.0f; cz = 6.0f;
		lx = 10.0f; ly = 15.0f;	lz = 5.0f;

		if (!QueryPerformanceCounter(&atBegin))
		{
			wprintf(L" \n�� ������� �������� ��������� �������� ������������� �������.");
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
			wprintf(L" \n�� ������� �������� �������� �������� ������������� �������.");
			return 0;
		}

		lixmv = atEnd.QuadPart - atBegin.QuadPart;
		lixmns = lixmv * 1000000000ll;
		lixmns /= resl.QuadPart;
		wprintf(L"\n   � ������� FLOAT    ");
		wprintf(L"������ %6lld ����� ��� %6lld ����������", lixmv, lixmns);
		flops = 6000000000000000ll / lixmns;
		flops /= 1000000; // Mflops
		wprintf(L"\n   ������������������ %6lld ���������", flops);
		
		if (nx != XMVectorGetX(xmv_new) || ny != XMVectorGetY(xmv_new) || nz != XMVectorGetZ(xmv_new))
			wprintf(L"\n   ������! ������� ��� XMVECTOR � FLOAT �� ���������!");
	}

	{ // ���� 3 - �������� 3 ���. 4D ��������
		wprintf(L"\n\n 3. �������� 3 ���. 4D �������� �� ����� � ��������� �������");

		// XMVECTOR
		nx = 0.0f;	ny = 0.0f;	nz = 0.0f;	nw = 0.0f;
		cx = 30.0f; cy = 85.0f; cz = 6.0f;	cw = 32.0f;
		lx = 10.0f; ly = 15.0f;	lz = 5.0f;	lw = 9.0f;

		xmv_last = XMLoadFloat4(&XMFLOAT4(lx, ly, lz, lw));
		xmv_correct = XMLoadFloat4(&XMFLOAT4(cx, cy, cz, cw));
		xmv_new = XMLoadFloat4(&XMFLOAT4(nx, ny, nz, nw));

		if (!QueryPerformanceCounter(&atBegin))
		{
			wprintf(L" \n�� ������� �������� ��������� �������� ������������� �������.");
			return 0;
		}

		for (j = 0ul; j < 1000000ul; j++)
		{
			xmv_new = xmv_last + xmv_correct + xmv_new;
		}

		if (!QueryPerformanceCounter(&atEnd))
		{
			wprintf(L" \n�� ������� �������� �������� �������� ������������� �������.");
			return 0;
		}

		lixmv = atEnd.QuadPart - atBegin.QuadPart;
		lixmns = lixmv * 1000000000ll;
		lixmns /= resl.QuadPart;
		wprintf(L"\n   � ������� XMVECTOR ");
		wprintf(L"������ %6lld ����� ��� %6lld ����������", lixmv, lixmns);
		flops = 8000000000000000ll / lixmns;
		flops /= 1000000; // Mflops
		wprintf(L"\n   ������������������ %6lld ���������", flops);

		// FLOAT
		nx = 0.0f;	ny = 0.0f;	nz = 0.0f;	nw = 0.0f;
		cx = 30.0f; cy = 85.0f; cz = 6.0f;	cw = 32.0f;
		lx = 10.0f; ly = 15.0f;	lz = 5.0f;	lw = 9.0f;

		if (!QueryPerformanceCounter(&atBegin))
		{
			wprintf(L" \n�� ������� �������� ��������� �������� ������������� �������.");
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
			wprintf(L" \n�� ������� �������� �������� �������� ������������� �������.");
			return 0;
		}

		lixmv = atEnd.QuadPart - atBegin.QuadPart;
		lixmns = lixmv * 1000000000ll;
		lixmns /= resl.QuadPart;

		wprintf(L"\n   � ������� FLOAT    ");
		wprintf(L"������ %6lld ����� ��� %6lld ����������", lixmv, lixmns);
		flops = 8000000000000000ll / lixmns;
		flops /= 1000000; // Mflops
		wprintf(L"\n   ������������������ %6lld ���������", flops);

		if (nx != XMVectorGetX(xmv_new) || ny != XMVectorGetY(xmv_new) 
			|| nz != XMVectorGetZ(xmv_new) || nw != XMVectorGetW(xmv_new))
			wprintf(L"\n   ������! ������� ��� XMVECTOR � FLOAT �� ���������!");
	}

	wprintf(L"\n\n ���� ��������.\n");
	flushall();
	char d = 0;
	scanf("%c", &d);

    return 0;
}

