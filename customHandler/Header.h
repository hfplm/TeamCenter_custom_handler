#include<stdio.h>
#include<conio.h>
#include<ps/ps.h>
#include<tc/emh.h>
#include<tc/emh.h>
#include<epm/epm.h>
#include<tc/folder.h>
#include<tccore/aom.h>
#include<tccore/grm.h>
#include<ae/dataset.h>
#include<epm/signoff.h>
#include<pom/pom/pom.h>	
#include<tccore/item.h>
#include<tc/tc_startup.h>
#include<tccore/custom.h>
#include<tc/tc_startup.h>
#include<sa/groupmember.h>
#include<ae/datasettype.h>
#include<tccore/aom_prop.h>
#include<tc/tc_arguments.h>
#include<fclasses/tc_string.h>
#include<tccore/workspaceobject.h>

#define DLLAPI __declspec(dllexport)

int ifail;

extern DLLAPI int libhandler_register_callbacks();
extern DLLAPI int login(int* decision, va_list args);
extern DLLAPI int logout(int* decision, va_list args);

int errorHandler(int ifail);

// EPM_decision_t checkOwner(EPM_rule_message_t msg);
// EPM_decision_t checkStatus(EPM_rule_message_t msg);
// EPM_decision_t checkForm(EPM_rule_message_t msg);
// EPM_decision_t checkInProcess(EPM_rule_message_t msg);
// EPM_decision_t checkBOM(EPM_rule_message_t msg);
//EPM_decision_t checkDataset(EPM_rule_message_t msg);


// int attachDataset(EPM_action_message_t msg);
// int attachDatasetAsTarget(EPM_action_message_t msg);
// int folderAction(EPM_action_message_t msg);
// int signoffAction(EPM_action_message_t msg);
int parentOwnerAsSignoff(EPM_action_message_t msg);

