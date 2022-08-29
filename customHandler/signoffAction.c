#include"Header.h"

int signoffAction(EPM_action_message_t msg) {

	tag_t rootTask;
	tag_t* attachment;
	tag_t* signoffAttachment;
	tag_t sub_task;
	tag_t user_tag;
	tag_t group_tag;
	tag_t member;


	int count, numOfArgs, signoffCount;
	char* argName;
	char* argValue;
	char* obj;
	char* object_type = NULL;
	char* comments;

	EPM_signoff_decision_t decision;

	SIGNOFF_TYPE_t member_type;


	date_t date;


	ifail = EPM_ask_root_task(msg.task, &rootTask);
	errorHandler(ifail);

	ifail = EPM_ask_attachments(rootTask, EPM_target_attachment, &count, &attachment);
	errorHandler(ifail);


	if (count) {
		numOfArgs = TC_number_of_arguments(msg.arguments);
		for (int i = 0; i < numOfArgs; i++) {
			ifail = ITK_ask_argument_named_value(TC_next_argument(msg.arguments), &argName, &argValue);
			errorHandler(ifail);


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
			errorHandler(ifail);

			ifail = EPM_ask_attachments(sub_task, EPM_signoff_attachment, &signoffCount, &signoffAttachment);
			errorHandler(ifail);

			//for (int j = 0; j < signoffCount; j++) {
			//	ifail = EPM_ask_signoff_decision(signoffAttachment[j], &decision, &comments, &date);
			//	errorHandler(ifail);

			//	if(decision == EPM_approve_decision) {

			//		ifail = AOM_ask_owner(signoffAttachment[j], &owningUser);
			//		errorHandler(ifail);

			//		ifail = AOM_ask_group(signoffAttachment[j], &owningGroup);
			//		errorHandler(ifail);

			//		ifail = ITK_set_bypass(TRUE);
			//		errorHandler(ifail);

			//		ifail = AOM_set_ownership(attachment[i], owningUser, owningGroup);
			//		errorHandler(ifail);

			//		//ifail = AOM_save(attachment[i]);
			//		//errorHandler(ifail);

			//	}
			//}

			for (int j = 0; j < signoffCount; j++) {	

				ifail = EPM_ask_signoff_member(signoffAttachment[j], &member, &member_type);
				errorHandler(ifail);

				ifail = SA_ask_groupmember_user(member, &user_tag);
				errorHandler(ifail);

				ifail = SA_ask_groupmember_group(member, &group_tag);
				errorHandler(ifail);

				ifail = EPM_ask_signoff_decision(signoffAttachment[j], &decision, &comments, &date);
				errorHandler(ifail);


				if(decision == EPM_approve_decision) {

					ifail = ITK_set_bypass(true);
					errorHandler(ifail);

					ifail = AOM_set_ownership(attachment[i], user_tag, group_tag);
					errorHandler(ifail);

					//ifail = AOM_save(attachment[i]);
					//errorHandler(ifail);

				}

			}
			if (signoffAttachment)MEM_free(signoffAttachment);
		}

	}

	if (attachment)MEM_free(attachment);
	return 0;
}