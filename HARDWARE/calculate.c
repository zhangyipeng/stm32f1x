#include "calculate.h"
/****************************************************************************
* Function Name :   char2hex
* Description   :   将字符串转化为16进制
* Input         :*s字符串，qq需转换字符串的起始位下标，number需转换字符串的个数
* Output        :
*****************************************************************************/
int char2hex(const char *s,uint8_t qq,uint8_t number){
    int n = 0;
    uint8_t q;
    s=s+qq;
    if( !s )
        return 0;
    for(q=0;q<number;q++){
        n <<= 4;
        if( *s <= '9' )
            n |= ( *s & 0xf );
        else
            n |= ( (*s & 0xf) + 9 );
        s++;
    }
return n;
}
/****************************************************************************
* Function Name :   pow2
* Description   :   2的x幂
* Input         :   幂指数x
* Output        :   y=2^x
*****************************************************************************/
int pow2(int x){
    int y = 1;
    int i = 0;
    for(i = x; i >0; i--){
        y = y*2;
    }
return y;
}

