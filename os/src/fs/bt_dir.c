#include <bitthunder.h>

struct _BT_OPAQUE_HANDLE {
	BT_HANDLE_HEADER h;
};

BT_ERROR BT_ReadDir(BT_HANDLE hDir, BT_DIRENT *pDirent) {
	return hDir->h.pIf->oIfs.pDirIF->pfnReadDir(hDir, pDirent);
}
