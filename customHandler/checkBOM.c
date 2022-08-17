#include"Header.h"
#define errorCode (EMH_USAGE_error_base + 551)

EPM_decision_t checkBOM(EPM_rule_message_t msg) {
	EPM_decision_t decision = EPM_nogo;

	int count, revCount, index = -1;
	tag_t* attachments, * rev_list, item_tag;
	char* objType, * value;

	EPM_ask_attachments(msg.task, EPM_target_attachment, &count, &attachments);
	for (int i = 0; i < count; i++) {

		WSOM_ask_object_type2(attachments[i], &objType);

		if (tc_strcmp(objType, "ItemRevision") == 0) {

			ITEM_ask_item_of_rev(attachments[i], &item_tag);

			ITEM_list_all_revs(item_tag, &revCount, &rev_list);

			for (int j = 0; j < revCount; j++) {

				if (rev_list[j] == attachments[i]) {

					index = j;
					break;

				}
			}

			if (index != -1) {
				if (index == 0) {
					AOM_UIF_ask_value(rev_list[i], "structure_revisions", &value);

					if (tc_strcmp(value, "") != 0) {

						decision = EPM_go;
						// return decision;
					}
					else {
						EMH_store_error_s1(EMH_severity_error, errorCode, " BOM Line is not attached ! ");
						decision = EPM_nogo;
						return decision;
					}
				}
				else {
					for (int i = 0; i < index; i++)
					{
						AOM_UIF_ask_value(rev_list[i], "structure_revisions", &value);

						if (tc_strcmp(value, "") != 0) {

							decision = EPM_go;
							// return decision;
						}
						else {
							EMH_store_error_s1(EMH_severity_error, errorCode, " BOM Line is not attached ! ");
							decision = EPM_nogo;
							return decision;
						}

					}


				}
			}
			else {
				decision = EPM_nogo;
				return decision;
			}
		}
	}
	if (attachments)MEM_free(attachments);
	return decision;

}