// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       ESP8266_MFRC522.ino
    Created:	2022/3/29 21:29:22
    Author:     GAO\Gao
*/

// Define User Types below here or use a .h file
//


// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//

#include <SPI.h>
#include <MFRC522.h>
#define RST_PIN         5           // 配置针脚
#define SS_PIN          4

//标注用户卡号
byte nuidPICC[4] = { 0xCC, 0xAF, 0x08, 0x32 };
#define mycard {0xCC, 0xAF, 0x08, 0x32}

MFRC522 mfrc522(SS_PIN, RST_PIN);   // 创建新的RFID实例
MFRC522::MIFARE_Key key;
void setup() {
    Serial.begin(9600); // 设置串口波特率为9600
    SPI.begin();        // SPI开始
    mfrc522.PCD_Init(); // Init MFRC522 card
    mfrc522.PCD_DumpVersionToSerial();  //  展示软件版本号
    Serial.println("测试开始\n");
}

void loop() {
    // 寻找新卡
    if (!mfrc522.PICC_IsNewCardPresent()) {
        //Serial.println("没有找到卡");
        return;
    }

    // 选择一张卡
    if (!mfrc522.PICC_ReadCardSerial()) {
        Serial.println("没有卡可选");
        return;
    }

    // 显示卡片的详细信息
    Serial.print(F("卡片 UID:"));
    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
    Serial.println();

    Serial.print(F("卡片类型: "));
    MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
    Serial.println(mfrc522.PICC_GetTypeName(piccType));

    test();

    // 检查兼容性
    if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI
        && piccType != MFRC522::PICC_TYPE_MIFARE_1K
        && piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
        Serial.println(F("仅仅适合Mifare Classic卡的读写"));
        return;
    }

    MFRC522::StatusCode status;
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("身份验证失败？或者是卡链接失败"));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }
    //停止 PICC
    mfrc522.PICC_HaltA();
    //停止加密PCD
    mfrc522.PCD_StopCrypto1();
    return;
}

/*
   将字节数组转储为串行的十六进制值
*/
//将缓冲区的字节读入存入数组，并打印出来
void dump_byte_array(byte* buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
}

void test() {

}

void printDec(byte* buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], DEC);
    }
}

String DecToHex(int num) {
    String string = String(num, HEX);
    return string;
}