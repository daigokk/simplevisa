#pragma comment(lib, "./VISA/visa64.lib")
#include <visa.h>
#include <stdio.h>

int main() {
    ViSession defaultRM;
    char buffer[256] = { 0 };

    // 1. �I�t�B�X�ɓ���i���\�[�X�}�l�[�W���������j
    viOpenDefaultRM(&defaultRM);
	int numInstruments = 0;
    for (int i = 0; i < 10; i++) {
        ViSession instr = 0;
		char addr[256];
		sprintf_s(addr, "TCPIP0::172.16.145.%d::55555::SOCKET", 140 + i);
        // 2. �h�A���J����i�v����ɐڑ��j
        viOpen(defaultRM, addr, VI_NULL, 10, &instr);
        if (instr == 0) {
            printf("%s: Failed to open instrument.\n", addr);
            continue;
		}
        numInstruments++;
        // 3. ���₷��iSCPI�R�}���h�𑗐M�@�Ⴆ�� *IDN?, ACQuire:STATE RUN, AUTOSet EXECute�j
        viPrintf(instr, "*IDN?\n");

        // 4. �����𕷂��i���O��SCPI�R�}���h�ɑ΂���ԐM����M�j
        viScanf(instr, "%255t", buffer);

        printf("%s: %s", addr, buffer); // ���ʕ\��

        // 5. ����Ȃ炷��i�ڑ������j
        viClose(instr);
    }
	printf("Number of instruments found: %d\n", numInstruments);
    viClose(defaultRM);

    return 0;
}