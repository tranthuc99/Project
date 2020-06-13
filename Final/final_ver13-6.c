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

#define FILE_INPUT   "In-Out/Data3.txt"
#define FILE_OUTPUT  "In-Out/Output.txt"
#define MAX         100             // Số lần lặp k tối đa
#define MAX_LIST    10              // Số lựa chọn trong menu

//  --------------- Khai báo nguyên mẫu hàm ---------------

void    set_console_color               (WORD*  Attributes, DWORD Colour);
void    reset_console_color             (WORD   Attributes);
void    get_matrix_from_keyboard        (double a[][MAX], int &n);
void    get_matrix_from_file            (double a[][MAX], int &n);
void    export_matrix                   (double a[][MAX], int n, int n_decimal);
void    is_diagonally_dominant_matrix   (double a[][MAX], int n);
void    matrix_transform                (double a[][MAX], int n);
double  norm_matrix                     (double a[][MAX], int n);
int     approximate_solution_method     (double a[][MAX], double result[][MAX], int n, double e);
void    error_estimators                (double a[][MAX], double result[][MAX], int n, int k, int n_decimal);
int     approximate_solution            (double result[][MAX], int n, double e);
void    iterative_method                (double a[][MAX], double result[][MAX], int n, int k);
void    seidel_iterative_method         (double a[][MAX], double result[][MAX], int n, int k);
void    print_result                    (double a[][MAX], int n, int k, int n_decimal);
void    set_decimals                    (char   *s, double d, int n);


//  ---------------------- Hàm chính ----------------------

int main()
{
    int     i_option,
            n_degree,
            k_import,
            k_iterative,
            k_seidel,
            k_approximate,
            n_decimal,
            d_error;
    int     pointer = 0,
            flag = 1;
    bool    flag_import = false;
    double  a[MAX][MAX],
            result[MAX][MAX],
            result2[MAX][MAX];
    double  norm, epsilon, e;
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
        for (i_option = 0; i_option < MAX_LIST; i_option++) {
            if (pointer == i_option) {
                set_console_color (&Attributes, BACKGROUND_INTENSITY | BACKGROUND_BLUE);
                printf("\n\t||    ");
                printf ("%c%c%s", 175, 175, menu[i_option]);
                reset_console_color (Attributes);
            } else {
                printf("\n\t||      ");
                printf ("%s", menu[i_option]);
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
                            scanf ("%d", &n_degree);
                            if (n_degree < 1 || n_degree > MAX)
                                printf ("\n\tSo bac khong hop le. Xin kiem tra lai !");
                        } while (n_degree < 1 || n_degree > MAX);
                        printf ("\n\tBan da nhap thanh cong!");
                        flag_import = true;
                        printf ("\n\n...Bam phim bat ky de tiep tuc!...");
                        getch();
                        break;
                    case 1:
                        if (flag_import) {
                            printf ("\n\t*Nhap vao ma tran A,b tu ban phim:\n");
                        } else {
                            printf ("\nNhap so bac cua he phuong trinh truoc !!!");
                            getch();
                            break;
                        }
                        printf ("\t----------------------------------------------------------\n");
                        get_matrix_from_keyboard (a,n_degree);
                        //NhapMaTranTuBP (b,n);
                        printf ("\n\tNhap so chu so thap phan: ");
                        scanf ("%d", &n_decimal);
                        printf ("\n\tMa tran [A | b] :\n");
                        printf ("\t---------------\n");
                        export_matrix (a, n_degree, n_decimal);
                        printf ("\t----------------------------------------------------------\n");
                        printf ("\n\n...Bam phim bat ky de tiep tuc!...");
                        getch();
                        break;

                    case 2:
                        if (flag_import) {
                            printf ("\n\t*Nhap vao ma tran A,b tu: %s :\n", FILE_INPUT);
                        } else {
                            printf ("\nNhap so bac cua he phuong trinh truoc !!!");
                            getch();
                            break;
                        }
                        printf ("\n\tNhap so chu so thap phan: ");
                        scanf ("%d", &n_decimal);
                        printf ("\t----------------------------------------------------------\n");
                        printf ("\tMa tran [A | b] :\n");
                        printf ("\t---------------\n");
                        get_matrix_from_file (a,n_degree);
                        export_matrix (a,n_degree, n_decimal);
                        printf ("\t----------------------------------------------------------\n");
                        printf ("\n\n...Bam phim bat ky de tiep tuc!...");
                        getch();
                        break;

                    case 3:
                        if (flag_import) {
                            printf ("\n\t*Kiem tra tinh cheo troi cua ma tran A:\n");
                        } else {
                            printf ("\nNhap so bac cua he phuong trinh & nhap ma tran A,b truoc !!!");
                            getch();
                            break;
                        }
                        printf ("\t----------------------------------------------------------\n");
                        is_diagonally_dominant_matrix (a,n_degree);
                        printf ("\t----------------------------------------------------------\n");
                        printf ("\n\n...Bam phim bat ky de tiep tuc!...");
                        getch();
                        break;

                    case 4:
                        if (flag_import) {
                            printf ("\n\t*Chuyen hpt ve dang Ix = Tx + c\n");
                        } else {
                            printf ("\nNhap so bac cua he phuong trinh & nhap ma tran A,b truoc !!!");
                            getch();
                            break;
                        }
                        printf ("\n\tNhap so chu so thap phan: ");
                        scanf ("%d", &n_decimal);
                        printf ("\t----------------------------------------------------------\n");
                        printf ("\tMa tran [T | c] :\n");
                        printf ("\t---------------\n");
                        matrix_transform (a, n_degree);
                        export_matrix (a, n_degree, n_decimal);
                        printf ("\t----------------------------------------------------------\n");
                        printf ("\n\n...Bam phim bat ky de tiep tuc!...");
                        getch();
                        break;

                    case 5:
                        if (flag_import) {
                            printf ("\n\t*Tinh chuan cua ma tran T, kiem tra su hoi tu:\n");
                        } else {
                            printf ("\nNhap so bac cua he phuong trinh & nhap ma tran A,b truoc !!!");
                            getch();
                            break;
                        }
                        printf ("\t----------------------------------------------------------\n");
                        printf ("\tChuan cua ma tran T la:  ");
                        norm = norm_matrix (a, n_degree);
                        printf ("||T|| = %.2lf\n", norm);
                        if (norm < 1 && norm > 0)
                            printf ("\n\t=> ||T|| < 1 => Nghiem cua he phuong trinh hoi tu toi X*\n");
                        else if (norm == 0)
                            printf ("\n\tKhong ton tai he phuong trinh!\n");
                        else
                            printf ("\n\t=> ||T|| > 1 => Nghiem cua hpt khong hoi tu toi X*\n");
                        printf ("\t----------------------------------------------------------\n");
                        printf ("\n\n...Bam phim bat ky de tiep tuc!...");
                        getch();
                        break;

                    case 6:
                        if (flag_import) {
                            printf ("\n\t*Tinh nghiem gan dung voi so lan lap k, sai so:\n");
                        } else {
                            printf ("\nNhap so bac cua he phuong trinh & nhap ma tran A,b truoc !!!");
                            getch();
                            break;
                        }
                        printf ("\n\t-Nhap so lan lap k = ");
                        scanf ("%d", &k_import);

                        printf ("\n\t-Nhap so chu so thap phan cua nghiem: ");
                        scanf ("%d", &n_decimal);

                        printf ("\n\t-Nhap so chu so thap phan cua sai so: ");
                        scanf ("%d", &d_error);

                        printf ("\n\t* Phuong phap lap don");
                        iterative_method (a, result, n_degree, k_import);
                        fileOut = fopen (FILE_OUTPUT, "a");
                        fprintf (fileOut, "\n 4. TÍNH NGHIỆM GẦN ĐÚNG VỚI SỐ LẦN LẶP k = %d\n", k_import);
                        fprintf (fileOut, "\n\t*Phương pháp lặp đơn:\n");
                        fclose (fileOut);
                        print_result (result, n_degree, k_import, n_decimal);
                        error_estimators (a, result, n_degree, k_import, d_error);

                        printf ("\n\t* Phuong phap lap Seidel");
                        seidel_iterative_method (a, result2, n_degree, k_import);
                        fileOut = fopen (FILE_OUTPUT, "a");
                        fprintf (fileOut, "\n\t*Phương pháp lặp Seidel:\n");
                        fclose (fileOut);
                        print_result (result2, n_degree, k_import, n_decimal);
                        error_estimators (a, result2, n_degree, k_import, d_error);

                        printf ("\n\n...Bam phim bat ky de tiep tuc!...");
                        getch();
                        break;

                    case 7:
                        if (flag_import) {
                            printf ("\n\t*Tinh nghiem gan dung voi sai so e:\n");
                        } else {
                            printf ("\nNhap so bac cua he phuong trinh & nhap ma tran A,b truoc !!!");
                            getch();
                            break;
                        }
                        printf ("\t-Nhap sai so: e = ");
                        scanf ("%lf", &epsilon);

                        printf ("\n\t-Nhap so chu so thap phan: ");
                        scanf ("%d", &n_decimal);

                        printf ("\n\t* Phuong phap lap don");
                        k_iterative = approximate_solution_method (a, result, n_degree, epsilon);
                        iterative_method (a, result, n_degree, k_iterative);
                        fileOut = fopen (FILE_OUTPUT, "a");
                        fprintf (fileOut, "\n 5. TÍNH NGHIỆM GẦN ĐÚNG VỚI SAI SỐ e = %lf\n", epsilon);
                        fprintf (fileOut, "\n\t*Phương pháp lặp đơn:\n");
                        fclose (fileOut);
                        print_result (result, n_degree, k_iterative, n_decimal);

                        printf ("\n\t* Phuong phap lap Seidel");
                        k_seidel = approximate_solution_method (a, result2, n_degree, epsilon);
                        seidel_iterative_method (a, result2, n_degree, k_seidel);
                        fileOut = fopen (FILE_OUTPUT, "a");
                        fprintf (fileOut, "\t-----------------------------------------------------------\n");
                        fprintf (fileOut, "\n\t*Phương pháp lặp Seidel:\n");
                        fclose (fileOut);
                        print_result (result2, n_degree, k_seidel, n_decimal);

                        printf ("\n...Bam phim bat ky de tiep tuc!...");
                        getch();
                        break;

                    case 8:
                        if (flag_import) {
                            printf ("\nTinh nghiem gan dung thoa man dieu kien:");
                        } else {
                            printf ("\nNhap so bac cua he phuong trinh & nhap ma tran A,b truoc !!!");
                            getch();
                            break;
                        }
                        printf ("\n\t-Nhap: e = ");
                        scanf ("%lf", &e);

                        printf ("\n\t-Nhap so chu so thap phan: ");
                        scanf ("%d", &n_decimal);
                        
                        k_approximate = approximate_solution (result2, n_degree, e);
                        seidel_iterative_method (a, result2, n_degree, k_approximate);
                        fileOut = fopen (FILE_OUTPUT, "a");
                        fprintf (fileOut, "\n 6. TÍNH NGHIỆM GẦN ĐÚNG THỎA MÃN ĐỀ\n");
                        fclose (fileOut);
                        print_result (result2, n_degree, k_approximate, n_decimal);

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

void set_console_color (WORD* Attributes, DWORD Colour)
{
    CONSOLE_SCREEN_BUFFER_INFO Info;
    HANDLE hStdout = GetStdHandle (STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo (hStdout, &Info);
    *Attributes = Info.wAttributes;
    SetConsoleTextAttribute (hStdout, Colour);
}

void reset_console_color (WORD Attributes)
{
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), Attributes);
}

//  Hàm nhập ma trận vào chương trình từ bàn phím
void get_matrix_from_keyboard (double a[][MAX], int &n)
{
    int i, j;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            printf("\ta[%d][%d] = ", i, j);
            scanf ("%lf", &a[i][j]);
        }
    }
    for (i = 1; i <= n; i++) {
        printf("\tb[%d]    = ", i);
        scanf ("%lf", &a[i][n+1]);
    }
}

//  Hàm nhập ma trận vào chương trình từ file
void get_matrix_from_file (double a[][MAX], int &n)
{
    int i, j;
    FILE *FileIn;
    FileIn = fopen (FILE_INPUT , "r");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n+1; j++) {
            fscanf (FileIn, "%lf", &a[i][j]);
        }
    }
    fclose (FileIn);
}

//  Hàm xuất ma trận A, b, T, c
void export_matrix (double a[][MAX], int n, int n_decimal)
{
    char str[50];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n+1; j++) {
            set_decimals (str, a[i][j], n_decimal);
            printf ("\t\t%s", str);
        }
        printf ("\n\n");
    }
}

//  Hàm kiểm tra tính chéo trội của ma trận
void is_diagonally_dominant_matrix (double a[][MAX], int n)
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

//  Hàm biến đổi ma trận về dạng Ix = Tx + c
void matrix_transform (double a[][MAX], int n)
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

//  Hàm tìm chuẩn của ma trận theo dòng
double norm_matrix (double a[][MAX], int n)
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

//  Hàm tìm nghiệm gần đúng của 2 phương pháp
int approximate_solution_method (double a[][MAX], double result[][MAX], int n, double e)
{
    double q = norm_matrix (a, n);
    double r, c;
    int t = 1;
    do {
        double norm = -999;
        for (int i = 1; i <= n; i++) {
            result[0][i] = result[i][t] - result[i][t-1];
            if (fabs (result[0][i]) > norm)
                norm = result[0][i];
        }
        c = norm;
        r = e * (1 - q) / q;
        t++;
    } while (c >= r);
    return t-1;
}

//  Hàm tính sai số, in ra màn hình và tệp văn bản
void error_estimators (double a[][MAX], double result[][MAX], int n, int k, int n_decimal)
{
    FILE *fileOut;
    char str[50];
    double norm = -999;

    for (int i = 1; i <= n; i++) {
        result[i][k+1] = result[i][k] - result[i][k-1];
        if (fabs (result[i][k+1]) > norm)
            norm = result[i][k+1];
    }
    double q = norm_matrix (a, n);
    double saiso = q / (1-q) * norm;
    set_decimals (str, saiso, n_decimal);
    printf ("\tSai so phuong phap: e = %s\n", str);

    fileOut = fopen (FILE_OUTPUT, "a");
    set_decimals (str, saiso, n_decimal);
    fprintf (fileOut, "\t-Sai số phương pháp: e = %s\n", str);
    fprintf (fileOut, "\t-----------------------------------------------------------\n");
    fclose (fileOut);
}

//  Hàm tìm nghiệm gần đúng thỏa mãn kiều kiện ý 6
int approximate_solution (double result[][MAX], int n, double e)
{
    double c;
    int t = 1;
    do {
        double norm = -999;
        for (int i = 1; i <= n; i++) {
            result[0][i] = result[i][t] - result[i][t-1];
            if (fabs (result[0][i]) > norm)
                norm = result[0][i];
        }
        c = norm;
        t++;
    } while (c >= e);
    return t-1;
}

//  Phương pháp lặp đơn
void iterative_method (double a[][MAX], double result[][MAX], int n, int k)
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

//  Phương pháp lặp Seidel
void seidel_iterative_method (double a[][MAX], double result[][MAX], int n, int k)
{
    for (int i = 1; i <= n; i++)
        result[i][0] = a[i][n+1];

    for (int h = 1; h <= k; h++) {
        result[1][h] = result[1][0];
        for (int j = 1; j <= n; j++)
            result[1][h] += a[1][j] * result[j][h-1];
        for (int i = 2; i <= n; i++) {
            result[i][h] = result[i][0];
            for (int j = 1; j <= i-1; j++)
                result[i][h] += a[i][j] * result[j][h];
            for (int t = i; t <= n; t++)
                result[i][h] += a[i][t] * result[t][h-1];
        }
    }
}

//  Hàm in kết quả và kết quả trung gian ra màn hình và tệp văn bản
void print_result (double a[][MAX], int n, int k, int n_decimal)
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
            set_decimals (str, a[i][j], n_decimal);
            printf ("\tx%d= %s", i, str);
        }
        printf ("\n\n");
    }
    printf ("\t-------------------------------------------------------------\n");

    FILE *fileOut;
    fileOut = fopen (FILE_OUTPUT, "a");
    fprintf (fileOut, "\n");
    for (int j = 0; j <= k; j++) {
        a[0][j] = j;
        fprintf (fileOut, "\t k =%4.0lf", a[0][j]);
    }
    fprintf (fileOut, "\n\n");
    for (int i = 1; i <= n; i++) {
        for(int j = 0; j <= k; j++) {
            set_decimals (str, a[i][j], n_decimal);
            fprintf (fileOut, "\tx%d= %s", i, str);
        }
        fprintf (fileOut, "\n");
    }
    fprintf (fileOut, "\n");
    fclose (fileOut);
}

//  Hàm in ra số chữ số thập phân nhập từ bàn phím
void set_decimals (char *s, double d, int n)
{
    int sz; double d2;
    d2 = (d >= 0) ? d : -d;
    sz = (d >= 0) ? 0 : 1;
    if (d2 < 1) sz++;
    while (d2 >= 1) { d2 /= 10.0; sz++; }
    sz += 1 + n;
    sprintf (s, "%*.*f", sz, n, d);
}