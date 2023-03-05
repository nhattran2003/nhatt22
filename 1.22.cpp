#include<stdio.h>
#include<conio.h>
const int minYear = 1900, maxYear = 10000;
struct Ngay
{
       int Day, Month, Year;
};
typedef struct Ngay NGAY;

void NhapNgay(NGAY &);
void XuatNgay(NGAY);

bool KiemTraNamNhuan(NGAY);

int TinhSoThuTuNgayTrongNam(NGAY);
int TinhSoThuTuNgayTuNgayChoTruoc(NGAY);

int TimNgayKhiBietNamVaSoThuTuNgayTrongNam(int, int);
int TimNgayKhiBietSoThuTuNgayChoTruoc(int);

NGAY TimNgayKeTiep(NGAY);
NGAY TimNgayHomQua(NGAY);

NGAY TimNgayKeDoKNgay(NGAY, int);
NGAY TimNgayTruocDoKNgay(NGAY, int);

int TimKhoangCach2Ngay(NGAY);
int SoSanh2Ngay(NGAY);

void TinhThuTrongTuanCua1NgayBatKyTrongNam(NGAY);


bool KiemTraNamNhuan(NGAY a)
{
    return (a.Year % 4 == 0 && a.Year % 100 != 0) || (a.Year % 400 == 0);
}

bool KiemTraNamNhuan(int i)
{
    if (i % 4 == 0 && i % 100!=0)
        return true;
    if (i % 400 == 0)
        return true;
    return false;
}
int TimSoNgayTrongThang(NGAY a)
{
    int NgayTrongThang;
    switch(a.Month)
    {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        NgayTrongThang = 31;
        break;
    case 4: case 6: case 9 : case 11:
        NgayTrongThang = 30;
        break;
    case 2:
        int Check = KiemTraNamNhuan(a);
        if(Check == 1)
        {
            NgayTrongThang = 29;
        }
        else
        {
            NgayTrongThang = 28;
        }
    }
    return NgayTrongThang;
}


void NhapNgay(NGAY &a)
{
    do
    {
        printf("\nNhap vao nam: ");
        scanf("%d", &a.Year);
        if(a.Year < minYear || a.Year > maxYear)
        {
            printf("\nDu lieu nam khong hop le. Xin kiem tra lai!");
        }
    }while(a.Year < minYear || a.Year > maxYear);

    do
    {
        printf("\nNhap vao thang: ");
        scanf("%d", &a.Month);
        if (a.Month < 1 || a.Month > 12)
            printf("\nDu lieu thang khong hop le. Xin kiem tra lai!");
    }while(a.Month < 1 || a.Month > 12);

    int NgayTrongThang = TimSoNgayTrongThang(a);
    do
    {
        printf("\nNhap vao ngay: ");
        scanf("%d",&a.Day);
        if(a.Day < 1 || a.Day > NgayTrongThang)
        {
            printf("\nDu lieu ngay khong hop le. Xin kiem tra lai!");
        }
    }while(a.Day < 1 || a.Day > NgayTrongThang);
}


void XuatNgay(NGAY ng)
{
    printf("%d/%d/%d", ng.Day, ng.Month, ng.Year);
}


int TinhSoThuTuNgayTrongNam(NGAY a)
{
   
    int S = a.Day;
    for(int i = 1; i < a.Month; i++) 
    { 
        switch (i)
        {
            case 4: case 6: case 9 : case 11: S += 30; break;
            case 2: S += (a.Year % 4 == 0 && a.Year % 100 != 0 || a.Year % 400 == 0) ? 29 : 28;
                break;
        default: S += 31;
        }
    }
    return S;
}

int TinhSoThuTuNgayTuNgayChoTruoc(NGAY a)
{
    int stt = 0;
    for(int i = 1; i < a.Year; i++)
    {
        if(KiemTraNamNhuan(i))
        {
            stt += 366;
        }
        else
        {
            stt += 365;
        }
    }
    return stt + TinhSoThuTuNgayTrongNam(a);
}


int TimNgayKhiBietNamVaSoThuTuNgayTrongNam(int Year, int STT)
{
    int n[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (KiemTraNamNhuan(Year))
        n[1] = 29;
    for (int i = 0; i < 12; i++)
    {
        if (n[i] < STT)
            STT -= n[i];
        else
            break;
    }
    return STT;
}


int TimNgayKhiBietSoThuTuNgayChoTruoc(int STT)
{
    int Year = 1;
    while(1)
    {
        if(KiemTraNamNhuan(Year))
        {
            if(STT > 366)
            {
                STT -= 366;
            }
            else
            {
                return TimNgayKhiBietNamVaSoThuTuNgayTrongNam(Year, STT);
            }
        }
        else
        {
            if(STT > 365)
            {
                STT -= 365;
            }
            else
            {
                return TimNgayKhiBietNamVaSoThuTuNgayTrongNam(Year, STT);
            }
        }
        Year++;
    }
    return -1;
}

NGAY TimNgayKeTiep(NGAY a)
{
    int NgayTrongThang = TimSoNgayTrongThang(a);
    if (a.Day < NgayTrongThang)  // Tang ngày lên
    {
        a.Day++;
    }
    else if (a.Month < 12)     // Ngày k? ti?p là d?u tháng
    {
        a.Day = 1; a.Month++;
    }
    else                      // Ngày k? là d?u nam m?i t?c là hi?n tai dang là tháng 12
    {
        a.Day = a.Month = 1;
        a.Year++;
    }
    return a;
}

NGAY TimNgayHomQua(NGAY a)
{
    int NgayTrongThang = TimSoNgayTrongThang(a);
    if(a.Day == 1)            // N?u ngày nh?p vào là 1
    {
        a.Day = NgayTrongThang;        // ngày tru?c dó là s? ngày trong tháng tru?c 
        if(a.Month == 1)            // N?u tháng là 1
        {
            a.Month = 12;
            a.Year--;
        }
        else                     // Tháng khác 1
            a.Month--;
    }
    else                // Ngày khác 1
        a.Day--;
    return a;
}

NGAY TimNgayKeDoKNgay(NGAY a, int k)
{
    while(k > 0)
    {
        a = TimNgayKeTiep(a);
        k--;
    }
    return a;
}

NGAY TimNgayTruocDoKNgay(NGAY a, int k)
{
    while(k>0)
    {
        a = TimNgayHomQua(a);
        k--;
    }
    return a;
}

int TimKhoangCach2Ngay(NGAY a, NGAY b)
{
    int STTa = TinhSoThuTuNgayTrongNam(a);
    int STTb = TinhSoThuTuNgayTrongNam(b);

    if(STTa > STTb)
    {
        return STTa - STTb;
    }
    return STTb - STTa;
}



int SoSanh2Ngay(NGAY a, NGAY b)
{
    int STTa = TinhSoThuTuNgayTrongNam(a);
    int STTb = TinhSoThuTuNgayTrongNam(b);

    if(STTa > STTb)
    {
        return 1;
    }
    if(STTb > STTa)
    {
        return 0;
    }
    return -1;
}


void TinhThuTrongTuanCua1NgayBatKyTrongNam(NGAY a)
{
    
    a.Year -= (14 - a.Month) / 12;
    a.Month += 12 * ((14 - a.Month) / 12) - 2;

    int dayofweek = (a.Day + a.Year + a.Year / 4 - a.Year / 100 + a.Year / 400 + (31 * a.Month)/12) % 7;

    if(!dayofweek)
        printf("\nChu nhat");
    else 
        printf("\nThu %d", dayofweek + 1);
}

int main()
{
    NGAY a;
    NhapNgay(a);
    XuatNgay(a);

    if(KiemTraNamNhuan(a))
    {
        printf("\nNam %d la nam nhuan", a.Year);
    }
    else
    {
        printf("\nNam %d la nam thuong", a.Year);
    }

    int STTNgay = TinhSoThuTuNgayTrongNam(a);
    printf("\nNgay thu %d trong nam", STTNgay);

    int STT = TinhSoThuTuNgayTuNgayChoTruoc(a);
    printf("\nNgay thu %d trong nam tu ngay 1/1/1", STT);

    int Ngay = TimNgayKhiBietNamVaSoThuTuNgayTrongNam(2015, 365);
    printf("\nNgay thu %d trong nam %d la ngay %d", 365, 2015, Ngay);

    NGAY c = TimNgayKeTiep(a);
    printf("\nNgay ke tiep la ngay %d/%d/%d", c.Day, c.Month, c.Year);

    NGAY d = TimNgayHomQua(a);
    printf("\nNgay hom qua la ngay %d/%d/%d", d.Day, d.Month, d.Year);

    printf("\nNgay ke tiep 5 ngay: ");
    XuatNgay(TimNgayKeDoKNgay(a, 5));
    printf("\nNgay hom truoc 5 ngay: ");
    XuatNgay(TimNgayTruocDoKNgay(a, 5));

    TinhThuTrongTuanCua1NgayBatKyTrongNam(a);
    getch();
    return 0;
}