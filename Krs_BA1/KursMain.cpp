//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "KursMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include<stdlib.h>
#include<math.h>
#include<stdio.h>
TForm1 *Form1;
int SizeN = 9,SizeM = 9;
bool setset  = false, setrnd =false;
double H[81][81], hx, hy;
int pt[81][81][2];

//---------------------------------------

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
setset  = false; setrnd =false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    SizeN = StrToInt(Edit1->Text);
    SizeM = StrToInt(Edit2->Text);
    StringGrid1->RowCount = SizeM + 1;
    StringGrid1->ColCount = SizeN + 1;
    setset  = true;
    setrnd = false;


}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
int n,m,i,j,r,y;
  n  =   SizeN;
  m  =   SizeM;
randomize();
 double f;
 for(i = 0; i<n; i++)
        for(j = 0; j<m; j++) {
             r = rand()%100; y = rand()%100;

        f  = (double) (r+3)/(1 + y);
        if( f>3 )  f =  (double)(3 + y )/(r+1);
           StringGrid1->Cells[i+1][j+1] = FloatToStr(f);
        }
     setrnd = true;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button5Click(TObject *Sender)
{
 if(setset==false)   Button1Click(Sender);
 if(setrnd==false)   Button4Click(Sender);
double al,koef;
    al = StrToFloat(Edit5->Text);  al = al*M_PI/180;
    hx = StrToFloat(Edit3->Text);
    hy = StrToFloat(Edit4->Text);
    koef = StrToFloat(Edit6->Text);

  int n,m,i,j,r,y;
  n  =   SizeN;
  m  =   SizeM;
  for(i = 0; i<n; i++)
        for(j = 0; j<m; j++) {
        H[i][j] =  StrToFloat(StringGrid1->Cells[i+1][j+1]);
        }

  int cx, cy;
  cx = 50;
  cy = 400;
  //   osnova
    for(i = 0; i<n; i++)
        for(j = 0; j<m; j++) {
          pt[i][j][0] = cx + koef* ( hx*j +  hx*j * cos(al) +   hy * i *sin(al) );
          pt[i][j][1] = cy - koef*( /*H[i][j] + */ hy*i * sin(al) /*+  hy * j *cos(al)*/) ;

        }

 Image1->Canvas->Rectangle(0,0,Image1->Width, Image1->Height);
 //Image1->Canvas->Ellipse(pt[0][0][0]-3,pt[0][0][1]-3,pt[0][0][0]+3,pt[0][0][1]+3);
 Image1->Canvas->Pen->Color = clGray;
     for(i = 0; i<n; i++) {
                 Image1->Canvas->MoveTo(pt[i][0][0],pt[i][0][1]);
             for(j = 1; j<m; j++) {
                 Image1->Canvas->LineTo(pt[i][j][0],pt[i][j][1]);
             }
       }

// Image1->Canvas->Pen->Color = clGreen;
     for(j = 0; j<m; j++) {
                 Image1->Canvas->MoveTo(pt[0][j][0],pt[0][j][1]);
             for(i = 1; i<n; i++) {
                 Image1->Canvas->LineTo(pt[i][j][0],pt[i][j][1]);
             }
       }

  // karkas
       for(i = 0; i<n; i++)
        for(j = 0; j<m; j++) {
          pt[i][j][0] = cx + koef* ( hx*j +  hx*j * cos(al) +   hy * i *sin(al) );
          pt[i][j][1] = cy - koef*( H[i][j] +  hy*i * sin(al) /*+  hy * j *cos(al)*/) ;

        }

 //Image1->Canvas->Rectangle(0,0,Image1->Width, Image1->Height);
 //Image1->Canvas->Ellipse(pt[0][0][0]-3,pt[0][0][1]-3,pt[0][0][0]+3,pt[0][0][1]+3);
 Image1->Canvas->Pen->Color = clGreen;
     for(i = 0; i<n; i++) {
                 Image1->Canvas->MoveTo(pt[i][0][0],pt[i][0][1]);
             for(j = 1; j<m; j++) {
                 Image1->Canvas->LineTo(pt[i][j][0],pt[i][j][1]);
             }
       }

 Image1->Canvas->Pen->Color = clBlue;
     for(j = 0; j<m; j++) {
                 Image1->Canvas->MoveTo(pt[0][j][0],pt[0][j][1]);
             for(i = 1; i<n; i++) {
                 Image1->Canvas->LineTo(pt[i][j][0],pt[i][j][1]);
             }
       }



}
//---------------------------------------------------------------------------
inline double cube(double x) { return x*x*x; }
inline double sqr(double x) { return x*x; }
void BSL(double h, double p0, double p1, double p2, double p3, int num, double Rez[])
{
int i;
double ch,t;

        ch = 1./num;  t=0;
 for(i=0;i<num;i++) {
        Rez[i] =  cube(1-t)*p0 + 3*t*sqr(1-t) *p1
                   + 3*sqr(t)*(1-t)*p2 + cube(t) *p3;
                   t+=ch;
          }

 }
//---------------------------------------------------------------------------
void __fastcall TForm1::Button6Click(TObject *Sender)
{
 if(setset==false)   Button1Click(Sender);
 if(setrnd==false)   Button4Click(Sender);
int ptx[81][27][27][2];
int pty[27][81][27][2];
double al,koef;
    al = StrToFloat(Edit5->Text);  al = al*M_PI/180;
    hx = StrToFloat(Edit3->Text);
    hy = StrToFloat(Edit4->Text);
    koef = StrToFloat(Edit6->Text);

  int n,m,i,j,r,y;
  n  =   SizeN;
  m  =   SizeM;
  for(i = 0; i<n; i++)
        for(j = 0; j<n; j++) {
        H[i][j] =  StrToFloat(StringGrid1->Cells[i+1][j+1]);
        }

  int cx, cy;
  cx = 50;
  cy = 400;

   // karkas
       int j0,l;
       double hxj;
       int num;
       num = 18;
       double Rez[27];
       for(i = 0; i<n; i++)
        for(j = 0; j<m; j+=3) {
            if(j==0) j0=0; else j0=j-1;
           BSL(hx, H[i][j0], H[i][j], H[i][j+1], H[i][j+2],num,Rez);
           for (l=0; l<num;l++) {
          hxj = hx*j + 3.0*l/num;
          ptx[i][j/3][l][0] = cx + koef* ( hxj +  hxj * cos(al) +   hy * i *sin(al) );
          ptx[i][j/3][l][1] = cy - koef*( Rez[l] +  hy*i * sin(al) ) ;
           }
        }

 Image1->Canvas->Rectangle(0,0,Image1->Width, Image1->Height);

 Image1->Canvas->Pen->Color = clGreen;
     for(i = 0; i<n; i++) {
                 Image1->Canvas->MoveTo(ptx[i][0][0][0],ptx[i][0][0][1]);
             for(j = 0; j<m; j+=3) {
                   if (j*3 <= m)
                  for (l=0; l<num;l++)
                 Image1->Canvas->LineTo(ptx[i][j/3][l][0],ptx[i][j/3][l][1]);
                else for (l=0; l<=(num - num/3);l++)
                 Image1->Canvas->LineTo(ptx[i][j/3][l][0],ptx[i][j/3][l][1]);
             }
       }

       int i0;  double hyi;
        for(j = 0; j<m; j++)
         for(i = 0; i<n; i+=3)
            {
            if(i==0) i0=0; else j0=j-1;
           BSL(hy, H[i0][j], H[i][j], H[i+1][j], H[i+2][j],num,Rez);
           for (l=0; l<num;l++) {
          hyi = hy*i + 3.0*l/num;
          pty[i/3][j][l][0] = cx + koef* ( hx*j +  hx*j * cos(al) +   hyi *sin(al) );
          pty[i/3][j][l][1] = cy - koef*( Rez[l] +  hyi * sin(al) ) ;
           }
        }


 Image1->Canvas->Pen->Color = clBlue;
             for(j = 0; j<m; j++) {
                      Image1->Canvas->MoveTo(pty[0][j][0][0],pty[0][j][0][1]);
                   for(i = 0; i<n; i+=3) {
                   if (i*3 <= n)
                  for (l=0; l<num;l++)
                 Image1->Canvas->LineTo(pty[i/3][j][l][0],pty[i/3][j][l][1]);
                else for (l=0; l<=(num - num/3);l++)
                 Image1->Canvas->LineTo(pty[i/3][j][l][0],pty[i/3][j][l][1]);
             }
       }


       // karkas
       for(i = 0; i<n; i++)
        for(j = 0; j<m; j++) {
          pt[i][j][0] = cx + koef* ( hx*j +  hx*j * cos(al) +   hy * i *sin(al) );
          pt[i][j][1] = cy - koef*( 0 +  hy*i * sin(al) /*+  hy * j *cos(al)*/) ;

        }


 Image1->Canvas->Pen->Color = clGray;
     for(i = 0; i<n; i++) {
                 Image1->Canvas->MoveTo(pt[i][0][0],pt[i][0][1]);
             for(j = 1; j<m; j++) {
                 Image1->Canvas->LineTo(pt[i][j][0],pt[i][j][1]);
             }
       }
         for(j = 0; j<m; j++) {
                 Image1->Canvas->MoveTo(pt[0][j][0],pt[0][j][1]);
             for(i = 1; i<n; i++) {
                 Image1->Canvas->LineTo(pt[i][j][0],pt[i][j][1]);
             }
       }

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
   SaveDialog1->Execute();
   AnsiString filename;
   filename=SaveDialog1->FileName;
   double d;
   if(filename!="")
   {
   FILE *fp;
   fp = fopen(filename.c_str(),"w");
   if (fp==NULL) return;
   fprintf(fp,"%d %d\n", SizeN ,SizeM);
   for(int i =0; i< SizeN; i++)
   {
    for(int j =0; j< SizeM; j++)
     {
     d = StrToFloat(StringGrid1->Cells[i+1][j+1]);
     fprintf(fp, "%f ", d);
     }
    fprintf(fp, "\n");
   }
    fclose(fp);
   }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
     OpenDialog1->Execute();
   AnsiString filename;
   filename=OpenDialog1->FileName;
   double d;
   if(filename!="")
   {
   FILE *fp;
   fp = fopen(filename.c_str(),"r");
   if (fp==NULL) return;
   fscanf(fp,"%d %d\n", &SizeN ,&SizeM);
    Edit1->Text = IntToStr(SizeN);
    Edit2->Text = IntToStr(SizeM);
    StringGrid1->RowCount = SizeM + 1;
    StringGrid1->ColCount = SizeN + 1;
   for(int i =0; i< SizeN; i++)
   {
    for(int j =0; j< SizeM; j++)
     {
     fscanf(fp, "%lf", &d);
     StringGrid1->Cells[i+1][j+1] = FloatToStr(d);
     }
   
   }
    fclose(fp);
   }
   setset  = true;
    setrnd = true;
}
//---------------------------------------------------------------------------

