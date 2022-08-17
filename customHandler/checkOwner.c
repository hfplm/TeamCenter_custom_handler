#include"Header.h"
#define errorCode (EMH_USAGE_error_base + 351)

EPM_decision_t checkOwner(EPM_rule_message_t msg) {

	EPM_decision_t decision = EPM_nogo;

	int count;
	char *object_type, *userName;
	tag_t* attachments, owningUser, userTag;

	EPM_ask_attachments(msg.task, EPM_target_attachment, &count, &attachments);

	for (int i = 0; i < count; i++) {
		WSOM_ask_object_type2(attachments[i], &object_type);

		if (tc_strcmp(object_type, "ItemRevision") == 0) {
			AOM_ask_owner(attachments[i], &owningUser);
			POM_get_user(&userName, &userTag);

			if (owningUser == userTag) {
				decision = EPM_go;
				return decision;
			}
			else {
				EMH_store_error_s1(EMH_severity_error, errorCode, " Object owning user and login user in unmatched ! ");
				return decision;
			}
		}

	}
	if (attachments) MEM_free(attachments);
	return decision;

}