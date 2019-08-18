#include<stdio.h>
//#include"de_money.h"

#if defined(HAVE_CONFIG_H)
    #include "config.h"
#endif

#include <stdlib.h>
#include<string.h>
#include <stdio.h>
#include <nfc/nfc.h>
#include <unistd.h>
#include "mifare.c"
#include "de_money.h"


static mifare_param mp;
static nfc_device *pnd;
static nfc_target nt;
static nfc_context *context;
static mifare_cmd mc;
static uint8_t uid[4];
static uint8_t key[6];

const nfc_modulation nmMifare = {
    .nmt = NMT_ISO14443A,
    .nbr = NBR_106,
};


void init(void){
    nfc_init(&context);
    if (context == NULL) {
	printf("libnfc初始化失败！\n");
	exit(EXIT_FAILURE);
    }
    
    pnd = nfc_open(context, NULL); 
    if (pnd == NULL) {
	printf("错误: %s\n", "你确定插好读卡器了？");
	exit(EXIT_FAILURE);
    }
    
    if (nfc_initiator_init(pnd) < 0) {
	nfc_perror(pnd, "nfc_initiator_init");
	exit(EXIT_FAILURE);
    }
 
    printf("NFC 读卡器: %s 已打开\n", nfc_device_get_name(pnd));
}


void
print_hex(const uint8_t *pbtData, const size_t szBytes)
{
  size_t  szPos;

  for (szPos = 0; szPos < szBytes; szPos++) {
    printf("%02x  ", pbtData[szPos]);
  }
  printf("\n");
}


int main(void){
    /*while (1)
    {

    printf("请输入想要的金额：");
    float temp;
    scanf("%f",&temp);
    number_t *data =number_init(temp*100);
    print_hex(data->data,3);
    printf("%x\n",(uint8_t)~(data->data[0]+data->data[1]+data->data[2]));
    }
    */


    init();
    mc=MC_AUTH_A;
    uint8_t key[]={0xff,0xff,0xff,0xff,0xff,0xff};
    memcpy(mp.mpa.abtKey,key,6);
    nfc_initiator_mifare_cmd(pnd,mc,56,&mp);

}