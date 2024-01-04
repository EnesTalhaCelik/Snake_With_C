#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#define WIDTH 30            //ekran genisligini ayarlamak icin degistirebilirsiniz
#define HEIGHT 10

//Enes Talha Celik
//31 / 05 / 23


void yilan_hareket(int yilan[][2], int durum, int yilan_uzunluk){


    for (int i = yilan_uzunluk - 1 ; 0 < i; i-- ){
        for(int k = 0 ; k < 2 ; k++){
            yilan[i][k]= yilan[i-1][k];
        }
    }

if (durum == 8){
    yilan[0][1] = yilan[0][1] - 1;
}
else if (durum == 6){
    yilan[0][0] = yilan[0][0] + 1;
}
else if (durum == 4){
    yilan[0][0] = yilan[0][0] - 1;
}
else{
    yilan[0][1] = yilan[0][1] + 1;
}

}



/*void yilan_can_kontrol(int yilan[][2],int oyun_durumu,int yilan_uzunluk){
    for (int i = 1; i < yilan_uzunluk; i++){

        if( yilan[0][0]==yilan[i][0]&& yilan[0][0]==yilan[i][0]){
            oyun_durumu = 0;
        }



    }
}
*/

int main()
{

srand(time(NULL));              // kullandigimiz rand fonksiyonuna seed ayarlamasi için gerekli
 SMALL_RECT windowSize = {0 , 0 , WIDTH + 10 , HEIGHT + 5}; // ekan buyuklugu ayarlama
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);


int durum = 6 ;          //yilanýn hareket yönü numpad numaralarýnýn yönlerine göre belirlendi 6 sað 8 üst 4 sol 2 alt ismini deðiþtir

int yilan_uzunluk = 5;                                                      // yilanin uzunlugu
int yilan[WIDTH*HEIGHT][2] = {{15,4},{14,4},{13,4},{12,4},{11,4}};          //yilan kordinatlari
int yemek[1][2] = {};                                                       //yemek kordinat
int basildi = 0;                                                            // yilani ekrana gösterirken kullanilan degisken
//int y, i;
int oyun_durumu = 1; //oyun devam ediyor mu
unsigned char tus;          //yilani hareket ettirmek icin kullandigimiz degisken
int yemek_mevcut = 0;        // haritada yemek var mi
while(oyun_durumu){

printf("\e[?25l");


if(kbhit()){        //bir tuş basilinca aktifles
    tus=getch();
            if(tus==224)
            {
                tus=getch();
                switch(tus)
                {
                    case 72:            //yon tuslari kontrol
                        if(durum != 2)
                        durum =8;
                        break;
                    case 80:
                        if(durum != 8)
                        durum = 2;
                        break;
                    case 77:
                        if(durum != 4)
                        durum =6;
                        break;
                    case 75:
                        if(durum != 6)
                        durum = 4;

                }
            }
        }

system("cls");                                 //yilanin hareket ediyor gibi görünmesi icin her hareketinde yeni kare olusturuyoruz
                                                // daha sonra ekrani temizleyip tekrar ediyoruz

if(yemek_mevcut == 0 ){
    yemek[0][0] = (rand() %(WIDTH-2)) + 2;    //oyun sınırlarından dolayı +2 yaptik
    yemek[0][1] = (rand() %(HEIGHT-2)) + 2;
yemek_mevcut = 1;
}




yilan_hareket( yilan, durum, yilan_uzunluk);            //yilani hareket ettiren fonksiyon


  for (int i = 1; i < yilan_uzunluk; i++){                              //yilan kendi kuyrugunu isirmis mi kontrol ediyoruz
        if( yilan[0][0]==yilan[i][0] && yilan[0][1]==yilan[i][1]){
            oyun_durumu = 0;

  }


if (yilan[0][0]== 1){
    yilan[0][0] = WIDTH - 1;

}
else if (yilan[0][0]== WIDTH){
    yilan[0][0] = 2;

}
else if (yilan[0][1]== 1){
    yilan[0][1] = HEIGHT - 1;
}
else if(yilan[0][1]== HEIGHT){
     yilan[0][1] = 2;
}

}


if(yilan[0][0]== yemek[0][0] && yilan[0][1]== yemek[0][1]){             //yilan yemegi yemis mi kontrol ediyoruz

    yilan[yilan_uzunluk][0] = yilan[yilan_uzunluk - 1][0] -1;
    yilan[yilan_uzunluk][1] = yilan[yilan_uzunluk - 1][1] ;
    yemek_mevcut = 0;
    yilan_uzunluk++;
}

                                    //ekran yenileme fonksiyonu
for (int y = 1; y < HEIGHT + 1 ; y++){
    for (int x = 1; x < WIDTH + 1; x++){
    for (int i = 0; i < yilan_uzunluk; i++){

        if (yilan[i][0]==x && yilan[i][1]== y){
            printf("%c",219);
            basildi = 1;
            break;
            }
    }

    if (basildi == 1){
        basildi = 0;
        continue;
    }
    else if (yemek[0][0] == x && yemek[0][1] == y){
        printf("O");
    }
    else if (x==1 || y == 1 || x == WIDTH || y == HEIGHT){
        printf("%c",176);
    }
    else{printf(" ");

    }


}

printf("\n");               //ekran yenileme fonksiyonu bitiş.
}


printf("\n score: %d",yilan_uzunluk - 5 );
Sleep(20);
}
Sleep(50);

printf("\n Oyun bitti.");

sleep(2);

return 0;
}
