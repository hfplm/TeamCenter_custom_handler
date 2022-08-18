#include"Header.h"

int signoffAction(EPM_action_message_t msg) {

	tag_t rootTask;
	tag_t* attachment;
	tag_t* signoffAttachment;
	tag_t sub_task;
	tag_t owningUser;
	tag_t owningGroup;

	int count, numOfArgs, signoffCount;
	int attachmentType[1] = { EPM_target_attachment };

	char* argName;
	char* argValue;
	char* obj;
	char* object_type = NULL;
	char* comments;

	EPM_signoff_decision_t decision;

	date_t date;


	ifail = EPM_ask_root_task(msg.task, &rootTask);
	ifail = EPM_ask_attachments(rootTask, EPM_target_attachment, &count, &attachment);

	if (count) {
		numOfArgs = TC_number_of_arguments(msg.arguments);
		for (int i = 0; i < numOfArgs; i++) {
			ifail = ITK_ask_argument_named_value(TC_next_argument(msg.arguments), &argName, &argValue);

			if (tc_strcmp(argName, "object_type") == 0) {
				object_type = (char*)MEM_alloc(100);
				tc_strcpy(object_type, "");
				tc_strcpy(object_type, argValue);
			}
			if (argName)MEM_free(argName);
			if (argValue)MEM_free(argValue);
		}
	}

	for (int i = 0; i < count; i++) {
		ifail = WSOM_ask_object_type2(attachment[i], &obj);
		errorHandler(ifail);
		if (tc_strcmp(obj, object_type) == 0) {
			ifail = EPM_ask_sub_task(msg.task, "select-signoff-team", &sub_task);
			ifail = EPM_ask_attachments(sub_task, EPM_signoff_attachment, &signoffCount, &signoffAttachment);

			for (int j = 0; j < signoffCount; j++) {
				ifail = EPM_ask_signoff_decision(signoffAttachment[j], &decision, &comments, &date);
				if(decision == EPM_approve_decision) {
					//ifail = ITK_set_bypass(true);
					ifail = AOM_ask_owner(signoffAttachment[j], &owningUser);
					ifail = AOM_ask_group(signoffAttachment[j], &owningGroup);
					ifail = AOM_set_ownership(attachment[i], owningUser, owningGroup);
					ifail = AOM_save(attachment[i]);

				}
			}
			if (signoffAttachment)MEM_free(signoffAttachment);
		}

	}

	if (attachment)MEM_free(attachment);
	return 0;
}