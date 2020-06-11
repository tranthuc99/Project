/*
    Name: Bài tập lớn ktlt
    Copyright: 
    Author: Nhóm 10 - Nguyễn Trần Thức & Đoàn Quốc Vĩnh
    Date: 07/06/20 00:26
    Description: Giải gần đúng hệ phương trình, bằng phương pháp lặp đơn và lặp Seidel.
        Trong phạm vi chương tình này ta chỉ giải hpt có bậc < 10,
        lần lặp k tối đa 10 và Input là ma trận chéo trội
*/

//  ---------------- Khai báo thư viện hàm ----------------

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#define fileInput "data.txt"
#define fileOuput "Output.txt"
#define MAX 10

//  --------------- Khai báo nguyên mẫu hàm ---------------

void NhapMaTran(double a[][MAX], int &n);
void XuatMaTran(double a[][MAX], int n);
void KiemTraCheoTroi(double a[][MAX], int n);
double ChuanMaTran_Row(double a[][MAX], int n);
void BienDoiMaTran(double a[][MAX], int n);
void phuongPhapLapDonk(double a[][MAX], double result[][MAX], int n, int k);
//void phuongPhapLapDone(double a[][MAX], int n, double e);   // chưa tạo hàm con
void phuongPhapSeidelk(double a[][MAX], int n, int k);      // chưa tạo hàm con
void phuongPhapSeidele(double a[][MAX], int n, double e);   // chưa tạo hàm con
void printResult(double a[][MAX], int n, int k);
double SaiSo(double a[][MAX], double result[][MAX], int n, int k);


//  ---------------------- Hàm chính ----------------------

int main()
{
    int n, k, key;
    bool daNhap = false;
    double a[MAX][MAX];
    double result[MAX][MAX], result2[MAX][MAX];
    double chuan, e;

    while(true){
        system("cls");
        system("color 3");
        printf("\n");
        printf("\t*============================================================*\n");
        printf("\t||**                                                      **||\n");
        printf("\t||*        CHUONG TRINH GIAI HE PHUONG TRINH Ax=b          *||\n");
        printf("\t||        Phuong phap lap don & lap Seidel - Bai 3          ||\n");
        printf("\t||__________________________________________________________||\n");
        printf("\t||               MENU DIEU KHIEN CHUONG TRINH               ||\n");
        printf("\t||__________________________________________________________||\n");
        printf("\t||      1. Nhap so bac cua he phuong trinh                  ||\n");
        printf("\t||      2. Nhap vao ma tran A,b                             ||\n");
        printf("\t||      3. Kiem tra tinh cheo troi cua ma tran A            ||\n");
        printf("\t||      4. Chuyen hpt ve dang Ix = Tx + c                   ||\n");
        printf("\t||      5. Tinh chuan cua ma tran T, kiem tra su hoi tu     ||\n");
        printf("\t||      6. Tinh nghiem gan dung voi so lan lap k            ||\n");
        printf("\t||         va danh gia sai so                               ||\n");
        printf("\t||      7. Tinh nghiem gan dung voi sai so e                ||\n");
        printf("\t||      8. Tinh nghiem gan dung thoa man dieu kien          ||\n");
        printf("\t||      0. Thoat                                            ||\n");
        printf("\t||__________________________________________________________||\n");
        printf("\t||*        Coding by Nhom 10 - KTLT MI3310 - 116444        *||\n");
        printf("\t||**           Nguyen Tran Thuc & Doan Quoc Vinh          **||\n");
        printf("\t*============================================================*\n");
        printf("\nMoi ban nhap lua chon: ");

        scanf("%d",&key);
        switch(key)
        {
            case 1:
                do
                {
                    printf("\t----------------------------------------------------------\n");
                    printf("\tNhap so bac cua he phuong trinh: ");
                    scanf("%d", &n);
                    printf("\t----------------------------------------------------------\n");
                    if(n < 1 || n > MAX)
                        printf("\nSo bac khong hop le. Xin kiem tra lai !");
                }
                while(n < 1 || n > MAX);
                printf("\nBan da nhap thanh cong!");
                daNhap = true;
                printf("\n\n...Bam phim bat ky de tiep tuc!...");
                getch();
                break;

            case 2:
                if(daNhap)
                    printf("\nBan da chon lua chon 2!\n");
                else
                    printf("\nNhap so bac cua he phuong trinh truoc!!!");
                
                printf("\t----------------------------------------------------------\n");
                printf("\tMa tran A | b :\n");
                printf("\t---------------\n");
                NhapMaTran(a,n);
                XuatMaTran(a,n);
                printf("\t----------------------------------------------------------\n");
                printf("\n\n...Bam phim bat ky de tiep tuc!...");
                getch();
                break;

            case 3:
                if(daNhap)
                    printf("\nBan da chon lua chon 3!\n");
                else
                    printf("\n\nNhap so bac cua he phuong trinh truoc!!!");
                printf("\t----------------------------------------------------------\n");
                KiemTraCheoTroi(a,n);
                printf("\t----------------------------------------------------------\n");
                printf("\n\n...Bam phim bat ky de tiep tuc!...");
                getch();
                break;

            case 4:
                if(daNhap)
                    printf("\nBan da chon lua chon 4!\n");
                else
                    printf("\n\nNhap so bac cua he phuong trinh truoc!!!");
                printf("\t----------------------------------------------------------\n");
                printf("\tMa tran T | c :\n");
                printf("\t---------------\n");
                BienDoiMaTran(a,n);
                XuatMaTran(a,n);
                printf("\t----------------------------------------------------------\n");
                printf("\n\n...Bam phim bat ky de tiep tuc!...");
                getch();
                break;

            case 5:
                if(daNhap)
                    printf("\nBan da chon lua chon 5!\n");
                else
                    printf("\n\nNhap so bac cua he phuong trinh truoc!!!");
                printf("\t----------------------------------------------------------\n");
                printf("\tChuan cua ma tran T la:  ");
                chuan = ChuanMaTran_Row(a,n);
                printf("||T|| = %.2lf\n", chuan);
                if(chuan < 1)
                    printf("\n\t=> ||T|| < 1 => Nghiem cua he phuong trinh hoi tu toi X*\n");
                printf("\t----------------------------------------------------------\n");
                printf("\n\n...Bam phim bat ky de tiep tuc!...");
                getch();
                break;

            case 6:
                if(daNhap)
                    printf("\nBan da chon lua chon 6!");
                else
                    printf("\n\nNhap so bac cua he phuong trinh truoc!!!");
                printf("Nhap so lan lap k = ");
                scanf("%d", &k);
                phuongPhapLapDonk(a, result, n, k);
                printResult(result, n, k);
                e = SaiSo(a, result, n, k);
                printf("\tSai so: e = %.20lf", e);

                FILE *fileOut;
                fileOut = fopen( fileOuput, "a");
                fprintf(fileOut, "\tSai số: e = %.20lf", e);
                fclose(fileOut);

                printf("\n\n...Bam phim bat ky de tiep tuc!...");
                getch();
                break;

            case 7:
                if(daNhap)
                    printf("\nBan da chon lua chon 7!");
                else
                    printf("\n\nNhap so bac cua he phuong trinh truoc!!!");
                
                printf("\n...Bam phim bat ky de tiep tuc!...");
                getch();
                break;

            case 8:
                if(daNhap)
                    printf("\nBan da chon lua chon 8!");
                else
                    printf("\n\nNhap so bac cua he phuong trinh truoc!!!");
                
                printf("\n...Bam phim bat ky de tiep tuc!...");
                getch();
                break;

            case 0:
                printf("\nBan da chon thoat chuong trinh!");
                getch();
                return 0;

            default:
                printf("\nKhong co lua chon nay nay!");
                printf("\nBam phim bat ky de tiep tuc!");
                getch();
                break;
        }
    }
}

//  ----------------- Cài đặt các hàm con -----------------

//  Hàm nhập ma trận từ file vào chương trình
void NhapMaTran(double a[][MAX], int &n)
{
    FILE *FileIn;
    FileIn = fopen( fileInput , "r");
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n+1; j++)
        {
            fscanf(FileIn, "%lf", &a[i][j]);
        }
    }
    fclose(FileIn);
}

//  Hàm xuất ma trận
void XuatMaTran(double a[][MAX], int n)
{
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n+1; j++)
        {
            printf("%15.3lf",a[i][j]);
        }
        printf("\n\n");
    }
}


void printResult(double a[][MAX], int n, int k)
{
    printf("\n\t-------------------------------------------------------------\n");
    for(int j = 0; j <= k; j++)
    {
        a[0][j] = j;
        printf("\tk = %4.0lf", a[0][j]);
    }
    printf("\n\t-------------------------------------------------------------\n");
    for(int i = 1; i <= n; i++)
    {
        for(int j = 0; j <= k; j++)
        {
            printf("\tx%d=(%3.3lf)",i, a[i][j]);
        }
        printf("\n\n");
    }
    printf("\t-------------------------------------------------------------\n");




    FILE *fileOut;
    fileOut = fopen( fileOuput, "w");

    fprintf(fileOut, "\n\t-------------------------------------------------------------\n");
    for(int j = 0; j <= k; j++)
    {
        a[0][j] = j;
        fprintf(fileOut, "\tk = %4.0lf", a[0][j]);
    }
    fprintf(fileOut, "\n\t-------------------------------------------------------------\n");
    for(int i = 1; i <= n; i++)
    {
        for(int j = 0; j <= k; j++)
        {
            fprintf(fileOut, "\tx%d=(%3.3lf)",i, a[i][j]);
        }
        fprintf(fileOut, "\n\n");
    }
    fprintf(fileOut, "\t-------------------------------------------------------------\n");


    fclose(fileOut);
}



void KiemTraCheoTroi(double a[][MAX], int n)
{
    bool flag = true;
    double sum_row = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if(i != j)
                sum_row += fabs(a[i][j]);
        }
        if(fabs(a[i][i]) < sum_row)
            flag = false;
        else
            sum_row = 0;
    }
    if(flag == false)
        printf("\tMa tran A khong la ma tran cheo troi\n");
    else
        printf("\tMa tran A la ma tran cheo troi\n");
}

//  Hàm tìm chuẩn của ma trận theo dòng
double ChuanMaTran_Row(double a[][MAX], int n)
{
    double sum_row = 0;
    double sumMax = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if(i == j)
                continue;
            sum_row += fabs(a[i][j]);

        }
        //printf("sum_row = %lf ", sum_row);
        if(sum_row >= sumMax)
            sumMax = sum_row;
        sum_row = 0;
    }
    return sumMax;
} // hàm này chưa test

void BienDoiMaTran(double a[][MAX], int n)
{
    double x;
    for (int i = 1; i <= n; i++)
    {
        a[i][0] = -a[i][i];
        a[i][i] = 0;
        a[i][n+1] = -a[i][n+1];
        x = a[i][0];
        for (int j = 1; j <= n+1; j++)
        {
            if(i != j)
                a[i][j]= a[i][j]/x;
        }

    }
}

void phuongPhapLapDonk(double a[][MAX], double result[][MAX], int n, int k)
{
    for (int i = 1; i <= n; i++)
    {
        result[i][0] = a[i][n+1];
    }
    for (int h = 1; h <= k; h++)
    {
        for (int i = 1; i <= n; i++)
        {
            result[i][h] = 0;
            for (int j = 1; j <= n; j++)
            {
                result[i][h] += (a[i][j] * result[j][h-1]);
                //result[i][h] += a[i][n+1];
            }
            result[i][h] += a[i][n+1];
        }
    }
}

double SaiSo(double a[][MAX], double result[][MAX], int n, int k)
{   
    double chuan = -999;
    for (int i = 1; i <= n; i++)
    {
        result[i][k+1] = result[i][k] - result[i][k-1];
        if(fabs(result[i][k+1]) > chuan)
            chuan = result[i][k+1];
    }
    double q = ChuanMaTran_Row(a, n);
    double saiso = q / (1-q) * chuan;
    return saiso;
}
/*
void phuongPhapSeidelk(double a[][MAX], double result[][MAX], int n, int k)
{
    for (int i = 1; i <= n; i++)
    {
        result[i][0] = a[i][n+1];
    }
    for (int h = 1; h <= k; h++)
    {
        for (int i = 1; i <= n; i++)
        {
            result[i][h] = 0;
            for (int j = 1; j <= n; j++)
            {
                if(i == 1)
                    result[1][h] = result[1][h] + a[1][n+1] + a[1][j] * result[j][h-1];
                else
                    result[i][h] += (a[i][j] * result[j][h-1]);
            }
            result[i][h] += a[i][n+1];
        }
    }
}
*/