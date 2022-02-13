//#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
#define max 10
struct DoVat
{
	char loai[21];
	float gt;
	int tl, dchon;
};

void nhapDL(DoVat dsdv[], int& w, int& n)
{
	printf("\nNhap thong tin loai vang");
	_flushall();
	printf("\nNhap trong luong toi da: ");
	scanf_s("%d", &w);
	printf("\nNhap so luong loai vang: ");
	scanf_s("%d", &n);
	for (int i = 0; i < n; i++)
	{
		printf("\nNhap loai vang %d: ", i);
		scanf("%s", dsdv[i].loai);
		printf("\nNhap trong luong vang: ");
		scanf_s("%d", &dsdv[i].tl);
		printf("Nhap gia tri vang: ");
		scanf_s("%f", &dsdv[i].gt);
	}
}
DoVat *DocFile(int *w, int *n)
{
	FILE *f;
	DoVat *dsdv;
	f = fopen("input.txt", "r");
	fscanf(f, "%d", w);
	dsdv = (DoVat*)malloc(sizeof(DoVat));
	int i = 0;
	while (!feof(f))
	{
		fscanf(f, "%d%f%[^\n]", &dsdv[i].tl, &dsdv[i].gt, &dsdv[i].loai);
		dsdv[i].dchon = 0;
		i++;
		dsdv = (DoVat*)realloc(dsdv, sizeof(DoVat)*(i + 1));
	}
	*n = i;
	fclose(f);
	return dsdv;
}
void InDSDV(DoVat *dsdv, int n, int w)
{
	int i, Tongtl = 0;
	float Tonggt = 0.0;
	printf("\nQuy hoach dong\n");
	printf("|STT|     Ten Do Vat     |T.Luong | Gia Tri |So Lan Chon|\n");
	for (i = 0; i < n; i++)
	{
		printf("|%-3d|%-18s|%8d|%9.2f|%11d|\n", i + 1, dsdv[i].loai, dsdv[i].tl, dsdv[i].gt, dsdv[i].dchon);
		Tongtl = Tongtl + dsdv[i].dchon*dsdv[i].tl;
		Tonggt = Tonggt + dsdv[i].dchon*dsdv[i].gt;
	}
	printf("Trong luong cua ba lo: %d\n", w);
	printf("Tong trong luong cac do vat duoc chon: %d\nTong gia tri: %-9.2f\n", Tongtl, Tonggt);
}
void TaoBang(DoVat *dsdv, int n, int w, float f[][max], int x[][max])
{
	int xk, yk, k;
	int xMax, v;
	float fMax;
	for (v = 0; v <= w; v++)
	{
		x[0][v] = v / dsdv[0].tl;
		f[0][v] = x[0][v] * dsdv[0].gt;
	}
	for (k = 1; k < n; k++)
	{
		for (v = 0; v <= w; v++)
		{
			fMax = f[k - 1][v];
			xMax = 0;
			yk = v / dsdv[k].tl;
			for (xk = 1; xk <= yk; xk++)
			{
				if (f[k - 1][v - xk*dsdv[k].tl] + xk*dsdv[k].gt>fMax)
				{
					fMax = f[k - 1][v - xk*dsdv[k].tl] + xk*dsdv[k].gt;
					xMax = xk;
				}
			}
			f[k][v] = fMax;
			x[k][v] = xMax;

		}
	}
}
void InBang(int n, int w, float f[][max], int x[][max])
{
	int k, v;
	printf("\nBang F va X la:\n");
	for (k = 0; k < n; k++)
	{
		for (v = 0; v <= w; v++)
			printf("%c%4.1f|%2d", 186, f[k][v], x[k][v]);
		printf("%c\n", 186);
	}
}
void TraBang(DoVat *dsdv, int n, int w, int x[][max])
{
	int k, v;
	v = w;
	for (k = n - 1; k >= 0; k--)
	{
		dsdv[k].dchon = x[k][v];
		v = v - x[k][v] * dsdv[k].tl;
	}
}

void main()
{
	int n, w;
	DoVat *dsdv;
	dsdv = DocFile(&w, &n);
	float f[5][10];
	int x[5][10];
	int choose;
	do
	{
		printf("1.Doc thong tin vang tu file\n");
		printf("2.Nhap thong tin vang tu ban phim\n");
		printf("\nChon chuong trinh: ");
		scanf_s("%d", &choose);
		switch (choose)
		{
		case 0:
			exit(1);
			break;
		case 1:
			dsdv = DocFile(&w, &n);
			TaoBang(dsdv, n, w, f, x);
			InBang(n, w, f, x);
			TraBang(dsdv, n, w, x);
			InDSDV(dsdv, n, w);
			free(dsdv);
			break;
		case 2:
			nhapDL(dsdv, w, n);
			TaoBang(dsdv, n, w, f, x);
			InBang(n, w, f, x);
			TraBang(dsdv, n, w, x);
			InDSDV(dsdv, n, w);
			//free(dsdv);
			break;
		default: printf("\nSai! Chon lai.");
			break;
		}
	} while (choose != 0);
	/*nhapDL(dsdv, w, n);
	TaoBang(dsdv, n, w, f, x);
	InBang(n, w, f, x);
	TraBang(dsdv, n, w, x);
	InDSDV(dsdv, n, w);
	free(dsdv);*/
	getch();
}
