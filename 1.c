#include <stdio.h>
char check_r (char r){
    printf("�� ����� ����� �����४⭮!\n");
    printf("�롥�� ०�� ����:\n");
    scanf("%c", &r);
    return r;
}
void main(){
    char r; //०��
    //int ; 
    printf("����� ����! �� ��� \"�모 � ��஢�!\"\n");
    printf("�ࠢ���...\n");
    printf("�롥�� ०�� ����:\n");
    printf("1 - �� ��⨢ ��������\n2 - �������� ��⨢ ���\n3 - � ��㣮�\n");
    scanf("%c", &r); 
    while (((r=='1')||(r=='2')||(r=='3'))==0){
        check_r(r);
    }
    
    // while ((r!='1' && r!='2' && r!='3')==1) { //� �᫨ 2,5? //�᫨ �� �᫮, � ��横��������!!!
    //     printf("�� ����� ����� �����४⭮!\n");
    //     printf("�롥�� ०�� ����:\n");
    //     scanf("%c ", &r);
    // }
    if (r=='1'){
        printf("1\n");
    }
    if (r=='2'){
        printf("2\n");
    }
    if (r=='3'){
        printf("3\n");
    }
}