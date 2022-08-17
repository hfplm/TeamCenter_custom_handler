#include"Header.h"

extern DLLAPI int libhandler_register_callbacks() {

	CUSTOM_register_exit("libhandler", "USER_init_module", (CUSTOM_EXIT_ftn_t)login);
	CUSTOM_register_exit("libhandler", "USER_exit_module", (CUSTOM_EXIT_ftn_t)logout);

	return 0; 
}

extern DLLAPI int login(int* decision, va_list args) {
	*decision = ALL_CUSTOMIZATIONS;
	printf("\n\n\n*********************************************\n");
	printf("*                                           *\n");
	printf("*\t \t Welcome               *\n");
	printf("*                                           *\n");
	printf("*********************************************\n\n\n");

	// ======================== Rule Handlers ======================== \\

	// EPM_register_rule_handler("C_check_owner", "", (EPM_rule_handler_t)checkOwner);
	// EPM_register_rule_handler("C_check_status", "", (EPM_rule_handler_t)checkStatus);
	// EPM_register_rule_handler("C_check_form", "", (EPM_rule_handler_t)checkForm);
	// EPM_register_rule_handler("C_check_In_Process", "", (EPM_rule_handler_t)checkInProcess);
	// EPM_register_rule_handler("C_check_BOM", "", (EPM_rule_handler_t)checkBOM);
	// EPM_register_rule_handler("C_check_Dataset", "", (EPM_rule_handler_t)checkDataset);

	// ======================== Action Handlers ======================== \\

	// EPM_register_action_handler("C_Attach_Dataset", NULL, (EPM_action_handler_t)attachDataset);
	// EPM_register_action_handler("C_Attach_Dataset", NULL, (EPM_action_handler_t)attachDatasetAsTarget);
	 EPM_register_action_handler("C_Action_Handler", NULL, (EPM_action_handler_t)folderAction);


	return 0;
}

extern DLLAPI int logout(int* decision, va_list args) {
	*decision = ALL_CUSTOMIZATIONS;
	printf("\n\n\n*********************************************\n");
	printf("*                                           *\n");
	printf("*\t \t Thank You               *\n");
	printf("*                                           *\n");
	printf("*********************************************\n\n\n");
	return 0;
}