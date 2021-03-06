#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"


queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* TODO: What if malloc returned NULL? */
    if (!q)
        return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

void q_free(queue_t *q)
{
    if (!q) {
        return;
    }
    list_ele_t *tmp = q->head;
    while (q->head) {
        q->head = q->head->next;
        free(tmp->value);
        free(tmp);
        tmp = q->head;
    }
    free(q);
}

bool q_insert_head(queue_t *q, char *s)
{
    if (!q) {
        return false;
    }
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    if (!newh) {
        return false;
    }
    newh->value = malloc(sizeof(char) * (strlen(s) + 1));

    if (newh->value == NULL) {
        free(newh->value);
        free(newh);
        return false;
    }
    strncpy(newh->value, s, strlen(s) + 1);
    newh->next = q->head;
    if (q->size == 0) {
        q->tail = newh;
    }
    q->head = newh;
    q->size += 1;
    return true;
}


bool q_insert_tail(queue_t *q, char *s)
{
    if (!q) {
        return false;
    }
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    if (!newh) {
        free(newh);
        return false;
    }

    newh->value = malloc(sizeof(char) * (strlen(s) + 1));
    strncpy(newh->value, s, strlen(s) + 1);
    newh->next = NULL;
    if (!q->tail) {
        q->tail = newh;
        q->head = newh;
    } else {
        q->tail->next = newh;
        q->tail = newh;
    }
    q->size++;
    return true;
}

bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (!q || !q->head) {
        return false;
    }
    list_ele_t *tmp = q->head;
    q->head = tmp->next;

    if (sp) {
        strncpy(sp, tmp->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    free(tmp->value);
    free(tmp);
    q->size--;
    return true;
}

int q_size(queue_t *q)
{
    if (!q) {
        return 0;
    }
    return q->size;
}

void q_reverse(queue_t *q)
{
    if (!q) {
        return;
    }
    if (q->size < 2) {
        return;
    }
    list_ele_t *cur = q->head;
    list_ele_t *nxt = cur;
    list_ele_t *prev = NULL;
    q->tail = q->head;

    while (nxt) {
        nxt = cur->next;
        cur->next = prev;
        prev = cur;
        cur = nxt;
    }
    q->head = prev;
}

list_ele_t *merge_sort(list_ele_t *l1, list_ele_t *l2)
{
    list_ele_t *tmp, *q;
    if (strcmp(l1->value, l2->value) < 0) {
        tmp = l1;
        l1 = l1->next;
    } else {
        tmp = l2;
        l2 = l2->next;
    }
    q = tmp;
    while (l1 && l2) {
        if (strcmp(l1->value, l2->value) < 0) {
            tmp->next = l1;
            tmp = tmp->next;
            l1 = l1->next;
        } else {
            tmp->next = l2;
            tmp = tmp->next;
            l2 = l2->next;
        }
    }
    if (l1) {
        tmp->next = l1;
    }
    if (l2) {
        tmp->next = l2;
    }
    return q;
}


list_ele_t *split_list(list_ele_t *head)
{
    if (!head || !head->next) {
        return head;
    }

    list_ele_t *rabt = head->next;
    list_ele_t *turt = head;

    while (rabt && rabt->next) {
        turt = turt->next;
        rabt = rabt->next->next;
    }
    rabt = turt->next;
    turt->next = NULL;

    list_ele_t *l1 = split_list(head);
    list_ele_t *l2 = split_list(rabt);

    return merge_sort(l1, l2);
}




void q_sort(queue_t *q)
{
    if (!q || q->size == 0) {
        return;
    }
    q->head = split_list(q->head);
    while (q->tail->next) {
        q->tail = q->tail->next;
    }
}
