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

bool q_insert_head(queue_t *q, char *s) {}

bool q_insert_tail(queue_t *q, char *s) {}

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
    list_ele_t *prev = NULL;
    list_ele_t *next = NULL;
    q->tail = q->head;
    while (next) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    q->head = cur;
}

void q_sort(queue_t *q) {}
