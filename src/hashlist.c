#include <stdlib.h>
#include <stdio.h>
#include <esent.h>
#include <windows.h>

#include "config.h"
#include "debug.h"
#include "ese_guard.h"

int main(int argc, char *argv[]) {

	/* Get current temporary path */
	TCHAR temp_path[MAX_PATH];
	DWORD ret_temp = 0;
	ret_temp = GetTempPathA(MAX_PATH, temp_path);
	if(ret_temp>MAX_PATH||!ret_temp){
		error_out("[%d] Can`t GetTempPath...\n", ret_temp);
		return(-100);
	}

	debug_out("Try init Jet engine.\n");

	ese_guard_start();

	JET_INSTANCE jet = JET_instanceNil;
	JET_SESID jet_id = JET_sesidNil;

	/* Setup database pagesize for NTDS.DIT size 0x2000 */
	ese_guard(
		JetSetSystemParameter(&jet, jet_id, JET_paramDatabasePageSize, 0x2000, NULL),
		"Can`t Setup database page size"
	);

	ese_guard(JetCreateInstance(&jet, argv[0]), "Can`t create Jet instance.");

	/* Setup the recovery option is "off" */
	ese_guard(
		JetSetSystemParameter(&jet, jet_id, JET_paramRecovery, 0, "off"),
		"Can`t Setup recovery option to 'off'."
	);

	/* Setup defragmentation level */
	ese_guard(
		JetSetSystemParameter(&jet, jet_id, JET_paramEnableOnlineDefrag, 0, NULL),
		"Can`t Setup defrag option."
	);

	/* Setup the maximum number tmp tables is 7 */
	ese_guard(
		JetSetSystemParameter(&jet, jet_id, JET_paramMaxTemporaryTables, 7, NULL),
		"Can`t Setup recovery option to 'off'."
	);

#if 0
	/* Setup temp path to engine Don`t use for Russian User Name*/
	debug_out("Setup temp path for Jet engine: %s\n", temp_path);
	ese_guard(
		JetSetSystemParameter(&jet, jet_id, JET_paramTempPath, 0, temp_path),
		"Can`t Setup temporery folder to $TEMP."
	);
#endif

	/* Init engine and stat session */
	ese_guard(JetInit(&jet), "Can`t Init Jet instance.");

	debug_out("Init Jet engine successed.\nTry start session...\n");

	ese_guard(JetBeginSession(jet, &jet_id, 0, 0), "Can`t Begin Jet session.");

	debug_out("Session is started.\n");

	/* Attach to a NTDS.dit */
//	ese_guard(JetAttachDatabase(jet_id, "NTDS.dit", 1), "Can`t attach NTDS.dit database.");



	ese_guard_end(0);
	debug_out("Task ended.\n");

	return 0;
}