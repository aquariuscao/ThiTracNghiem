#include <stdio.h>
struct nhanvien{
    int ID;
    char hoten[100];
    int solg [100];
    int cost [100];
    };
int main (){
    struct nhanvien TTNV[30];
    int i,n,m,j;
    printf ("Moi ban nhap so luong nhan vien: ");
    scanf ("%d",&n);
    // nhap du lieu
    for (i=0; i<n; i++){
        printf ("Nhap thong tin nhan vien thu %d", i+1);
        printf ("\nID: "); scanf ("%d",&TTNV[i].ID);
        fflush (stdin);
        printf ("Ho va ten: "); scanf ("%c", &TTNV[i].hoten);
        fflush (stdin);
        printf ("Vui long nhap so luong san pham: "); scanf ("%d", &m);
            for ( j = 0; j < m; j++)
            {
                printf ("San pham: "); scanf ("%d", &TTNV[i].solg[j]);
                printf ("Gia tien: "); scanf ("%d", &TTNV[i].cost[j]);
            }
        
    }
    // in
    for (i=0; i<n; i++){
        printf ("\nThong tin nhan vien thu %d la: ", i+1);
        printf ("\nID: %d\n", TTNV[i].ID);
        printf ("Ho va ten: %s \n", TTNV[i].hoten);
        for (j = 0; j < m; j++) {
            printf ("So luong: "); printf ("%d ",TTNV[i].solg[j]);
            printf ("Gia tien: "); printf ("%d ",TTNV[i].cost[j]);
            }
   
    return 0;
    }
}
