from random import randint


def get_k_max(arr, k):
    arr = sorted(arr)
    return arr[-k]


def testgen():
    n = 20
    values = list(set(randint(-100, 100) for x in range(n)))
    input_str = str(2*len(values)) + '\n'
    input_str += '\n'.join('+1 {}'.format(v) for v in values)
    input_str += '\n'
    input_str += '\n'.join('0 {}'.format(k) for k in range(1, len(values)+1))
    sorted_values = sorted(values)
    answer = '\n'.join(str(sorted_values[-k])
                       for k in range(1, len(sorted_values)+1))
    test_text = '\n'.join(
        ['input begin', input_str, 'input end', 'output begin', answer, 'output end'])
    with open('avl_gen_test.txt', 'w') as fd:
        print(test_text, file=fd)


testgen()
