#include <bitthunder.h>
#include <stdlib.h>
#include <hash/bt_md5.h>


#define BUF_SIZE	1024*1024*4

static sprint_digest(char dbuf[33], BT_u8 digest[16]) {
	BT_u32 i;
	dbuf[0] = '\0';
	for(i = 0; i < 16; i++) {
		bt_sprintf(&dbuf[i*2], "%02x", digest[i]);
	}
}

static int bt_md5sum(BT_HANDLE hShell, int argc, char **argv) {
	
	BT_ERROR Error;
	BT_HANDLE hStdout = BT_ShellGetStdout(hShell);

	if(argc != 2 && argc != 3) {
		bt_fprintf(hStdout, "Usage: %s [path]\n", argv[0]);
		bt_fprintf(hStdout, "Usage: %s [start-address] [length]\n", argv[0]);
		return -1;
	}

	if(argc == 2) {
		BT_HANDLE hFile = BT_Open(argv[1], BT_GetModeFlags("rb"), &Error);
		if(!hFile) {
			bt_printf(hStdout, "Cannot open file: %s\n", argv[1]);
			return -1;
		}

		void *buffer = BT_kMalloc(BUF_SIZE);
		struct bt_md5_context ctx;
		bt_md5_init(&ctx);

		BT_u32 read;
		while((read = BT_Read(hFile, 0, BUF_SIZE, buffer, &Error))) {
			bt_md5_append(&ctx, buffer, read);
		}

		BT_u8 digest[16];
		bt_md5_finish(&ctx, digest);

		char dbuf[33];
		sprint_digest(dbuf, digest);

		bt_fprintf(hStdout, "%s  %s\n", dbuf, argv[1]);

		BT_kFree(buffer);
		
		return 0;
	}

	if(argc == 3) {

	}

	return 0;
}


BT_SHELL_COMMAND_DEF oCommand = {
	.szpName = "md5sum",
	.pfnCommand = bt_md5sum,
};
