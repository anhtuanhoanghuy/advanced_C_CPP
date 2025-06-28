#include <stdio.h>
#include <setjmp.h>
#include <unistd.h>
#include <stdbool.h>




// -------------------Hãy gán lại giá trị cho các biến bool File_Exist, Network_Connected, Correct_Checksum trong Main() để test-------------------





typedef enum { 
    NO_ERROR, 
    FILE_ERROR, 
    NETWORK_ERROR, 
    CALCULATION_ERROR 
} ErrorCodes ;

jmp_buf env;
int exception = NO_ERROR;
char* message_error;

#define TRY if ((exception = setjmp(env)) == 0)
#define CATCH(ErrorCodes) else if (exception == ErrorCodes)
#define THROW(ErrorCodes, message)  message_error = message;\
                                    longjmp(env,ErrorCodes);
bool File_Exist;
bool Network_Connected;
bool Correct_Checksum;

void readFile() {
    printf("Đang đọc file");
    fflush(stdout);
    for (int i = 0; i <3; i++) {
        sleep(1);
        printf(".");
        fflush(stdout);
    }
    printf("\n");
    if (File_Exist) {
        printf("--> Đọc file thành công.\n");
        fflush(stdout);
        sleep(1);
    } else {
        THROW(FILE_ERROR, "--> Lỗi đọc file: File không tồn tại.\n");
    }
}

void networkOperation() {
    printf("Đang truyền file đến Client");
    fflush(stdout);
    for (int i = 0; i <3; i++) {
        sleep(1);
        printf(".");
        fflush(stdout);
    }
    printf("\n");
    if (Network_Connected) {
        printf("--> Đã truyền dữ liệu tới Client.\n");
        fflush(stdout);
        sleep(1);
    } else {
        THROW(NETWORK_ERROR, "--> Lỗi mạng: Mất kết nối Internet.\n");
    }
}

void calculateData() {
    printf("Đang kiểm tra Checksum");
    fflush(stdout);
    for (int i = 0; i <3; i++) {
        sleep(1);
        printf(".");
        fflush(stdout);
    }
    printf("\n");
    if (Correct_Checksum) {
        printf("--> Dữ liệu truyền đi đầy đủ.\n");
        fflush(stdout);
        sleep(1);
    } else {
        THROW(CALCULATION_ERROR, "--> Lỗi dữ liệu: Dữ liệu truyền đi bị mất mát.\n");
    }
}
int main() {

    File_Exist = true;
    Network_Connected = false;
    Correct_Checksum = true;

    TRY { 
        readFile();
        networkOperation();
        calculateData();
    } 
    CATCH(FILE_ERROR) {
        printf("%s\n", message_error);
    }
    CATCH(NETWORK_ERROR) {
        printf("%s\n", message_error);
    }
    CATCH(CALCULATION_ERROR){
        printf("%s\n", message_error);
    }
    return 0;
}