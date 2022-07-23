//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"

#include "mtrand.hpp"

MTRand *rnd;

// Размер сети Nx и Ny
#define SZ_X 533
#define SZ_Y 333

// Выходное значение логического оператора
char net[SZ_Y][SZ_X];

// Прошлое значение логического оператора
char onet[SZ_Y][SZ_X];

// Левый и правый троичные входы
char tnetL[SZ_Y][SZ_X];
char tnetR[SZ_Y][SZ_X];

// Координаты L и N - позиция в бесконечном регистре
int  posL[SZ_Y][SZ_X];
int  posN[SZ_Y][SZ_X];

bool pause=0;

Graphics::TBitmap *bmp;

// Обработка троичного логического оператора

int LogicOp(int L, int R, int i, int j)
{
  char C=onet[i][j], tmp;

  if (C==0 && L==R)
  {
	tnetL[i][j]=L; tnetR[i][j]=R;

	onet[i][j]=R;

	return R;
  }
  if (C==0)
  {
	tnetL[i][j]=L; tnetR[i][j]=R;

	// Увеличение позиции в бесконечном регистре

	posN[i][j]++;

	if (posN[i][j]>=posL[i][j])
	{
	  posN[i][j]=0;
	  posL[i][j]++;
	}

	// Чтение бита из бесконечного регистра

	tmp=posL[i][j]%2;

	onet[i][j]=tmp;

	return tmp;
  }

  if (C==1 && L==R)
  {
	if (R==0)
	{
	  tnetL[i][j]=2; tnetR[i][j]=0;
	}
	else
	{
	  tnetL[i][j]=0; tnetR[i][j]=2;
	}

	onet[i][j]=1;

	return 1;
  }

  if (R==0)
  {
	tnetL[i][j]=2; tnetR[i][j]=1;
  }
  else
  {
	tnetL[i][j]=1; tnetR[i][j]=2;
  }

  onet[i][j]=0;

  return 0;
}

// Инициализация универсальной вычислительной сети

void InitNet()
{
  for (int i=0;i<SZ_Y;i++)
  {
	for (int j=0;j<SZ_X;j++)
	{
	  net[i][j]=0;

	  tnetR[i][j]=0;
	  tnetL[i][j]=0;

	  onet[i][j]=0;

	  posL[i][j]=1;
	  posN[i][j]=0;
	}
  }
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
  // Инициализация генератора случайных чисел и графики

  rnd = new MTRand();

  bmp = new Graphics::TBitmap();

  bmp->Width=SZ_X;

  bmp->Height=SZ_Y;

  bmp->PixelFormat = pf24bit;

  DoubleBuffered=1;

  InitNet();
}

//---------------------------------------------------------------------------

void __fastcall TForm1::FormDestroy(TObject *Sender)
{
  delete rnd, bmp;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
  bool usernd=CheckBox1->Checked;

  int speed=2+18*CheckBox2->Checked;

  if (!pause)
  {
	for (int z=0;z<speed;z++)
	{
	  if (usernd==1)
	  {
		for (int j=0;j<SZ_X;j++)
		{
		  // Подача случайных сигналов на входы сети

		  net[0][j]=rnd->randInt()%2;
		}
	  }

	  // Обработка сигналов универсальной вычислительной сети

	  for (int i=0;i<SZ_Y-1;i++)
	  {
		for (int j=0;j<SZ_X;j++)
		{
		  net[i+1][j]=LogicOp(net[i][j],net[i][(j+1)%SZ_X],i,j);
		}
	  }

	  // Обработка обратных связей

	  for (int j=0;j<SZ_X;j++)
	  {
		net[0][(j+SZ_Y/2)%SZ_X]=LogicOp(net[SZ_Y-1][j],net[SZ_Y-1][(j+1)%SZ_X],SZ_Y-1,j);
	  }

	}
  }

  Repaint();
}

//---------------------------------------------------------------------------

void __fastcall TForm1::FormPaint(TObject *Sender)
{
  // Отрисовка универсальной вычислительной сети

  int ps;

  for (int i=0;i<SZ_Y;i++)
  {
	unsigned char *b=(unsigned char*)bmp->ScanLine[i];

	unsigned char cl, cm;

	for (int j=0;j<SZ_X;j++)
	{
	  ps = (j+i/2)%SZ_X;

	  if (tnetR[i][j]==2)
	  {
		b[ps*3+0]=127+128*tnetL[i][j];
		b[ps*3+1]=0;
		b[ps*3+2]=0;
	  }
	  else
	  if (tnetL[i][j]==2)
	  {
		b[ps*3+0]=0;
		b[ps*3+1]=0;
		b[ps*3+2]=127+128*tnetR[i][j];
	  }
	  else
	  {
		cl=85*(tnetL[i][j]+2*tnetR[i][j]);

		b[ps*3+0]=cl;
		b[ps*3+1]=cl;
		b[ps*3+2]=cl;
	  }
	}
  }

  TRect r;

  r.top=PaintBox1->Top;

  r.left=PaintBox1->Left;

  r.bottom=PaintBox1->Top+PaintBox1->Height;

  r.right=PaintBox1->Left+PaintBox1->Width;

  Canvas->Pen->Color=clRed;

  Canvas->Rectangle(r.left-1,r.top-1,r.right+1,r.bottom+1);

  Canvas->StretchDraw(r,bmp);
}

//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
  pause^=1;

  if (pause==1)
	Button1->Caption="Запуск...";
  else
	Button1->Caption="Пауза";

}
//---------------------------------------------------------------------------

void __fastcall TForm1::PaintBox1Click(TObject *Sender)
{
/*  double x=SZ_X;

  x/=(double)(PaintBox1->Width);

  TPoint pt = PaintBox1->ScreenToClient(Mouse->CursorPos);

  x*=(double)(pt.X);

  int ps=x;
*/
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
  InitNet();

  Repaint();
}
//---------------------------------------------------------------------------

