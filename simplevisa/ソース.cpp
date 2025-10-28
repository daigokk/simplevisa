#pragma comment(lib, "./VISA/visa64.lib")
#include <visa.h>
#include <stdio.h>

int main() {
    ViSession defaultRM;
    char buffer[256] = { 0 };

    // 1. オフィスに入る（リソースマネージャ初期化）
    viOpenDefaultRM(&defaultRM);
    for (int i = 0; i < 10; i++) {
        ViSession instr = 0;
		char addr[256];
		sprintf_s(addr, "TCPIP0::172.16.145.%d::12345::SOCKET", 140 + i);
        // 2. ドアを開ける（計測器に接続）
        viOpen(defaultRM, addr, VI_NULL, 10, &instr);
        if (instr == 0) {
            printf("Failed to open instrument at %s\n", addr);
            continue;
		}

        // 3. 質問する（SCPIコマンドを送信　例えば *IDN?, ACQuire:STATE RUN, AUTOSet EXECute）
        viPrintf(instr, "*IDN?\n");

        // 4. 答えを聞く（直前のSCPIコマンドに対する返信を受信）
        viScanf(instr, "%255t", buffer);

        printf("%s: %s", addr, buffer); // 結果表示

        // 5. さよならする（接続を閉じる）
        viClose(instr);
    }
    viClose(defaultRM);

    return 0;
}