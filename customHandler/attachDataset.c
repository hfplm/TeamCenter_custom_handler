#include"Header.h"

int attachDataset(EPM_action_message_t msg) {

	tag_t rootTask;
	tag_t* attachment;

	int count;
	int numOfArgs;

	char* argName;
	char* argValue;
	char* type = NULL;
	char* name = NULL;
	char* relation = NULL;

	EPM_ask_root_task(msg.task, &rootTask);
	EPM_ask_attachments(rootTask, EPM_target_attachment, &count, &attachment);

	if (count) {
		numOfArgs = TC_number_of_arguments(msg.arguments);

		for (int i = 0; i < numOfArgs; i++){
			ITK_ask_argument_named_value(TC_next_argument(msg.arguments), &argName, &argValue);

			if (tc_strcmp(argName, "type") == 0) {

				type = (char*)MEM_alloc(100);
				tc_strcpy(type, "");
				tc_strcpy(type, argValue);
			}

			if (tc_strcmp(argName, "name") == 0) {

				name = (char*)MEM_alloc(100);
				tc_strcpy(name, "");
				tc_strcpy(name, argValue);
			}

			if (tc_strcmp(argName, "relation") == 0) {

				relation = (char*)MEM_alloc(100);
				tc_strcpy(relation, "");
				tc_strcpy(relation, argValue);
			}
		}
		
	}

	char* objType;
	tag_t datasetType, dataset, realtionType, relationTag;

	for (int i = 0; i < count; i++) {

		WSOM_ask_object_type2(attachment[i], &objType);

		if (tc_strcmp(objType, "ItemRevision") == 0) {

			AE_find_datasettype2(type, &datasetType);
			AE_create_dataset_with_id(datasetType, name, NULL, NULL, NULL, &dataset);
			AE_save_myself(dataset);

			GRM_find_relation_type(relation, &realtionType);
			GRM_create_relation(attachment[i], dataset, realtionType, NULLTAG, &relationTag);
			GRM_save_relation(relationTag);
		}
	}
	if (type)MEM_free(type);
	if (name)MEM_free(name);
	if (relation)MEM_free(relation);

	if (attachment)MEM_free(attachment);
	return 0;
}