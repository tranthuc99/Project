/*
 *  Name: Bài tập lớn ktlt MI3310 - 116444
 *  Author: Nhóm 10 - Nguyễn Trần Thức & Đoàn Quốc Vĩnh
 *  Date: 07/06/20 00:26
 *  Description: Giải gần đúng hệ phương trình,
        bằng phương pháp lặp đơn và lặp Seidel.
        Input ma trận hệ số là ma trận chéo trội
 */
//  ---------------- Khai báo thư viện hàm ----------------

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

//  ---------------- Khai báo biến toàn cục ---------------

#define fileInput   "In-Out/Data.txt"
#define fileOutput  "In-Out/Output.txt"
#define MAX         100             // Số vòng lặp tối đa
#define MAX_LIST    10              // Số lựa chọn trong menu

//  --------------- Khai báo nguyên mẫu hàm ---------------

void    SetConsoleColour    (WORD* Attributes, DWORD Colour);
void    ResetConsoleColour  (WORD Attributes);
void    NhapMaTranTuFile    (double a[][MAX], int &n);
void    NhapMaTranTuBP      (double a[][MAX], int &n);
void    XuatMaTran          (double a[][MAX], int n, int stp);
void    KiemTraCheoTroi     (double a[][MAX], int n);
double  ChuanMaTran_Row     (double a[][MAX], int n);
void    BienDoiMaTran       (double a[][MAX], int n);
void    phuongPhapLapDonk   (double a[][MAX], double result[][MAX], int n, int k);
void    phuongPhapSeidelk   (double a[][MAX], double result[][MAX], int n, int k);
void    printResult         (double a[][MAX], int n, int k, int stp);
void    SaiSo               (double a[][MAX], double result[][MAX], int n, int k, int stp);
double  nghiemGanDung       (double a[][MAX], double result[][MAX], int n, double e);
void    nDecimals           (char *s, double d, int n);

//  ---------------------- Hàm chính ----------------------

int main()
{
    int     n, k, u, stp;
    int     pointer = 0,
            flag = 1;
    bool    daNhap = false;
    double  a[MAX][MAX],
            result[MAX][MAX],
            result2[MAX][MAX];
    double  chuan, e2, h;
    WORD    Attributes = 0;
    FILE    *fileOut;

    char x1[] = " Nhap so bac cua he phuong trinh                    ||";
    char x2[] = " Nhap vao ma tran A,b tu ban phim                   ||";
    char x3[] = " Nhap vao ma tran A,b tu file                       ||";
    char x4[] = " Kiem tra tinh cheo troi cua ma tran A              ||";
    char x5[] = " Chuyen hpt ve dang Ix = Tx + c                     ||";
    char x6[] = " Tinh chuan cua ma tran T, kiem tra su hoi tu       ||";
    char x7[] = " Tinh nghiem gan dung voi so lan lap k, sai so      ||";
    char x8[] = " Tinh nghiem gan dung voi sai so e                  ||";
    char x9[] = " Tinh nghiem gan dung thoa man dieu kien            ||";
    char x0[] = " Thoat chuong trinh                                 ||";

    char* menu[] = {x1, x2, x3, x4, x5, x6, x7, x8, x9, x0};

    while (1) {
        system ("cls");
        system ("color 3");
        printf ("\n");
        printf ("\t*============================================================*\n");
        printf ("\t||**                                                      **||\n");
        printf ("\t||*        CHUONG TRINH GIAI HE PHUONG TRINH Ax=b          *||\n");
        printf ("\t||            Phuong phap lap don & lap Seidel              ||\n");
        printf ("\t||__________________________________________________________||\n");
        printf ("\t||               MENU DIEU KHIEN CHUONG TRINH               ||\n");
        printf ("\t||__________________________________________________________||");
        for (int i = 0; i < MAX_LIST; i++) {
            if (pointer == i) {
                SetConsoleColour (&Attributes, BACKGROUND_INTENSITY | BACKGROUND_BLUE);
                printf("\n\t||    ");
                printf ("%c%c%s", 175, 175, menu[i]);
                ResetConsoleColour (Attributes);
            } else {
                printf("\n\t||      ");
                printf ("%s", menu[i]);
            }
        }
        printf ("\n\t||__________________________________________________________||");
        printf ("\n\t||*        Coding by Nhom 10 - KTLT MI3310 - 116444        *||");
        printf ("\n\t||**           Nguyen Tran Thuc & Doan Quoc Vinh          **||");
        printf ("\n\t*============================================================*\n");

        // Bắt sự kiện từ bàn phím để điều khiển menu
        while (1) {
            if (kbhit()) {
                char key = getch();
                if (key == 72) {
                    if (pointer > 0)
                        -- pointer;
                    else
                        pointer = MAX_LIST - 1;
                    break;
                }
                if (key == 80) {
                    if (pointer < MAX_LIST - 1)
                        ++ pointer;
                    else
                        pointer = 0;
                    break;
                }
                if (key == 13) {
                    switch (pointer) {
                    case 0:
                        do {
                            printf ("\n\t----------------------------------------\n");
                            printf ("\t*Nhap so bac cua he phuong trinh: ");
                            scanf ("%d", &n);
                            if (n < 1 || n > MAX)
                                printf ("\n\tSo bac khong hop le. Xin kiem tra lai !");
                        } while (n < 1 || n > MAX);
                        printf ("\n\tBan da nhap thanh cong!");
                        daNhap = true;
                        printf ("\n\n...Bam phim bat ky de tiep tuc!...");
                        getch();
                        break;
                    case 1:
                        if (daNhap) {
                            printf ("\n\t*Nhap vao ma tran A,b tu ban phim:\n");
                        } else {
                            printf ("\nNhap so bac cua he phuong trinh truoc !!!");
                            getch();
                            break;
                        }
                        printf ("\t----------------------------------------------------------\n");
                        NhapMaTranTuBP (a,n);
                        printf ("\n\tNhap so chu so thap phan: ");
                        scanf ("%d", &stp);
                        printf ("\n\tMa tran [A | b] :\n");
                        printf ("\t---------------\n");
                        XuatMaTran (a, n, stp);
                        printf ("\t----------------------------------------------------------\n");
                        printf ("\n\n...Bam phim bat ky de tiep tuc!...");
                        getch();
                        break;

                    case 2:
                        if (daNhap) {
                            printf ("\n\t*Nhap vao ma tran A,b tu: %s :\n", fileInput);
                        } else {
                            printf ("\nNhap so bac cua he phuong trinh truoc !!!");
                            getch();
                            break;
                        }
                        printf ("\n\tNhap so chu so thap phan: ");
                        scanf ("%d", &stp);
                        printf ("\t----------------------------------------------------------\n");
                        printf ("\tMa tran [A | b] :\n");
                        printf ("\t---------------\n");
                        NhapMaTranTuFile (a,n);
                        XuatMaTran (a,n, stp);
                        printf ("\t----------------------------------------------------------\n");
                        printf ("\n\n...Bam phim bat ky de tiep tuc!...");
                        getch();
                        break;

                    case 3:
                        if (daNhap) {
                            printf ("\n\t*Kiem tra tinh cheo troi cua ma tran A:\n");
                        } else {
                            printf ("\nNhap so bac cua he phuong trinh & nhap ma tran A,b truoc !!!");
                            getch();
                            break;
                        }
                        printf ("\t----------------------------------------------------------\n");
                        KiemTraCheoTroi (a,n);
                        printf ("\t----------------------------------------------------------\n");
                        printf ("\n\n...Bam phim bat ky de tiep tuc!...");
                        getch();
                        break;

                    case 4:
                        if (daNhap) {
                            printf ("\n\t*Chuyen hpt ve dang Ix = Tx + c\n");
                        } else {
                            printf ("\nNhap so bac cua he phuong trinh & nhap ma tran A,b truoc !!!");
                            getch();
                            break;
                        }
                        printf ("\n\tNhap so chu so thap phan: ");
                        scanf ("%d", &stp);
                        printf ("\t----------------------------------------------------------\n");
                        printf ("\tMa tran [T | c] :\n");
                        printf ("\t---------------\n");
                        BienDoiMaTran (a,n);
                        XuatMaTran (a,n, stp);
                        printf ("\t----------------------------------------------------------\n");
                        printf ("\n\n...Bam phim bat ky de tiep tuc!...");
                        getch();
                        break;

                    case 5:
                        if (daNhap) {
                            printf ("\n\t*Tinh chuan cua ma tran T, kiem tra su hoi tu:\n");
                        } else {
                            printf ("\nNhap so bac cua he phuong trinh & nhap ma tran A,b truoc !!!");
                            getch();
                            break;
                        }
                        printf ("\t----------------------------------------------------------\n");
                        printf ("\tChuan cua ma tran T la:  ");
                        chuan = ChuanMaTran_Row (a,n);
                        printf ("||T|| = %.2lf\n", chuan);
                        if (chuan < 1 && chuan > 0)
                            printf ("\n\t=> ||T|| < 1 => Nghiem cua he phuong trinh hoi tu toi X*\n");
                        else if (chuan == 0)
                            printf("\n\tKhong ton tai he phuong trinh!\n");
                        else
                            printf ("\n\t=> ||T|| > 1 => Nghiem cua hpt khong hoi tu toi X*\n");
                        printf ("\t----------------------------------------------------------\n");
                        printf ("\n\n...Bam phim bat ky de tiep tuc!...");
                        getch();
                        break;

                    case 6:
                        if (daNhap) {
                            printf ("\n\t*Tinh nghiem gan dung voi so lan lap k, sai so:\n");
                        } else {
                            printf ("\nNhap so bac cua he phuong trinh & nhap ma tran A,b truoc !!!");
                            getch();
                            break;
                        }
                        printf ("\n\t-Nhap so lan lap k = ");
                        scanf ("%d", &k);

                        printf ("\n\t-Nhap so chu so thap phan: ");
                        scanf ("%d", &stp);

                        printf ("\n\t* Phuong phap lap don");
                        phuongPhapLapDonk (a, result, n, k);
                        fileOut = fopen (fileOutput, "a");
                        fprintf (fileOut, "\n\t-Phương pháp lặp đơn:\n");
                        fclose (fileOut);
                        printResult (result, n, k, stp);
                        SaiSo (a, result, n, k, stp);

                        printf ("\n\t* Phuong phap lap Seidel");
                        phuongPhapSeidelk (a, result2, n, k);
                        fileOut = fopen (fileOutput, "a");
                        fprintf (fileOut, "\n\t-Phương pháp lặp Seidel:\n");
                        fclose (fileOut);
                        printResult (result2, n, k, stp);
                        SaiSo (a, result2, n, k, stp);

                        printf ("\n\n...Bam phim bat ky de tiep tuc!...");
                        getch();
                        break;

                    case 7:
                        if (daNhap) {
                            printf ("\n\t*Tinh nghiem gan dung voi sai so e:\n");
                        } else {
                            printf ("\nNhap so bac cua he phuong trinh & nhap ma tran A,b truoc !!!");
                            getch();
                            break;
                        }
                        printf ("\t-Nhap sai so: e = ");
                        scanf ("%lf", &e2);
                        h = nghiemGanDung (a, result, n, e2);
                        phuongPhapLapDonk (a, result, n, h);
                        u = nghiemGanDung (a, result2, n, e2);
                        phuongPhapSeidelk (a, result2, n, u);
                        printf ("\n\t-Nhap so thap phan: ");
                        scanf ("%d", &stp);
                        printResult (result, n, h, stp);
                        printResult (result2, n, u, stp);
                        printf ("\n...Bam phim bat ky de tiep tuc!...");
                        getch();
                        break;

                    case 8:
                        if (daNhap) {
                            printf ("\nTinh nghiem gan dung thoa man dieu kien:");
                        } else {
                            printf ("\nNhap so bac cua he phuong trinh & nhap ma tran A,b truoc !!!");
                            getch();
                            break;
                        }
                        printf ("\n...Bam phim bat ky de tiep tuc!...");
                        getch();
                        break;

                    case 9:
                        printf ("\nBan da chon thoat chuong trinh\n\n");
                        flag = -1;
                        break;
                    default:
                        printf ("error!!"); 
                    }
                    break;
                }
            }
        }
        if (flag == -1)
        break;
    }
}// End Main

//  ----------------- Cài đặt các hàm con -----------------

void SetConsoleColour (WORD* Attributes, DWORD Colour)
{
    CONSOLE_SCREEN_BUFFER_INFO Info;
    HANDLE hStdout = GetStdHandle (STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo (hStdout, &Info);
    *Attributes = Info.wAttributes;
    SetConsoleTextAttribute (hStdout, Colour);
}

void ResetConsoleColour (WORD Attributes)
{
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), Attributes);
}


void NhapMaTranTuFile (double a[][MAX], int &n)
{
    FILE *FileIn;
    FileIn = fopen (fileInput , "r");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n+1; j++) {
            fscanf (FileIn, "%lf", &a[i][j]);
        }
    }
    fclose (FileIn);
}

void NhapMaTranTuBP (double a[][MAX], int &n)
{
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("\ta[%d][%d] = ", i, j);
            scanf ("%lf", &a[i][j]);

        }
    }
    for (int i = 1; i <= n; i++) {
        printf("\tb[%d]    = ", i);
        scanf ("%lf", &a[i][n+1]);
    }
}

//  Hàm xuất ma trận
void XuatMaTran (double a[][MAX], int n, int stp)
{
    char str[50];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n+1; j++) {
            nDecimals (str, a[i][j], stp);
            printf ("\t\t%s", str);
        }
        printf ("\n\n");
    }
}


void printResult (double a[][MAX], int n, int k, int stp)
{
    char str[50];
    printf ("\n\t-------------------------------------------------------------\n");
    for (int j = 0; j <= k; j++) {
        a[0][j] = j;
        printf ("\tk = %4.0lf", a[0][j]);
    }
    printf ("\n\t-------------------------------------------------------------\n");
    for (int i = 1; i <= n; i++) {
        for(int j = 0; j <= k; j++) {
            nDecimals (str, a[i][j], stp);
            printf ("\tx%d= %s", i, str);
            //printf ("\tx%d= %3.5lf",i, a[i][j]);
        }
        printf ("\n\n");
    }
    printf ("\t-------------------------------------------------------------\n");

    FILE *fileOut;
    fileOut = fopen (fileOutput, "a");
    fprintf (fileOut, "\n");
    for (int j = 0; j <= k; j++) {
        a[0][j] = j;
        fprintf (fileOut, "\t k =%4.0lf", a[0][j]);
    }
    fprintf (fileOut, "\n\n");
    for (int i = 1; i <= n; i++) {
        for(int j = 0; j <= k; j++) {
            nDecimals (str, a[i][j], stp);
            fprintf (fileOut, "\tx%d= %s", i, str);
            //fprintf (fileOut, "\tx%d= %3.10lf",i, a[i][j]);
        }
        fprintf (fileOut, "\n");
    }
    fprintf (fileOut, "\n");
    fclose (fileOut);
}

void KiemTraCheoTroi (double a[][MAX], int n)
{
    bool flag = true;
    double sum_row = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j)
                sum_row += fabs (a[i][j]);
        }
        if (fabs (a[i][i]) < sum_row || a[i][i] == 0)
            flag = false;
        else
            sum_row = 0;
    }
    if (flag == false)
        printf ("\tMa tran A khong la ma tran cheo troi\n");
    else
        printf ("\tMa tran A la ma tran cheo troi\n");
}

//  Hàm tìm chuẩn của ma trận theo dòng
double ChuanMaTran_Row (double a[][MAX], int n)
{
    double sum_row = 0;
    double sumMax = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j)
                continue;
            sum_row += fabs (a[i][j]);
        }
        if (sum_row >= sumMax)
            sumMax = sum_row;
        sum_row = 0;
    }
    return sumMax;
}

void BienDoiMaTran (double a[][MAX], int n)
{
    double x;
    for (int i = 1; i <= n; i++) {
        a[i][0] = -a[i][i];
        a[i][i] = 0;
        a[i][n+1] = -a[i][n+1];
        x = a[i][0];
        for (int j = 1; j <= n+1; j++) {
            if (i != j)
                a[i][j]= a[i][j]/x;
        }

    }
}

void phuongPhapLapDonk (double a[][MAX], double result[][MAX], int n, int k)
{
    for (int i = 1; i <= n; i++)
        result[i][0] = a[i][n+1];
    for (int h = 1; h <= k; h++) {
        for (int i = 1; i <= n; i++) {
            result[i][h] = 0;
            for (int j = 1; j <= n; j++)
                result[i][h] += (a[i][j] * result[j][h-1]);
            result[i][h] += a[i][n+1];
        }
    }
}

void phuongPhapSeidelk (double a[][MAX], double result[][MAX], int n, int k)
{
     for (int i = 1; i <= n; i++)
         result[i][0] = a[i][n+1];

    for (int h = 1; h <= k; h++) {
        //result[1][h] = a[1][n+1];
        result[1][h] = result[1][0];
        for (int j = 1; j <= n; j++)
            result[1][h] += a[1][j] * result[j][h-1];
        for (int i = 2; i <= n; i++) {
            result[i][h] = a[i][n+1];
            for (int j = 1; j <= i - 1; j++)
                result[i][h] += a[i][j] * result[j][h-1];
            for (int j = 1; j <= n; j++)
                result[i][h] += a[i][j] * result[j][h-1];
        }
    }
}

void SaiSo (double a[][MAX], double result[][MAX], int n, int k, int stp)
{
    FILE *fileOut;
    char str[50];
    double chuan = -999;

    for (int i = 1; i <= n; i++) {
        result[i][k+1] = result[i][k] - result[i][k-1];
        if (fabs (result[i][k+1]) > chuan)
            chuan = result[i][k+1];
    }
    double q = ChuanMaTran_Row (a, n);
    double saiso = q / (1-q) * chuan;
    nDecimals (str, saiso, stp);
    printf ("\tSai so phuong phap: e = %s\n", str);

    fileOut = fopen (fileOutput, "a");
    nDecimals (str, saiso, stp);
    fprintf (fileOut, "\t*Sai số phương pháp: e = %s\n", str);
    fprintf (fileOut, "\t-----------------------------------------------------------\n");
    fclose (fileOut);
}
        
double nghiemGanDung (double a[][MAX], double result[][MAX], int n, double e)
{
    double q = ChuanMaTran_Row (a, n);
    double chuan = -999;
    for (int i = 1; i <= n; i++)
        result[i][0] = a[i][n+1];
    for (int i = 1; i <= n; i++) {
            result[i][1] = 0;
            for (int j = 1; j <= n; j++)
                result[i][1] += (a[i][j] * result[j][0]);
            result[i][1] += a[i][n+1];
        }
    for (int i = 1; i <= n; i++) {
        result[i][2] = result[i][1] - result[i][0];
        if (fabs (result[i][2]) > chuan)
            chuan = result[i][2];
    }
    double k = floor (log ((1-q) * e / chuan) / log (q));
    return k;
}

void nDecimals (char *s, double d, int n)
{
    int sz; double d2;
    d2 = (d >= 0) ? d : -d;
    sz = (d >= 0) ? 0 : 1;
    if (d2 < 1) sz++;
    while (d2 >= 1) { d2 /= 10.0; sz++; }
    sz += 1 + n;
    sprintf (s, "%*.*f", sz, n, d);
}