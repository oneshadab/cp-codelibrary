#include <bits/stdtr1c++.h>

#define MAX 100010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;
using namespace tr1;

char ch, str[MAX], str2[MAX];

int main(){
    FILE *test1;
    test1 = fopen("test1.txt", "r");
    FILE *test2;
    test2 = fopen("test2.txt", "r");

    int counter = 0;
    for (int i = 1; ;i++){
        fscanf(test1, "%[^\n]", str);
        fscanf(test1, "%c", &ch);
        fscanf(test2, "%[^\n]", str2);
        fscanf(test2, "%c", &ch);
        if (feof(test1) || feof(test2)){
            if (!counter && feof(test1) && feof(test2)) puts("Accepted");
            else{
                puts("Wrong Answer");
                printf("%d Mistakes\n", counter);
            }
            break;
        }

        if (strcmp(str, str2) != 0){
            counter++;
            printf("Line %d\n", i);
        }
    }

    fflush(test1);
    fflush(test2);
    return 0;
}
