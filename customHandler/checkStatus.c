#include"Header.h"
#define errorCode (EMH_USAGE_error_base + 351)

EPM_decision_t checkStatus(EPM_rule_message_t msg) {
	EPM_decision_t decision = EPM_nogo;

	int count;
	tag_t* attachments;
	char* objType, *value;

	EPM_ask_attachments(msg.task, EPM_target_attachment, &count, &attachments);
	for (int i = 0; i < count; i++) {

		WSOM_ask_object_type2(attachments[i], &objType);

		if (tc_strcmp(objType, "ItemRevision") == 0) {
			
			AOM_UIF_ask_value(attachments[i], "release_status_list", &value);

			if (tc_strcmp(value, "Toyota Released") == 0) {
				decision = EPM_go;
				return decision;
			}
			else {
				EMH_store_error_s1(EMH_severity_error, errorCode, " Revision is not having Toyota Released status ! ");
				return decision;
			}

		}
	}
	if (attachments)MEM_free(attachments);
	return decision;
	
}