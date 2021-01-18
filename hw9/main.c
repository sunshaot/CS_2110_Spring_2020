#include "list.h"

#include <stdio.h>

int main(void) {
    printf("Test\n");
    LinkedList* mylist = create_list();
    push_back(mylist, "ab");
    push_back(mylist, "bc");
    push_back(mylist, "cd");
    push_back(mylist, "de");
    merge_nodes(mylist,1);
    printf("%s , %s , %s", mylist->head->data, mylist->head->next->data, mylist->head->next->next->data);


}