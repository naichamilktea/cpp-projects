#include <stdio.h>
#include <stdbool.h>
#include "watch.h"
int main(){
    int k;
    Watch wtc;
    bool end=false;
    while(!end){
        printf("1.start 2.stop 3.restart \n4.viewsecond 5.viewms 6.viewus 0.exit\n");
        scanf("%d",&k);
        switch (k)
        {
            case 1:{
                wtc.Start();
                break;
            }
            case 2:{
                wtc.Stop();
                break;
            }
            case 3:{
                wtc.Restart();
                break;
            }
            case 4:{
                double sec=wtc.ElapsedSecond();
                printf("the second is %f\n",sec);
                break;
            }
            case 5:{
                double ms=wtc.ElapsedMS();
                printf("the ms is %f\n",ms);
                break;
            }
            case 6:{
                double us=wtc.Elapsed();
                printf("the us is %f\n",us);
                break;
            }
            case 0:{
                end=true;
            }
            default:break;
        }
    }
    return 0;
}