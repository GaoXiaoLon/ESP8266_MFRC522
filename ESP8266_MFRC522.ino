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
#define RST_PIN         5           // �������
#define SS_PIN          4

//��ע�û�����
byte nuidPICC[4] = { 0xCC, 0xAF, 0x08, 0x32 };
#define mycard {0xCC, 0xAF, 0x08, 0x32}

MFRC522 mfrc522(SS_PIN, RST_PIN);   // �����µ�RFIDʵ��
MFRC522::MIFARE_Key key;
void setup() {
    Serial.begin(9600); // ���ô��ڲ�����Ϊ9600
    SPI.begin();        // SPI��ʼ
    mfrc522.PCD_Init(); // Init MFRC522 card
    mfrc522.PCD_DumpVersionToSerial();  //  չʾ����汾��
    Serial.println("���Կ�ʼ\n");
}

void loop() {
    // Ѱ���¿�
    if (!mfrc522.PICC_IsNewCardPresent()) {
        //Serial.println("û���ҵ���");
        return;
    }

    // ѡ��һ�ſ�
    if (!mfrc522.PICC_ReadCardSerial()) {
        Serial.println("û�п���ѡ");
        return;
    }

    // ��ʾ��Ƭ����ϸ��Ϣ
    Serial.print(F("��Ƭ UID:"));
    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
    Serial.println();

    Serial.print(F("��Ƭ����: "));
    MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
    Serial.println(mfrc522.PICC_GetTypeName(piccType));

    test();

    // ��������
    if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI
        && piccType != MFRC522::PICC_TYPE_MIFARE_1K
        && piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
        Serial.println(F("�����ʺ�Mifare Classic���Ķ�д"));
        return;
    }

    MFRC522::StatusCode status;
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("�����֤ʧ�ܣ������ǿ�����ʧ��"));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }
    //ֹͣ PICC
    mfrc522.PICC_HaltA();
    //ֹͣ����PCD
    mfrc522.PCD_StopCrypto1();
    return;
}

/*
   ���ֽ�����ת��Ϊ���е�ʮ������ֵ
*/
//�����������ֽڶ���������飬����ӡ����
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