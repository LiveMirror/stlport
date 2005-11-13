//esanfo - not essential to STLport; ok to remove from distribution

#include <windows.h>
#include <stdio.h>

void main () {

	HKEY hkSubKey;
  unsigned char scKeyValue[128] = {0x0,};

	if (RegOpenKey(HKEY_LOCAL_MACHINE, "System\\CurrentControlSet\\Control\\TimeZoneInformation", &hkSubKey) == ERROR_SUCCESS) {

    DWORD dwIndex = 0;
    char scKey[128] = {0x0,};
    DWORD dwKeysize = 128;
    DWORD dwType;
    DWORD dwKeyValueSize = 128;
    long gmt_offset_m;
    long gmt_offset_h;
    long gmt_offset_x;

		if (RegEnumValue( hkSubKey, dwIndex, scKey, &dwKeysize, NULL,
    									&dwType, (unsigned char *)scKeyValue,
                      &dwKeyValueSize) == ERROR_SUCCESS)
    {

			// +0430
			//scKeyValue[3] = 0x00;
      //scKeyValue[2] = 0x00;
      //scKeyValue[1] = 0x01;
      //scKeyValue[0] =	0x0E;

      // -0930
			//scKeyValue[3] = 0xFF;
      //scKeyValue[2] = 0xFF;
      //scKeyValue[1] = 0xFD;
      //scKeyValue[0] =	0xC6;

			gmt_offset_m = (scKeyValue[3] * 0x1000000) +
                     (scKeyValue[2] * 0x10000) +
                     (scKeyValue[1] * 0x100) +
                     (scKeyValue[0] * 0x1);

      gmt_offset_h = gmt_offset_m / 60;
      gmt_offset_x = abs(gmt_offset_m % 60);

			if ( gmt_offset_h >= 0 ) {
	      printf("+%02d%02d", abs(gmt_offset_h), gmt_offset_x);
      } else {
	      printf("-%02d%02d", abs(gmt_offset_h), gmt_offset_x);
      }
    }
    RegCloseKey(hkSubKey);
  }
}
