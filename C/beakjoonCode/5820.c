#include <stdio.h>
#include <stdlib.h>
#define INF 500000

typedef struct __node {
    struct __node* link;
    int v;
    int c;
} Node;

typedef struct __tree {
    Node* t[200001];
} Tree;

void initialize_tree(Tree* t) {
    for (int i = 0; i < 200001; i++) {
        t->t[i] = NULL;
    }
}

void insert_node_to_tree(Tree* t, int u, int v, int c) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->v = v;
    node->c = c;
    node->link = t->t[u];
    t->t[u] = node;
}

int visit_status[200001];
int length_array[1000001];
int s_array[1000001];
int s_index_array[200001];
int l_index_array[200001];
int value_array[200001];
int K;
int minimum_course = INF;
int num_of_nodes = 0;
int num_of_lengths = 0;

int minimum_value(int a, int b) {
    if (a > b) {
        return b;
    } else {
        return a;
    }
}

int depth_first_search_1(Tree* t, int start_node, int parent_node) {
    value_array[start_node] = 1;
    for (Node* node = t->t[start_node]; node; node = node->link) {
        if (node->v != parent_node && visit_status[node->v] != 1) {
            value_array[start_node] += depth_first_search_1(t, node->v, start_node);
        }
    }
    return value_array[start_node];
}

int find_centroid(Tree* t, int start_node, int parent_node, int root_value) {
    for (Node* node = t->t[start_node]; node; node = node->link) {
        if (node->v != parent_node && visit_status[node->v] != 1 && root_value < value_array[node->v] * 2) {
            return find_centroid(t, node->v, start_node, root_value);
        }
    }
    return start_node;
}

void depth_first_search_2(Tree* t, int start_node, int parent_node, int distance, int length) {
    if (distance > K) {
        return;
    }
    if (distance == K) {
        minimum_course = minimum_value(minimum_course, length);
    }
    if (distance < K) {
        if (length_array[K - distance] != INF) {
            minimum_course = minimum_value(minimum_course, length_array[K - distance] + length);
        }
    }
    l_index_array[num_of_lengths++] = distance;
    s_index_array[num_of_nodes++] = distance;
    s_array[distance] = minimum_value(s_array[distance], length);
    for (Node* node = t->t[start_node]; node; node = node->link) {
        if (node->v != parent_node && visit_status[node->v] != 1) {
            depth_first_search_2(t, node->v, start_node, distance + node->c, length + 1);
        }
    }
}

void divide_and_conquer(Tree* t, int root_node) {
    int centroid_node = find_centroid(t, root_node, -1, depth_first_search_1(t, root_node, -1));
    for (Node* node = t->t[centroid_node]; node; node = node->link) {
        if (visit_status[node->v] != 1) {
            depth_first_search_2(t, node->v, centroid_node, node->c, 1);
            for (int i = 0; i < num_of_lengths; i++) {
                length_array[l_index_array[i]] = minimum_value(length_array[l_index_array[i]], s_array[l_index_array[i]]);
            }
            num_of_lengths = 0;
        }
    }
    for (int i = 0; i < num_of_nodes; i++) {
        length_array[s_index_array[i]] = INF;
        s_array[s_index_array[i]] = INF;
    }
    num_of_nodes = 0;
    visit_status[centroid_node] = 1;
    for (Node* node = t->t[centroid_node]; node; node = node->link) {
        if (visit_status[node->v] != 1) {
            divide_and_conquer(t, node->v);
        }
    }
}

int main() {
    int N;
    Tree t;
    initialize_tree(&t);
    scanf("%d %d", &N, &K);
    int u, v, c;
    for (int i = 1; i < N; i++) {
        scanf("%d %d %d", &u, &v, &c);
        insert_node_to_tree(&t, u, v, c);
        insert_node_to_tree(&t, v, u, c);
    }
    for (int i = 0; i <= K; i++) {
        length_array[i] = INF;
        s_array[i] = INF;
    }
    divide_and_conquer(&t, 0);
    if (minimum_course == INF) {
        printf("%d\n", -1);
    } else {
        printf("%d\n", minimum_course);
    }
    return 0;
}
