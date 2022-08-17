#include"Header.h"

int folderAction(EPM_action_message_t msg) {

	tag_t rootTask;
	tag_t* attachment;
	tag_t* list;

	int count, refCount;
	int attachmentType[1] = { EPM_target_attachment };


	EPM_ask_root_task(msg.task, &rootTask);
	EPM_ask_attachments(rootTask, EPM_target_attachment, &count, &attachment);


	char* objType;
	FL_sort_criteria_t sortCriteria;

	for (int i = 0; i < count; i++) {

		WSOM_ask_object_type2(attachment[i], &objType);

		if (tc_strcmp(objType, "Folder") == 0) {
			FL_ask_sort_criteria(attachment[i], &sortCriteria);
			FL_ask_references(attachment[i], sortCriteria, &refCount, &list);

			for (int j = 0; j < refCount; j++) {
				EPM_add_attachments(rootTask, 1, &list[j], attachmentType);
			}

		}
	}
	

	if (attachment)MEM_free(attachment);
	return 0;
}