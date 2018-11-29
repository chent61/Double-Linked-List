#include "assignment3.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void printHBlist(const HBnodePtr L) {
  HBnodePtr hori = L;
  if (!L)
    printf("NULL\n");
  while (hori) {
    SLnodePtr ver = hori->bottom;
    printf("%d: ", hori->key);
    if (ver) {
      printf("%d -> ", ver->key);
      while (ver->next) {
        printf("%d -> ", ver->next->key);
        ver = ver->next;
      }
    }
    hori = hori->next;
    printf("NULL\n");
  }
}

static int cmpfunc(const void *a, const void *b) {
  return (*(int *)a - *(int *)b);
}

HBnodePtr createHBlist(int n, int m) {
  srand(time(NULL));
  int randomNum;
  int *HB = malloc(sizeof(int) * n);
  HBnodePtr HBhead = NULL, HBtail = NULL, HBp = NULL;
  SLnodePtr SLtail = NULL, SLp = NULL;

  if (n == 0)
    return NULL;
  for (int i = 0; i < n; ++i) {
    HB[i] = rand() % (15) + 1;
  }
  qsort(HB, n, sizeof(int), cmpfunc);
  // HBLIST
  for (int i = 0; i < n; i++) {
    HBp = malloc(sizeof(struct HBnode));
    HBp->key = HB[i];
    HBp->next = NULL;

    if (i == 0)
      HBhead = HBp;
    else
      HBtail->next = HBp;
    HBtail = HBp;

    // SLLIST
    if (m == 0)
      randomNum = 0;
    else
      randomNum = rand() % m + 1;

    if (randomNum == 0) {
      HBp->bottom = NULL;
    } else {
      int *SL = malloc(sizeof(int) * randomNum);
      for (int i = 0; i < randomNum; ++i) {
        SL[i] = rand() % 20;
      }
      qsort(SL, randomNum, sizeof(int), cmpfunc);

      for (int j = 0; j < randomNum; j++) {
        SLp = malloc(sizeof(struct SLnode));
        SLp->key = SL[j] + HB[i];
        SLp->next = NULL;
        if (j == 0) {
          HBp->bottom = SLp;
        } else {
          SLtail->next = SLp;
        }
        SLtail = SLp;
      }
      free(SL);
    }
  }
  free(HB);
  return HBhead;
}

void printSLlist(const SLnodePtr L) {
  SLnodePtr curr = L;
  while (curr) {
    printf("%d -> ", curr->key);
    curr = curr->next;
  }
  printf("NULL\n");
}

static SLnodePtr merge(SLnodePtr a, SLnodePtr b) {
  if (a == NULL)
    return b;
  if (b == NULL)
    return a;
  SLnodePtr result;
  if (a->key < b->key) {
    result = a;
    result->next = merge(a->next, b);
  } else {
    result = b;
    result->next = merge(a, b->next);
  }
  return result;
}

SLnodePtr flattenList(const HBnodePtr L) {
  SLnodePtr a = NULL, b = NULL, root1 = NULL, root2 = NULL, p = NULL, q = NULL,
            tmp1 = NULL, tmp2 = NULL;
  HBnodePtr list = L;
  int first = 0;
  while (list) {
    if (first == 0) {
      a = malloc(sizeof(struct SLnode));
      a->key = list->key;
      root1 = a;
      p = list->bottom;
      while (p) {
        tmp1 = malloc(sizeof(struct SLnode));
        tmp1->key = p->key;
        a->next = tmp1;
        a = a->next;
        p = p->next;
      }
      a->next = NULL;
      first = 1;
    } else {
      b = malloc(sizeof(struct SLnode));
      b->key = list->key;
      root2 = b;
      q = list->bottom;
      while (q) {
        tmp2 = malloc(sizeof(struct SLnode));
        tmp2->key = q->key;
        b->next = tmp2;
        b = b->next;
        q = q->next;
      }
      root1 = merge(root1, root2);
    }
    list = list->next;
  }
  return root1;
}

void freeHBlist(HBnodePtr L) {
  if (!L)
    return;
  if (L->next != NULL)
    freeHBlist(L->next);
  freeSLlist(L->bottom);
  free(L);
  return;
}

void freeSLlist(SLnodePtr L) {
  if (!L)
    return;
  freeSLlist(L->next);
  free(L);
}

int main ()
{
	int n = 5, m = 5;
	HBnodePtr L = createHBlist (n,m);
	printf ("HB  list \n");
	printHBlist (L);
	printf ("\n");

	printf ("SL  list \n");
	SLnodePtr P = flattenList (L);
	printSLlist (P);
	printf ("\n");

	freeSLlist (P);
	freeHBlist (L);

	return 0;
}