/*
 *	Name: Bài tập lớn ktlt
 *	Copyright: 
 *	Author: Nhóm 10 - Nguyễn Trần Thức & Đoàn Quốc Vĩnh
 *	Date: 07/06/20 00:26
 *	Description: Giải gần đúng hệ phương trình, bằng phương pháp lặp đơn và lặp Seidel.
        Trong phạm vi chương tình này ta chỉ giải hpt có bậc < 10,
        lần lặp k tối đa 10 và Input là ma trận chéo trội
*/

//  ---------------- Khai báo thư viện hàm ----------------

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

//  ---------------- Khai báo biến toàn cục ---------------

#define fileInput "data.txt"
#define fileOuput "Output.txt"
#define MAX 10
#define  MAX_LIST 9
static int flag;

//  --------------- Khai báo nguyên mẫu hàm ---------------

void SetConsoleColour(WORD* Attributes, DWORD Colour);
void ResetConsoleColour(WORD Attributes);
void NhapMaTran(double a[][MAX], int &n);
void XuatMaTran(double a[][MAX], int n);
void KiemTraCheoTroi(double a[][MAX], int n);
double ChuanMaTran_Row(double a[][MAX], int n);
void BienDoiMaTran(double a[][MAX], int n);
void phuongPhapLapDonk(double a[][MAX], double result[][MAX], int n, int k);
void phuongPhapSeidelk(double a[][MAX], double result[][MAX], int n, int k);      // chưa tạo hàm con
void printResult(double a[][MAX], int n, int k);
double SaiSo(double a[][MAX], double result[][MAX], int n, int k);

//  ---------------------- Hàm chính ----------------------

int main()
{
	int n, k;
    bool daNhap = false;
    double a[MAX][MAX];
    double result[MAX][MAX]; //result2[MAX][MAX];
    double chuan, e;
	WORD Attributes = 0;
	int pointer = 0;
	flag = 1;

	char x1[] = "||      1. Nhap so bac cua he phuong trinh                  ||";
	char x2[] = "||      2. Nhap vao ma tran A,b                             ||";
	char x3[] = "||      3. Kiem tra tinh cheo troi cua ma tran A            ||";
	char x4[] = "||      4. Chuyen hpt ve dang Ix = Tx + c                   ||";
	char x5[] = "||      5. Tinh chuan cua ma tran T, kiem tra su hoi tu     ||";
	char x6[] = "||      6. Tinh nghiem gan dung voi so lan lap k            ||";
	char x7[] = "||      7. Tinh nghiem gan dung voi sai so e                ||";
	char x8[] = "||      8. Tinh nghiem gan dung thoa man dieu kien          ||";
	char x9[] = "||      0. Thoat                                            ||";

	char* menu[] = {x1, x2, x3, x4, x5, x6, x7, x8, x9};

	while (1) {
		system("cls");
        system("color 3");
        printf("\n");
        printf("\t*============================================================*\n");
        printf("\t||**                                                      **||\n");
        printf("\t||*        CHUONG TRINH GIAI HE PHUONG TRINH Ax=b          *||\n");
        printf("\t||        Phuong phap lap don & lap Seidel - Bai 3          ||\n");
        printf("\t||__________________________________________________________||\n");
        printf("\t||               MENU DIEU KHIEN CHUONG TRINH               ||\n");
        printf("\t||__________________________________________________________||");

		for (int i = 0; i < MAX_LIST; i++) {
			if (pointer == i) {
				SetConsoleColour(&Attributes, BACKGROUND_INTENSITY | BACKGROUND_BLUE);
				printf("\n\t%s %c", menu[i], 174);
				ResetConsoleColour(Attributes);
			} else {
				printf("\n\t%s", menu[i]);
			}
		}
		printf("\n\t||__________________________________________________________||");
       	printf("\n\t||*        Coding by Nhom 10 - KTLT MI3310 - 116444        *||");
        printf("\n\t||**           Nguyen Tran Thuc & Doan Quoc Vinh          **||");
		printf("\n\t*============================================================*\n");

		while(1) {
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
						++pointer;
					else
						pointer = 0;
					break;
				}
				if (key == 13) {
					switch (pointer) {
						case 0:
							do {
                    			printf("\t----------------------------------------------------------\n");
                    			printf("\tNhap so bac cua he phuong trinh: ");
                    			scanf("%d", &n);
                    			printf("\t----------------------------------------------------------\n");
                    			if(n < 1 || n > MAX)
                        			printf("\nSo bac khong hop le. Xin kiem tra lai !");
                			} while(n < 1 || n > MAX);
                			printf("\nBan da nhap thanh cong!");
                			daNhap = true;
                			printf("\n\n...Bam phim bat ky de tiep tuc!...");
                			getch();
                			break;
						case 1:
							if(daNhap)
                    			printf("\nBan da chon lua chon 2!\n");
                			else
                    			printf("\nNhap so bac cua he phuong trinh truoc!!!");
                			printf("\t----------------------------------------------------------\n");
                			printf("\tMa tran [A | b] :\n");
                			printf("\t---------------\n");
                			NhapMaTran(a,n);
                			XuatMaTran(a,n);
                			printf("\t----------------------------------------------------------\n");
                			printf("\n\n...Bam phim bat ky de tiep tuc!...");
                			getch();
                			break;

                		case 2:
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

                		case 3:
                			if(daNhap)
                    			printf("\nBan da chon lua chon 4!\n");
                			else
                    			printf("\n\nNhap so bac cua he phuong trinh truoc!!!");
                			printf("\t----------------------------------------------------------\n");
                			printf("\tMa tran [T | c] :\n");
                			printf("\t---------------\n");
                			BienDoiMaTran(a,n);
                			XuatMaTran(a,n);
                			printf("\t----------------------------------------------------------\n");
                			printf("\n\n...Bam phim bat ky de tiep tuc!...");
                			getch();
                			break;

                		case 4:
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

                		case 5:
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

                		case 6:
                			if(daNhap)
                    			printf("\nBan da chon lua chon 7!");
                			else
                    			printf("\n\nNhap so bac cua he phuong trinh truoc!!!");
                			printf("\n...Bam phim bat ky de tiep tuc!...");
                			getch();
                			break;

                		case 7:
                			if(daNhap)
                    			printf("\nBan da chon lua chon 8!");
                			else
                    			printf("\n\nNhap so bac cua he phuong trinh truoc!!!");
                			printf("\n...Bam phim bat ky de tiep tuc!...");
                			getch();
                			break;

						case 8:
							printf("\nlua chon 3\n\n");
							flag = -1;
							break;
						default:
							printf("error!!");
							
					}
					break;
				}
			}
		}
		if (flag == -1)
		break;
	}
}//	End Menu

//  ----------------- Cài đặt các hàm con -----------------

void SetConsoleColour(WORD* Attributes, DWORD Colour)
{
    CONSOLE_SCREEN_BUFFER_INFO Info;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdout, &Info);
    *Attributes = Info.wAttributes;
    SetConsoleTextAttribute(hStdout, Colour);
}

void ResetConsoleColour(WORD Attributes)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Attributes);
}


void NhapMaTran(double a[][MAX], int &n)
{
    FILE *FileIn;
    FileIn = fopen( fileInput , "r");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n+1; j++) {
            fscanf(FileIn, "%lf", &a[i][j]);
        }
    }
    fclose(FileIn);
}

//  Hàm xuất ma trận
void XuatMaTran(double a[][MAX], int n)
{
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n+1; j++)
            printf("%15.3lf",a[i][j]);
        printf("\n\n");
    }
}


void printResult(double a[][MAX], int n, int k)
{
    printf("\n\t-------------------------------------------------------------\n");
    for (int j = 0; j <= k; j++) {
        a[0][j] = j;
        printf("\tk = %4.0lf", a[0][j]);
    }
    printf("\n\t-------------------------------------------------------------\n");
    for (int i = 1; i <= n; i++) {
        for(int j = 0; j <= k; j++)
            printf("\tx%d= %3.3lf",i, a[i][j]);
        printf("\n\n");
    }
    printf("\t-------------------------------------------------------------\n");

    FILE *fileOut;
    fileOut = fopen( fileOuput, "w");
    fprintf(fileOut, "\n\t-------------------------------------------------------------\n");
    for (int j = 0; j <= k; j++) {
        a[0][j] = j;
        fprintf(fileOut, "\tk = %4.0lf", a[0][j]);
    }
    fprintf(fileOut, "\n\t-------------------------------------------------------------\n");
    for (int i = 1; i <= n; i++) {
        for(int j = 0; j <= k; j++)
            fprintf(fileOut, "\tx%d= %3.3lf",i, a[i][j]);
        fprintf(fileOut, "\n\n");
    }
    fprintf(fileOut, "\t-------------------------------------------------------------\n");
    fclose(fileOut);
}



void KiemTraCheoTroi(double a[][MAX], int n)
{
    bool flag = true;
    double sum_row = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j)
                sum_row += fabs(a[i][j]);
        }
        if (fabs(a[i][i]) < sum_row)
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
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if(i == j)
                continue;
            sum_row += fabs(a[i][j]);
        }
        if(sum_row >= sumMax)
            sumMax = sum_row;
        sum_row = 0;
    }
    return sumMax;
}

void BienDoiMaTran(double a[][MAX], int n)
{
    double x;
    for (int i = 1; i <= n; i++) {
        a[i][0] = -a[i][i];
        a[i][i] = 0;
        a[i][n+1] = -a[i][n+1];
        x = a[i][0];
        for (int j = 1; j <= n+1; j++) {
            if(i != j)
                a[i][j]= a[i][j]/x;
        }

    }
}

void phuongPhapLapDonk(double a[][MAX], double result[][MAX], int n, int k)
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

void phuongPhapSeidelk(double a[][MAX], double result[][MAX], int n, int k)
{

}


double SaiSo(double a[][MAX], double result[][MAX], int n, int k)
{   
    double chuan = -999;
    for (int i = 1; i <= n; i++) {
        result[i][k+1] = result[i][k] - result[i][k-1];
        if (fabs(result[i][k+1]) > chuan)
            chuan = result[i][k+1];
    }
    double q = ChuanMaTran_Row(a, n);
    double saiso = q / (1-q) * chuan;
    return saiso;
}
		
		