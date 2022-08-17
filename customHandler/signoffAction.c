#include"Header.h"

int folderAction(EPM_action_message_t msg) {

	tag_t rootTask;
	tag_t* attachment;
	tag_t* list;

	int count, numOfArgs;
	int attachmentType[1] = { EPM_target_attachment };

	char* argName;
	char* argValue;


	EPM_ask_root_task(msg.task, &rootTask);
	EPM_ask_attachments(rootTask, EPM_target_attachment, &count, &attachment);

	if (count) {
		numOfArgs = TC_number_of_arguments(msg.arguments);
		for (int i = 0; i < numOfArgs; i++) {
			ITK_ask_argument_named_value(TC_next_argument(msg.arguments), &argName, &argValue);

			if(tc_strcmp())
		}
	}

	if (attachment)MEM_free(attachment);
	return 0;
}