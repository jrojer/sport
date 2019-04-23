from random import randint, shuffle, seed
import numpy as np

seed(5)

def generate_random_tree(num_vertices):
    vertices = list(range(num_vertices))
    shuffle(vertices)

    def next_random_vertex():
        return None if len(vertices) == 0 else vertices.pop()

    root = next_random_vertex()
    fifo = [root]
    inc_list = [[] for i in range(num_vertices)]

    while fifo and vertices:
        v = fifo.pop(0)
        num_children = randint(1, len(vertices))
        for i in range(num_children):
            child = next_random_vertex()
            inc_list[v].append(child)
            if child:
                fifo.append(child)

    return root, inc_list


def solve(root, inc_list):
    inc_list = [sorted(l) for l in inc_list]
    res = []
    def dfs(root):
        stack = [(root,0)]
        while stack:
            v, i = stack.pop()
            if i == 0:
                res.append(v)
            if i < len(inc_list[v]):
                stack.append((v,i+1))
                stack.append((inc_list[v][i],0))
    dfs(root)
    return res


def generate_linked_list(num_vertices):
    root = 0
    inc_list = [[i] for i in range(1,num_vertices)]
    inc_list.append([])
    return root, inc_list


def generate():

    def make_test(root, inc_list, num_vertices):
        pairs = ['{} {}'.format(i,j) for i in range(num_vertices) for j in inc_list[i]]
        shuffle(pairs)
        test = '\n'.join([str(num_vertices),str(root),*pairs])
        clue = ' '.join(map(str,solve(root, inc_list)))
        return test, clue

    tests = []

    num_vertices = 5
    root, inc_list = generate_random_tree(num_vertices)
    tests.append(make_test(root,inc_list,num_vertices))

    num_vertices = 10
    root, inc_list = generate_linked_list(num_vertices)
    tests.append(make_test(root,inc_list,num_vertices))

    return tests


for t,c in generate():
    print(t)
    print()
    print(c)
    print()


