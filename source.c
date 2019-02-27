#include <stdio.h>
#include <termios.h>
#include <my_global.h>
#include <openssl/md5.h>
#include <string.h>
#include <mysql.h>

#define SERVIDOR "127.0.0.1"
#define USUARIO "root"
#define SENHA ""
#define BANCO "dbase"

int exibeValidaUsuario(MYSQL *con);
int validaUsuario(MYSQL *con, char *login, char *senha);
void limpaTela() { printf("\e[1;1H\e[2J"); }
char *str2md5(const char *str, int length);

// SIMULA O GETCH() DO CONIO.H
static struct termios old, new;
void initTermios(int echo)
{
    tcgetattr(0, &old);
    new = old;
    new.c_lflag &= ~ICANON;
    new.c_lflag &= echo ? ECHO : ~ECHO;
    tcsetattr(0, TCSANOW, &new);
}
void resetTermios(void) { tcsetattr(0, TCSANOW, &old); }
char getch_(int echo)
{
    char ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}
char getch(void){ return getch_(0); }
char getche(void) { return getch_(1); }
// FINAL - SIMULA O GETCH() DO CONIO.H

int main(int argc, char **argv)
{
    limpaTela();

    MYSQL *con = mysql_init(NULL);

    if (mysql_real_connect(con, SERVIDOR, USUARIO, SENHA, BANCO, 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }

    printf(" *******************************************\n");
    printf("*                                           *\n");
    printf("*   SISTEMA DE AUTENTICACAO DO MOTORISTA:   *\n");
    printf("*                                           *\n");
    printf(" *******************************************");
    printf("\n\n");

    exibeValidaUsuario(con);

    mysql_close(con);
    exit(0);
}

int validaUsuario(MYSQL *con, char *login, char *senha) {

    limpaTela();

    char *senhaEncodada = str2md5(senha, strlen(senha)), sql[256];
    snprintf(sql, sizeof sql, "%s%s%s%s%s", "SELECT * FROM usuario WHERE email = '", login, "' AND senha = '", senhaEncodada, "'");

    mysql_query(con, sql);
    MYSQL_RES *confres = mysql_store_result(con);
    int totalrows = mysql_num_rows(confres);

    if (totalrows > 0) {

        printf(" ************************************\n");
        printf("*                                    *\n");
        printf("*   SUCESSO, VOCE LOGOU NO SISTEMA   *\n");
        printf("*                                    *\n");
        printf(" ************************************");
        printf("\n\n");

    } else {
        printf(" **************************************************\n");
        printf("*                                                  *\n");
        printf("*   OCORREU UM ERRO, SUA AUTENTICACAO É INVALIDA   *\n");
        printf("*                                                  *\n");
        printf(" **************************************************");
        printf("\n\n");

        exibeValidaUsuario(con);
    }

    return 0;
}

int exibeValidaUsuario(MYSQL *con) {

    char senha[25], login[25], a;
    int Continue = 1, c = 0;

    printf("\tInsira seu e-mail: ");
    gets(login);
    printf("\tInsira sua senha: ");

    while (Continue) {
        a = getch();
        if (a == 13 || a == 10) {
            Continue = 0;
            senha[c] = 0;
        } else {
            senha[c] = a;
            printf("*");
            c++;
        }
    };

    validaUsuario(con, login, senha);

    return 0;
}

char *str2md5(const char *str, int length) {
    int n;
    MD5_CTX c;
    unsigned char digest[16];
    char *out = (char*)malloc(33);

    MD5_Init(&c);

    while (length > 0) {
        if (length > 512) {
            MD5_Update(&c, str, 512);
        } else {
            MD5_Update(&c, str, length);
        }
        length -= 512;
        str += 512;
    }

    MD5_Final(digest, &c);

    for (n = 0; n < 16; ++n) {
        snprintf(&(out[n*2]), 16*2, "%02x", (unsigned int)digest[n]);
    }

    return out;
}