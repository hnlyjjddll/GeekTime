#include <stdio.h>
void main(void){
  int num=9; /* num是整型变量，设为9 */
  float* pFloat=&num; /* pFloat表示num的内存地址，但是设为浮点数 */
  printf("num的值为：%d\n",num); /* 显示num的整型值 */
  printf("*pFloat的值为：%2.50f\n",*pFloat); /* 显示num的浮点值 %f printf默认打印6位小数*/
  *pFloat=9.0; /* 将num的值改为浮点数 */
  printf("num的值为：%d\n",num); /* 显示num的整型值 */
  printf("num2的值为：%d\n",0x41100000); /* 显示num的整型值 */
  printf("*pFloat的值为：%f\n",*pFloat); /* 显示num的浮点值 */

  int fMax = 0x7f7fffff;
  float* pfMax = &fMax;
  printf("fMax = %10.10f\n",*pfMax);

  int fMin = 0x40133333;
  float* pfMin = &fMin;
  printf("fMin = %10.20f\n",*pfMin);
  return;
}
