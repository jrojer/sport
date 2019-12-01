
def distribution(a):
    res = []
    if len(a) == 0:
        return res
    a = sorted(a)
    v = a[0]
    c = 1
    for i in range(1,len(a)):
        if a[i] == v:
            c += 1
        else:
            res.append((v,c))
            v = a[i]
            c = 1
    if c > 0:
        res.append((v, c))
    return res


class Node:
    def __init__(self, value, weight, left, right, visited, edge):
        self.left = left
        self.right = right
        self.value = value
        self.weight = weight
        self.visited = visited
        self.edge = edge
    def __repr__(self):
        return '{}:{}'.format(self.value,self.weight)


def build_tree(distr):
    nodes = [Node(v,w,None,None,None,None) for v,w in distr]
    while len(nodes) > 1:
        nodes.sort(key = lambda x: -x.weight)
        n1 = nodes.pop()
        n2 = nodes.pop()
        n1.edge = 0
        n2.edge = 1
        nodes.append(Node(None, n1.weight + n2.weight, n1, n2, False, None))
    return nodes[0] #root


def build_code_table(tree_root):
    code_table = []
    stack = [tree_root]
    path = []
    while stack:
        node = stack[-1]
        if node.visited:
            stack.pop()
            if node.edge is not None:
                path.pop()
        else:
            node.visited = True
            if node.edge is not None:
                path.append(node.edge)
            if node.left and node.right:
                stack.append(node.left)
                stack.append(node.right)
            else: #leaf
                code_table.append((node.value,path[:]))
    return code_table


def test():
    assert distribution([1,1,3,4,3,0,4,4]) == [(0,1),(1,2),(3,2),(4,3)]
    build_code_table(build_tree(distribution([2,2,2,2,4,4,5])))

    s = 'aabbdccabaaedecdbaeadbaaabdcacaadaeacbe'
    build_code_table(build_tree(distribution([x for x in s])))




test()
