#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct node {
    int info;
    node* l, * r, * p;
};

void CreateTree(int a, int n, node** t, node* p = NULL)
{
    if ((*t) == NULL)
    {
        (*t) = new node;
        (*t)->info = a;
        (*t)->l = (*t)->r = NULL;     
        (*t)->p = p;
    }
    if (2 * a <= n) CreateTree(2 * a, n, &(*t)->l, *t);
    if (2 * a + 1 <= n) CreateTree(2 * a + 1, n, &(*t)->r, *t);
    return;
}

void PrintTree(node* t, int u, ofstream &fout)
{
    if (t == NULL) return;
    else
    {
        PrintTree(t->l, ++u, fout);
        fout << t->info << " ";
        u--;
    }
    PrintTree(t->r, ++u, fout);
}

node* Find(int n, node** t) {
    if (*t == NULL) return NULL;
    if ((*t)->info == n) return *t;
    node* tl = Find(n, &(*t)->l);
    if (tl != NULL) return tl;
    return Find(n, &(*t)->r);
}

int main()
{
    ifstream fin;
    ofstream fout;
    fin.open("input.txt");
    fout.open("output.txt");

    int n, q;
    fin >> n >> q;
    node *tree = NULL;
    CreateTree(1, n, &tree);

    for (int i = 0; i < n; i++) {
        int num;
        fin >> num;
        node* v = Find(num, &tree);
        if (v->p != NULL) {
            node* p = v->p;
            if (p->l == v) {
                node* vr = v->r, *vl = v->l, *pr = p->r, *pp = p->p;
                if (pp != NULL) {
                    if (pp->l == p) pp->l = v;
                    else pp->r = v;
                    v->p = pp;
                }
                else {
                    v->p = NULL;
                    tree = v;
                }
                v->l = p; p->p = v;
                v->r = vr; if (vr != NULL) vr->p = v;
                p->l = vl; if (vl != NULL) vl->p = p;
                p->r = pr; if (pr != NULL) pr->p = p;
            }
            else {
                node* vr = v->r, * vl = v->l, * pl = p->l, * pp = p->p;
                if (pp != NULL) {
                    if (pp->l == p) pp->l = v;
                    else pp->r = v;
                    v->p = pp;
                }
                else {
                    v->p = NULL;
                    tree = v;
                }
                v->r = p; p->p = v;
                v->l = vl; if (vl != NULL) vl->p = v;
                p->r = vr; if (vr != NULL) vr->p = p;
                p->l = pl; if (pl != NULL) pl->p = p;
            }
        }
    }

    PrintTree(tree, 0, fout);

    fin.close();
    fout.close();
}

