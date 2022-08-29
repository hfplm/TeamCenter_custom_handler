#include"Header.h"

int parentOwnerAsSignoff(EPM_action_message_t msg) {
	int count;
	tag_t* attachment;
	char* objType;
	ifail = EPM_ask_attachments(msg.task, EPM_target_attachment, &count, &attachment); errorHandler(ifail);
	for(int i = 0; i < count; i++) {
		ifail  = 
		ifail = PS_where_used_all(); errorHandler(ifail);
	}
	return 0;
}