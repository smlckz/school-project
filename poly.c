/* poly: creation and addition of polynomials using a singly-linked list representation */

#include <stdio.h>
#include <stdlib.h>

struct poly {
    size_t length;
    struct poly_node *list;
};

struct poly_node {
    double value;
    struct poly_node *next;
};

struct poly *
poly_new(size_t length, double *coeffs)
{
    struct poly *poly = malloc(sizeof(*poly));
    struct poly_node **node;
    size_t i;
    poly->length = length;
    node = &poly->list;
    for (i = 0; i < length; i++) {
        *node = malloc(sizeof(**node));
        (*node)->value = *coeffs++;
        node = &(*node)->next;
    }
    *node = NULL;
    return poly;
}

struct poly *
poly_add(struct poly *p1, struct poly *p2)
{
    size_t length = (p1->length > p2->length) 
                                ? p1->length 
                                : p2->length;
    size_t i;
    struct poly_node *n1 = p1->list, 
                     *n2 = p2->list;
    struct poly *sum;
    double *list = calloc(sizeof(double), length), *val = list;
    for (i = 0; i < length; i++) {
        *val++ = (n1 ? n1->value : 0) + (n2 ? n2->value : 0);
        if (n1) n1 = n1->next;
        if (n2) n2 = n2->next;
    }
    sum = poly_new(length, list);
    free(list);
    return sum;
}

void
poly_print(struct poly *poly)
{
    size_t i, n = poly->length;
    struct poly_node *node = poly->list;
    for (i = 0; i < n; i++, node = node->next) {
        printf("%.14g*x^%zu", node->value, i);
        if (node->next != NULL) printf(" + ");
    }
    printf("\n");
}

void
poly_free(struct poly *poly)
{
    struct poly_node *node = poly->list, *tmp;
    while ((tmp = node->next) != NULL) {
        free(node);
        node = tmp;
    }
}

#define ARRSZ(a) ((sizeof(a))/(sizeof((a)[0])))
#define POLY(arr) poly_new(ARRSZ(arr), arr)

void
poly_print_sum(struct poly *poly1, struct poly *poly2, struct poly *sum)
{
    poly_print(poly1); puts("+"); poly_print(poly2); puts("="); poly_print(sum); puts("");
}

void
poly__test(void)
{
    double arr1[] = {1, 2, 3.4, 5},
           arr2[] = {8, 12.34, -1.73},
           arr3[] = {-3.7, 12, 179.458, 22.22, 42};
    struct poly *p1 = POLY(arr1),
                *p2 = POLY(arr2),
                *p3 = POLY(arr3);
    struct poly *p1p1 = poly_add(p1, p1),
                *p1p2 = poly_add(p1, p2),
                *p2p3 = poly_add(p2, p3);
    poly_print_sum(p1, p1, p1p1);
    poly_print_sum(p1, p2, p1p2);
    poly_print_sum(p2, p3, p2p3);
    poly_free(p1), poly_free(p2), poly_free(p3);
    poly_free(p1p1), poly_free(p1p2), poly_free(p2p3);
}

int
main(void)
{
    poly__test();
    return 0;
}

