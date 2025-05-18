//Chương trình này sử dụng thư viện assert để kiểm tra điều kiện
#include <stdio.h>
#include <assert.h>
int divide(int a,int b){
  assert(b != 0 && "Không được chia cho 0");
    printf("result: %d",a/b);
}
void main(){
    divide(6,2); //hàm này chạy đúng và không thông báo lỗi
    divide(6,0); //hàm này chạy sai vì chia cho 0, dừng chương trình, in ra thông báo lỗi kèm dòng bị lỗi
}