#include"Header.h"
#define errorCode (EMH_USAGE_error_base + 551)

EPM_decision_t checkDataset(EPM_rule_message_t msg) {
	EPM_decision_t decision = EPM_nogo;

	int count, objCount, index = -1;
	tag_t* attachments, * secObj;
	char* objType, * value, *secObjType;

	EPM_ask_attachments(msg.task, EPM_target_attachment, &count, &attachments);
	for (int i = 0; i < count; i++) {

		WSOM_ask_object_type2(attachments[i], &objType);

		if (tc_strcmp(objType, "ItemRevision") == 0) {

			GRM_list_secondary_objects_only(attachments[i], NULLTAG, &objCount, &secObj);
			for (int j = 0; j < objCount; j++) {
				WSOM_ask_object_type2(secObj[j], &secObjType);

				if ((tc_strcmp(secObjType, "ItemRevision Master") == 0) || (tc_strcmp(secObjType, "ItemRevision") == 0)) continue;

				AOM_UIF_ask_value(secObj[j], "ref_list", &value);

				if (tc_strcmp(value, "") != 0) {
					decision = EPM_go;
					// return decision;
				}
				else {
					EMH_store_error_s1(EMH_severity_error, errorCode, " Dataset has no file attached ! ");
					decision = EPM_nogo;
					return decision;
				}


			}
		}
	}
	if (attachments)MEM_free(attachments);
	return decision;

}